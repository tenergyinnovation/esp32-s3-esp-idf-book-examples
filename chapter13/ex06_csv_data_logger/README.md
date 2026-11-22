# ex06_csv_data_logger

**บทที่ 13** · บันทึกค่าเซนเซอร์เป็นไฟล์ CSV

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) fs: mount /data แล้ว ...
I (...) log: บันทึกแล้ว ไฟล์ขนาด 41 bytes
I (...) log: บันทึกแล้ว ไฟล์ขนาด 126 bytes
```
