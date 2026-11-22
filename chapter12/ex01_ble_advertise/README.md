# ex01_ble_advertise

**บทที่ 12** · ประกาศชื่ออุปกรณ์ให้มือถือเห็น (advertising)

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) ble: BLE พร้อม address 7c:df:a1:xx:xx:xx
I (...) ble: กำลังประกาศตัวชื่อ "Greenhouse-S3"
```

## หมายเหตุ

- ทดสอบด้วยแอปมือถือ **nRF Connect** (Android/iOS) แท็บ Scanner
