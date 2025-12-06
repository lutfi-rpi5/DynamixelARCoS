/*
    Example 09: Set CCW Angle Limit
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    dxl.setCCWLimit(1, 800);
}

void loop() {}
