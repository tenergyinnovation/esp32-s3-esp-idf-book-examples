/*
 * บทที่ 16 Capstone: Smart Greenhouse Node
 * รวมทุกบท: GPIO + ADC + I2C (SHT31/OLED) + PWM + FreeRTOS + Wi-Fi + MQTT + NVS + Watchdog + OTA rollback
 *
 * โครงสร้าง task (ดูรูปในหนังสือ):
 *   sensor_task  (core 1, ทุก 2 s)  -> อ่าน SHT31 หรือ potentiometer จำลอง -> q_samples
 *   control_task (core 1)            -> รับค่า ตัดสินใจพัดลม (hysteresis + fail-safe) -> PWM, OLED
 *   cloud_task   (core 0)            -> ส่ง JSON ขึ้น MQTT ทุก report_s วินาที, รับคำสั่ง cmd
 * คำสั่ง MQTT (หัวข้อ tenergy/gh/<id>/cmd):  fan=auto | fan=on | fan=off | setpoint=<C> | reboot
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/i2c_master.h"
#include "driver/ledc.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_task_wdt.h"
#include "esp_ota_ops.h"
#include "esp_app_desc.h"
#include "esp_mac.h"
#include "esp_timer.h"
#include "esp_system.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "wifi_connect.h"
#include "oled.h"
#include "sht31.h"

static const char *TAG = "node";

typedef enum { FAN_AUTO, FAN_ON, FAN_OFF } fan_mode_t;
typedef struct { float setpoint; uint16_t report_s; fan_mode_t mode; } node_cfg_t;
typedef struct { float t, rh; bool valid; int64_t ts; } sample_t;

static node_cfg_t s_cfg = { .setpoint = 32.0f, .report_s = 30, .mode = FAN_AUTO };
static QueueHandle_t s_q;
static SemaphoreHandle_t s_lock;           /* ป้องกัน s_latest และ s_cfg ที่หลาย task ใช้ร่วมกัน */
static sample_t s_latest;
static int s_fan_pct;
static char s_id[16];
static esp_mqtt_client_handle_t s_mqtt;
static i2c_master_bus_handle_t s_bus;
static adc_oneshot_unit_handle_t s_adc;
static bool s_have_sht;

/* ---------- NVS ---------- */
static void cfg_load(void)
{
    nvs_handle_t h; size_t len = sizeof(s_cfg); node_cfg_t tmp;
    if (nvs_open("node", NVS_READONLY, &h) == ESP_OK) {
        if (nvs_get_blob(h, "cfg", &tmp, &len) == ESP_OK && len == sizeof(tmp)) s_cfg = tmp;
        nvs_close(h);
    }
}
static void cfg_save(void)
{
    nvs_handle_t h;
    if (nvs_open("node", NVS_READWRITE, &h) == ESP_OK) { nvs_set_blob(h, "cfg", &s_cfg, sizeof(s_cfg)); nvs_commit(h); nvs_close(h); }
}

/* ---------- hardware ---------- */
static void hw_init(void)
{
    i2c_master_bus_config_t b = { .i2c_port = I2C_NUM_0, .sda_io_num = 8, .scl_io_num = 9, .clk_source = I2C_CLK_SRC_DEFAULT,
                                  .glitch_ignore_cnt = 7, .flags.enable_internal_pullup = true };
    ESP_ERROR_CHECK(i2c_new_master_bus(&b, &s_bus));
    if (oled_init(s_bus, 0x3C) != ESP_OK) ESP_LOGW(TAG, "ไม่พบจอ OLED");
    s_have_sht = i2c_master_probe(s_bus, 0x44, 50) == ESP_OK && sht31_init(s_bus, 0x44) == ESP_OK;
    adc_oneshot_unit_init_cfg_t u = { .unit_id = ADC_UNIT_1 };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&u, &s_adc));
    adc_oneshot_chan_cfg_t c = { .atten = ADC_ATTEN_DB_12, .bitwidth = ADC_BITWIDTH_DEFAULT };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(s_adc, ADC_CHANNEL_0, &c));
    ledc_timer_config_t t = { .speed_mode = LEDC_LOW_SPEED_MODE, .timer_num = LEDC_TIMER_0, .duty_resolution = LEDC_TIMER_10_BIT,
                              .freq_hz = 25000, .clk_cfg = LEDC_AUTO_CLK };
    ESP_ERROR_CHECK(ledc_timer_config(&t));
    ledc_channel_config_t ch = { .speed_mode = LEDC_LOW_SPEED_MODE, .channel = LEDC_CHANNEL_0, .timer_sel = LEDC_TIMER_0, .gpio_num = 6 };
    ESP_ERROR_CHECK(ledc_channel_config(&ch));
    ESP_LOGI(TAG, "เซนเซอร์: %s", s_have_sht ? "SHT31" : "potentiometer จำลอง (GPIO1)");
}

/* ---------- tasks ---------- */
static void sensor_task(void *arg)
{
    ESP_ERROR_CHECK(esp_task_wdt_add(NULL));
    while (1) {
        sample_t s = { .ts = esp_timer_get_time() / 1000, .rh = -1 };
        if (s_have_sht) s.valid = sht31_read(&s.t, &s.rh) == ESP_OK;
        else { int raw = 0; s.valid = adc_oneshot_read(s_adc, ADC_CHANNEL_0, &raw) == ESP_OK && raw > 120; s.t = 20 + raw * 25.0f / 4095; }
        xQueueOverwrite(s_q, &s);                   /* คิวขนาด 1: เก็บเฉพาะค่าล่าสุด */
        esp_task_wdt_reset();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

static void control_task(void *arg)
{
    ESP_ERROR_CHECK(esp_task_wdt_add(NULL));
    sample_t s; int fails = 0; bool hot = false;
    while (1) {
        if (xQueueReceive(s_q, &s, pdMS_TO_TICKS(5000)) != pdTRUE) s.valid = false;
        fails = s.valid ? 0 : fails + 1;
        xSemaphoreTake(s_lock, portMAX_DELAY);
        node_cfg_t cfg = s_cfg;
        if (s.valid) s_latest = s;
        xSemaphoreGive(s_lock);

        int pct;
        if (cfg.mode == FAN_ON) pct = 100;
        else if (cfg.mode == FAN_OFF) pct = 0;
        else if (fails >= 3) pct = 100;                                   /* fail-safe */
        else {
            hot = hot ? s_latest.t > cfg.setpoint - 2 : s_latest.t >= cfg.setpoint;
            pct = !hot ? 0 : (int)(40 + (s_latest.t - cfg.setpoint + 2) * 15);
            if (pct > 100) pct = 100;
        }
        s_fan_pct = pct;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, pct * 1023 / 100);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

        char l[24];
        oled_clear();
        oled_text(0, 0, s_id);
        oled_text(84, 0, wifi_is_connected() ? "WiFi" : "----");
        snprintf(l, sizeof l, fails >= 3 ? "ERR" : "%.1fC", s_latest.t); oled_text_big(0, 2, l);
        snprintf(l, sizeof l, "SP %.1f %s", cfg.setpoint, cfg.mode == FAN_AUTO ? "AUTO" : "MAN"); oled_text(0, 5, l);
        snprintf(l, sizeof l, "FAN %3d%%", pct); oled_text(0, 7, l);
        oled_rect(60, 56, pct * 68 / 100, 8, true);
        oled_flush();
        esp_task_wdt_reset();
    }
}

static void on_mqtt(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    esp_mqtt_event_handle_t e = data;
    char topic[64];
    if (id == MQTT_EVENT_CONNECTED) {
        snprintf(topic, sizeof topic, "tenergy/gh/%s/cmd", s_id);
        esp_mqtt_client_subscribe(e->client, topic, 1);
        snprintf(topic, sizeof topic, "tenergy/gh/%s/status", s_id);
        esp_mqtt_client_publish(e->client, topic, "online", 0, 1, 1);
        ESP_LOGI(TAG, "MQTT พร้อม รับคำสั่งที่ tenergy/gh/%s/cmd", s_id);
    } else if (id == MQTT_EVENT_DATA) {
        char cmd[32] = { 0 };
        memcpy(cmd, e->data, e->data_len < 31 ? e->data_len : 31);
        ESP_LOGI(TAG, "คำสั่ง: %s", cmd);
        xSemaphoreTake(s_lock, portMAX_DELAY);
        if (!strcmp(cmd, "fan=auto")) s_cfg.mode = FAN_AUTO;
        else if (!strcmp(cmd, "fan=on")) s_cfg.mode = FAN_ON;
        else if (!strcmp(cmd, "fan=off")) s_cfg.mode = FAN_OFF;
        else if (!strncmp(cmd, "setpoint=", 9)) { float v = atof(cmd + 9); if (v >= 20 && v <= 45) s_cfg.setpoint = v; }
        xSemaphoreGive(s_lock);
        if (!strcmp(cmd, "reboot")) esp_restart();
        cfg_save();
    }
}

static void cloud_task(void *arg)
{
    if (wifi_connect(pdMS_TO_TICKS(30000)) != ESP_OK) ESP_LOGW(TAG, "ยังไม่มี Wi-Fi ทำงานแบบออฟไลน์ต่อ (จะต่อเองเมื่อสัญญาณกลับ)");
    char topic[64];
    snprintf(topic, sizeof topic, "tenergy/gh/%s/status", s_id);
    esp_mqtt_client_config_t mc = { .broker.address.uri = CONFIG_NODE_MQTT_URI, .session.keepalive = 30,
                                    .session.last_will = { .topic = topic, .msg = "offline", .qos = 1, .retain = 1 } };
    s_mqtt = esp_mqtt_client_init(&mc);
    esp_mqtt_client_register_event(s_mqtt, ESP_EVENT_ANY_ID, on_mqtt, NULL);
    esp_mqtt_client_start(s_mqtt);
    snprintf(topic, sizeof topic, "tenergy/gh/%s/telemetry", s_id);
    while (1) {
        xSemaphoreTake(s_lock, portMAX_DELAY);
        sample_t s = s_latest; node_cfg_t cfg = s_cfg;
        xSemaphoreGive(s_lock);
        char json[200];
        int n = snprintf(json, sizeof json, "{\"t\":%.1f,\"rh\":%.1f,\"fan\":%d,\"sp\":%.1f,\"mode\":%d,\"heap\":%u,\"up\":%lld,\"fw\":\"%s\"}",
                         s.t, s.rh, s_fan_pct, cfg.setpoint, cfg.mode, (unsigned)esp_get_free_heap_size(),
                         esp_timer_get_time() / 1000000, esp_app_get_description()->version);
        if (wifi_is_connected()) esp_mqtt_client_publish(s_mqtt, topic, json, n, 0, 0);
        ESP_LOGI(TAG, "%s", json);
        vTaskDelay(pdMS_TO_TICKS(cfg.report_s * 1000));
    }
}

void app_main(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) { nvs_flash_erase(); nvs_flash_init(); }
    uint8_t mac[6]; esp_read_mac(mac, ESP_MAC_WIFI_STA);
    snprintf(s_id, sizeof s_id, "GH-%02X%02X%02X", mac[3], mac[4], mac[5]);
    ESP_LOGI(TAG, "%s firmware %s", s_id, esp_app_get_description()->version);
    cfg_load();
    s_lock = xSemaphoreCreateMutex();
    s_q = xQueueCreate(1, sizeof(sample_t));
    hw_init();

    xTaskCreatePinnedToCore(sensor_task, "sensor", 4096, NULL, 6, NULL, 1);
    xTaskCreatePinnedToCore(control_task, "control", 4096, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(cloud_task, "cloud", 6144, NULL, 4, NULL, 0);

    /* OTA rollback: ถ้า firmware นี้เพิ่งอัปเดต ให้รอ 20 วินาทีแล้วตรวจว่าระบบหลักทำงาน จึงยืนยัน */
    esp_ota_img_states_t st;
    if (esp_ota_get_state_partition(esp_ota_get_running_partition(), &st) == ESP_OK && st == ESP_OTA_IMG_PENDING_VERIFY) {
        vTaskDelay(pdMS_TO_TICKS(20000));
        if (s_latest.ts > 0) { esp_ota_mark_app_valid_cancel_rollback(); ESP_LOGI(TAG, "ยืนยัน firmware ใหม่แล้ว"); }
        else esp_ota_mark_app_invalid_rollback_and_reboot();
    }
}
