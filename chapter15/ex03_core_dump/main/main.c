/*
 * บทที่ 15 ตัวอย่าง 3: core dump
 * เมื่อ crash ระบบบันทึก "ภาพนิ่ง" ของ task ทั้งหมดลง partition coredump
 * ดูทีหลังได้แม้ไม่ได้เปิด monitor ตอนเกิดเหตุ: idf.py coredump-info
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_core_dump.h"
#include "esp_log.h"

static void worker(void *arg)
{
    int *volatile bad = NULL;
    vTaskDelay(pdMS_TO_TICKS(5000));
    ESP_LOGE("cd", "worker กำลังจะ crash");
    *bad = 42;
}

void app_main(void)
{
    if (esp_core_dump_image_check() == ESP_OK) {
        ESP_LOGW("cd", "พบ core dump จากการ crash ครั้งก่อน -> รัน idf.py coredump-info เพื่อดู");
    } else {
        ESP_LOGI("cd", "ไม่มี core dump ค้างอยู่");
    }
    xTaskCreate(worker, "worker", 3072, NULL, 5, NULL);
}
