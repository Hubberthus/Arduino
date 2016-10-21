#ifdef ARDUINO_ESP_EXTRA

#include "Arduino.h"
#include "gpio_expansion.h"
#include "mcp23s17.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*voidFuncPtr)(void);

volatile uint8_t PORT_LIST[4] = {0, 0, 0, 0};
volatile uint8_t PORT_DIR[4] = {0xFF, 0xFF, 0xFF, 0xFF};
volatile uint8_t PORT_PUUP[4] = {0, 0, 0, 0};

void _gpio_expansion_startup() {
	_mcp23s17_init(CS_GPIO);
	attachInterrupt(INT_GPIO, _gpio_expansion_read_all, FALLING);
}

void ICACHE_RAM_ATTR _gpio_expansion_read_all() {

	noInterrupts();

	while ( ! digitalRead(INT_GPIO)) {
		PORTA = _mcp23s17_getA(MCP23S17_CHIP0);
		PORTB = _mcp23s17_getB(MCP23S17_CHIP0);
		PORTC = _mcp23s17_getA(MCP23S17_CHIP1);
		PORTD = _mcp23s17_getB(MCP23S17_CHIP1);
	}

	interrupts();
}

void ICACHE_RAM_ATTR _gpio_expansion_set_pin(uint8_t pin, uint8_t val) {

	noInterrupts();

	pin -= NUM_INTERNAL_PINS;
	switch(pin / 8) {
	case 0:
		if (PORTA_DIR & (1 << (pin % 8))) return;
		if(val) PORTA |= (1 << (pin % 8));
		else PORTA &= ~(1 << (pin % 8));
		_mcp23s17_setA(MCP23S17_CHIP0, PORTA);
		break;
	case 1:
		if (PORTB_DIR & (1 << (pin % 8))) return;
		if(val) PORTB |= (1 << (pin % 8));
		else PORTB &= ~(1 << (pin % 8));
		_mcp23s17_setB(MCP23S17_CHIP0, PORTB);
		break;
	case 2:
		if (PORTC_DIR & (1 << (pin % 8))) return;
		if(val) PORTC |= (1 << (pin % 8));
		else PORTC &= ~(1 << (pin % 8));
		_mcp23s17_setA(MCP23S17_CHIP1, PORTC);
		break;
	case 3:
		if (PORTD_DIR & (1 << (pin % 8))) return;
		if(val) PORTD |= (1 << (pin % 8));
		else PORTD &= ~(1 << (pin % 8));
		_mcp23s17_setB(MCP23S17_CHIP1, PORTD);
		break;
	}

	interrupts();
}

void ICACHE_RAM_ATTR _gpio_expansion_pin_mode(uint8_t pin, uint8_t mode) {

	if ((mode != INPUT) && (mode != OUTPUT) && (mode != INPUT_PULLUP)) {
		return;
	}

	noInterrupts();

	pin -= NUM_INTERNAL_PINS;
	switch(pin / 8) {
	case 0:
		if (mode == OUTPUT) {
			PORTA_DIR &= ~(1 << (pin % 8));
			_mcp23s17_setReg(MCP23S17_IODIRA, MCP23S17_CHIP0, PORTA_DIR);
			_mcp23s17_setReg(MCP23S17_GPINTENA, MCP23S17_CHIP0, PORTA_DIR);
			_mcp23s17_setA(MCP23S17_CHIP0, PORTA);
		} else {
			PORTA_DIR |= (1 << (pin % 8));
			_mcp23s17_setReg(MCP23S17_IODIRA, MCP23S17_CHIP0, PORTA_DIR);
			_mcp23s17_setReg(MCP23S17_GPINTENA, MCP23S17_CHIP0, PORTA_DIR);
			if (mode == INPUT_PULLUP) {
				PORTA_PUUP |= (1 << (pin % 8));
			} else {
				PORTA_PUUP &= ~(1 << (pin % 8));
			}
			_mcp23s17_setReg(MCP23S17_GPPUA, MCP23S17_CHIP0, PORTA_PUUP);
			PORTA = _mcp23s17_getA(MCP23S17_CHIP0);
		}
		break;
	case 1:
		if (mode == OUTPUT) {
			PORTB_DIR &= ~(1 << (pin % 8));
			_mcp23s17_setReg(MCP23S17_IODIRB, MCP23S17_CHIP0, PORTB_DIR);
			_mcp23s17_setReg(MCP23S17_GPINTENB, MCP23S17_CHIP0, PORTB_DIR);
			_mcp23s17_setB(MCP23S17_CHIP0, PORTB);
		} else {
			PORTB_DIR |= (1 << (pin % 8));
			_mcp23s17_setReg(MCP23S17_IODIRB, MCP23S17_CHIP0, PORTB_DIR);
			_mcp23s17_setReg(MCP23S17_GPINTENB, MCP23S17_CHIP0, PORTB_DIR);
			if (mode == INPUT_PULLUP) {
				PORTB_PUUP |= (1 << (pin % 8));
			} else {
				PORTB_PUUP &= ~(1 << (pin % 8));
			}
			_mcp23s17_setReg(MCP23S17_GPPUB, MCP23S17_CHIP0, PORTB_PUUP);
			PORTB = _mcp23s17_getB(MCP23S17_CHIP0);
		}
		break;
	case 2:
		if (mode == OUTPUT) {
			PORTC_DIR &= ~(1 << (pin % 8));
			_mcp23s17_setReg(MCP23S17_IODIRA, MCP23S17_CHIP1, PORTC_DIR);
			_mcp23s17_setReg(MCP23S17_GPINTENA, MCP23S17_CHIP1, PORTC_DIR);
			_mcp23s17_setA(MCP23S17_CHIP1, PORTC);
		} else {
			PORTC_DIR |= (1 << (pin % 8));
			_mcp23s17_setReg(MCP23S17_IODIRA, MCP23S17_CHIP1, PORTC_DIR);
			_mcp23s17_setReg(MCP23S17_GPINTENA, MCP23S17_CHIP1, PORTC_DIR);
			if (mode == INPUT_PULLUP) {
				PORTC_PUUP |= (1 << (pin % 8));
			} else {
				PORTC_PUUP &= ~(1 << (pin % 8));
			}
			_mcp23s17_setReg(MCP23S17_GPPUA, MCP23S17_CHIP1, PORTC_PUUP);
			PORTC = _mcp23s17_getA(MCP23S17_CHIP1);
		}
		break;
	case 3:
		if (mode == OUTPUT) {
			PORTD_DIR &= ~(1 << (pin % 8));
			_mcp23s17_setReg(MCP23S17_IODIRB, MCP23S17_CHIP1, PORTD_DIR);
			_mcp23s17_setReg(MCP23S17_GPINTENB, MCP23S17_CHIP1, PORTD_DIR);
			_mcp23s17_setB(MCP23S17_CHIP1, PORTD);
		} else {
			PORTD_DIR |= (1 << (pin % 8));
			_mcp23s17_setReg(MCP23S17_IODIRB, MCP23S17_CHIP1, PORTD_DIR);
			_mcp23s17_setReg(MCP23S17_GPINTENB, MCP23S17_CHIP1, PORTD_DIR);
			if (mode == INPUT_PULLUP) {
				PORTD_PUUP |= (1 << (pin % 8));
			} else {
				PORTD_PUUP &= ~(1 << (pin % 8));
			}
			_mcp23s17_setReg(MCP23S17_GPPUB, MCP23S17_CHIP1, PORTD_PUUP);
			PORTD = _mcp23s17_getB(MCP23S17_CHIP1);
		}
		break;
	}

	interrupts();
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

