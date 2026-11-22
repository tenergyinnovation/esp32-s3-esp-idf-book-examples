/*
 * บทที่ 7 ตัวอย่าง 6: dual-core
 * งานคำนวณหนัก 2 ชิ้น: ทำบน core เดียว vs แยก core 0 และ core 1
 */
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_timer.h"
#include "esp_log.h"

static SemaphoreHandle_t s_done;

static void heavy(void *arg)
{
    volatile float x = 0;
    for (int i = 0; i < 3000000; i++) x += i * 0.5f;     // งานคำนวณ float
    ESP_LOGI("heavy", "เสร็จบน core %d", xPortGetCoreID());
    xSemaphoreGive(s_done);
    vTaskDelete(NULL);
}

static int64_t run(int core_a, int core_b)
{
    int64_t t0 = esp_timer_get_time();
    xTaskCreatePinnedToCore(heavy, "h1", 3072, NULL, 5, NULL, core_a);
    xTaskCreatePinnedToCore(heavy, "h2", 3072, NULL, 5, NULL, core_b);
    xSemaphoreTake(s_done, portMAX_DELAY);
    xSemaphoreTake(s_done, portMAX_DELAY);
    return (esp_timer_get_time() - t0) / 1000;
}

void app_main(void)
{
    s_done = xSemaphoreCreateCounting(2, 0);
    int64_t same = run(1, 1);
    int64_t split = run(0, 1);
    ESP_LOGI("dual", "core เดียว: %" PRId64 " ms, แยกสอง core: %" PRId64 " ms", same, split);
}
