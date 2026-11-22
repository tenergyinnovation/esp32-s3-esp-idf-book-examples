/*
 * บทที่ 4 ตัวอย่าง 3: const และ static
 */
#include <stdint.h>
#include <inttypes.h>
#include "esp_log.h"

static const char *TAG = "const_static";

// const: ค่าเกณฑ์ที่ห้ามแก้ระหว่างทำงาน (มักถูกวางใน Flash ไม่กิน RAM)
static const int16_t k_fan_on_centi = 3200;    // 32.00 °C
static const uint16_t k_table[256] = { [0] = 1, [255] = 255 };

// static นอกฟังก์ชัน: มองเห็นเฉพาะไฟล์นี้
static uint32_t s_error_total;

static uint32_t count_plain(void)
{
    uint32_t n = 0;     // เกิดใหม่ทุกครั้งที่เรียก
    return ++n;
}

static uint32_t count_static(void)
{
    static uint32_t n = 0;   // เกิดครั้งเดียว จำค่าข้ามการเรียก
    return ++n;
}

void app_main(void)
{
    int local = 0;
    ESP_LOGI(TAG, "เกณฑ์เปิดพัดลม = %d.%02d C", k_fan_on_centi / 100, k_fan_on_centi % 100);
    for (int round = 1; round <= 3; round++) {
        s_error_total++;
        ESP_LOGI(TAG, "รอบ %d: plain=%" PRIu32 " static=%" PRIu32 " total=%" PRIu32,
                 round, count_plain(), count_static(), s_error_total);
    }
    // ดูว่าตัวแปรแต่ละแบบอยู่ที่ address ช่วงไหน
    ESP_LOGI(TAG, "const table (Flash) = %p", (const void *)k_table);
    ESP_LOGI(TAG, "static var (RAM)    = %p", (void *)&s_error_total);
    ESP_LOGI(TAG, "local var (stack)   = %p", (void *)&local);
    // k_fan_on_centi = 2500;   // ถ้าเอา comment ออก จะ build ไม่ผ่าน: assignment of read-only variable
}
