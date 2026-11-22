/*
 * บทที่ 14 ตัวอย่าง 2: heap monitor
 * task "leaky" ลืม free ทุกรอบ (จงใจให้รั่ว) task "monitor" รายงาน heap ทุก 2 วินาที
 * สังเกต: free ลดลงเรื่อยๆ และ minimum free (ต่ำสุดที่เคยเหลือ) ก็ลดตาม = สัญญาณ memory leak
 */
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_log.h"

static void leaky(void *arg)
{
    for (int i = 1; i <= 20; i++) {
        char *p = malloc(1024);          // จอง 1 KB
        if (p) p[0] = 1;                 // ...แล้วไม่ free (bug)
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    vTaskDelete(NULL);
}

static void monitor(void *arg)
{
    while (1) {
        ESP_LOGI("heap", "free=%u  min_free=%u  largest_block=%u",
                 (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
                 (unsigned)heap_caps_get_minimum_free_size(MALLOC_CAP_INTERNAL),
                 (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    xTaskCreate(monitor, "monitor", 3072, NULL, 5, NULL);
    xTaskCreate(leaky, "leaky", 3072, NULL, 4, NULL);
}
