/*
 * บทที่ 12 ตัวอย่าง 3: notify
 * เมื่อมือถือ "subscribe" บอร์ดจะส่งค่าใหม่ให้เองทุก 2 วินาที (ไม่ต้องกดอ่าน)
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"

#include <string.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"

static const char *TAG = "ble";
static uint8_t s_addr_type;
static uint16_t s_conn = BLE_HS_CONN_HANDLE_NONE;
static void advertise(void);

static int gap_event(struct ble_gap_event *ev, void *arg)
{
    switch (ev->type) {
    case BLE_GAP_EVENT_CONNECT:
        ESP_LOGI(TAG, "มือถือเชื่อมต่อ %s", ev->connect.status == 0 ? "สำเร็จ" : "ไม่สำเร็จ");
        if (ev->connect.status == 0) s_conn = ev->connect.conn_handle; else advertise();
        break;
    case BLE_GAP_EVENT_DISCONNECT:
        ESP_LOGI(TAG, "ตัดการเชื่อมต่อ (reason %d) กลับไปประกาศตัว", ev->disconnect.reason);
        s_conn = BLE_HS_CONN_HANDLE_NONE;
        advertise();
        break;
    case BLE_GAP_EVENT_SUBSCRIBE:
        ESP_LOGI(TAG, "มือถือ %s การแจ้งเตือน (handle %d)", ev->subscribe.cur_notify ? "เปิด" : "ปิด", ev->subscribe.attr_handle);
        break;
    default: break;
    }
    return 0;
}

static void advertise(void)
{
    struct ble_hs_adv_fields f = { 0 };
    const char *name = ble_svc_gap_device_name();
    f.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;   /* ค้นเจอได้ทั่วไป, ไม่รองรับ BT Classic */
    f.name = (uint8_t *)name; f.name_len = strlen(name); f.name_is_complete = 1;
    f.tx_pwr_lvl_is_present = 1; f.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;
    ESP_ERROR_CHECK(ble_gap_adv_set_fields(&f));
    struct ble_gap_adv_params p = { .conn_mode = BLE_GAP_CONN_MODE_UND, .disc_mode = BLE_GAP_DISC_MODE_GEN };
    int rc = ble_gap_adv_start(s_addr_type, NULL, BLE_HS_FOREVER, &p, gap_event, NULL);
    if (rc == 0) ESP_LOGI(TAG, "กำลังประกาศตัวชื่อ \"%s\"", name);
}

static void on_sync(void)
{
    ble_hs_id_infer_auto(0, &s_addr_type);
    uint8_t a[6] = { 0 };
    ble_hs_id_copy_addr(s_addr_type, a, NULL);
    ESP_LOGI(TAG, "BLE พร้อม address %02x:%02x:%02x:%02x:%02x:%02x", a[5], a[4], a[3], a[2], a[1], a[0]);
    advertise();
}

static void host_task(void *arg) { nimble_port_run(); nimble_port_freertos_deinit(); }

static void ble_start(const char *name, const struct ble_gatt_svc_def *svcs)
{
    esp_err_t err = nvs_flash_init();          /* BLE เก็บข้อมูล bonding ใน NVS */
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) { nvs_flash_erase(); err = nvs_flash_init(); }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(nimble_port_init());
    ble_hs_cfg.sync_cb = on_sync;
    ble_svc_gap_init();
    ble_svc_gatt_init();
    if (svcs) {
        ESP_ERROR_CHECK(ble_gatts_count_cfg(svcs));
        ESP_ERROR_CHECK(ble_gatts_add_svcs(svcs));
    }
    ble_svc_gap_device_name_set(name);
    nimble_port_freertos_init(host_task);
}

/* UUID 128 bit ของเราเอง (สุ่มสร้างครั้งเดียวแล้วใช้ตลอด) เขียนจาก byte ท้ายไปหน้า */
static const ble_uuid128_t __attribute__((unused)) SVC_UUID = BLE_UUID128_INIT(0x10,0x32,0x54,0x76,0x98,0xba,0xdc,0xfe,0x10,0x32,0x54,0x76,0x00,0x00,0x5e,0x7e);
static const ble_uuid128_t __attribute__((unused)) TEMP_UUID = BLE_UUID128_INIT(0x10,0x32,0x54,0x76,0x98,0xba,0xdc,0xfe,0x10,0x32,0x54,0x76,0x01,0x00,0x5e,0x7e);
static const ble_uuid128_t __attribute__((unused)) LED_UUID = BLE_UUID128_INIT(0x10,0x32,0x54,0x76,0x98,0xba,0xdc,0xfe,0x10,0x32,0x54,0x76,0x02,0x00,0x5e,0x7e);

static uint16_t s_temp_handle;
static char s_txt[16] = "--";

static int temp_access(uint16_t conn, uint16_t attr, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    return os_mbuf_append(ctxt->om, s_txt, strlen(s_txt)) == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

static const struct ble_gatt_svc_def SVCS[] = {
    { .type = BLE_GATT_SVC_TYPE_PRIMARY, .uuid = &SVC_UUID.u,
      .characteristics = (struct ble_gatt_chr_def[]) {
          { .uuid = &TEMP_UUID.u, .access_cb = temp_access, .val_handle = &s_temp_handle,
            .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY },
          { 0 } } },
    { 0 } };

static void sensor_task(void *arg)
{
    while (1) {
        snprintf(s_txt, sizeof s_txt, "%.1f C", 25.0f + (esp_random() % 100) / 10.0f);
        if (s_conn != BLE_HS_CONN_HANDLE_NONE) {
            struct os_mbuf *om = ble_hs_mbuf_from_flat(s_txt, strlen(s_txt));
            if (ble_gatts_notify_custom(s_conn, s_temp_handle, om) == 0) ESP_LOGI(TAG, "notify %s", s_txt);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    ble_start("Greenhouse-S3", SVCS);
    xTaskCreate(sensor_task, "sensor", 4096, NULL, 5, NULL);
}
