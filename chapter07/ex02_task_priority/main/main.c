/*
 * บทที่ 7 ตัวอย่าง 2: priority
 * ผูกทั้งสอง task ไว้ core 0 เพื่อให้เห็นผลชัด
 * task "busy" (priority สูง) ทำงาน 2 วินาทีโดยไม่พัก -> task "logger" (priority ต่ำ) ต้องรอ
 */
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"
#include "esp_log.h"

static void logger(void *arg)
{
    while (1) {
        ESP_LOGI("logger", "tick ที่ %" PRId64 " ms", esp_timer_get_time() / 1000);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

static void busy(void *arg)
{
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(3000));
        ESP_LOGW("busy", "เริ่มงานหนัก 2 วินาที (ไม่ยอมพัก)");
        int64_t t0 = esp_timer_get_time();
        while (esp_timer_get_time() - t0 < 2000000) {
            esp_rom_delay_us(1000);        // วนรอแบบไม่ปล่อย CPU (ห้ามทำในงานจริง)
        }
        ESP_LOGW("busy", "งานหนักเสร็จ");
    }
}

void app_main(void)
{
    xTaskCreatePinnedToCore(logger, "logger", 3072, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(busy,   "busy",   3072, NULL, 6, NULL, 0);
}
