/*
    Example 12: Move to Position
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    Serial.println("Testing servo ID 1...");
    if (!dxl.ping(1)) Serial.println("Servo not responding");

    dxl.setTorque(1, true);
}

void loop() {
    dxl.move(1, 200);
    delay(1000);

    dxl.move(1, 800);
    delay(1000);
}
