# ex03_kconfig_option

**บทที่ 5** · เพิ่มเมนูตั้งค่าเองใน menuconfig

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
I (...) kconfig: ชื่อโรงเรือน: Greenhouse-A
I (...) kconfig: เปิดพัดลมเมื่อเกิน: 32 C
I (...) kconfig: สัญญาณเตือน: เปิด
```

## หมายเหตุ

- เปิด `idf.py menuconfig` แล้วเข้าเมนู **Greenhouse settings** เพื่อแก้ค่า แล้ว build ใหม่
