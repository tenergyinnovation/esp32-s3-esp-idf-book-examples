# ex03_button_interrupt_queue

**บทที่ 6** · ปุ่มแบบ interrupt ส่งเหตุการณ์ผ่าน queue

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
| LED | A ผ่าน 330 Ω | GPIO4 |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) irq: พร้อม กดปุ่มได้เลย
I (...) irq: GPIO5 กดครั้งที่ 1 เวลา 2345 ms -> LED ON
```
