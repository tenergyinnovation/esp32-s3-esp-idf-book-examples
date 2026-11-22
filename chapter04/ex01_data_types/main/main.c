/*
 * บทที่ 4 ตัวอย่าง 1: ชนิดข้อมูลขนาดแน่นอน
 * ใช้ <stdint.h> เพื่อให้รู้ขนาดตัวแปรแน่นอน ไม่ขึ้นกับคอมไพเลอร์
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include "esp_log.h"

static const char *TAG = "types";

void app_main(void)
{
    uint8_t  sensor_id   = 7;          // 0..255
    int16_t  temp_centi  = -125;       // -1.25 °C เก็บเป็นหน่วย 0.01 °C
    uint32_t sample_cnt  = 123456;
    float    humidity    = 61.5f;      // ESP32-S3 มี FPU คำนวณ float ได้เร็ว
    bool     fan_on      = false;
    size_t   buf_size    = 128;

    ESP_LOGI(TAG, "sensor_id=%" PRIu8 ", temp=%" PRId16 " (x0.01 C)", sensor_id, temp_centi);
    ESP_LOGI(TAG, "samples=%" PRIu32 ", humidity=%.1f %%", sample_cnt, humidity);
    ESP_LOGI(TAG, "fan_on=%s, buf_size=%zu", fan_on ? "true" : "false", buf_size);
    ESP_LOGI(TAG, "sizeof: uint8=%zu int16=%zu uint32=%zu float=%zu size_t=%zu pointer=%zu",
             sizeof(uint8_t), sizeof(int16_t), sizeof(uint32_t), sizeof(float), sizeof(size_t), sizeof(void *));

    // ระวังล้น: uint8_t เก็บได้แค่ 0..255
    uint8_t counter = 250;
    for (int i = 0; i < 10; i++) counter++;
    ESP_LOGW(TAG, "uint8_t 250 + 10 = %" PRIu8 " (ล้นแล้ววนกลับ)", counter);
}
