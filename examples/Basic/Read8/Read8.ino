/*
    Example 02: Read 8-bit Register
    Membaca 1 byte dari alamat tertentu.
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    int val = dxl.read8(1, 25); // LED address
    Serial.print("LED Value: ");
    Serial.println(val);
}

void loop() {}
