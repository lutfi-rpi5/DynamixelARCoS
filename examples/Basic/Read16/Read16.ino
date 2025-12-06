/*
    Example 03: Read 16-bit Register
    Membaca 2 byte (low + high)
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    int pos = dxl.read16(1, 36); // Present Position
    Serial.print("Position: ");
    Serial.println(pos);
}

void loop() {}
