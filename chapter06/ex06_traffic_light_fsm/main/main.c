/*
 * บทที่ 6 ตัวอย่าง 6: state machine
 * สถานะ: GREEN -> YELLOW -> RED -> GREEN ...
 * กดปุ่มคนข้าม (GPIO7) ขณะเขียว จะตัดเหลือเวลาเขียวแค่ 2 วินาที
 */
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

typedef enum { ST_GREEN, ST_YELLOW, ST_RED } state_t;
static const char *NAMES[] = { "GREEN", "YELLOW", "RED" };
static const gpio_num_t LAMP[] = { GPIO_NUM_6, GPIO_NUM_5, GPIO_NUM_4 };   // green, yellow, red
static const int DURATION_MS[] = { 8000, 1500, 5000 };
#define BTN GPIO_NUM_7

static void show(state_t s)
{
    for (int i = 0; i < 3; i++) gpio_set_level(LAMP[i], i == s);
    ESP_LOGI("fsm", "-> %s", NAMES[s]);
}

void app_main(void)
{
    gpio_config_t out = { .pin_bit_mask = (1ULL << 4) | (1ULL << 5) | (1ULL << 6), .mode = GPIO_MODE_OUTPUT };
    gpio_config_t in  = { .pin_bit_mask = 1ULL << BTN, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    ESP_ERROR_CHECK(gpio_config(&out));
    ESP_ERROR_CHECK(gpio_config(&in));

    state_t st = ST_GREEN; int elapsed = 0; bool request = false;
    show(st);
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(50));
        elapsed += 50;
        if (st == ST_GREEN && !request && gpio_get_level(BTN) == 0) {
            request = true;
            ESP_LOGI("fsm", "มีคนกดขอข้ามถนน");
            if (elapsed < DURATION_MS[ST_GREEN] - 2000) elapsed = DURATION_MS[ST_GREEN] - 2000;
        }
        if (elapsed >= DURATION_MS[st]) {          // หมดเวลาของสถานะนี้ -> เปลี่ยนสถานะ
            st = (st == ST_RED) ? ST_GREEN : (state_t)(st + 1);
            elapsed = 0;
            if (st == ST_GREEN) request = false;
            show(st);
        }
    }
}
