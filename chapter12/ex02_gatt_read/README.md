# ex02_gatt_read

**บทที่ 12** · ให้มือถืออ่านค่าอุณหภูมิจากบอร์ด (GATT read)

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) ble: มือถือเชื่อมต่อ สำเร็จ
I (...) ble: มือถืออ่านค่า -> 28.4 C
```

## หมายเหตุ

- ทดสอบด้วยแอปมือถือ **nRF Connect** (Android/iOS) แท็บ Scanner → CONNECT → กดลูกศรลง (read) ที่ characteristic
