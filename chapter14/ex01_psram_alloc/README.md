# ex01_psram_alloc

**บทที่ 14** · จองหน่วยความจำใหญ่ใน PSRAM และวัดความเร็ว

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) psram: PSRAM ทั้งหมด 8192 KB ว่าง 8100 KB
I (...) psram: จอง 2 MB ใน PSRAM: สำเร็จ
I (...) psram: เขียน 640 KB: SRAM ... us, PSRAM ... us (ช้ากว่า ... เท่า)
```
