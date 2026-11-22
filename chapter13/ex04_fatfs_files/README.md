# ex04_fatfs_files

**บทที่ 13** · เขียนอ่านไฟล์ใน Flash ด้วย FAT + wear levelling

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) fs: mount /data แล้ว ขนาด 7000 KB ว่าง 6990 KB
I (...) fs: บรรทัด 1: สวัสดี ESP32-S3 จาก FATFS
```
