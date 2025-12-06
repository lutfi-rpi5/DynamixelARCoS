/*
    Example 04: Write 8-bit Register
    Contoh: Matikan/Menyala LED
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    dxl.write8(1, 25, 1); // LED ON
    delay(1000);
    dxl.write8(1, 25, 0); // LED OFF
}

void loop() {}
