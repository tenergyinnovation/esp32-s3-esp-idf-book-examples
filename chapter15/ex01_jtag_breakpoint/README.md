# ex01_jtag_breakpoint

**บทที่ 15** · หยุดโปรแกรมด้วย breakpoint ผ่าน JTAG ในตัว

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) debug: ค่าเฉลี่ย = 30
```

## หมายเหตุ

- optimization แบบ Debug (-Og) ทำให้ตัวแปรไม่ถูก optimize ทิ้ง debug ง่ายขึ้น
