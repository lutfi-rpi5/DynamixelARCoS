/*
    Example 01: Ping Dynamixel
    Fungsi: Mengecek apakah servo dengan ID tertentu merespon.
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    Serial.println("Ping test...");
    if (dxl.ping(1)) Serial.println("Servo ID 1 ditemukan!");
    else Serial.println("Servo ID 1 tidak merespon");
}

void loop() {}
