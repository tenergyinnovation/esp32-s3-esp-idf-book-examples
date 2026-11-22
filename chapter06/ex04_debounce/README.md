# ex04_debounce

**บทที่ 6** · กำจัดปุ่มเด้งด้วยซอฟต์แวร์

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
| ปุ่มกด | 1 | GPIO5 |
| ปุ่มกด | 2 | GND |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) debounce: กดจริงครั้งที่ 1
I (...) debounce: กดจริงครั้งที่ 2
```
