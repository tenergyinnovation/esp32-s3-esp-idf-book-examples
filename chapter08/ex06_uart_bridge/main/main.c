/*
 * บทที่ 8 ตัวอย่าง 6: UART bridge
 * ข้อมูลจาก Serial Monitor (UART0) ส่งต่อไปอุปกรณ์ภายนอกที่ UART1 (GPIO17/18) และกลับกัน
 * ใช้คุยกับโมดูล GPS, RS485 หรือ modem ผ่านคอมพิวเตอร์
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

typedef struct { uart_port_t from, to; } route_t;

static void pump(void *arg)
{
    const route_t *r = arg; uint8_t buf[128];
    while (1) {
        int n = uart_read_bytes(r->from, buf, sizeof(buf), pdMS_TO_TICKS(20));
        if (n > 0) uart_write_bytes(r->to, buf, n);
    }
}

void app_main(void)
{
    const uart_config_t cfg = { .baud_rate = 9600, .data_bits = UART_DATA_8_BITS, .parity = UART_PARITY_DISABLE,
                                .stop_bits = UART_STOP_BITS_1, .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, .source_clk = UART_SCLK_DEFAULT };
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, 1024, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &cfg));             // อุปกรณ์ภายนอก 9600 baud
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, 17, 18, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    static const route_t a = { UART_NUM_0, UART_NUM_1 }, b = { UART_NUM_1, UART_NUM_0 };
    xTaskCreate(pump, "pc_to_dev", 3072, (void *)&a, 5, NULL);
    xTaskCreate(pump, "dev_to_pc", 3072, (void *)&b, 5, NULL);
}
