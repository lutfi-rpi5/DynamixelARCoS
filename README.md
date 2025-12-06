# DynamixelARCoS Library

Driver setengah-duplex untuk servo Dynamixel AX-12A dan AX-18A menggunakan ESP32.
Mendukung ping, read, write, move, speed, torque, LED, limit, dan monitoring servo.

Hardware:
- ESP32 UART (Serial1/Serial2)
- Transceiver half-duplex 74HC241 / 74HC125
- CTRL pin untuk arah data

Cara pakai:

#include <DynamixelARCoS.h>
Dynamixel dxl(Serial2, 4, 1000000);

void setup() {
    dxl.begin();
    dxl.move(1, 512);
}
