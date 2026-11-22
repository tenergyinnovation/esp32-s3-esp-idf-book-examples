/*
 * บทที่ 5 ตัวอย่าง 6: ขนาดโปรแกรม
 * build แล้วรัน "idf.py size" และ "idf.py size-components" เทียบก่อน/หลังเปิด BIG_TABLE
 */
#include <stdint.h>
#include "esp_log.h"

#define USE_BIG_TABLE 1    // ลองเปลี่ยนเป็น 0 แล้วดูขนาด Flash Data ที่ลดลง

#if USE_BIG_TABLE
static const uint16_t k_sine_table[4096] = { [1] = 1 };   // 8 KB ใน Flash
#endif

void app_main(void)
{
#if USE_BIG_TABLE
    ESP_LOGI("size", "ตารางขนาด %u bytes", (unsigned)sizeof(k_sine_table));
#else
    ESP_LOGI("size", "ไม่มีตาราง");
#endif
}
