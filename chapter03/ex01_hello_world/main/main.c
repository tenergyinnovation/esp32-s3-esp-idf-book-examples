/*
 * บทที่ 3 ตัวอย่าง 1: Hello World
 * Target: ESP32-S3 (esp32s3) · ESP-IDF v6.1 · ภาษา C
 * พิมพ์ข้อความทุก 1 วินาที พร้อมตัวนับรอบ
 */
#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    printf("Hello ESP32-S3! สวัสดีจาก Tenergy Innovation\n");

    uint32_t count = 0;
    while (1) {
        printf("รอบที่ %" PRIu32 "\n", count);
        count++;
        vTaskDelay(pdMS_TO_TICKS(1000));   // รอ 1000 ms โดยไม่ผูก CPU ไว้
    }
}
