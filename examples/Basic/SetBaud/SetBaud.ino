/*
    Example 07: Change Baud Rate
    Setelah ganti baud, kamu harus restart koneksi.
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    dxl.setBaud(1, 34); // 1 Mbps example
    Serial.println("Baud changed!");
}

void loop() {}
