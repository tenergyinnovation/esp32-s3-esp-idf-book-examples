# ex02_nvs_config_struct

**บทที่ 13** · เก็บค่าตั้งเป็นชุดพร้อมเลขเวอร์ชัน (schema version)

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
W (...) cfg: ยังไม่มีค่าตั้ง ใช้ค่าเริ่มต้น
I (...) cfg: ค่าปัจจุบัน: Greenhouse-A เปิด 32.0 C ปิด 30.0 C รายงานทุก 60 s
I (...) cfg: บันทึกแล้ว รีเซ็ตบอร์ดเพื่อดูค่าที่จำไว้
```
