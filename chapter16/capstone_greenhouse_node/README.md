# capstone_greenhouse_node

**บทที่ 16** · Capstone: Smart Greenhouse Node (รวมทุกบท)

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
| SHT31 / OLED | SDA | GPIO8 |
| SHT31 / OLED | SCL | GPIO9 |
| Potentiometer (ถ้าไม่มี SHT31) | SIG | GPIO1 |
| LED แทนพัดลม (PWM) | A ผ่าน 330 Ω | GPIO6 |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) node: GH-A1B2C3 firmware 2.0.0
W (...) node: ไม่พบจอ OLED (ถ้าไม่ได้ต่อ)
I (...) node: เซนเซอร์: potentiometer จำลอง (GPIO1)
I (...) node: MQTT พร้อม รับคำสั่งที่ tenergy/gh/GH-A1B2C3/cmd
I (...) node: {"t":31.4,"rh":-1.0,"fan":45,"sp":32.0,"mode":0,"heap":245000,"up":32,"fw":"2.0.0"}
```

## หมายเหตุ

- ตั้งชื่อและรหัส Wi-Fi ด้วย `idf.py menuconfig` → **Example Wi-Fi** (ค่าเริ่มต้น `Wokwi-GUEST` สำหรับรันบน Wokwi)
- ส่งคำสั่งจากคอมพิวเตอร์: `mosquitto_pub -h broker.emqx.io -t tenergy/gh/GH-XXXXXX/cmd -m fan=on`
- ดูข้อมูล: `mosquitto_sub -h broker.emqx.io -t "tenergy/gh/#" -v`
