/*
 * บทที่ 15 ตัวอย่าง 1: debug ด้วย JTAG
 * เสียบสายที่พอร์ต "USB" (ไม่ใช่ UART) ESP32-S3 มี USB-JTAG ในตัว ไม่ต้องซื้อ debugger
 * ใน VS Code: ESP-IDF: Select OpenOCD Board Configuration -> ESP32-S3 chip (via builtin USB-JTAG)
 * แล้วกด F5 ตั้ง breakpoint ที่บรรทัด total += ... เพื่อดูค่าตัวแปรทีละรอบ
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static int average(const int *v, int n)
{
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += v[i];                 // <- ตั้ง breakpoint ตรงนี้ ดู i, v[i], total
    }
    return total / n;
}

void app_main(void)
{
    const int readings[] = { 28, 29, 31, 35, 27 };
    while (1) {
        int avg = average(readings, 5);
        ESP_LOGI("debug", "ค่าเฉลี่ย = %d", avg);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
