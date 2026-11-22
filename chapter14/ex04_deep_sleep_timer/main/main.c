/*
 * บทที่ 14 ตัวอย่าง 4: deep sleep + timer wake-up
 * ตื่น -> วัดค่า -> หลับ 10 วินาที วนไป ตัวแปร RTC_DATA_ATTR อยู่รอดข้ามการหลับลึก
 * ตื่นจาก deep sleep = เริ่ม app_main ใหม่ (เหมือนรีเซ็ต แต่ RTC memory ยังจำค่า)
 */
#include <inttypes.h>
#include "esp_sleep.h"
#include "esp_attr.h"
#include "esp_random.h"
#include "esp_log.h"

RTC_DATA_ATTR static uint32_t s_wake_count;
RTC_DATA_ATTR static float s_last_temp;

void app_main(void)
{
    s_wake_count++;
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
    ESP_LOGI("deep", "ตื่นครั้งที่ %" PRIu32 " สาเหตุ: %s", s_wake_count,
             cause == ESP_SLEEP_WAKEUP_TIMER ? "ครบเวลา" : "เปิดเครื่อง/รีเซ็ต");
    float t = 25 + (esp_random() % 100) / 10.0f;
    ESP_LOGI("deep", "วัดได้ %.1f C (ครั้งก่อน %.1f C)", t, s_last_temp);
    s_last_temp = t;
    ESP_LOGI("deep", "หลับลึก 10 วินาที...");
    esp_sleep_enable_timer_wakeup(10ULL * 1000 * 1000);
    esp_deep_sleep_start();                             // ไม่กลับมาบรรทัดนี้อีก
}
