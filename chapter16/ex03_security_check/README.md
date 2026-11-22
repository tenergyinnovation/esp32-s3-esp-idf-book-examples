# ex03_security_check

**บทที่ 16** · ตรวจสถานะ Secure Boot และ Flash Encryption (อ่านอย่างเดียว)

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) sec: Secure Boot     : ปิด
I (...) sec: Flash Encryption: ปิด
I (...) sec: โหมด            : DISABLED
I (...) sec: chip revision   : v0.2
W (...) sec: อุปกรณ์นี้ยังไม่พร้อมขายจริง: ...
```
