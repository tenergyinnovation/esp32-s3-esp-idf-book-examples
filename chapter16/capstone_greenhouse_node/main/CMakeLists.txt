idf_component_register(SRCS "main.c" "wifi_connect.c" "oled.c" "sht31.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES esp_wifi esp_netif esp_event nvs_flash esp_driver_i2c esp_lcd esp_driver_ledc esp_adc app_update esp_app_format nvs_flash esp_timer)
