# บทที่ 3 โปรเจกต์แรก: Hello World และไฟกะพริบ

ตัวอย่างประกอบบทที่ 3 ของหนังสือ

## หัวข้อในบท

3.1 โครงสร้างโปรเจกต์ ESP-IDF  
3.2 สายพานการผลิต: build → flash → monitor  
3.3 ตัวอย่างแรก: Hello World  
3.4 ถามบอร์ดว่า "คุณคือใคร"  
3.5 ไฟกะพริบ: LED ภายนอก  
3.6 ไฟ RGB บนบอร์ด และ component จาก Registry  
3.7 นับการรีสตาร์ต: หน่วยความจำที่ไม่ลืมเมื่อรีเซ็ต  
3.8 รันบน Wokwi ใน VS Code

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_hello_world` | พิมพ์ข้อความแรกออก Serial Monitor | Wokwi + บอร์ดจริง | [เปิด](ex01_hello_world/) |
| `ex02_chip_info` | แสดงจำนวน core, ขนาด Flash และ PSRAM ของบอร์ด | Wokwi + บอร์ดจริง | [เปิด](ex02_chip_info/) |
| `ex03_blink_external_led` | กะพริบ LED ภายนอก (ไฟเลี้ยวรถ) | Wokwi + บอร์ดจริง | [เปิด](ex03_blink_external_led/) |
| `ex04_rgb_led_onboard` | สั่ง RGB LED บนบอร์ด (GPIO38) เปลี่ยนสี | Wokwi + บอร์ดจริง | [เปิด](ex04_rgb_led_onboard/) |
| `ex05_restart_counter` | นับและแสดงสาเหตุการรีสตาร์ต | Wokwi + บอร์ดจริง | [เปิด](ex05_restart_counter/) |
