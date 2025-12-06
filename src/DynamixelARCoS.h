#ifndef DYNAMIXEL_ARCOS_H
#define DYNAMIXEL_ARCOS_H

#include <Arduino.h>

class DynamixelARCoS {
public:
    DynamixelARCoS(HardwareSerial& serialPort, uint8_t ctrlPin, uint32_t baud);

    void begin();

    void setTX();
    void setRX();

    void sendPacket(uint8_t* packet, uint8_t length);
    uint8_t readPacket(uint8_t* buffer, uint16_t timeout = 20);
    uint8_t checksum(uint8_t* packet, uint8_t length);

    bool ping(uint8_t id);

    int read8(uint8_t id, uint8_t address);
    int read16(uint8_t id, uint8_t address);

    bool write8(uint8_t id, uint8_t address, uint8_t data);
    bool write16(uint8_t id, uint8_t address, uint16_t data);

    bool setID(uint8_t oldID, uint8_t newID);
    bool setBaud(uint8_t id, uint8_t baudVal);
    bool setCWLimit(uint8_t id, uint16_t limit);
    bool setCCWLimit(uint8_t id, uint16_t limit);
    bool setLed(uint8_t id, bool state);
    bool setTorque(uint8_t id, bool enable);
    bool move(uint8_t id, uint16_t position);
    bool moveSpeed(uint8_t id, uint16_t position, uint16_t speed);
    int getPosition(uint8_t id);
    int getSpeed(uint8_t id);
    int getLoad(uint8_t id);
    int getTemperature(uint8_t id);
    int getVoltage(uint8_t id);

    // NEW FEATURES
    bool regWrite8(uint8_t id, uint8_t address, uint8_t data);
    bool regWrite16(uint8_t id, uint8_t addr, uint16_t data);
    bool action(uint8_t id = 0xFE);
    bool factoryReset(uint8_t id);
    bool setStatusReturnLevel(uint8_t id, uint8_t level);
    bool setAlarmShutdown(uint8_t id, uint8_t mask);
    bool setAlarmLED(uint8_t id, uint8_t mask);
    bool syncWrite(uint8_t address, uint8_t dataLen, uint8_t* idList, uint16_t* values, uint8_t count);

private:
    HardwareSerial& dxl;
    uint8_t ctrl;
    uint32_t baudrate;
};

#endif
