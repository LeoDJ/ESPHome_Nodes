# CM1106 CO2 Sensor

Custom ESPHome sensor component for the CM1106 CO2 sensor.

Implemented CM1106 UART protocol as described in the [sensor datasheet](https://en.gassensor.com.cn/Product_files/Specifications/CM1106-C%20Single%20Beam%20NDIR%20CO2%20Sensor%20Module%20Specification.pdf).

Connect the CM1106 sensor to the ESP32 as follows:  
- TX -> GPIO16
- RX -> GPIO17
- GND -> GND
- 5V -> 5V