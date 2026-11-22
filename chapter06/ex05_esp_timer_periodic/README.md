# ex05_esp_timer_periodic

**บทที่ 6** · ตั้งเวลาทำงานซ้ำทุก 500 ms ด้วย esp_timer

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
| LED | A ผ่าน 330 Ω | GPIO4 |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) timer: เริ่ม timer ที่ 300 ms (...)
I (...) timer: one-shot ทำงานที่ 3300 ms
```
