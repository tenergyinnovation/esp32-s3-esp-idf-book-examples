# บทที่ 7 FreeRTOS บน ESP32-S3 แบบ Dual-Core

ตัวอย่างประกอบบทที่ 7 ของหนังสือ

## หัวข้อในบท

7.1 Task และ scheduler  
7.2 Priority: ใครได้ก่อน  
7.3 Queue: ส่งข้อมูลระหว่าง task  
7.4 Race condition และ mutex  
7.5 Event group: รอหลายเงื่อนไข  
7.6 Dual-core: core 0 และ core 1  
7.7 Task watchdog: สุนัขเฝ้าบ้าน  
7.8 Stack high-water mark: stack พอไหม

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_two_tasks` | สอง task ทำงานพร้อมกัน | Wokwi + บอร์ดจริง | [เปิด](ex01_two_tasks/) |
| `ex02_task_priority` | ดูผลของ priority | Wokwi + บอร์ดจริง | [เปิด](ex02_task_priority/) |
| `ex03_queue_producer_consumer` | คนผลิต-คนใช้ข้อมูลผ่าน queue | Wokwi + บอร์ดจริง | [เปิด](ex03_queue_producer_consumer/) |
| `ex04_mutex_shared_counter` | แก้ race condition ด้วย mutex | Wokwi + บอร์ดจริง | [เปิด](ex04_mutex_shared_counter/) |
| `ex05_event_group` | รอหลายเงื่อนไขพร้อมกันด้วย event group | Wokwi + บอร์ดจริง | [เปิด](ex05_event_group/) |
| `ex06_pin_to_core` | ผูก task กับ core 0 และ core 1 | บอร์ดจริงเท่านั้น | [เปิด](ex06_pin_to_core/) |
| `ex07_task_watchdog` | ให้ watchdog จับ task ที่ค้าง | Wokwi + บอร์ดจริง | [เปิด](ex07_task_watchdog/) |
| `ex08_stack_watermark` | วัดว่า task ใช้ stack ไปเท่าไร | Wokwi + บอร์ดจริง | [เปิด](ex08_stack_watermark/) |
