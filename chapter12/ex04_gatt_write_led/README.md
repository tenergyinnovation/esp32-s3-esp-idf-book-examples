# ex04_gatt_write_led

**บทที่ 12** · มือถือสั่งเปิดปิด LED (GATT write)

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## การต่อวงจร

| อุปกรณ์ | ขาอุปกรณ์ | ESP32-S3 |
|---|---|---|
| LED | A ผ่าน 330 Ω | GPIO4 |

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) ble: มือถือสั่ง LED ON
I (...) ble: มือถือสั่ง LED OFF
```

## หมายเหตุ

- ทดสอบด้วยแอปมือถือ **nRF Connect** (Android/iOS) แท็บ Scanner → กดลูกศรขึ้น (write) เลือก UINT8 ใส่ 1 หรือ 0
