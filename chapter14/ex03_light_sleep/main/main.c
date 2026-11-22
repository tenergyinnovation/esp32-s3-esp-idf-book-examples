/*
 * บทที่ 14 ตัวอย่าง 3: light sleep
 * หลับ 2 วินาทีแล้วตื่นกลับมาทำงานต่อจากบรรทัดเดิม (RAM ยังอยู่ครบ)
 */
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "esp_log.h"

void app_main(void)
{
    for (int i = 1; ; i++) {
        ESP_LOGI("light", "รอบ %d ทำงาน 0.5 s แล้วหลับ 2 s", i);
        vTaskDelay(pdMS_TO_TICKS(500));
        esp_sleep_enable_timer_wakeup(2 * 1000 * 1000);
        int64_t t0 = esp_timer_get_time();
        esp_light_sleep_start();                       // หลับตรงนี้ ตื่นแล้วทำบรรทัดถัดไปต่อ
        ESP_LOGI("light", "ตื่นแล้ว หลับไป %lld ms สาเหตุ=%d", (esp_timer_get_time() - t0) / 1000, esp_sleep_get_wakeup_cause());
    }
}
