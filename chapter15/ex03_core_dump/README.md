# ex03_core_dump

**บทที่ 15** · เก็บ core dump ไว้ใน Flash เพื่อวิเคราะห์ทีหลัง

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) cd: ไม่มี core dump ค้างอยู่
E (...) cd: worker กำลังจะ crash
Guru Meditation Error ...
I (...) esp_core_dump_flash: Save core dump to flash...
(บูตใหม่)
W (...) cd: พบ core dump จากการ crash ครั้งก่อน -> รัน idf.py coredump-info เพื่อดู
```
