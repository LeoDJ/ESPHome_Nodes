# CM1106 CO2 Sensor

Custom ESPHome sensor component for the CM1106 CO2 sensor.

You need to copy the `cc1106.h` file into your esphome directory (where all the other .yaml files are stored). Everything else is shown in the yaml file.

Connect the CM1106 sensor to the ESP32 as follows:  
- TX -> GPIO16
- RX -> GPIO17
- GND -> GND
- 5V -> 5V

I implemented CM1106 UART protocol as described in the [sensor datasheet](https://en.gassensor.com.cn/Product_files/Specifications/CM1106-C%20Single%20Beam%20NDIR%20CO2%20Sensor%20Module%20Specification.pdf).