# ex05_event_group

**บทที่ 7** · รอหลายเงื่อนไขพร้อมกันด้วย event group

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

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) upload: รอ Wi-Fi และเวลา...
I (...) wifi: เชื่อมต่อแล้ว
I (...) sntp: ตั้งเวลาแล้ว
I (...) upload: พร้อมแล้ว เริ่มส่งข้อมูล
```
