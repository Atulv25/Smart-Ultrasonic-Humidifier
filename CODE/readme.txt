Smart Ultrasonic Humidifier Control Code
----------------------------------------

Functionality:
- Toggles humidifier ON/OFF via push button (PD2) or Bluetooth command
- Controls humidifier through MOSFET on PD3
- Status LED connected to PD4 indicates ON/OFF status

Bluetooth Commands:
- '1' → Turn ON humidifier
- '0' → Turn OFF humidifier

Pin Assignments:
- PD2: Push Button (External Interrupt INT0)
- PD3: MOSFET Gate (Controls Humidifier)
- PD4: Status LED
- PD0: UART RX (Connect to HC-05 TX)
- PD1: UART TX (Connect to HC-05 RX via voltage divider)

Compile & Upload:
- Use AVR-GCC or Atmel Studio
- 16MHz crystal recommended for accurate UART timing

Author: [Your Name]
