/*
 * บทที่ 8 ตัวอย่าง 1: UART echo บน UART0 (พอร์ตเดียวกับ Serial Monitor)
 * พิมพ์อะไรใน monitor บอร์ดจะส่งกลับเป็นตัวพิมพ์ใหญ่
 */
#include <ctype.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"

#define UART   UART_NUM_0
#define BUF    256

void app_main(void)
{
    // console ใช้ UART0 อยู่แล้ว ติดตั้ง driver เพิ่มเพื่อ "อ่าน" ได้
    ESP_ERROR_CHECK(uart_driver_install(UART, BUF * 2, 0, 0, NULL, 0));
    ESP_LOGI("echo", "พิมพ์ข้อความใน Serial Monitor ได้เลย");

    uint8_t data[BUF];
    while (1) {
        int len = uart_read_bytes(UART, data, sizeof(data), pdMS_TO_TICKS(100));
        for (int i = 0; i < len; i++) data[i] = toupper(data[i]);
        if (len > 0) uart_write_bytes(UART, data, len);
    }
}
