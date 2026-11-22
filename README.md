# esp32-s3-esp-idf-book-examples

โค้ดตัวอย่างประกอบหนังสือ **คู่มือการพัฒนา ESP32-S3 ด้วย ESP-IDF v6.1 และ VS Code – จากพื้นฐานฮาร์ดแวร์สู่การพัฒนาเฟิร์มแวร์ที่ใช้งานจริง**
โดย อุเทน บุญเลียม · Tenergy Innovation Co., Ltd.

| รายการ | ค่า |
|---|---|
| บอร์ดอ้างอิง | ESP32-S3-DevKitC-1-N16R8 (Flash 16 MB, PSRAM 8 MB) |
| Framework | ESP-IDF v6.1 |
| Target | `esp32s3` |
| ภาษา | C |
| เครื่องมือ | VS Code + ESP-IDF Extension, Wokwi for VS Code |
| ระบบที่ทดสอบ | macOS |

> สถานะ: ครบ 17 บท 92 ตัวอย่าง ทุกตัวอย่าง build ผ่านด้วย ESP-IDF v6.1 (ตรวจโดย GitHub Actions ทุก commit)

## วิธีใช้ตัวอย่าง

```bash
git clone https://github.com/tenergyinnovation/esp32-s3-esp-idf-book-examples.git
cd esp32-s3-esp-idf-book-examples/chapter03/ex01_hello_world
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออกจาก monitor: Ctrl + ]
```

- ชื่อพอร์ตบน macOS ขึ้นกับชิป USB-to-UART ของบอร์ด ดูด้วย `ls /dev/cu.*`
- ตัวอย่างที่มีไฟล์ `diagram.json` และ `wokwi.toml` รันบน Wokwi ได้: build ก่อน แล้วสั่ง **Wokwi: Start Simulator** ใน VS Code

## โครงสร้างของแต่ละตัวอย่าง

```text
chapterNN/exMM_name/
├── CMakeLists.txt
├── main/                 โค้ดหลัก
├── sdkconfig.defaults    ค่าตั้งของบอร์ด N16R8 (ไม่ commit sdkconfig)
├── diagram.json          วงจรสำหรับ Wokwi (ถ้ามี)
├── wokwi.toml            ตั้งค่า Wokwi (ถ้ามี)
└── README.md             วิธีต่อวงจรและผลที่คาดหวังจาก Serial Monitor
```

## สารบัญตัวอย่าง

ป้าย: **W** = รันบน Wokwi ได้และทดสอบบนบอร์ดจริง, **B** = ต้องใช้บอร์ดจริง

### ช่วงที่ 1 เริ่มต้นใช้งาน

**บทที่ 1 รู้จัก ESP32-S3 และบอร์ด DevKitC-1** — [`chapter01/`](chapter01/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `act01_board_inspection` | กิจกรรม: ตรวจบอร์ดจริง อ่านชื่อโมดูล และหาตำแหน่งปุ่ม/LED | B |
| `act02_pin_map_quiz` | กิจกรรม: หาขาที่ใช้ได้และขาที่ห้ามใช้จากแผนผังขา | — |
| `act03_wokwi_first_look` | กิจกรรม: เปิดโปรเจกต์ Wokwi ตัวอย่างและกด Start | W |

**บทที่ 2 ติดตั้ง ESP-IDF v6.1, VS Code และ Wokwi บน macOS** — [`chapter02/`](chapter02/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `act01_check_tools` | กิจกรรม: ตรวจเวอร์ชันเครื่องมือครบชุด | B |
| `act02_find_serial_port` | กิจกรรม: หาชื่อพอร์ต /dev/cu.* ของบอร์ด | B |
| `act03_wokwi_license` | กิจกรรม: เปิดใช้ Wokwi ใน VS Code | W |

**บทที่ 3 โปรเจกต์แรก: Hello World และไฟกะพริบ** — [`chapter03/`](chapter03/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_hello_world` | พิมพ์ข้อความแรกออก Serial Monitor | W |
| `ex02_chip_info` | แสดงจำนวน core, ขนาด Flash และ PSRAM ของบอร์ด | W |
| `ex03_blink_external_led` | กะพริบ LED ภายนอก (ไฟเลี้ยวรถ) | W |
| `ex04_rgb_led_onboard` | สั่ง RGB LED บนบอร์ด (GPIO38) เปลี่ยนสี | W |
| `ex05_restart_counter` | นับและแสดงสาเหตุการรีสตาร์ต | W |

### ช่วงที่ 2 พื้นฐานการเขียนโปรแกรม ESP-IDF

**บทที่ 4 ภาษา C ที่จำเป็นสำหรับ ESP-IDF** — [`chapter04/`](chapter04/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_data_types` | ชนิดข้อมูลและ sizeof บน ESP32-S3 | W |
| `ex02_struct_sensor_record` | เก็บข้อมูลเซนเซอร์ด้วย struct และ enum | W |
| `ex03_const_static_counter` | const กันแก้ค่า และ static นับสะสม | W |
| `ex04_volatile_button_flag` | volatile กับปุ่มกดผ่าน interrupt | W |
| `ex05_error_handling` | ตรวจ esp_err_t แบบปลอดภัย | W |
| `ex06_log_levels` | ใช้ Log ระดับต่างๆ และกรองตาม tag | W |
| `ex07_memory_regions` | ดูว่าตัวแปรแต่ละแบบอยู่ตรงไหนในหน่วยความจำ | W |

**บทที่ 5 ระบบ Build, Component และ Configuration** — [`chapter05/`](chapter05/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_multi_file` | แยกโค้ดเป็นหลายไฟล์ .c/.h | W |
| `ex02_custom_component` | สร้าง component ไฟจราจรใช้ซ้ำได้ | W |
| `ex03_kconfig_option` | เพิ่มเมนูตั้งค่าเองใน menuconfig | W |
| `ex04_sdkconfig_defaults` | ตั้งค่า Flash 16 MB และ PSRAM ด้วย sdkconfig.defaults | B |
| `ex05_managed_component` | ใช้ component led_strip จาก Registry | W |
| `ex06_build_size_report` | อ่านรายงานขนาดโปรแกรม idf.py size | W |

**บทที่ 6 GPIO, Interrupt, Timer และ State Machine** — [`chapter06/`](chapter06/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_led_output` | เปิดปิด LED หลายดวง | W |
| `ex02_button_polling` | อ่านปุ่มแบบวนถาม | W |
| `ex03_button_interrupt_queue` | ปุ่มแบบ interrupt ส่งเหตุการณ์ผ่าน queue | W |
| `ex04_debounce` | กำจัดปุ่มเด้งด้วยซอฟต์แวร์ | W |
| `ex05_esp_timer_periodic` | ตั้งเวลาทำงานซ้ำทุก 500 ms | W |
| `ex06_traffic_light_fsm` | ไฟจราจรด้วย state machine | W |
| `ex07_greenhouse_fan_logic` | งานจริง: ควบคุมพัดลมโรงเรือนตามปุ่มและเวลา | W |

**บทที่ 7 FreeRTOS บน ESP32-S3 แบบ Dual-Core** — [`chapter07/`](chapter07/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_two_tasks` | สอง task ทำงานพร้อมกัน | W |
| `ex02_task_priority` | ดูผลของ priority | W |
| `ex03_queue_producer_consumer` | คนผลิต-คนใช้ข้อมูลผ่าน queue | W |
| `ex04_mutex_shared_counter` | แก้ race condition ด้วย mutex | W |
| `ex05_event_group` | รอหลายเงื่อนไขพร้อมกันด้วย event group | W |
| `ex06_pin_to_core` | ผูก task กับ core 0 และ core 1 | B |
| `ex07_task_watchdog` | ให้ watchdog จับ task ที่ค้าง | W |
| `ex08_stack_watermark` | วัดว่า task ใช้ stack ไปเท่าไร | W |

### ช่วงที่ 3 Peripheral และ Hardware Interface

**บทที่ 8 UART และการออกแบบ Protocol** — [`chapter08/`](chapter08/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_uart_echo` | รับแล้วส่งกลับ (echo) | W |
| `ex02_uart_event_queue` | รับข้อมูลด้วย event queue | W |
| `ex03_command_parser` | คำสั่งแบบข้อความ เช่น LED ON | W |
| `ex04_frame_crc` | แพ็กเก็ตมี header, length และ CRC | W |
| `ex05_timeout_recovery` | จัดการข้อมูลขาดหายกลางทาง | W |
| `ex06_uart_bridge` | ส่งต่อข้อมูลระหว่าง UART สองพอร์ต | B |

**บทที่ 9 I2C, ADC, PWM และ SPI กับเซนเซอร์จริง** — [`chapter09/`](chapter09/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_i2c_scanner` | ค้นหาอุปกรณ์ทุกตัวบนบัส I2C | W |
| `ex02_sht31_temp_humidity` | อ่านอุณหภูมิและความชื้นจาก SHT31 | B |
| `ex03_oled_text` | แสดงข้อความบน OLED | W |
| `ex04_adc_potentiometer` | อ่านค่า potentiometer เป็นมิลลิโวลต์ | W |
| `ex05_ledc_fade` | หรี่ไฟ LED ด้วย PWM | W |
| `ex06_spi_loopback` | ทดสอบ SPI แบบเชื่อมขาวนกลับ | B |
| `ex07_greenhouse_station` | งานจริง: เซนเซอร์ + OLED + พัดลม PWM | W |

### ช่วงที่ 4 Network และ IoT

**บทที่ 10 Wi-Fi, IP Network และ Time Sync** — [`chapter10/`](chapter10/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_wifi_station` | เชื่อมต่อ Wi-Fi บ้าน | W |
| `ex02_wifi_reconnect_backoff` | หลุดแล้วต่อใหม่แบบเว้นระยะ | W |
| `ex03_softap` | บอร์ดเป็นจุดปล่อย Wi-Fi เอง | B |
| `ex04_wifi_scan` | สแกนหา Wi-Fi รอบตัว | W |
| `ex05_sntp_time` | ตั้งนาฬิกาจากอินเทอร์เน็ต | W |
| `ex06_http_server_status` | หน้าเว็บแสดงสถานะบอร์ด | W |

**บทที่ 11 HTTP, HTTPS, MQTT และ JSON** — [`chapter11/`](chapter11/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_http_get` | ดึงข้อมูลจากเว็บด้วย HTTP | W |
| `ex02_https_cert_bundle` | เชื่อมต่อ HTTPS อย่างปลอดภัย | W |
| `ex03_mqtt_basic` | publish/subscribe กับ broker | W |
| `ex04_mqtt_qos_lwt` | QoS และข้อความสั่งเสีย (LWT) | W |
| `ex05_mqtt_tls` | MQTT ผ่าน TLS | W |
| `ex06_json_telemetry` | ส่งค่าเซนเซอร์เป็น JSON | W |
| `ex07_offline_queue` | เก็บข้อมูลไว้ส่งเมื่อเน็ตกลับมา | W |

**บทที่ 12 Bluetooth Low Energy และ Provisioning** — [`chapter12/`](chapter12/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_ble_advertise` | ประกาศชื่ออุปกรณ์ให้มือถือเห็น | B |
| `ex02_gatt_read` | ให้มือถืออ่านค่าจากบอร์ด | B |
| `ex03_gatt_notify_sensor` | ส่งค่าเซนเซอร์แบบ notify | B |
| `ex04_gatt_write_led` | มือถือสั่งเปิดปิด LED | B |
| `ex05_wifi_provisioning_ble` | ตั้งค่า Wi-Fi ผ่านแอปมือถือ | B |

### ช่วงที่ 5 เก็บข้อมูลและออกแบบระบบจริง

**บทที่ 13 NVS, Partition Table และ File Storage** — [`chapter13/`](chapter13/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_nvs_boot_counter` | นับจำนวนครั้งที่เปิดเครื่องแม้ปิดไฟ | W |
| `ex02_nvs_config_struct` | เก็บค่าตั้งเป็นชุดพร้อมเลขเวอร์ชัน | W |
| `ex03_custom_partition_16mb` | ออกแบบ partition table สำหรับ 16 MB | B |
| `ex04_fatfs_files` | เขียนอ่านไฟล์ใน Flash (FAT) | B |
| `ex05_factory_reset_button` | กดปุ่มค้างเพื่อล้างค่ากลับโรงงาน | W |
| `ex06_csv_data_logger` | บันทึกค่าเซนเซอร์เป็นไฟล์ CSV | B |

**บทที่ 14 PSRAM, Power Management และ Reliability** — [`chapter14/`](chapter14/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_psram_alloc` | จองหน่วยความจำใหญ่ใน PSRAM | B |
| `ex02_heap_monitor` | เฝ้าดู heap คงเหลือ | W |
| `ex03_light_sleep` | งีบสั้นๆ ประหยัดไฟ | B |
| `ex04_deep_sleep_timer` | หลับลึกแล้วตื่นตามเวลา | W |
| `ex05_deep_sleep_button` | ตื่นเมื่อกดปุ่ม | W |
| `ex06_reset_reason_watchdog` | บันทึกสาเหตุการรีเซ็ต | B |
| `ex07_failsafe_state_machine` | งานจริง: พัดลมกลับสู่สถานะปลอดภัยเมื่อเซนเซอร์เสีย | W |

### ช่วงที่ 6 จาก Prototype สู่ Production

**บทที่ 15 Debugging, Testing และการจัดการ Source Code** — [`chapter15/`](chapter15/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_jtag_breakpoint` | หยุดโปรแกรมด้วย breakpoint | B |
| `ex02_panic_backtrace` | จงใจทำให้ crash แล้วอ่าน backtrace | W |
| `ex03_core_dump` | เก็บ core dump ไว้วิเคราะห์ | B |
| `ex04_unit_test` | ทดสอบฟังก์ชันอัตโนมัติ | W |
| `ex05_ci_build` | ตั้ง GitHub Actions ให้ build ทุก commit | — |
| `ex06_version_info` | แสดงเวอร์ชันและเวลา build | W |

**บทที่ 16 OTA, Security และ Capstone Project** — [`chapter16/`](chapter16/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_ota_https` | อัปเดต firmware ผ่าน HTTPS | B |
| `ex02_ota_rollback` | ย้อนกลับเวอร์ชันเดิมอัตโนมัติ | B |
| `ex03_security_check` | ตรวจสถานะ Secure Boot/Flash Encryption (อ่านอย่างเดียว) | B |
| `capstone_greenhouse_node` | Capstone: โหนดโรงเรือนครบวงจร | W |

**บทที่ 17 USB และจอแสดงผล: ความสามารถพิเศษของ ESP32-S3** — [`chapter17/`](chapter17/)

| ตัวอย่าง | สิ่งที่ทำ | รัน |
|---|---|---|
| `ex01_usb_cdc` | Serial ผ่าน USB OTG | B |
| `ex02_usb_hid_keyboard` | กดปุ่มแล้วพิมพ์ข้อความลงคอมพิวเตอร์ | B |
| `ex03_usb_msc` | ให้คอมพิวเตอร์เห็นบอร์ดเป็นไดรฟ์ | B |
| `ex04_rgb_led_effects` | เอฟเฟกต์ไฟ RGB | W |
| `ex05_oled_graphics` | กราฟิกบน OLED: เกจ กราฟ แอนิเมชัน | W |

## License

โค้ดตัวอย่างเผยแพร่ภายใต้ MIT License (ดู [LICENSE](LICENSE)) ส่วนเนื้อหาหนังสือเป็นลิขสิทธิ์ของผู้เขียน
