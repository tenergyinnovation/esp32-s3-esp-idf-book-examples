# บทที่ 8 UART และการออกแบบ Protocol

ตัวอย่างประกอบบทที่ 8 ของหนังสือ

## หัวข้อในบท

8.1 UART ทำงานอย่างไร  
8.2 UART echo บนพอร์ต Serial Monitor  
8.3 UART1 และ event queue  
8.4 ตัวแปลคำสั่งแบบข้อความ  
8.5 แพ็กเก็ตแบบมี CRC  
8.6 Timeout: เมื่อแพ็กเก็ตมาไม่ครบ  
8.7 UART bridge

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_uart_echo` | รับแล้วส่งกลับ (echo) | Wokwi + บอร์ดจริง | [เปิด](ex01_uart_echo/) |
| `ex02_uart_event_queue` | รับข้อมูลด้วย event queue | Wokwi + บอร์ดจริง | [เปิด](ex02_uart_event_queue/) |
| `ex03_command_parser` | คำสั่งแบบข้อความ เช่น LED ON | Wokwi + บอร์ดจริง | [เปิด](ex03_command_parser/) |
| `ex04_frame_crc` | แพ็กเก็ตมี header, length และ CRC | Wokwi + บอร์ดจริง | [เปิด](ex04_frame_crc/) |
| `ex05_timeout_recovery` | จัดการข้อมูลขาดหายกลางทาง | Wokwi + บอร์ดจริง | [เปิด](ex05_timeout_recovery/) |
| `ex06_uart_bridge` | ส่งต่อข้อมูลระหว่าง UART สองพอร์ต | บอร์ดจริงเท่านั้น | [เปิด](ex06_uart_bridge/) |
