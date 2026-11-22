/*
 * บทที่ 7 ตัวอย่าง 7: Task Watchdog Timer (TWDT)
 * task ลงทะเบียนกับ watchdog แล้วต้อง "รายงานตัว" (reset) เป็นระยะ
 * หลัง 5 รอบ จำลองว่า task ค้าง -> watchdog แจ้งเตือนภายใน timeout
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "esp_log.h"

static void worker(void *arg)
{
    ESP_ERROR_CHECK(esp_task_wdt_add(NULL));        // ลงทะเบียน task นี้
    for (int i = 1; ; i++) {
        if (i <= 5) {
            ESP_LOGI("worker", "ทำงานปกติ รอบ %d", i);
            ESP_ERROR_CHECK(esp_task_wdt_reset()); // รายงานตัว "ยังอยู่"
        } else if (i == 6) {
            ESP_LOGE("worker", "จำลองค้าง: เลิกรายงานตัว");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    xTaskCreate(worker, "worker", 3072, NULL, 5, NULL);
}
