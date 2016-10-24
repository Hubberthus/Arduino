
#ifdef ARDUINO_ESP_EXTRA

#include "Arduino.h"
#include "gpio_expansion.h"
#include "gpio_exp_devs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*voidFuncPtr)(void);

volatile uint8_t PORT_LIST[4] = {0, 0, 0, 0};
volatile uint8_t PORT_DIR[4] = {0xFF, 0xFF, 0xFF, 0xFF};
volatile uint8_t PORT_PUUP[4] = {0, 0, 0, 0};

void _gpio_expansion_startup() {
	_mcp23s17_init(CS_MCP23S17);
	_mcp3008_init(CS_MCP3008);
	attachInterrupt(INT_GPIO, _gpio_expansion_read_digital, FALLING);
}

void _gpio_expansion_read_digital() {

	noInterrupts();

	while ( ! digitalRead(INT_GPIO)) {
		PORTA = _mcp23s17_getA(0);
		PORTB = _mcp23s17_getB(0);
		PORTC = _mcp23s17_getA(1);
		PORTD = _mcp23s17_getB(1);
	}

	interrupts();
}

void _gpio_expansion_set_pin(uint8_t pin, uint8_t val) {

	noInterrupts();

	pin -= NUM_INTERNAL_PINS;
	switch(pin / 8) {
	case 0:
		if (PORTA_DIR & (1 << (pin % 8))) return;
		if(val) PORTA |= (1 << (pin % 8));
		else PORTA &= ~(1 << (pin % 8));
		_mcp23s17_setA(0, PORTA);
		break;
	case 1:
		if (PORTB_DIR & (1 << (pin % 8))) return;
		if(val) PORTB |= (1 << (pin % 8));
		else PORTB &= ~(1 << (pin % 8));
		_mcp23s17_setB(0, PORTB);
		break;
	case 2:
		if (PORTC_DIR & (1 << (pin % 8))) return;
		if(val) PORTC |= (1 << (pin % 8));
		else PORTC &= ~(1 << (pin % 8));
		_mcp23s17_setA(1, PORTC);
		break;
	case 3:
		if (PORTD_DIR & (1 << (pin % 8))) return;
		if(val) PORTD |= (1 << (pin % 8));
		else PORTD &= ~(1 << (pin % 8));
		_mcp23s17_setB(1, PORTD);
		break;
	}

	interrupts();
}

void _gpio_expansion_pin_mode(uint8_t pin, uint8_t mode) {

	if ((mode != INPUT) && (mode != OUTPUT) && (mode != INPUT_PULLUP)) {
		return;
	}

	noInterrupts();

	pin -= NUM_INTERNAL_PINS;
	switch(pin / 8) {
	case 0:
		if (mode == OUTPUT) {
			PORTA_DIR &= ~(1 << (pin % 8));
			_mcp23s17_setReg(0, MCP23S17_IODIRA, PORTA_DIR);
			_mcp23s17_setReg(0, MCP23S17_GPINTENA, PORTA_DIR);
			_mcp23s17_setA(0, PORTA);
		} else {
			PORTA_DIR |= (1 << (pin % 8));
			_mcp23s17_setReg(0, MCP23S17_IODIRA, PORTA_DIR);
			_mcp23s17_setReg(0, MCP23S17_GPINTENA, PORTA_DIR);
			if (mode == INPUT_PULLUP) {
				PORTA_PUUP |= (1 << (pin % 8));
			} else {
				PORTA_PUUP &= ~(1 << (pin % 8));
			}
			_mcp23s17_setReg(0, MCP23S17_GPPUA, PORTA_PUUP);
			PORTA = _mcp23s17_getA(0);
		}
		break;
	case 1:
		if (mode == OUTPUT) {
			PORTB_DIR &= ~(1 << (pin % 8));
			_mcp23s17_setReg(0, MCP23S17_IODIRB, PORTB_DIR);
			_mcp23s17_setReg(0, MCP23S17_GPINTENB, PORTB_DIR);
			_mcp23s17_setB(0, PORTB);
		} else {
			PORTB_DIR |= (1 << (pin % 8));
			_mcp23s17_setReg(0, MCP23S17_IODIRB, PORTB_DIR);
			_mcp23s17_setReg(0, MCP23S17_GPINTENB, PORTB_DIR);
			if (mode == INPUT_PULLUP) {
				PORTB_PUUP |= (1 << (pin % 8));
			} else {
				PORTB_PUUP &= ~(1 << (pin % 8));
			}
			_mcp23s17_setReg(0, MCP23S17_GPPUB, PORTB_PUUP);
			PORTB = _mcp23s17_getB(0);
		}
		break;
	case 2:
		if (mode == OUTPUT) {
			PORTC_DIR &= ~(1 << (pin % 8));
			_mcp23s17_setReg(1, MCP23S17_IODIRA, PORTC_DIR);
			_mcp23s17_setReg(1, MCP23S17_GPINTENA, PORTC_DIR);
			_mcp23s17_setA(1, PORTC);
		} else {
			PORTC_DIR |= (1 << (pin % 8));
			_mcp23s17_setReg(1, MCP23S17_IODIRA, PORTC_DIR);
			_mcp23s17_setReg(1, MCP23S17_GPINTENA, PORTC_DIR);
			if (mode == INPUT_PULLUP) {
				PORTC_PUUP |= (1 << (pin % 8));
			} else {
				PORTC_PUUP &= ~(1 << (pin % 8));
			}
			_mcp23s17_setReg(1, MCP23S17_GPPUA, PORTC_PUUP);
			PORTC = _mcp23s17_getA(1);
		}
		break;
	case 3:
		if (mode == OUTPUT) {
			PORTD_DIR &= ~(1 << (pin % 8));
			_mcp23s17_setReg(1, MCP23S17_IODIRB, PORTD_DIR);
			_mcp23s17_setReg(1, MCP23S17_GPINTENB, PORTD_DIR);
			_mcp23s17_setB(1, PORTD);
		} else {
			PORTD_DIR |= (1 << (pin % 8));
			_mcp23s17_setReg(1, MCP23S17_IODIRB, PORTD_DIR);
			_mcp23s17_setReg(1, MCP23S17_GPINTENB, PORTD_DIR);
			if (mode == INPUT_PULLUP) {
				PORTD_PUUP |= (1 << (pin % 8));
			} else {
				PORTD_PUUP &= ~(1 << (pin % 8));
			}
			_mcp23s17_setReg(1, MCP23S17_GPPUB, PORTD_PUUP);
			PORTD = _mcp23s17_getB(1);
		}
		break;
	}

	interrupts();
}

uint16_t _gpio_expansion_analog_read(uint8_t pin) {

	uint16_t retVal = 0;

	noInterrupts();

	retVal = _mcp3008_read(pin);

	interrupts();

	return retVal;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

