/*
 * บทที่ 14 ตัวอย่าง 7: fail-safe state machine
 * NORMAL   : ควบคุมพัดลมตามอุณหภูมิ
 * DEGRADED : อ่านเซนเซอร์พลาด 1-4 ครั้งติด -> ใช้ค่าล่าสุดที่ดี
 * FAILSAFE : พลาด 5 ครั้งติด หรือค่าผิดธรรมชาติ -> เปิดพัดลมเต็มที่ (ร้อนเกินอันตรายกว่าพัดลมเปลืองไฟ)
 * ตัวต้านทานปรับค่า (GPIO1) จำลองเซนเซอร์: หมุนสุดซ้าย (< 0.1 V) = สายขาด
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

typedef enum { ST_NORMAL, ST_DEGRADED, ST_FAILSAFE } st_t;
static const char *NAMES[] = { "NORMAL", "DEGRADED", "FAILSAFE" };
#define FAN GPIO_NUM_6
static adc_oneshot_unit_handle_t s_adc;

static bool read_sensor(float *t)          /* คืน false ถ้าค่าใช้ไม่ได้ */
{
    int raw;
    if (adc_oneshot_read(s_adc, ADC_CHANNEL_0, &raw) != ESP_OK || raw < 120) return false;   // ใกล้ 0 V = สายขาด
    *t = 20.0f + raw * 25.0f / 4095.0f;
    return *t < 60.0f;
}

void app_main(void)
{
    gpio_config_t out = { .pin_bit_mask = 1ULL << FAN, .mode = GPIO_MODE_OUTPUT };
    ESP_ERROR_CHECK(gpio_config(&out));
    adc_oneshot_unit_init_cfg_t u = { .unit_id = ADC_UNIT_1 };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&u, &s_adc));
    adc_oneshot_chan_cfg_t c = { .atten = ADC_ATTEN_DB_12, .bitwidth = ADC_BITWIDTH_DEFAULT };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(s_adc, ADC_CHANNEL_0, &c));

    st_t st = ST_NORMAL, last_st = -1; int fails = 0; float good_t = 25, t; bool fan = false;
    while (1) {
        if (read_sensor(&t)) { good_t = t; fails = 0; st = ST_NORMAL; }
        else if (++fails >= 5) st = ST_FAILSAFE;
        else st = ST_DEGRADED;

        if (st == ST_FAILSAFE) fan = true;
        else fan = fan ? good_t > 30.0f : good_t >= 32.0f;        /* hysteresis 30/32 C */
        gpio_set_level(FAN, fan);
        if (st != last_st) {
            ESP_LOGW("failsafe", "สถานะ -> %s (พลาดติดกัน %d)", NAMES[st], fails);
            last_st = st;
        }
        ESP_LOGI("failsafe", "[%s] T=%.1f C พัดลม=%s", NAMES[st], good_t, fan ? "เปิด" : "ปิด");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
