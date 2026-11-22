/*
 * บทที่ 8 ตัวอย่าง 3: ตัวแปลคำสั่ง (command parser)
 * พิมพ์ใน Serial Monitor: HELP, LED ON, LED OFF, STATUS แล้วกด Enter
 */
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"

#define LED GPIO_NUM_4
#define CMD_LINE_MAX 32
static const char *TAG = "cmd";
static int s_led = 0;

static void handle(char *line)
{
    // ตัดช่องว่างท้ายบรรทัด
    for (int i = strlen(line) - 1; i >= 0 && isspace((unsigned char)line[i]); i--) line[i] = 0;
    if (line[0] == 0) return;
    if (strcasecmp(line, "LED ON") == 0)       { s_led = 1; gpio_set_level(LED, 1); ESP_LOGI(TAG, "OK LED=ON"); }
    else if (strcasecmp(line, "LED OFF") == 0) { s_led = 0; gpio_set_level(LED, 0); ESP_LOGI(TAG, "OK LED=OFF"); }
    else if (strcasecmp(line, "STATUS") == 0)  { ESP_LOGI(TAG, "LED=%s uptime=%lld s", s_led ? "ON" : "OFF", esp_timer_get_time() / 1000000); }
    else if (strcasecmp(line, "HELP") == 0)    { ESP_LOGI(TAG, "คำสั่ง: LED ON | LED OFF | STATUS | HELP"); }
    else                                       { ESP_LOGW(TAG, "ไม่รู้จักคำสั่ง '%s' พิมพ์ HELP", line); }
}

void app_main(void)
{
    gpio_config_t out = { .pin_bit_mask = 1ULL << LED, .mode = GPIO_MODE_OUTPUT };
    ESP_ERROR_CHECK(gpio_config(&out));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, 512, 0, 0, NULL, 0));
    ESP_LOGI(TAG, "พิมพ์ HELP แล้วกด Enter");

    char line[CMD_LINE_MAX]; int pos = 0; uint8_t ch;
    while (1) {
        if (uart_read_bytes(UART_NUM_0, &ch, 1, portMAX_DELAY) != 1) continue;
        if (ch == '\r' || ch == '\n') {          // จบบรรทัด -> แปลคำสั่ง
            line[pos] = 0; handle(line); pos = 0;
        } else if (pos < CMD_LINE_MAX - 1) {
            line[pos++] = ch;
        } else {                                  // ยาวเกิน -> ทิ้งทั้งบรรทัด
            ESP_LOGW(TAG, "คำสั่งยาวเกิน %d ตัวอักษร", CMD_LINE_MAX - 1); pos = 0;
        }
    }
}
