/*
 * บทที่ 7 ตัวอย่าง 1: สร้าง task สองตัว
 * task A พิมพ์ทุก 500 ms, task B พิมพ์ทุก 1200 ms แต่ละตัวมีจังหวะของตัวเอง
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

typedef struct { const char *name; int period_ms; } job_t;

static void worker(void *arg)
{
    const job_t *job = (const job_t *)arg;
    int n = 0;
    while (1) {
        ESP_LOGI(job->name, "ทำงานรอบที่ %d บน core %d", ++n, xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(job->period_ms));
    }
}

void app_main(void)
{
    static const job_t a = { "task_A", 500 }, b = { "task_B", 1200 };   // static: อยู่ตลอดโปรแกรม
    xTaskCreate(worker, "task_A", 3072, (void *)&a, 5, NULL);
    xTaskCreate(worker, "task_B", 3072, (void *)&b, 5, NULL);
    ESP_LOGI("main", "สร้าง task แล้ว app_main จบได้ task ยังทำงานต่อ");
}
