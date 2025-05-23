# Smart Ultrasonic Humidifier Control System

This project controls an ultrasonic humidifier using an ATmega328P microcontroller. The system supports both physical button control and remote control via serial commands (UART). The humidifier's state is indicated by an LED, and the system can be toggled on/off with both a physical button and serial commands.

## Features

- **Physical Button Control**: Use the button to toggle the humidifier on/off.
- **UART Control**: Send '1' to turn the humidifier on and '0' to turn it off via serial communication.
- **LED Indicator**: The system uses an LED to show the current state of the humidifier (on/off).
- **Debounced Button Handling**: Prevents multiple button presses from triggering the system unintentionally.

## Components

- **ATmega328P Microcontroller**: The main controller.
- **Ultrasonic Humidifier**: Controlled via a MOSFET or relay.
- **LED**: Indicates the state of the humidifier.
- **Button**: Used for manual control.
- **HC-05 Bluetooth Module (Optional)**: Can be added for wireless control.
- **Power Supply**: Suitable for the microcontroller and peripherals.

## Pin Mapping

- **LED_PIN** (PD4) – Controls the LED indicator.
- **MOSFET_PIN** (PD3) – Controls the humidifier.
- **BUTTON_PIN** (PD2) – Button input for toggling the humidifier.

## Setup

1. **Hardware Setup**:
   - Connect the **LED_PIN** (PD4) to an LED (with an appropriate current-limiting resistor).
   - Connect the **MOSFET_PIN** (PD3) to the control pin of the humidifier.
   - Connect the **BUTTON_PIN** (PD2) to a push-button with a pull-up resistor.

2. **Software Setup**:
   - Install **AVR-GCC** toolchain and **AVRDude** for compiling and uploading the firmware to the ATmega328P.
   - Open the project in your favorite IDE (such as **Atmel Studio** or **Arduino IDE**) and upload the code to the ATmega328P.

3. **Serial Communication**:
   - The system uses **USART** at a baud rate of 9600 to receive commands.
   - Send '1' to turn the humidifier on and '0' to turn it off.

## Code Overview

- **USART_Init()**: Initializes the UART for serial communication.
- **USART_Receive()**: Reads a character from the serial port.
- **toggle_humidifier()**: Toggles the humidifier state and LED on/off.
- **ISR(INT0_vect)**: Interrupt Service Routine for button presses, with a debounce delay to prevent multiple triggers.
- **Main Loop**: Waits for serial commands ('1' to turn on, '0' to turn off) and toggles the humidifier accordingly.

## Example Usage

1. **Button Press**: Press the button connected to PD2 to toggle the humidifier on or off.
2. **Serial Command**: Open a serial terminal (e.g., **PuTTY**, **Tera Term**, **Arduino Serial Monitor**), set the baud rate to 9600, and send:
   - `1` to turn the humidifier on.
   - `0` to turn the humidifier off.

## Troubleshooting

- **Button Press Not Detected**: Ensure the button is properly connected with the correct pull-up resistor configuration.
- **Serial Communication Issues**: Double-check the baud rate and ensure the microcontroller is properly connected to your PC's serial port.

## Acknowledgements

- AVR Libc for the AVR-specific library functions.
- The **ATmega328P** microcontroller for its flexibility in embedded projects.

