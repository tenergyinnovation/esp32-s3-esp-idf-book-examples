# ex03_gatt_notify_sensor

**บทที่ 12** · ส่งค่าเซนเซอร์แบบ notify ทุก 2 วินาที

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) ble: มือถือ เปิด การแจ้งเตือน (handle 3)
I (...) ble: notify 27.6 C
```

## หมายเหตุ

- ทดสอบด้วยแอปมือถือ **nRF Connect** (Android/iOS) แท็บ Scanner → กดไอคอนลูกศรสามเส้น (notify) เพื่อ subscribe
