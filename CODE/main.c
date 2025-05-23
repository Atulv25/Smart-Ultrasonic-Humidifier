#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_PIN     PD4
#define MOSFET_PIN  PD3
#define BUTTON_PIN  PD2

volatile uint8_t humidifier_on = 0;
volatile uint8_t button_pressed = 0;

void USART_Init(unsigned int ubrr) {
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

char USART_Receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void toggle_humidifier() {
    humidifier_on = !humidifier_on;

    if (humidifier_on) {
        PORTD |= (1 << MOSFET_PIN);  // Turn ON humidifier
        PORTD |= (1 << LED_PIN);     // Turn ON LED
    } else {
        PORTD &= ~(1 << MOSFET_PIN); // Turn OFF humidifier
        PORTD &= ~(1 << LED_PIN);    // Turn OFF LED
    }
}

ISR(INT0_vect) {
    if (button_pressed == 0) {  // Check if not already pressed
        _delay_ms(50);  // Debounce delay
        if (!(PIND & (1 << BUTTON_PIN))) {
            toggle_humidifier();
            button_pressed = 1;  // Mark button as pressed
        }
    }
}

ISR(INT0_vect) {
    // Check for button release and reset the flag
    if (PIND & (1 << BUTTON_PIN)) {
        button_pressed = 0;  // Reset button pressed flag
    }
}

int main(void) {
    // Set LED and MOSFET pins as output
    DDRD |= (1 << LED_PIN) | (1 << MOSFET_PIN);

    // Set button pin as input with pull-up
    DDRD &= ~(1 << BUTTON_PIN);
    PORTD |= (1 << BUTTON_PIN);

    // Enable INT0 interrupt on falling edge (button press)
    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);
    sei();

    USART_Init(103); // 9600 baud at 16MHz

    while (1) {
        char cmd = USART_Receive();
        if (cmd == '1') {
            if (!humidifier_on) toggle_humidifier();
        } else if (cmd == '0') {
            if (humidifier_on) toggle_humidifier();
        }
    }
}
