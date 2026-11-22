/*
 * บทที่ 17 ตัวอย่าง 5: กราฟิกบนจอ OLED SSD1306 128x64
 * หน้าจอสลับทุก 4 วินาที:
 *   1) เกจแถบ (bar gauge) แสดงค่า potentiometer เป็น %
 *   2) กราฟเส้นย้อนหลัง 128 จุด (เลื่อนเหมือนเครื่องวัดคลื่นหัวใจ)
 *   3) ลูกบอลเด้ง เพื่อดูอัตรา frame ต่อวินาที (FPS)
 * หลักการ: วาดทุกอย่างลง buffer ใน RAM ก่อน แล้วค่อย oled_flush() ครั้งเดียวต่อเฟรม จอจึงไม่กะพริบ
 */
#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "oled.h"

static const char *TAG = "gfx";
static adc_oneshot_unit_handle_t s_adc;
static uint8_t s_hist[128];

static int read_pct(void)
{
    int raw = 0;
    adc_oneshot_read(s_adc, ADC_CHANNEL_0, &raw);
    return raw * 100 / 4095;
}

static void draw_line(int x0, int y0, int x1, int y1)        // Bresenham: วาดเส้นด้วยจำนวนเต็มล้วน
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1, dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1, err = dx + dy;
    while (1) {
        oled_pixel(x0, y0, true);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

static void screen_gauge(int pct)
{
    char s[16];
    oled_text(0, 0, "BAR GAUGE");
    snprintf(s, sizeof s, "%3d%%", pct);
    oled_text_big(40, 2, s);
    oled_rect(4, 44, 120, 14, false);                          // กรอบ
    oled_rect(6, 46, pct * 116 / 100, 10, true);               // แถบเติม
}

static void screen_chart(void)
{
    oled_text(0, 0, "TREND");
    for (int x = 1; x < 128; x++) draw_line(x - 1, 63 - s_hist[x - 1] * 50 / 100, x, 63 - s_hist[x] * 50 / 100);
}

static void screen_ball(int frame, int fps)
{
    static float x = 10, y = 20, vx = 2.3f, vy = 1.7f;
    char s[16];
    x += vx; y += vy;
    if (x < 3 || x > 124) vx = -vx;
    if (y < 11 || y > 60) vy = -vy;
    oled_rect((int)x - 3, (int)y - 3, 6, 6, true);
    snprintf(s, sizeof s, "FPS %d", fps);
    oled_text(0, 0, s);
}

void app_main(void)
{
    i2c_master_bus_config_t b = { .i2c_port = I2C_NUM_0, .sda_io_num = 8, .scl_io_num = 9, .clk_source = I2C_CLK_SRC_DEFAULT,
                                  .glitch_ignore_cnt = 7, .flags.enable_internal_pullup = true };
    i2c_master_bus_handle_t bus;
    ESP_ERROR_CHECK(i2c_new_master_bus(&b, &bus));
    ESP_ERROR_CHECK(oled_init(bus, 0x3C));
    adc_oneshot_unit_init_cfg_t u = { .unit_id = ADC_UNIT_1 };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&u, &s_adc));
    adc_oneshot_chan_cfg_t c = { .atten = ADC_ATTEN_DB_12, .bitwidth = ADC_BITWIDTH_DEFAULT };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(s_adc, ADC_CHANNEL_0, &c));

    int frame = 0, fps = 0, frames_this_sec = 0;
    int64_t t_sec = esp_timer_get_time();
    while (1) {
        int pct = read_pct();
        for (int i = 0; i < 127; i++) s_hist[i] = s_hist[i + 1];  // เลื่อนกราฟไปทางซ้าย
        s_hist[127] = pct;

        int screen = (int)(esp_timer_get_time() / 4000000) % 3;
        oled_clear();
        if (screen == 0) screen_gauge(pct);
        else if (screen == 1) screen_chart();
        else screen_ball(frame, fps);
        ESP_ERROR_CHECK(oled_flush());

        frame++; frames_this_sec++;
        if (esp_timer_get_time() - t_sec >= 1000000) {
            fps = frames_this_sec; frames_this_sec = 0; t_sec = esp_timer_get_time();
            ESP_LOGI(TAG, "หน้าจอ %d  ค่า %d%%  FPS %d", screen + 1, pct, fps);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
