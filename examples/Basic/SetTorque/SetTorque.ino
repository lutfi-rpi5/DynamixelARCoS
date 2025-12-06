/*
    Example 11: Enable/Disable Torque
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    dxl.setTorque(1, false);
    delay(1000);
    dxl.setTorque(1, true);
}

void loop() {}
