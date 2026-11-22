/*
 * บทที่ 7 ตัวอย่าง 4: race condition และ mutex
 * สอง task บวกตัวนับร่วมกันคนละ 100000 ครั้ง บน core คนละตัว
 * แบบไม่ป้องกัน: ผลรวม < 200000 (ข้อมูลหาย)  แบบมี mutex: ได้ 200000 พอดี
 */
#include <stdint.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

#define LOOPS 100000
static volatile uint32_t s_unsafe = 0;
static uint32_t s_safe = 0;
static SemaphoreHandle_t s_mutex;
static SemaphoreHandle_t s_done;

static void adder(void *arg)
{
    for (int i = 0; i < LOOPS; i++) {
        s_unsafe++;                                   // อ่าน-บวก-เขียน ถูกแทรกกลางทางได้
        xSemaphoreTake(s_mutex, portMAX_DELAY);       // ล็อกห้องน้ำ
        s_safe++;
        xSemaphoreGive(s_mutex);                      // ปลดล็อก
    }
    xSemaphoreGive(s_done);
    vTaskDelete(NULL);
}

void app_main(void)
{
    s_mutex = xSemaphoreCreateMutex();
    s_done  = xSemaphoreCreateCounting(2, 0);
    xTaskCreatePinnedToCore(adder, "adder0", 3072, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(adder, "adder1", 3072, NULL, 5, NULL, 1);
    xSemaphoreTake(s_done, portMAX_DELAY);
    xSemaphoreTake(s_done, portMAX_DELAY);
    ESP_LOGI("race", "คาดหวัง %d", 2 * LOOPS);
    ESP_LOGW("race", "ไม่ป้องกัน: %" PRIu32, s_unsafe);
    ESP_LOGI("race", "ใช้ mutex: %" PRIu32, s_safe);
}
