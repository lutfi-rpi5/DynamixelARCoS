/*
    Example 13:Read Sensors
*/

#include <DynamixelARCoS.h>

DynamixelARCoS dxl(Serial2, 4, 1000000);

void setup() {
    Serial.begin(115200);
    dxl.begin();
    dxl.ping(1);
}

void loop() {
    int pos = dxl.getPosition(1);
    int spd = dxl.getSpeed(1);
    int load = dxl.getLoad(1);
    int volt = dxl.getVoltage(1);
    int temp = dxl.getTemperature(1);

    Serial.print("Pos: ");  Serial.print(pos);
    Serial.print(" | Speed: "); Serial.print(spd);
    Serial.print(" | Load: "); Serial.print(load);
    Serial.print(" | Volt: "); Serial.print(volt);
    Serial.print(" | Temp: "); Serial.println(temp);

    delay(500);
}
