# ex04_volatile_button_flag

**บทที่ 4** · volatile กับปุ่มกดผ่าน interrupt

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
| ปุ่มกด | ขาข้างหนึ่ง | GPIO5 |
| ปุ่มกด | ขาอีกข้าง | GND |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) volatile: พร้อม กดปุ่มที่ GPIO5
I (...) volatile: มีการกดปุ่ม (ISR ทำงานรวม 1 ครั้ง)
```
