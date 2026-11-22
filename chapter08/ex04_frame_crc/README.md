# ex04_frame_crc

**บทที่ 8** · แพ็กเก็ตมี header, length และ CRC

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
| สายจัมเปอร์ | GPIO17 (TX ของ UART1) | GPIO18 (RX ของ UART1) |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) frame: แพ็กเก็ตถูกต้อง: "FAN=ON"
W (...) frame: CRC ไม่ตรง ทิ้งแพ็กเก็ต
I (...) frame: แพ็กเก็ตถูกต้อง: "HUM=62"
```
