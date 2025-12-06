/*
    Example 05: Write 16-bit Register
    Contoh: Set Goal Position
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    dxl.write16(1, 30, 512); // Move to middle
}

void loop() {}
