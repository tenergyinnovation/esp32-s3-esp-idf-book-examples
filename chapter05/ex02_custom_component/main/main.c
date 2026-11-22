/*
 * บทที่ 5 ตัวอย่าง 2: component ของเราเอง
 * โค้ดไฟจราจรอยู่ใน components/traffic_light/ นำไปใช้ซ้ำโปรเจกต์อื่นได้
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "traffic_light.h"

void app_main(void)
{
    traffic_light_t tl;
    ESP_ERROR_CHECK(traffic_light_init(&tl, GPIO_NUM_4, GPIO_NUM_5, GPIO_NUM_6));
    while (1) {
        traffic_light_set(&tl, TL_GREEN);  vTaskDelay(pdMS_TO_TICKS(3000));
        traffic_light_set(&tl, TL_YELLOW); vTaskDelay(pdMS_TO_TICKS(1000));
        traffic_light_set(&tl, TL_RED);    vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
