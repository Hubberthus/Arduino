#ifndef GPIO_EXPANSION_H
#define GPIO_EXPANSION_H

typedef void (*voidFuncPtr)(void);

extern volatile uint8_t PORT_LIST[];
extern volatile uint8_t PORT_DIR[];
extern volatile uint8_t PORT_PUUP[];
extern volatile uint8_t PORT_INT[];

#define PORTA PORT_LIST[0]
#define PORTB PORT_LIST[1]
#define PORTC PORT_LIST[2]
#define PORTD PORT_LIST[3]

#define PORTA_DIR PORT_DIR[0]
#define PORTB_DIR PORT_DIR[1]
#define PORTC_DIR PORT_DIR[2]
#define PORTD_DIR PORT_DIR[3]

#define PORTA_PUUP PORT_PUUP[0]
#define PORTB_PUUP PORT_PUUP[1]
#define PORTC_PUUP PORT_PUUP[2]
#define PORTD_PUUP PORT_PUUP[3]

#define PORTA_INT PORT_INT[0]
#define PORTB_INT PORT_INT[1]
#define PORTC_INT PORT_INT[2]
#define PORTD_INT PORT_INT[3]

void _gpio_expansion_startup();
uint8_t _gpio_expansion_digitalRead(uint8_t pin);
void _gpio_expansion_digitalWrite(uint8_t pin, uint8_t val);
void _gpio_expansion_pinMode(uint8_t pin, uint8_t mode);
void _gpio_expansion_attachInterrupt(uint8_t pin, voidFuncPtr userFunc, int mode);
void _gpio_expansion_detachInterrupt(uint8_t pin);
uint16_t _gpio_expansion_analogRead(uint8_t pin);

#define PINA0   0
#define PINA1   1
#define PINA2   2
#define PINA3   3
#define PINA4   4
#define PINA5   5
#define PINA6   6
#define PINA7   7

#define PINB0   0
#define PINB1   1
#define PINB2   2
#define PINB3   3
#define PINB4   4
#define PINB5   5
#define PINB6   6
#define PINB7   7

#define PINC0   0
#define PINC1   1
#define PINC2   2
#define PINC3   3
#define PINC4   4
#define PINC5   5
#define PINC6   6
#define PINC7   7

#define PIND0   0
#define PIND1   1
#define PIND2   2
#define PIND3   3
#define PIND4   4
#define PIND5   5
#define PIND6   6
#define PIND7   7

#endif /* GPIO_EXPANSION_H */
