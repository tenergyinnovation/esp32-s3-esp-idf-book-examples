/*
 * บทที่ 5 ตัวอย่าง 1: แยกโค้ดหลายไฟล์
 * main.c เรียกใช้ฟังก์ชันจาก temperature.c ผ่าน temperature.h
 */
#include "temperature.h"
#include "esp_log.h"

static const char *TAG = "main";

void app_main(void)
{
    const float readings_c[] = { 25.0f, 31.5f, 40.0f };
    for (int i = 0; i < 3; i++) {
        float f = temp_c_to_f(readings_c[i]);
        ESP_LOGI(TAG, "%.1f C = %.1f F  ร้อนเกิน? %s", readings_c[i], f,
                 temp_is_hot(readings_c[i]) ? "ใช่" : "ไม่");
    }
}
