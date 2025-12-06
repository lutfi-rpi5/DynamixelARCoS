#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();

    dxl.setTorque(1, true);

    dxl.setCWLimit(1, 0);
    dxl.setCCWLimit(1, 0);
}

void loop() {
    dxl.write16(1, 32, 300);  
    delay(1500);

    dxl.write16(1, 32, 1023); 
    delay(1500);

    dxl.write16(1, 32, 0);
    delay(1000);
}
