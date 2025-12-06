/*
    Example 06: Change ID
    WARNING: Pastikan hanya satu servo yang terhubung.
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    Serial.println("Changing ID 1 -> 2");

    if (dxl.setID(1, 2))
        Serial.println("ID changed");
    else
        Serial.println("Failed");
}

void loop() {}
