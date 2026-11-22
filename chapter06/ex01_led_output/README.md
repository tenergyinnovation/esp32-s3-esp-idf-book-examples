# ex01_led_output

**บทที่ 6** · เปิดปิด LED หลายดวง (ไฟวิ่ง)

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
| LED 1-4 | A ผ่าน 330 Ω | GPIO4, 5, 6, 7 |
| LED ทุกดวง | C | GND |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) leds: ดวงที่ 1 ติด
I (...) leds: ดวงที่ 2 ติด
...
```
