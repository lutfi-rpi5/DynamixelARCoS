#include <DynamixelARCoS.h>

// ===== KONFIGURASI PIN =====
#define RX_PIN   2
#define TX_PIN   15
#define CTRL_PIN 4
#define BAUDRATE 1000000

// ===== INISIALISASI OBJEK =====
DynamixelARCoS dxl(Serial2, CTRL_PIN, BAUDRATE);

// ===== DAFTAR SERVO =====
uint8_t idList[] = {1, 2, 3};
uint16_t goalPos[] = {300, 512, 750};  // posisi target masing-masing servo
const uint8_t servoCount = 3;

// ===== ADDRESS DYNAMIXEL =====
#define ADDR_TORQUE_ENABLE 24
#define ADDR_GOAL_POSITION 30

void setup() {
    Serial.begin(115200);

    // Mapping UART ESP32
    Serial2.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);

    // Init library
    dxl.begin();

    // Aktifkan torque semua servo
    for (uint8_t i = 0; i < servoCount; i++) {
        dxl.setTorque(idList[i], true);
    }
}

void loop() {

    // === KIRIM POSISI SERENTAK ===
    dxl.syncWrite(
        ADDR_GOAL_POSITION, // Address awal
        2,                  // Data length = 2 byte (word)
        idList,             // List ID servo
        goalPos,            // Data posisi
        servoCount          // Jumlah servo
    );

    delay(2000);

    // === GERAK BALIK (contoh dinamis) ===
    uint16_t backPos[] = {750, 300, 512};

    dxl.syncWrite(
        ADDR_GOAL_POSITION,
        2,
        idList,
        backPos,
        servoCount
    );

    delay(2000);
}
