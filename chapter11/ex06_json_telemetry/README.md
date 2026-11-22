# ex06_json_telemetry

**บทที่ 11** · ส่งค่าเซนเซอร์เป็น JSON

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
I (...) json: {"device":"gh-a1b2c3","seq":1,"temp":28.4,"hum":61.0,"fan":false,"uptime":8}
```

## หมายเหตุ

- ตั้งชื่อและรหัส Wi-Fi ด้วย `idf.py menuconfig` → **Example Wi-Fi** (ค่าเริ่มต้น `Wokwi-GUEST` สำหรับรันบน Wokwi)
