# ex03_command_parser

**บทที่ 8** · รับคำสั่งแบบข้อความ เช่น LED ON

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
I (...) cmd: พิมพ์ HELP แล้วกด Enter
I (...) cmd: คำสั่ง: LED ON | LED OFF | STATUS | HELP
I (...) cmd: OK LED=ON
```
