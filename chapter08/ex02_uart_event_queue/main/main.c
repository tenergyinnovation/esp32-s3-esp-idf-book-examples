/*
 * บทที่ 8 ตัวอย่าง 2: UART event queue
 * UART1: TX=GPIO17, RX=GPIO18 ต่อสายวนกลับ (loopback) เพื่อทดสอบโดยไม่ต้องมีอุปกรณ์อื่น
 * task หนึ่งส่งข้อความ อีก task รอ "เหตุการณ์" จาก driver: มีข้อมูล, buffer ล้น, frame error
 */
#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"

#define U      UART_NUM_1
#define TX_PIN 17
#define RX_PIN 18
static QueueHandle_t s_uart_q;
static const char *TAG = "uart_evt";

static void sender(void *arg)
{
    for (int n = 1; ; n++) {
        char msg[48];
        int len = snprintf(msg, sizeof(msg), "TEMP=%d.%d\n", 25 + n % 5, n % 10);
        uart_write_bytes(U, msg, len);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void receiver(void *arg)
{
    uart_event_t e; uint8_t buf[128];
    while (1) {
        if (!xQueueReceive(s_uart_q, &e, portMAX_DELAY)) continue;
        switch (e.type) {
        case UART_DATA: {
            int len = uart_read_bytes(U, buf, e.size < sizeof(buf) - 1 ? e.size : sizeof(buf) - 1, 0);
            buf[len] = 0;
            ESP_LOGI(TAG, "ได้ %d bytes: %s", len, (char *)buf);
            break; }
        case UART_FIFO_OVF:
        case UART_BUFFER_FULL:
            ESP_LOGW(TAG, "ข้อมูลล้น ล้าง buffer");
            uart_flush_input(U); xQueueReset(s_uart_q); break;
        case UART_FRAME_ERR:  ESP_LOGW(TAG, "frame error (baud rate ไม่ตรง?)"); break;
        case UART_PARITY_ERR: ESP_LOGW(TAG, "parity error"); break;
        default: break;
        }
    }
}

void app_main(void)
{
    const uart_config_t cfg = {
        .baud_rate = 115200, .data_bits = UART_DATA_8_BITS, .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1, .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, .source_clk = UART_SCLK_DEFAULT,
    };
    ESP_ERROR_CHECK(uart_driver_install(U, 1024, 1024, 20, &s_uart_q, 0));
    ESP_ERROR_CHECK(uart_param_config(U, &cfg));
    ESP_ERROR_CHECK(uart_set_pin(U, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    xTaskCreate(receiver, "rx", 4096, NULL, 10, NULL);
    xTaskCreate(sender, "tx", 3072, NULL, 5, NULL);
}
