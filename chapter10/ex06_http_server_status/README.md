# ex06_http_server_status

**บทที่ 10** · หน้าเว็บแสดงสถานะบอร์ด

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
I (...) wifi: ได้ IP: 10.10.0.2
I (...) web: เว็บเซิร์ฟเวอร์พร้อมที่พอร์ต 80
```

## หมายเหตุ

- ตั้งชื่อและรหัส Wi-Fi ด้วย `idf.py menuconfig` → **Example Wi-Fi** (ค่าเริ่มต้น `Wokwi-GUEST` สำหรับรันบน Wokwi)
- บน Wokwi ใช้ `[[net.forward]]` ใน wokwi.toml เพื่อเปิดหน้าเว็บจากเครื่อง เช่น `from = "localhost:8180"` `to = "target:80"`
