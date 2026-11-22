#include "traffic_light.h"
#include "esp_log.h"

static const char *TAG = "traffic_light";

esp_err_t traffic_light_init(traffic_light_t *tl, gpio_num_t red, gpio_num_t yellow, gpio_num_t green)
{
    tl->red = red; tl->yellow = yellow; tl->green = green;
    gpio_config_t cfg = {
        .pin_bit_mask = (1ULL << red) | (1ULL << yellow) | (1ULL << green),
        .mode = GPIO_MODE_OUTPUT,
    };
    esp_err_t err = gpio_config(&cfg);
    traffic_light_set(tl, TL_OFF);
    return err;
}

void traffic_light_set(traffic_light_t *tl, tl_state_t s)
{
    static const char *names[] = { "ดับ", "แดง", "เหลือง", "เขียว" };
    gpio_set_level(tl->red,    s == TL_RED);
    gpio_set_level(tl->yellow, s == TL_YELLOW);
    gpio_set_level(tl->green,  s == TL_GREEN);
    tl->state = s;
    ESP_LOGI(TAG, "ไฟ: %s", names[s]);
}
