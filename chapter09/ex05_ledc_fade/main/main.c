/*
 * บทที่ 9 ตัวอย่าง 5: PWM ด้วย LEDC
 * ความถี่ 5 kHz ความละเอียด 13 bit (duty 0..8191)
 * ให้ LED ค่อยๆ สว่างและค่อยๆ หรี่ ใช้เวลาข้างละประมาณ 1.5 วินาที
 * ปรับ duty ทีละขั้นด้วย ledc_set_duty() + ledc_update_duty() (50 ขั้น ขั้นละ 30 ms)
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define LED_GPIO  4
#define MAX_DUTY  ((1 << 13) - 1)
#define STEPS     50
#define STEP_MS   30            /* 50 x 30 ms = 1.5 s */

static void set_duty(uint32_t duty)
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));   /* ค่าใหม่มีผลรอบ PWM ถัดไป */
}

void app_main(void)
{
    ledc_timer_config_t t = { .speed_mode = LEDC_LOW_SPEED_MODE, .timer_num = LEDC_TIMER_0,
                              .duty_resolution = LEDC_TIMER_13_BIT, .freq_hz = 5000, .clk_cfg = LEDC_AUTO_CLK };
    ESP_ERROR_CHECK(ledc_timer_config(&t));
    ledc_channel_config_t ch = { .speed_mode = LEDC_LOW_SPEED_MODE, .channel = LEDC_CHANNEL_0, .timer_sel = LEDC_TIMER_0,
                                 .gpio_num = LED_GPIO, .duty = 0 };
    ESP_ERROR_CHECK(ledc_channel_config(&ch));

    while (1) {
        ESP_LOGI("pwm", "ค่อยๆ สว่าง -> duty %d (100%%)", MAX_DUTY);
        for (int i = 1; i <= STEPS; i++) {
            set_duty((uint32_t)MAX_DUTY * i / STEPS);
            vTaskDelay(pdMS_TO_TICKS(STEP_MS));
        }
        ESP_LOGI("pwm", "ค่อยๆ หรี่ -> duty 0");
        for (int i = STEPS - 1; i >= 0; i--) {
            set_duty((uint32_t)MAX_DUTY * i / STEPS);
            vTaskDelay(pdMS_TO_TICKS(STEP_MS));
        }
    }
}
