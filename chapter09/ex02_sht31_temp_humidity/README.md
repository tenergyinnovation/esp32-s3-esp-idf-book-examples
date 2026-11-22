# ex02_sht31_temp_humidity

**บทที่ 9** · อ่านอุณหภูมิและความชื้นจาก SHT31

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## การต่อวงจร

| อุปกรณ์ | ขาอุปกรณ์ | ESP32-S3 |
|---|---|---|
| SHT31 / OLED | SDA | GPIO8 |
| SHT31 / OLED | SCL | GPIO9 |
| SHT31 / OLED | VCC | 3V3 |
| SHT31 / OLED | GND | GND |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) sht31: อุณหภูมิ 27.84 C  ความชื้น 63.2 %RH
```
