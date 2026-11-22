/*
 * บทที่ 9 ตัวอย่าง 4: ADC + calibration
 * GPIO1 = ADC1 channel 0, attenuation 12 dB อ่านได้ราว 0-3.1 V
 * แปลงค่า raw (0-4095) เป็น mV ด้วย calibration ที่โรงงานบันทึกไว้ใน eFuse
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"

static const char *TAG = "adc";

void app_main(void)
{
    adc_oneshot_unit_handle_t adc;
    adc_oneshot_unit_init_cfg_t ucfg = { .unit_id = ADC_UNIT_1 };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&ucfg, &adc));
    adc_oneshot_chan_cfg_t ccfg = { .atten = ADC_ATTEN_DB_12, .bitwidth = ADC_BITWIDTH_DEFAULT };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc, ADC_CHANNEL_0, &ccfg));

    adc_cali_handle_t cali = NULL;
    adc_cali_curve_fitting_config_t kcfg = { .unit_id = ADC_UNIT_1, .chan = ADC_CHANNEL_0,
                                             .atten = ADC_ATTEN_DB_12, .bitwidth = ADC_BITWIDTH_DEFAULT };
    bool calibrated = adc_cali_create_scheme_curve_fitting(&kcfg, &cali) == ESP_OK;
    if (!calibrated) ESP_LOGW(TAG, "ไม่มีข้อมูล calibration ใช้สูตรประมาณแทน");

    while (1) {
        int raw = 0, mv = 0, sum = 0;
        for (int i = 0; i < 16; i++) {                 // เฉลี่ย 16 ครั้ง ลดสัญญาณรบกวน
            ESP_ERROR_CHECK(adc_oneshot_read(adc, ADC_CHANNEL_0, &raw));
            sum += raw;
        }
        raw = sum / 16;
        if (calibrated) adc_cali_raw_to_voltage(cali, raw, &mv);
        else mv = raw * 3100 / 4095;
        ESP_LOGI(TAG, "raw=%4d  แรงดัน=%4d mV  (%3d%%)", raw, mv, raw * 100 / 4095);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
