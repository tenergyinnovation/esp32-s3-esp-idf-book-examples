/*
 * บทที่ 9 ตัวอย่าง 7: สถานีวัดโรงเรือน
 * - อ่าน SHT31 (ถ้าไม่พบ ใช้ potentiometer ที่ GPIO1 จำลองอุณหภูมิ 20-45 C เพื่อรันบน Wokwi ได้)
 * - แสดงผลบน OLED
 * - ความเร็วพัดลมแปรตามอุณหภูมิด้วย PWM (LED น้ำเงิน GPIO6 แทนพัดลม): <28 C = 0%, >=36 C = 100%
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "driver/ledc.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "oled.h"
#include "sht31.h"

static const char *TAG = "station";
static adc_oneshot_unit_handle_t s_adc;

static i2c_master_bus_handle_t i2c_bus_start(void)
{
    i2c_master_bus_config_t cfg = {
        .i2c_port = I2C_NUM_0, .sda_io_num = 8, .scl_io_num = 9,     /* SDA=GPIO8, SCL=GPIO9 */
        .clk_source = I2C_CLK_SRC_DEFAULT, .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,                       /* โมดูลส่วนใหญ่มี pull-up ภายนอกแล้ว */
    };
    i2c_master_bus_handle_t bus;
    ESP_ERROR_CHECK(i2c_new_master_bus(&cfg, &bus));
    return bus;
}

static void fan_init(void)
{
    ledc_timer_config_t t = { .speed_mode = LEDC_LOW_SPEED_MODE, .timer_num = LEDC_TIMER_0,
                              .duty_resolution = LEDC_TIMER_10_BIT, .freq_hz = 25000, .clk_cfg = LEDC_AUTO_CLK };
    ESP_ERROR_CHECK(ledc_timer_config(&t));      // 25 kHz = ความถี่มาตรฐานพัดลม PWM 4 สาย
    ledc_channel_config_t c = { .speed_mode = LEDC_LOW_SPEED_MODE, .channel = LEDC_CHANNEL_0,
                                .timer_sel = LEDC_TIMER_0, .gpio_num = 6, .duty = 0 };
    ESP_ERROR_CHECK(ledc_channel_config(&c));
}

static float simulated_temp(void)
{
    int raw = 0;
    adc_oneshot_read(s_adc, ADC_CHANNEL_0, &raw);
    return 20.0f + raw * 25.0f / 4095.0f;
}

void app_main(void)
{
    i2c_master_bus_handle_t bus = i2c_bus_start();
    ESP_ERROR_CHECK(oled_init(bus, 0x3C));
    bool have_sht = i2c_master_probe(bus, 0x44, 50) == ESP_OK;
    if (have_sht) ESP_ERROR_CHECK(sht31_init(bus, 0x44));
    else ESP_LOGW(TAG, "ไม่พบ SHT31 ใช้ potentiometer จำลองอุณหภูมิ");

    adc_oneshot_unit_init_cfg_t u = { .unit_id = ADC_UNIT_1 };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&u, &s_adc));
    adc_oneshot_chan_cfg_t ac = { .atten = ADC_ATTEN_DB_12, .bitwidth = ADC_BITWIDTH_DEFAULT };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(s_adc, ADC_CHANNEL_0, &ac));
    fan_init();

    while (1) {
        float t = 0, rh = -1;
        if (!have_sht || sht31_read(&t, &rh) != ESP_OK) t = simulated_temp();
        int pct = t <= 28 ? 0 : t >= 36 ? 100 : (int)((t - 28) * 100 / 8);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, pct * 1023 / 100);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

        char l1[24], l2[24], l3[24];
        snprintf(l1, sizeof l1, "%.1fC", t);
        snprintf(l2, sizeof l2, rh >= 0 ? "Humidity %.0f%%" : "Humidity --", rh);
        snprintf(l3, sizeof l3, "Fan %3d%%", pct);
        oled_clear();
        oled_text(0, 0, "GREENHOUSE A");
        oled_text_big(0, 2, l1);
        oled_text(0, 5, l2);
        oled_text(0, 7, l3);
        oled_rect(60, 56, pct * 68 / 100, 8, true);    // แถบความเร็วพัดลม
        oled_flush();
        ESP_LOGI(TAG, "T=%.1f C RH=%.0f%% fan=%d%%", t, rh, pct);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
