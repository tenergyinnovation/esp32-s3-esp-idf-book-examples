# ex04_sdkconfig_defaults

**บทที่ 5** · ตั้งค่า Flash 16 MB และ PSRAM ด้วย sdkconfig.defaults

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) defaults: CPU: 240 MHz
I (...) defaults: Flash ตาม sdkconfig: 16MB / ตรวจจริง: 16 MB
I (...) defaults: PSRAM เปิดใช้: พบ, ขนาด 8 MB
```
