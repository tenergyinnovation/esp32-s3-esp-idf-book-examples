/*
 * บทที่ 17 ตัวอย่าง 1: USB CDC-ACM
 * เสียบพอร์ต USB แล้วคอมพิวเตอร์จะเห็นพอร์ต COM ใหม่ (macOS: /dev/cu.usbmodemXXXX)
 * พิมพ์อะไรเข้าไป บอร์ดจะส่งกลับเป็นตัวพิมพ์ใหญ่ ส่วน log ยังออกที่พอร์ต UART เหมือนเดิม
 */
#include <ctype.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "tinyusb.h"
#include "tinyusb_default_config.h"
#include "tinyusb_cdc_acm.h"
#include "esp_log.h"

static const char *TAG = "cdc";
typedef struct { uint8_t buf[CONFIG_TINYUSB_CDC_RX_BUFSIZE]; size_t len; } rx_msg_t;
static QueueHandle_t s_q;

/* callback นี้ถูกเรียกจาก task ของ TinyUSB (ไม่ใช่ ISR) แต่ก็ควรสั้น: อ่านแล้วโยนเข้าคิว */
static void on_rx(int itf, cdcacm_event_t *event)
{
    rx_msg_t m;
    if (tinyusb_cdcacm_read(itf, m.buf, sizeof m.buf, &m.len) == ESP_OK && m.len) xQueueSend(s_q, &m, 0);
}

static void on_line_state(int itf, cdcacm_event_t *event)
{
    ESP_LOGI(TAG, "โปรแกรม terminal %s (DTR=%d)", event->line_state_changed_data.dtr ? "เปิดพอร์ตแล้ว" : "ปิดพอร์ต",
             event->line_state_changed_data.dtr);
}

void app_main(void)
{
    s_q = xQueueCreate(4, sizeof(rx_msg_t));
    const tinyusb_config_t tusb_cfg = TINYUSB_DEFAULT_CONFIG();       // ใช้ descriptor มาตรฐานของ esp_tinyusb
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
    tinyusb_config_cdcacm_t acm = {
        .cdc_port = TINYUSB_CDC_ACM_0,
        .callback_rx = on_rx,
        .callback_line_state_changed = on_line_state,
    };
    ESP_ERROR_CHECK(tinyusb_cdcacm_init(&acm));
    ESP_LOGI(TAG, "พร้อมแล้ว เปิดพอร์ต COM ใหม่ด้วยโปรแกรม terminal ใดก็ได้");

    rx_msg_t m;
    while (1) {
        if (xQueueReceive(s_q, &m, portMAX_DELAY)) {
            for (size_t i = 0; i < m.len; i++) m.buf[i] = (uint8_t)toupper(m.buf[i]);
            tinyusb_cdcacm_write_queue(TINYUSB_CDC_ACM_0, m.buf, m.len);
            esp_err_t err = tinyusb_cdcacm_write_flush(TINYUSB_CDC_ACM_0, pdMS_TO_TICKS(100));
            if (err != ESP_OK) ESP_LOGW(TAG, "ส่งกลับไม่สำเร็จ: %s", esp_err_to_name(err));
            ESP_LOGI(TAG, "รับ %u ไบต์ ส่งกลับเป็นตัวพิมพ์ใหญ่", (unsigned)m.len);
        }
    }
}
