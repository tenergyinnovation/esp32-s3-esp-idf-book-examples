# บทที่ 9 I2C, ADC, PWM และ SPI กับเซนเซอร์จริง

ตัวอย่างประกอบบทที่ 9 ของหนังสือ

## หัวข้อในบท

9.1 I2C: หนึ่งคู่สาย หลายอุปกรณ์  
9.2 SHT31: เซนเซอร์อุณหภูมิและความชื้น  
9.3 จอ OLED SSD1306  
9.4 ADC: อ่านแรงดันแอนะล็อก  
9.5 PWM ด้วย LEDC: ปรับความแรง  
9.6 SPI: เร็วกว่า I2C  
9.7 งานจริง: สถานีวัดโรงเรือน

## ตัวอย่าง

| โฟลเดอร์ | สิ่งที่ทำ | รัน | สถานะ |
|---|---|---|---|
| `ex01_i2c_scanner` | ค้นหาอุปกรณ์ทุกตัวบนบัส I2C | Wokwi + บอร์ดจริง | [เปิด](ex01_i2c_scanner/) |
| `ex02_sht31_temp_humidity` | อ่านอุณหภูมิและความชื้นจาก SHT31 | บอร์ดจริงเท่านั้น | [เปิด](ex02_sht31_temp_humidity/) |
| `ex03_oled_text` | แสดงข้อความบน OLED | Wokwi + บอร์ดจริง | [เปิด](ex03_oled_text/) |
| `ex04_adc_potentiometer` | อ่านค่า potentiometer เป็นมิลลิโวลต์ | Wokwi + บอร์ดจริง | [เปิด](ex04_adc_potentiometer/) |
| `ex05_ledc_fade` | หรี่ไฟ LED ด้วย PWM | Wokwi + บอร์ดจริง | [เปิด](ex05_ledc_fade/) |
| `ex06_spi_loopback` | ทดสอบ SPI แบบเชื่อมขาวนกลับ | บอร์ดจริงเท่านั้น | [เปิด](ex06_spi_loopback/) |
| `ex07_greenhouse_station` | งานจริง: เซนเซอร์ + OLED + พัดลม PWM | Wokwi + บอร์ดจริง | [เปิด](ex07_greenhouse_station/) |
