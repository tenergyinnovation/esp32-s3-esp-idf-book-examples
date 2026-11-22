/*
 * บทที่ 6 ตัวอย่าง 7: ระบบพัดลมโรงเรือน (ฉบับ GPIO)
 * - อุณหภูมิจำลองจาก potentiometer (GPIO1, ADC) 0-3.3 V แปลงเป็น 20-45 C
 * - LED สีน้ำเงิน (GPIO6) แทนรีเลย์พัดลม
 * - ปุ่ม (GPIO5) สลับโหมด AUTO / MANUAL-ON
 * - hysteresis: เปิดที่ 32 C ปิดที่ 30 C กันพัดลมเปิดปิดถี่
 */
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

#define FAN_GPIO   GPIO_NUM_6
#define BTN_GPIO   GPIO_NUM_5
#define FAN_ON_C   32.0f
#define FAN_OFF_C  30.0f
static const char *TAG = "greenhouse";

void app_main(void)
{
    gpio_config_t out = { .pin_bit_mask = 1ULL << FAN_GPIO, .mode = GPIO_MODE_OUTPUT };
    gpio_config_t in  = { .pin_bit_mask = 1ULL << BTN_GPIO, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    ESP_ERROR_CHECK(gpio_config(&out));
    ESP_ERROR_CHECK(gpio_config(&in));

    adc_oneshot_unit_handle_t adc;
    adc_oneshot_unit_init_cfg_t ucfg = { .unit_id = ADC_UNIT_1 };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&ucfg, &adc));
    adc_oneshot_chan_cfg_t ccfg = { .atten = ADC_ATTEN_DB_12, .bitwidth = ADC_BITWIDTH_DEFAULT };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc, ADC_CHANNEL_0, &ccfg));   // GPIO1 = ADC1 channel 0

    bool manual = false, fan = false; int last_btn = 1;
    while (1) {
        int btn = gpio_get_level(BTN_GPIO);
        if (last_btn == 1 && btn == 0) {
            manual = !manual;
            ESP_LOGI(TAG, "โหมด: %s", manual ? "MANUAL (เปิดพัดลมค้าง)" : "AUTO");
        }
        last_btn = btn;

        int raw = 0;
        ESP_ERROR_CHECK(adc_oneshot_read(adc, ADC_CHANNEL_0, &raw));
        float temp = 20.0f + (raw / 4095.0f) * 25.0f;      // จำลอง 20-45 C

        bool want = manual ? true : (fan ? temp > FAN_OFF_C : temp >= FAN_ON_C);
        if (want != fan) {
            fan = want;
            gpio_set_level(FAN_GPIO, fan);
            ESP_LOGI(TAG, "อุณหภูมิ %.1f C -> พัดลม %s", temp, fan ? "เปิด" : "ปิด");
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
