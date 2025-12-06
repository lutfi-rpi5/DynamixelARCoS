#include "DynamixelARCoS.h"

DynamixelARCoS::DynamixelARCoS(HardwareSerial& serialPort, uint8_t ctrlPin, uint32_t baud)
: dxl(serialPort), ctrl(ctrlPin), baudrate(baud) {}

void DynamixelARCoS::begin() {
    pinMode(ctrl, OUTPUT);
    setRX();
    dxl.begin(baudrate);
}

void DynamixelARCoS::setTX() { digitalWrite(ctrl, HIGH); }
void DynamixelARCoS::setRX() { digitalWrite(ctrl, LOW); }

uint8_t DynamixelARCoS::checksum(uint8_t* packet, uint8_t length) {
    uint16_t sum = 0;
    for (uint8_t i = 2; i < length - 1; i++) sum += packet[i];
    return (~sum) & 0xFF;
}

void DynamixelARCoS::sendPacket(uint8_t* packet, uint8_t length) {
    setTX();
    delayMicroseconds(8);

    for (uint8_t i = 0; i < length; i++)
        dxl.write(packet[i]);

    dxl.flush();
    delayMicroseconds(8);
    setRX();
}

uint8_t DynamixelARCoS::readPacket(uint8_t* buffer, uint16_t timeout) {
    uint32_t start = millis();
    uint8_t i = 0;

    while (millis() - start < timeout) {
        if (dxl.available()) {
            buffer[i++] = dxl.read();
            if (i > 3 && i >= buffer[3] + 4) break;
        }
    }
    return i;
}

/* Basic Commands */

bool DynamixelARCoS::ping(uint8_t id) {
    uint8_t packet[6] = {0xFF, 0xFF, id, 0x02, 0x01, 0};
    packet[5] = checksum(packet, 6);
    sendPacket(packet, 6);

    uint8_t resp[20];
    uint8_t len = readPacket(resp);
    return (len > 0 && resp[2] == id && resp[4] == 0);
}

int DynamixelARCoS::read8(uint8_t id, uint8_t address) {
    uint8_t packet[8] = {0xFF,0xFF,id,0x04,0x02,address,0x01,0};
    packet[7] = checksum(packet, 8);
    sendPacket(packet, 8);

    uint8_t resp[20];
    uint8_t len = readPacket(resp);
    if (len < 6) return -1;
    return resp[5];
}

int DynamixelARCoS::read16(uint8_t id, uint8_t address) {
    int low = read8(id, address);
    int high = read8(id, address + 1);
    if (low < 0 || high < 0) return -1;
    return (high << 8) | low;
}

bool DynamixelARCoS::write8(uint8_t id, uint8_t address, uint8_t data) {
    uint8_t packet[9] = {0xFF,0xFF,id,0x04,0x03,address,data,0};
    packet[7] = checksum(packet, 9);
    sendPacket(packet, 9);

    uint8_t resp[20];
    uint8_t len = readPacket(resp);
    return (len > 0 && resp[4] == 0);
}

bool DynamixelARCoS::write16(uint8_t id, uint8_t address, uint16_t data) {
    write8(id, address, data & 0xFF);
    return write8(id, address + 1, data >> 8);
}

bool DynamixelARCoS::setID(uint8_t oldID, uint8_t newID) {
    return write8(oldID, 3, newID);
}

bool DynamixelARCoS::setBaud(uint8_t id, uint8_t baudVal) {
    return write8(id, 4, baudVal);
}

bool DynamixelARCoS::setCWLimit(uint8_t id, uint16_t limit) {
    return write16(id, 6, limit);
}

bool DynamixelARCoS::setCCWLimit(uint8_t id, uint16_t limit) {
    return write16(id, 8, limit);
}

bool DynamixelARCoS::setLed(uint8_t id, bool state) {
    return write8(id, 25, state);
}

bool DynamixelARCoS::setTorque(uint8_t id, bool enable) {
    return write8(id, 24, enable);
}

bool DynamixelARCoS::move(uint8_t id, uint16_t position) {
    return write16(id, 30, position);
}

bool DynamixelARCoS::moveSpeed(uint8_t id, uint16_t position, uint16_t speed) {
    write16(id, 32, speed);
    return write16(id, 30, position);
}

int DynamixelARCoS::getPosition(uint8_t id) { return read16(id, 36); }
int DynamixelARCoS::getSpeed(uint8_t id) { return read16(id, 38); }
int DynamixelARCoS::getLoad(uint8_t id) { return read16(id, 40); }
int DynamixelARCoS::getTemperature(uint8_t id) { return read8(id, 43); }
int DynamixelARCoS::getVoltage(uint8_t id) { return read8(id, 42); }

/* NEW FEATURES */

// Reg Write for deferred move
bool DynamixelARCoS::regWrite8(uint8_t id, uint8_t address, uint8_t data) {
    uint8_t packet[9] = {0xFF,0xFF,id,0x04,0x04,address,data,0};
    packet[7] = checksum(packet, 9);
    sendPacket(packet, 9);

    uint8_t resp[20];
    uint8_t len = readPacket(resp);
    return (len > 0 && resp[4] == 0);
}

bool DynamixelARCoS::regWrite16(uint8_t id, uint8_t addr, uint16_t data) {
    regWrite8(id, addr, data & 0xFF);
    return regWrite8(id, addr + 1, data >> 8);
}

bool DynamixelARCoS::action(uint8_t id) {
    uint8_t packet[6] = {0xFF,0xFF,id,0x02,0x05,0};
    packet[5] = checksum(packet, 6);
    sendPacket(packet, 6);
    return true;
}

// Factory Reset
bool DynamixelARCoS::factoryReset(uint8_t id) {
    uint8_t packet[6] = {0xFF,0xFF,id,0x02,0x06,0};
    packet[5] = checksum(packet,6);
    sendPacket(packet,6);

    uint8_t resp[20];
    return readPacket(resp, 50) > 0;
}

// Status return level
bool DynamixelARCoS::setStatusReturnLevel(uint8_t id, uint8_t level) {
    return write8(id, 16, level);
}

bool DynamixelARCoS::setAlarmShutdown(uint8_t id, uint8_t mask) {
    return write8(id, 18, mask);
}

bool DynamixelARCoS::setAlarmLED(uint8_t id, uint8_t mask) {
    return write8(id, 17, mask);
}

// Sync Write
bool DynamixelARCoS::syncWrite(uint8_t address, uint8_t dataLen, uint8_t* idList, uint16_t* values, uint8_t count) {
    uint8_t length = 4 + (count * (1 + dataLen));
    uint8_t packet[128];

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = 0xFE; // Broadcast
    packet[3] = length;
    packet[4] = 0x83;
    packet[5] = address;
    packet[6] = dataLen;

    uint8_t idx = 7;
    for (uint8_t i = 0; i < count; i++) {
        packet[idx++] = idList[i];
        if (dataLen == 2) {
            packet[idx++] = values[i] & 0xFF;
            packet[idx++] = values[i] >> 8;
        } else {
            packet[idx++] = values[i];
        }
    }

    packet[idx] = checksum(packet, idx + 1);
    sendPacket(packet, idx + 1);

    return true;
}
