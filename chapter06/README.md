# บทที่ 6 GPIO, Interrupt, Timer และ State Machine

ตัวอย่างประกอบบทที่ 6 ของหนังสือ

## หัวข้อในบท

6.1 GPIO output หลายขา  
6.2 อ่านปุ่ม: input, pull-up และ polling  
6.3 Interrupt และ queue: ตอบสนองทันทีโดยไม่ถามซ้ำ  
6.4 Debounce: ปุ่มเด้ง  
6.5 esp_timer: นาฬิกาปลุกความละเอียดไมโครวินาที  
6.6 State machine: คิดเป็นสถานะ  
6.7 งานจริง: พัดลมโรงเรือนพร้อม hysteresis

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_led_output` | เปิดปิด LED หลายดวง | Wokwi + บอร์ดจริง | [เปิด](ex01_led_output/) |
| `ex02_button_polling` | อ่านปุ่มแบบวนถาม | Wokwi + บอร์ดจริง | [เปิด](ex02_button_polling/) |
| `ex03_button_interrupt_queue` | ปุ่มแบบ interrupt ส่งเหตุการณ์ผ่าน queue | Wokwi + บอร์ดจริง | [เปิด](ex03_button_interrupt_queue/) |
| `ex04_debounce` | กำจัดปุ่มเด้งด้วยซอฟต์แวร์ | Wokwi + บอร์ดจริง | [เปิด](ex04_debounce/) |
| `ex05_esp_timer_periodic` | ตั้งเวลาทำงานซ้ำทุก 500 ms | Wokwi + บอร์ดจริง | [เปิด](ex05_esp_timer_periodic/) |
| `ex06_traffic_light_fsm` | ไฟจราจรด้วย state machine | Wokwi + บอร์ดจริง | [เปิด](ex06_traffic_light_fsm/) |
| `ex07_greenhouse_fan_logic` | งานจริง: ควบคุมพัดลมโรงเรือนตามปุ่มและเวลา | Wokwi + บอร์ดจริง | [เปิด](ex07_greenhouse_fan_logic/) |
