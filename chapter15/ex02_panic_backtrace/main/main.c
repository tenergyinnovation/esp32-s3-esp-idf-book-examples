/*
 * บทที่ 15 ตัวอย่าง 2: อ่าน panic
 * กดปุ่ม GPIO5 -> โปรแกรมเขียนข้อมูลผ่าน pointer ว่าง (NULL) -> crash
 * idf.py monitor จะแปล address ใน backtrace เป็นชื่อฟังก์ชันและบรรทัดให้อัตโนมัติ
 */
#include <stddef.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

typedef struct { int temp; } sensor_t;

static void save_reading(sensor_t *s, int value)
{
    s->temp = value;                         // ถ้า s == NULL จะ crash ที่บรรทัดนี้
}

static sensor_t *find_sensor(int id)
{
    static sensor_t zone1;
    return id == 1 ? &zone1 : NULL;          // ไม่พบ -> คืน NULL (และผู้เรียกลืมตรวจ = bug)
}

void app_main(void)
{
    gpio_config_t in = { .pin_bit_mask = 1ULL << 5, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    ESP_ERROR_CHECK(gpio_config(&in));
    ESP_LOGI("panic", "กดปุ่ม GPIO5 เพื่อเรียก find_sensor(2) ซึ่งคืน NULL");
    while (gpio_get_level(5) == 1) vTaskDelay(pdMS_TO_TICKS(20));
    save_reading(find_sensor(2), 30);
}
