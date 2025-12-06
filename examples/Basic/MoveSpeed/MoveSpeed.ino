/*
    Example 13: Move with Speed Control
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();
    dxl.setTorque(1, true);
}

void loop() {
    dxl.moveSpeed(1, 300, 100);
    delay(1000);

    dxl.moveSpeed(1, 700, 50);
    delay(1000);
}
