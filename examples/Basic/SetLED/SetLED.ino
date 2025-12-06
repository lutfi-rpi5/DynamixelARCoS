/*
    Example 10: LED Control
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    dxl.setLed(1, true);
    delay(1000);
    dxl.setLed(1, false);
}

void loop() {}
