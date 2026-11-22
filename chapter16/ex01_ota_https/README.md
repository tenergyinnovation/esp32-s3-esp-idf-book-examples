# ex01_ota_https

**บทที่ 16** · อัปเดต firmware ผ่าน HTTPS (OTA)

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) ota: เวอร์ชันปัจจุบัน 1.0.0 รันจาก ota_0
I (...) ota: เริ่มดาวน์โหลดจาก https://...
I (...) ota: อัปเดตสำเร็จ จะบูตจาก ota_1 หลังรีสตาร์ต
```

## หมายเหตุ

- ตั้งชื่อและรหัส Wi-Fi ด้วย `idf.py menuconfig` → **Example Wi-Fi** (ค่าเริ่มต้น `Wokwi-GUEST` สำหรับรันบน Wokwi)
- ตั้ง URL ใน menuconfig → **OTA** ทดลองในเครื่องด้วย `openssl s_server -WWW -key key.pem -cert cert.pem -port 8070` ในโฟลเดอร์ build ของเวอร์ชันใหม่
