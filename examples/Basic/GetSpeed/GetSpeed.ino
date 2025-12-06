/*
    Example 15: Read Present Speed
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115100);
    dxl.begin();
}

void loop() {
    Serial.println(dxl.getSpeed(1));
    delay(200);
}
