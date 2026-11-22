/*
 * บทที่ 8 ตัวอย่าง 4: แพ็กเก็ตแบบมี CRC
 * ส่ง 3 แพ็กเก็ตผ่าน UART1 loopback โดยแพ็กเก็ตที่ 2 ถูกทำให้เสีย 1 bit
 */
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "frame.h"

#define U UART_NUM_1
static const char *TAG = "frame";

static void rx_task(void *arg)
{
    frame_parser_t p; frame_parser_reset(&p);
    uint8_t b; bool crc_err;
    while (1) {
        if (uart_read_bytes(U, &b, 1, portMAX_DELAY) != 1) continue;
        if (frame_parser_feed(&p, b, &crc_err)) {
            ESP_LOGI(TAG, "แพ็กเก็ตถูกต้อง: \"%.*s\"", p.len, (char *)p.data);
        } else if (crc_err) {
            ESP_LOGW(TAG, "CRC ไม่ตรง ทิ้งแพ็กเก็ต");
        }
    }
}

void app_main(void)
{
    const uart_config_t cfg = { .baud_rate = 115200, .data_bits = UART_DATA_8_BITS, .parity = UART_PARITY_DISABLE,
                                .stop_bits = UART_STOP_BITS_1, .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, .source_clk = UART_SCLK_DEFAULT };
    ESP_ERROR_CHECK(uart_driver_install(U, 512, 512, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(U, &cfg));
    ESP_ERROR_CHECK(uart_set_pin(U, 17, 18, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    xTaskCreate(rx_task, "rx", 4096, NULL, 10, NULL);

    const char *msgs[] = { "FAN=ON", "TEMP=31.5", "HUM=62" };
    for (int i = 0; i < 3; i++) {
        uint8_t out[FRAME_MAX_LEN + 3];
        size_t n = frame_build(out, (const uint8_t *)msgs[i], strlen(msgs[i]));
        if (i == 1) out[4] ^= 0x01;              // จำลองสัญญาณรบกวนทำให้ 1 bit เพี้ยน
        uart_write_bytes(U, out, n);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
