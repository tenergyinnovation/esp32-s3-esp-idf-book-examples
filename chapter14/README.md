# บทที่ 14 PSRAM, Power Management และ Reliability

ตัวอย่างประกอบบทที่ 14 ของหนังสือ

## หัวข้อในบท

14.1 PSRAM 8 MB  
14.2 Heap monitor: จับ memory leak  
14.3 โหมดประหยัดไฟ  
14.4 Light sleep  
14.5 Deep sleep: ตื่นตามเวลา  
14.6 Deep sleep: ตื่นด้วยปุ่ม  
14.7 Reset reason และ watchdog  
14.8 Fail-safe state machine

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_psram_alloc` | จองหน่วยความจำใหญ่ใน PSRAM | บอร์ดจริงเท่านั้น | [เปิด](ex01_psram_alloc/) |
| `ex02_heap_monitor` | เฝ้าดู heap คงเหลือ | Wokwi + บอร์ดจริง | [เปิด](ex02_heap_monitor/) |
| `ex03_light_sleep` | งีบสั้นๆ ประหยัดไฟ | บอร์ดจริงเท่านั้น | [เปิด](ex03_light_sleep/) |
| `ex04_deep_sleep_timer` | หลับลึกแล้วตื่นตามเวลา | Wokwi + บอร์ดจริง | [เปิด](ex04_deep_sleep_timer/) |
| `ex05_deep_sleep_button` | ตื่นเมื่อกดปุ่ม | Wokwi + บอร์ดจริง | [เปิด](ex05_deep_sleep_button/) |
| `ex06_reset_reason_watchdog` | บันทึกสาเหตุการรีเซ็ต | บอร์ดจริงเท่านั้น | [เปิด](ex06_reset_reason_watchdog/) |
| `ex07_failsafe_state_machine` | งานจริง: พัดลมกลับสู่สถานะปลอดภัยเมื่อเซนเซอร์เสีย | Wokwi + บอร์ดจริง | [เปิด](ex07_failsafe_state_machine/) |
