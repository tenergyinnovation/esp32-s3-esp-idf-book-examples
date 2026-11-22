/*
 * บทที่ 8 ตัวอย่าง 5: inter-byte timeout
 * ถ้า byte ถัดไปไม่มาภายใน 20 ms ถือว่าแพ็กเก็ตขาด เริ่มรอแพ็กเก็ตใหม่
 * ทดสอบ: ส่งครึ่งแพ็กเก็ต (สายหลุด) แล้วตามด้วยแพ็กเก็ตเต็ม
 */
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "frame.h"

#define U UART_NUM_1
#define BYTE_TIMEOUT_US (20 * 1000)
static const char *TAG = "timeout";

static void rx_task(void *arg)
{
    frame_parser_t p; frame_parser_reset(&p);
    int64_t last = 0; uint8_t b; bool crc_err;
    while (1) {
        int n = uart_read_bytes(U, &b, 1, pdMS_TO_TICKS(10));
        int64_t now = esp_timer_get_time();
        if (p.state != WAIT_START && now - last > BYTE_TIMEOUT_US) {
            ESP_LOGW(TAG, "timeout กลางแพ็กเก็ต (ได้ %d/%d bytes) เริ่มใหม่", p.pos, p.len);
            frame_parser_reset(&p);
        }
        if (n != 1) continue;
        last = now;
        if (frame_parser_feed(&p, b, &crc_err)) ESP_LOGI(TAG, "ได้แพ็กเก็ต: \"%.*s\"", p.len, (char *)p.data);
        else if (crc_err) ESP_LOGW(TAG, "CRC ผิด");
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

    uint8_t out[FRAME_MAX_LEN + 3];
    size_t n = frame_build(out, (const uint8_t *)"PUMP=OFF", 8);
    uart_write_bytes(U, out, 5);                 // ส่งแค่ 5 จาก 11 bytes (สายหลุด)
    vTaskDelay(pdMS_TO_TICKS(200));
    uart_write_bytes(U, out, n);                 // ส่งใหม่ทั้งแพ็กเก็ต
}
