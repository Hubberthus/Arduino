#ifndef GPIO_EXPANSION_H
#define GPIO_EXPANSION_H

#include "stdint.h"

typedef void (*voidFuncPtr)(void);

extern volatile uint32_t PORT_VAL;
extern volatile uint32_t PORT_DIR;
extern volatile uint32_t PORT_PUUP;

#define PORTA ((uint8_t*)&PORT_VAL)[0]
#define PORTB ((uint8_t*)&PORT_VAL)[1]
#define PORTC ((uint8_t*)&PORT_VAL)[2]
#define PORTD ((uint8_t*)&PORT_VAL)[3]

#define PORTA_DIR ((uint8_t*)&PORT_DIR)[0]
#define PORTB_DIR ((uint8_t*)&PORT_DIR)[1]
#define PORTC_DIR ((uint8_t*)&PORT_DIR)[2]
#define PORTD_DIR ((uint8_t*)&PORT_DIR)[3]

#define PORTA_PUUP ((uint8_t*)&PORT_PUUP)[0]
#define PORTB_PUUP ((uint8_t*)&PORT_PUUP)[1]
#define PORTC_PUUP ((uint8_t*)&PORT_PUUP)[2]
#define PORTD_PUUP ((uint8_t*)&PORT_PUUP)[3]

void _gpio_expansion_startup();
uint8_t _gpio_expansion_digitalRead(uint8_t pin);
void _gpio_expansion_digitalWrite(uint8_t pin, uint8_t val);
void _gpio_expansion_pinMode(uint8_t pin, uint8_t mode);
void _gpio_expansion_attachInterrupt(uint8_t pin, voidFuncPtr userFunc, int mode);
void _gpio_expansion_detachInterrupt(uint8_t pin);
uint16_t _gpio_expansion_analogRead(uint8_t pin);

#endif /* GPIO_EXPANSION_H */
