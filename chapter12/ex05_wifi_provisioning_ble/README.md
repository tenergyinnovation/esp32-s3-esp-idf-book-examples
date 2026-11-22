# ex05_wifi_provisioning_ble

**บทที่ 12** · ตั้งค่า Wi-Fi ผ่านแอปมือถือด้วย BLE provisioning

## รันบนบอร์ดจริง

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/cu.usbserial-XXXX flash monitor   # ออก: Ctrl + ]
```

> ตัวอย่างนี้ต้องใช้บอร์ดจริง

## ผลที่คาดหวัง (Serial Monitor)

```text
I (...) prov: ยังไม่มี Wi-Fi เปิดแอปแล้วเลือก PROV_A1B2C3 รหัส PoP: tenergy1
I (...) prov: ได้รับ Wi-Fi "MyHome" จากมือถือ
I (...) prov: ตั้งค่า Wi-Fi สำเร็จ
I (...) prov: ออนไลน์แล้ว IP 192.168.1.57
```

## หมายเหตุ

- ใช้ NETWORK_PROV_SECURITY_1 + PoP เพื่อความง่าย ผลิตภัณฑ์จริงควรใช้ SECURITY_2 (SRP6a)
- ติดตั้งแอป **ESP BLE Provisioning** ของ Espressif จาก App Store หรือ Google Play
