/*
 * บทที่ 4 ตัวอย่าง 2: struct + enum + pointer + array
 * จำลองเซนเซอร์อุณหภูมิ 3 จุดในโรงเรือน
 */
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include "esp_log.h"

static const char *TAG = "record";

typedef enum {
    STATUS_OK = 0,
    STATUS_WARNING,     // ร้อนเกิน 30 °C
    STATUS_ERROR,       // ค่าผิดปกติ (เซนเซอร์เสีย)
} sensor_status_t;

typedef struct {
    uint8_t         id;
    int16_t         temp_centi;    // หน่วย 0.01 °C
    uint32_t        samples;
    sensor_status_t status;
} sensor_record_t;

static sensor_status_t classify(int16_t t)
{
    if (t < -2000 || t > 6000) return STATUS_ERROR;
    if (t > 3000)              return STATUS_WARNING;
    return STATUS_OK;
}

static const char *status_name(sensor_status_t s)
{
    static const char *names[] = { "OK", "WARNING", "ERROR" };
    return (s <= STATUS_ERROR) ? names[s] : "UNKNOWN";
}

// รับ pointer เพื่อแก้ข้อมูลตัวจริง (ไม่ใช่สำเนา)
static void update(sensor_record_t *rec, int16_t new_temp)
{
    if (rec == NULL) return;          // กันโปรแกรม crash เมื่อได้ pointer ว่าง
    rec->temp_centi = new_temp;
    rec->samples++;
    rec->status = classify(new_temp);
}

void app_main(void)
{
    sensor_record_t zones[] = {
        { .id = 1 }, { .id = 2 }, { .id = 3 },   // field ที่ไม่ระบุจะเป็น 0
    };
    const size_t count = sizeof(zones) / sizeof(zones[0]);
    const int16_t readings[] = { 2850, 3150, 7200 };

    for (size_t i = 0; i < count; i++) {
        update(&zones[i], readings[i]);
    }
    ESP_LOGI(TAG, "จำนวนโซน=%zu, ขนาด struct=%zu bytes", count, sizeof(sensor_record_t));
    for (size_t i = 0; i < count; i++) {
        const sensor_record_t *z = &zones[i];
        ESP_LOGI(TAG, "โซน %" PRIu8 ": %d.%02d C  สถานะ=%s  ที่อยู่=%p",
                 z->id, z->temp_centi / 100, z->temp_centi % 100, status_name(z->status), (void *)z);
    }
}
