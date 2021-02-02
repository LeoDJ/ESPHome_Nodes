// put this file in your esphome folder
// protocol implemented as described in https://en.gassensor.com.cn/Product_files/Specifications/CM1106-C%20Single%20Beam%20NDIR%20CO2%20Sensor%20Module%20Specification.pdf

#include "esphome.h"

class CM1106Component : public PollingComponent, public UARTDevice {
    public:
    Sensor *co2_sensor = new Sensor();
    const char *TAG = "cm1106";


    CM1106Component(UARTComponent *parent, uint32_t update_interval) : PollingComponent(update_interval), UARTDevice(parent) { }

    float get_setup_priority() const { return setup_priority::DATA; }

    void setup() override {
    }

    // Checksum: 256-(HEAD+LEN+CMD+DATA)%256
    uint8_t calcCRC(uint8_t* response, size_t len) {
        uint8_t crc = 0;
        // last byte of response is checksum, don't calculate it
        for(int i = 0; i < len - 1; i++) {
            crc -= response[i];
        }
        return crc;
    }

    uint8_t CM1106_CMD_GET_CO2[4] = {0x11, 0x01, 0x01, 0xED}; // head, len, cmd, [data], crc

    void update() override {
        // Empty RX Buffer
        while (available())
            read();

        uint8_t response[8] = {0}; // response: 0x16, 0x05, 0x01, DF1, DF2, DF3, DF4, CRC. PPM: DF1*256+DF2

        write_array(CM1106_CMD_GET_CO2, sizeof(CM1106_CMD_GET_CO2));
        flush();
        bool success = read_array(response, sizeof(response));

        if(!success) {
            ESP_LOGW(TAG, "Reading data from CM1106 failed!");
            return;
        }

        if(!(response[0] == 0x16 && response[1] == 0x05 && response[2] == 0x01)) {
            ESP_LOGW(TAG, "Got wrong UART response: %02X %02X %02X %02X...", response[0], response[1], response[2], response[3]);
            return;
        }

        uint8_t checksum = calcCRC(response, sizeof(response));
        if(response[7] != checksum) {
            ESP_LOGW(TAG, "Got wrong UART checksum: 0x%02X - Calculated: 0x%02X", response[7], checksum);
            return;
        }

        uint16_t ppm = response[3] << 8 | response[4];
        ESP_LOGD(TAG, "CM1106 Received CO₂=%uppm DF3=%02X DF4=%02X", ppm, response[5], response[6]);
        this->co2_sensor->publish_state(ppm);
    }
}; 