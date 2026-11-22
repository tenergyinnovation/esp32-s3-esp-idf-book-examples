/*
 * บทที่ 6 ตัวอย่าง 3: interrupt + queue
 * ISR ส่งหมายเลขขาเข้า queue, task รับไปทำงานต่อ (deferred handling)
 */
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"

#define BTN GPIO_NUM_5
#define LED GPIO_NUM_4
static QueueHandle_t s_evt_q;

static void IRAM_ATTR on_button(void *arg)
{
    uint32_t pin = (uint32_t)arg;
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR(s_evt_q, &pin, &woken);   // ห้ามใช้ xQueueSend ใน ISR
    if (woken) portYIELD_FROM_ISR();
}

static void button_task(void *arg)
{
    uint32_t pin; int led = 0; int presses = 0;
    while (1) {
        if (xQueueReceive(s_evt_q, &pin, portMAX_DELAY)) {   // หลับรอจนมีเหตุการณ์
            led = !led; presses++;
            gpio_set_level(LED, led);
            ESP_LOGI("irq", "GPIO%" PRIu32 " กดครั้งที่ %d เวลา %lld ms -> LED %s",
                     pin, presses, esp_timer_get_time() / 1000, led ? "ON" : "OFF");
        }
    }
}

void app_main(void)
{
    s_evt_q = xQueueCreate(10, sizeof(uint32_t));
    gpio_config_t out = { .pin_bit_mask = 1ULL << LED, .mode = GPIO_MODE_OUTPUT };
    gpio_config_t in  = { .pin_bit_mask = 1ULL << BTN, .mode = GPIO_MODE_INPUT,
                          .pull_up_en = GPIO_PULLUP_ENABLE, .intr_type = GPIO_INTR_NEGEDGE };
    ESP_ERROR_CHECK(gpio_config(&out));
    ESP_ERROR_CHECK(gpio_config(&in));
    xTaskCreate(button_task, "button_task", 3072, NULL, 10, NULL);
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(BTN, on_button, (void *)BTN));
    ESP_LOGI("irq", "พร้อม กดปุ่มได้เลย");
}
