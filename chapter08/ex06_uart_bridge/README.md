# ex06_uart_bridge

**บทที่ 8** · ส่งต่อข้อมูลระหว่าง UART0 กับ UART1 (สะพาน)

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
| อุปกรณ์ UART 3.3 V | RX | GPIO17 (TX) |
| อุปกรณ์ UART 3.3 V | TX | GPIO18 (RX) |
| อุปกรณ์ | GND | GND |

## หมายเหตุ

- อุปกรณ์ที่ใช้ระดับสัญญาณ 5 V ต้องผ่าน level shifter ก่อนเข้า GPIO18
