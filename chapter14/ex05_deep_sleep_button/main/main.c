/*
 * บทที่ 14 ตัวอย่าง 5: ตื่นด้วยปุ่ม
 * GPIO5 เป็น RTC GPIO ใช้ปลุกจาก deep sleep ได้ กดปุ่ม (ดึงลง GND) -> ตื่น
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "esp_log.h"

#define WAKE_GPIO GPIO_NUM_5

void app_main(void)
{
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) ESP_LOGI("btn", "ตื่นเพราะมีคนกดปุ่ม!");
    else ESP_LOGI("btn", "เปิดเครื่องครั้งแรก");

    vTaskDelay(pdMS_TO_TICKS(3000));                   // ทำงานสักพัก
    ESP_ERROR_CHECK(rtc_gpio_pullup_en(WAKE_GPIO));    // pull-up ที่ทำงานได้ขณะหลับ
    ESP_ERROR_CHECK(rtc_gpio_pulldown_dis(WAKE_GPIO));
    ESP_ERROR_CHECK(esp_sleep_enable_ext0_wakeup(WAKE_GPIO, 0));   // 0 = ตื่นเมื่อขาเป็น LOW
    ESP_LOGI("btn", "หลับลึก กดปุ่มที่ GPIO5 เพื่อปลุก");
    esp_deep_sleep_start();
}
