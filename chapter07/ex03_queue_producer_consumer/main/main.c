/*
 * บทที่ 7 ตัวอย่าง 3: queue
 * sensor_task (ผู้ผลิต) ส่ง struct การวัดเข้า queue ทุก 500 ms
 * display_task (ผู้ใช้) รับมาแสดงผลและหาค่าเฉลี่ย
 */
#include <stdint.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_random.h"
#include "esp_log.h"

typedef struct { uint32_t seq; float temp_c; } reading_t;
static QueueHandle_t s_q;

static void sensor_task(void *arg)
{
    uint32_t seq = 0;
    while (1) {
        reading_t r = { .seq = ++seq, .temp_c = 25.0f + (esp_random() % 1000) / 100.0f };
        if (xQueueSend(s_q, &r, pdMS_TO_TICKS(100)) != pdPASS) {
            ESP_LOGW("sensor", "queue เต็ม ทิ้งค่า #%" PRIu32, r.seq);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void display_task(void *arg)
{
    reading_t r; float sum = 0; int n = 0;
    while (1) {
        if (xQueueReceive(s_q, &r, portMAX_DELAY) == pdPASS) {
            sum += r.temp_c; n++;
            ESP_LOGI("display", "#%" PRIu32 " = %.2f C  (เฉลี่ย %.2f C, ค้างในคิว %u)",
                     r.seq, r.temp_c, sum / n, (unsigned)uxQueueMessagesWaiting(s_q));
        }
    }
}

void app_main(void)
{
    s_q = xQueueCreate(5, sizeof(reading_t));     // ช่องรับของได้ 5 ชิ้น
    configASSERT(s_q);
    xTaskCreate(sensor_task, "sensor", 3072, NULL, 5, NULL);
    xTaskCreate(display_task, "display", 3072, NULL, 4, NULL);
}
