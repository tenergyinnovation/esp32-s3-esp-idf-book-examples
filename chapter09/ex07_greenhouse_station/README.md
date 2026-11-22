# ex07_greenhouse_station

**บทที่ 9** · งานจริง: SHT31 + OLED + พัดลม PWM

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

## รันบน Wokwi (VS Code)

1. `idf.py build`
2. Command Palette → **Wokwi: Start Simulator** (อ่าน `wokwi.toml` และ `diagram.json`) หรือเปิด `diagram.json` แล้วกดปุ่มเล่นสีเขียว
3. ถ้าแก้โค้ดแล้ว build ใหม่ Wokwi จะโหลดเฟิร์มแวร์ใหม่เอง ถ้ายังเป็นตัวเก่าให้ปิดแท็บ Wokwi Simulator แล้วเปิดใหม่

## การต่อวงจร

| อุปกรณ์ | ขาอุปกรณ์ | ESP32-S3 |
|---|---|---|
| SHT31 / OLED | SDA | GPIO8 |
| SHT31 / OLED | SCL | GPIO9 |
| SHT31 / OLED | VCC | 3V3 |
| SHT31 / OLED | GND | GND |
| Potentiometer (ถ้าไม่มี SHT31) | SIG | GPIO1 |
| LED/พัดลม PWM | A ผ่าน 330 Ω | GPIO6 |

## ผลที่คาดหวัง (Serial Monitor)

```text
W (...) station: ไม่พบ SHT31 ใช้ potentiometer จำลองอุณหภูมิ
I (...) station: T=31.4 C RH=-1% fan=42%
```
