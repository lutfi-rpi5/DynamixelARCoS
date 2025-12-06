/*
    Example 08: Set CW Angle Limit
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    dxl.setCWLimit(1, 200); // mechanical limit
}

void loop() {}
