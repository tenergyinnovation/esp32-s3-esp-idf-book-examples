/*
 * บทที่ 3 ตัวอย่าง 3: กะพริบ LED ภายนอก
 * วงจร: GPIO4 -> ตัวต้านทาน 330 Ω -> LED -> GND
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO     GPIO_NUM_4
#define BLINK_MS     500          // ไฟเลี้ยวรถยนต์กะพริบราว 1-2 ครั้งต่อวินาที

void app_main(void)
{
    gpio_reset_pin(LED_GPIO);
    ESP_ERROR_CHECK(gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT));

    bool on = false;
    while (1) {
        on = !on;
        gpio_set_level(LED_GPIO, on);
        printf("LED %s\n", on ? "ON" : "OFF");
        vTaskDelay(pdMS_TO_TICKS(BLINK_MS));
    }
}
