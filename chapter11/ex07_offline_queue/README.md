# ex07_offline_queue

**บทที่ 11** · เก็บข้อมูลไว้ส่งเมื่อเน็ตกลับมา (store-and-forward)

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
I (...) sf: เก็บค่า #1 ไว้ในคิว (1/32)
...
I (...) sf: ออนไลน์ มีของค้าง 6 ค่า
I (...) sf: ส่ง {"seq":1,"t_ms":312,"temp":27.4} (เหลือ 5)
```

## หมายเหตุ

- ตั้งชื่อและรหัส Wi-Fi ด้วย `idf.py menuconfig` → **Example Wi-Fi** (ค่าเริ่มต้น `Wokwi-GUEST` สำหรับรันบน Wokwi)
- ในงานจริงถ้าต้องเก็บนานหลายชั่วโมง ให้เก็บคิวลง Flash (บทที่ 13)
