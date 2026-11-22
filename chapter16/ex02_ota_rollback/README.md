# ex02_ota_rollback

**บทที่ 16** · ย้อนกลับเวอร์ชันเดิมอัตโนมัติถ้าเวอร์ชันใหม่เสีย

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) rollback: เวอร์ชัน 1.1.0 บน ota_1
W (...) rollback: firmware ใหม่ รอพิสูจน์ตัวเอง...
I (...) rollback: self-test ผ่าน ยืนยันใช้เวอร์ชันนี้
```
