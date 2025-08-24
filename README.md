````markdown
# ESP32 Dual SPI RF Test Project

*Educational ESP32 project demonstrating dual SPI NRF24L01 modules with real-time 16×2 LCD feedback.*

## Disclaimer
⚠️ This project is for educational and lab purposes only. Do not transmit harmful signals or interfere with real Wi-Fi/Bluetooth networks.

## Features
- Dual NRF24L01 modules operating simultaneously on HSPI and VSPI buses
- Real-time status on 16×2 LCD showing “RF Test Mode” and channel activity
- Safe signal stress simulation for SPI communication testing
- Demonstrates ESP32 flexibility with multiple SPI peripherals

## Hardware Required
- ESP32 Development Board
- 2 × NRF24L01 modules
- 16×2 I2C LCD display
- Jumper wires and breadboard

## Wiring Overview

![ESP32 Dual SPI Circuit](assets/esp32_dual_spi_circuit.png)

**NRF24 Modules:**  
- HSPI (Module 1) → `CE: 26`, `CS: 15`, `SCK: 14`, `MOSI: 13`, `MISO: 12`  
- VSPI (Module 2) → `CE: 4`, `CS: 2`, `SCK: 18`, `MOSI: 23`, `MISO: 19`  

**LCD Display:**  
- `SDA` → ESP32 SDA (e.g., GPIO 21)  
- `SCL` → ESP32 SCL (e.g., GPIO 22)  
- `VCC` → 3.3V or 5V (check LCD spec)  
- `GND` → GND

## Installation
1. Clone this repository:
```bash
git clone https://github.com/yourusername/esp32-dual-spi-rf-test.git
````

2. Open the project in Arduino IDE or PlatformIO.
3. Install the required libraries:

   * `RF24`
   * `ezButton`
   * `Wire` (for I2C LCD)
4. Select the ESP32 board and correct COM port.

## Usage

1. Upload the code to the ESP32.
2. Observe the 16×2 LCD displaying:

   * “RF Test Mode”
   * HSPI & VSPI channel activity
3. Toggle the switch to switch between:

   * Simulated constant carrier mode (channel stress simulation)
   * Random channel mode (testing SPI updates)

## Code Highlights

* Dual SPI initialization: `initHP()` for HSPI, `initSP()` for VSPI
* Safe channel stress simulation: `one()` and `two()` functions
* LCD feedback: Real-time display updates of SPI channel values

## Learning Outcomes

* Configuring HSPI & VSPI on ESP32
* Managing multiple SPI peripherals simultaneously
* Using 16×2 LCD for live feedback
* Implementing safe RF signal simulations for lab experimentation

## License

This project is licensed under the [MIT License](LICENSE).

```

This version keeps your content intact, adds proper Markdown formatting, and improves readability on GitHub.  

I can also **generate the LICENSE file with your name pre-filled** if you want. Do you want me to do that?
```
