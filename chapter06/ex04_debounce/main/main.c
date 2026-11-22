/*
 * บทที่ 6 ตัวอย่าง 4: debounce
 * ยอมรับการเปลี่ยนสถานะเมื่อค่าคงที่ต่อเนื่องอย่างน้อย DEBOUNCE_MS
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BTN          GPIO_NUM_5
#define SAMPLE_MS    5
#define DEBOUNCE_MS  30      // ปุ่มกดทั่วไปเด้งประมาณ 1-20 ms

void app_main(void)
{
    gpio_config_t in = { .pin_bit_mask = 1ULL << BTN, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    ESP_ERROR_CHECK(gpio_config(&in));

    int stable = 1, candidate = 1, stable_ms = 0, count = 0;
    while (1) {
        int raw = gpio_get_level(BTN);
        if (raw != candidate) {           // ค่าเปลี่ยน -> เริ่มจับเวลาใหม่
            candidate = raw;
            stable_ms = 0;
        } else if (stable_ms < DEBOUNCE_MS) {
            stable_ms += SAMPLE_MS;
            if (stable_ms >= DEBOUNCE_MS && candidate != stable) {
                stable = candidate;       // นิ่งพอแล้ว ยอมรับค่าใหม่
                if (stable == 0) ESP_LOGI("debounce", "กดจริงครั้งที่ %d", ++count);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(SAMPLE_MS));
    }
}
