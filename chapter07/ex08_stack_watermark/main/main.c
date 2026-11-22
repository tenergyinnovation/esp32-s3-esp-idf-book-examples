/*
 * บทที่ 7 ตัวอย่าง 8: stack high-water mark
 * ค่า "เหลือน้อยที่สุดที่เคยเหลือ" บอกว่าตั้ง stack มากหรือน้อยเกินไป
 */
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static void small_job(void *arg)
{
    char buf[64]; memset(buf, 1, sizeof(buf));
    ESP_LOGI("small", "เหลือ stack น้อยสุด %u bytes", (unsigned)uxTaskGetStackHighWaterMark(NULL));
    vTaskDelete(NULL);
}

static void big_job(void *arg)
{
    char buf[2048]; memset(buf, 1, sizeof(buf));      // ตัวแปรใหญ่บน stack
    ESP_LOGI("big", "buf[0]=%d เหลือ stack น้อยสุด %u bytes", buf[0], (unsigned)uxTaskGetStackHighWaterMark(NULL));
    vTaskDelete(NULL);
}

void app_main(void)
{
    xTaskCreate(small_job, "small", 4096, NULL, 5, NULL);
    vTaskDelay(pdMS_TO_TICKS(100));
    xTaskCreate(big_job, "big", 4096, NULL, 5, NULL);
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_LOGI("main", "app_main เหลือ stack น้อยสุด %u bytes", (unsigned)uxTaskGetStackHighWaterMark(NULL));
}
