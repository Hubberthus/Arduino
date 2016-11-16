
#ifdef ARDUINO_ESP_EXTRA

#include "Arduino.h"
#include "gpio_expansion.h"
#include "gpio_exp_devs.h"

#ifdef __cplusplus
extern "C" {
#endif

volatile uint8_t PORT_LIST[4] = {0,};
volatile uint8_t PORT_DIR[4] = {0xFF,};
volatile uint8_t PORT_PUUP[4] = {0,};
volatile uint8_t PORT_INT[4] = {0,};
volatile uint8_t PORT_INT_CON[4] = {0,};
volatile uint8_t PORT_INT_DEFVAL[4] = {0,};

#define PORTA_INT PORT_INT[0]
#define PORTB_INT PORT_INT[1]
#define PORTC_INT PORT_INT[2]
#define PORTD_INT PORT_INT[3]

#define PORTA_INT_CON PORT_INT_CON[0]
#define PORTB_INT_CON PORT_INT_CON[1]
#define PORTC_INT_CON PORT_INT_CON[2]
#define PORTD_INT_CON PORT_INT_CON[3]

#define PORTA_INT_DEFVAL PORT_INT_DEFVAL[0]
#define PORTB_INT_DEFVAL PORT_INT_DEFVAL[1]
#define PORTC_INT_DEFVAL PORT_INT_DEFVAL[2]
#define PORTD_INT_DEFVAL PORT_INT_DEFVAL[3]

typedef struct {
  uint8_t mode;
  void (*fn)(void);
} interrupt_handler_t;

static interrupt_handler_t PORT_INT_FUNC[NUM_EXTERNAL_DIGITAL_PINS];

void _gpio_expansion_startup() {
	_mcp23s17_init(CS_MCP23S17);
	_mcp3008_init(CS_MCP3008);
	pinMode(INT_GPIO, INPUT_PULLUP);
}

void _gpio_expansion_pinMode(uint8_t pin, uint8_t mode) {

	uint32_t savedPS = xt_rsil(15); // stop other interrupts
	uint32_t mask = 0;

	if ((mode != INPUT) && (mode != OUTPUT) && (mode != INPUT_PULLUP)) {
		xt_wsr_ps(savedPS);
		return;
	}

	pin -= NUM_INTERNAL_PINS;

	if (pin >= NUM_EXTERNAL_DIGITAL_PINS) {
		xt_wsr_ps(savedPS);
		return;
	}

	mask = (1 << pin);

	_mcp23s17_transaction_start();

	switch(pin >> 3) {
	case 0:
		if (mode == OUTPUT) {
			PORTA_DIR &= ~mask;
			PORTA_INT &= ~mask;
			interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
			handler->mode = 0;
			handler->fn = 0;
			_mcp23s17_setReg(0, MCP23S17_IODIRA, PORTA_DIR);
			_mcp23s17_setReg(0, MCP23S17_GPINTENA, PORTA_INT);
			_mcp23s17_setA(0, PORTA);
		} else {
			PORTA_DIR |= mask;
			_mcp23s17_setReg(0, MCP23S17_IODIRA, PORTA_DIR);
			if (mode == INPUT_PULLUP) {
				PORTA_PUUP |= mask;
			} else {
				PORTA_PUUP &= ~mask;
			}
			_mcp23s17_setReg(0, MCP23S17_GPPUA, PORTA_PUUP);
			PORTA = _mcp23s17_getA(0);
		}
		break;
	case 1:
		if (mode == OUTPUT) {
			PORTB_DIR &= ~mask;
			PORTB_INT &= ~mask;
			interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
			handler->mode = 0;
			handler->fn = 0;
			_mcp23s17_setReg(0, MCP23S17_IODIRB, PORTB_DIR);
			_mcp23s17_setReg(0, MCP23S17_GPINTENB, PORTB_INT);
			_mcp23s17_setB(0, PORTB);
		} else {
			PORTB_DIR |= mask;
			_mcp23s17_setReg(0, MCP23S17_IODIRB, PORTB_DIR);
			if (mode == INPUT_PULLUP) {
				PORTB_PUUP |= mask;
			} else {
				PORTB_PUUP &= ~mask;
			}
			_mcp23s17_setReg(0, MCP23S17_GPPUB, PORTB_PUUP);
			PORTB = _mcp23s17_getB(0);
		}
		break;
	case 2:
		if (mode == OUTPUT) {
			PORTC_DIR &= ~mask;
			PORTC_INT &= ~mask;
			interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
			handler->mode = 0;
			handler->fn = 0;
			_mcp23s17_setReg(1, MCP23S17_IODIRA, PORTC_DIR);
			_mcp23s17_setReg(1, MCP23S17_GPINTENA, PORTC_INT);
			_mcp23s17_setA(1, PORTC);
		} else {
			PORTC_DIR |= mask;
			_mcp23s17_setReg(1, MCP23S17_IODIRA, PORTC_DIR);
			if (mode == INPUT_PULLUP) {
				PORTC_PUUP |= mask;
			} else {
				PORTC_PUUP &= ~mask;
			}
			_mcp23s17_setReg(1, MCP23S17_GPPUA, PORTC_PUUP);
			PORTC = _mcp23s17_getA(1);
		}
		break;
	case 3:
		if (mode == OUTPUT) {
			PORTD_DIR &= ~mask;
			PORTD_INT &= ~mask;
			interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
			handler->mode = 0;
			handler->fn = 0;
			_mcp23s17_setReg(1, MCP23S17_IODIRB, PORTD_DIR);
			_mcp23s17_setReg(1, MCP23S17_GPINTENB, PORTD_INT);
			_mcp23s17_setB(1, PORTD);
		} else {
			PORTD_DIR |= mask;
			_mcp23s17_setReg(1, MCP23S17_IODIRB, PORTD_DIR);
			if (mode == INPUT_PULLUP) {
				PORTD_PUUP |= mask;
			} else {
				PORTD_PUUP &= ~mask;
			}
			_mcp23s17_setReg(1, MCP23S17_GPPUB, PORTD_PUUP);
			PORTD = _mcp23s17_getB(1);
		}
		break;
	}

	xt_wsr_ps(savedPS);
}

uint8_t _gpio_expansion_digitalRead(uint8_t pin) {

	uint32_t savedPS = xt_rsil(15); // stop other interrupts
	uint32_t mask = 0;

	pin -= NUM_INTERNAL_PINS;

	if (pin >= NUM_EXTERNAL_DIGITAL_PINS) {
		xt_wsr_ps(savedPS);
		return 0;
	}

	mask = (1 << pin);

	if ( ! (PORT_DIR[0] & mask)) { // pin is OUTPUT
		xt_wsr_ps(savedPS);
		return (PORT_LIST[0] & mask);
	}

	_mcp23s17_transaction_start();

	switch(pin >> 3) {
	case 0:
		if ( ! (PORT_INT[0] & mask)) {
			PORT_INT[0] &= ~mask;
			PORT_INT[0] |= (_mcp23s17_getA(0) & mask);
		}
		break;
	case 1:
		if ( ! (PORT_INT[0] & mask)) {
			PORT_INT[0] &= ~mask;
			PORT_INT[0] |= (_mcp23s17_getB(0) & mask);
		}
		break;
	case 2:
		if ( ! (PORT_INT[0] & mask)) {
			PORT_INT[0] &= ~mask;
			PORT_INT[0] |= (_mcp23s17_getA(1) & mask);
		}
		break;
	case 3:
		if ( ! (PORT_INT[0] & mask)) {
			PORT_INT[0] &= ~mask;
			PORT_INT[0] |= (_mcp23s17_getB(1) & mask);
		}
		break;
	}

	xt_wsr_ps(savedPS);

	return (PORT_LIST[0] & mask);
}

void _gpio_expansion_digitalWrite(uint8_t pin, uint8_t val) {

	uint32_t savedPS = xt_rsil(15); // stop other interrupts
	uint32_t mask = 0;

	pin -= NUM_INTERNAL_PINS;

	if (pin >= NUM_EXTERNAL_DIGITAL_PINS) {
		xt_wsr_ps(savedPS);
		return;
	}

	mask = (1 << pin);

	if (PORT_DIR[0] & mask) { // pin is not OUTPUT
		xt_wsr_ps(savedPS);
		return;
	}

	if(val) PORT_LIST[0] |= mask;
	else PORT_LIST[0] &= ~mask;

	_mcp23s17_transaction_start();

	switch(pin >> 3) {
	case 0:
		_mcp23s17_setA(0, PORTA);
		break;
	case 1:
		_mcp23s17_setB(0, PORTB);
		break;
	case 2:
		_mcp23s17_setA(1, PORTC);
		break;
	case 3:
		_mcp23s17_setB(1, PORTD);
		break;
	}

	xt_wsr_ps(savedPS);
}

void _gpio_expansion_interrupt_handler() {

	uint32_t savedPS = xt_rsil(15); // stop other interrupts
	uint8_t i = 0;
	uint8_t mask = 0;
	interrupt_handler_t *handler;

	if (PORTA_INT) {
		_mcp23s17_transaction_start();

		uint8_t port = _mcp23s17_getReg(0, MCP23S17_INTCAPA);
		for (i = 0, mask = 1; i < 8; ++i, mask <<= 1) {
			if ((PORTA_INT & mask) && ((port & mask) != (PORTA & mask))) {
				handler = &PORT_INT_FUNC[i];
				if (handler->fn &&
					(handler->mode == CHANGE ||
					 (handler->mode & 1) == (port & mask))) {
				  if ((port & mask)) PORTA |= (port & mask);
				  else PORTA &= ~(port & mask);
				  handler->fn();
				}
			}
		}
	}

	if (PORTB_INT) {
		_mcp23s17_transaction_start();

		uint8_t port = _mcp23s17_getReg(0, MCP23S17_INTCAPB);
		for (i = 0, mask = 1; i < 8; ++i, mask <<= 1) {
			if ((PORTB_INT & mask) && ((port & mask) != (PORTB & mask))) {
				handler = &PORT_INT_FUNC[i + 8];
				if (handler->fn &&
					(handler->mode == CHANGE ||
					 (handler->mode & 1) == (port & mask))) {
				  if ((port & mask)) PORTB |= (port & mask);
				  else PORTB &= ~(port & mask);
				  handler->fn();
				}
			}
		}
	}

	if (PORTC_INT) {
		_mcp23s17_transaction_start();

		uint8_t port = _mcp23s17_getReg(1, MCP23S17_INTCAPA);
		for (i = 0, mask = 1; i < 8; ++i, mask <<= 1) {
			if ((PORTC_INT & mask) && ((port & mask) != (PORTC & mask))) {
				handler = &PORT_INT_FUNC[i + 16];
				if (handler->fn &&
					(handler->mode == CHANGE ||
					 (handler->mode & 1) == (port & mask))) {
				  if ((port & mask)) PORTC |= (port & mask);
				  else PORTC &= ~(port & mask);
				  handler->fn();
				}
			}
		}
	}

	if (PORTD_INT) {
		_mcp23s17_transaction_start();

		uint8_t port = _mcp23s17_getReg(1, MCP23S17_INTCAPB);
		for (i = 0, mask = 1; i < 8; ++i, mask <<= 1) {
			if ((PORTD_INT & mask) && ((port & mask) != (PORTD & mask))) {
				handler = &PORT_INT_FUNC[i + 24];
				if (handler->fn &&
					(handler->mode == CHANGE ||
					 (handler->mode & 1) == (port & mask))) {
				  if ((port & mask)) PORTD |= (port & mask);
				  else PORTD &= ~(port & mask);
				  handler->fn();
				}
			}
		}
	}

	xt_wsr_ps(savedPS);
}

void _gpio_expansion_attachInterrupt(uint8_t pin, voidFuncPtr userFunc, int mode) {

	uint32_t savedPS = xt_rsil(15); // stop other interrupts
	uint32_t mask = 0;

	pin -= NUM_INTERNAL_PINS;

	if (pin >= NUM_EXTERNAL_DIGITAL_PINS) {
		xt_wsr_ps(savedPS);
		return;
	}

	mask = (1 << pin);

	if ( ! (PORT_DIR[0] & mask)) { // pin is OUTPUT
		xt_wsr_ps(savedPS);
		return;
	}

	interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
	handler->mode = mode;
	handler->fn = userFunc;

	if (PORT_INT[0] & mask) { // already an interrupt pin
		xt_wsr_ps(savedPS);
		return;
	}

	PORT_INT[0] |= mask;
	if (mode & 0x3) { // FALLING, RISING, CHANGE
		PORT_INT_CON[0] &= ~mask;
	} else if (mode & 0x1) {
		PORT_INT_CON[0] |= mask;
		PORT_INT_DEFVAL[0] &= ~mask;
	} else {
		PORT_INT_CON[0] |= mask;
		PORT_INT_DEFVAL[0] |= mask;
	}

	_mcp23s17_transaction_start();

	switch(pin >> 3) {
	case 0:
		_mcp23s17_setReg(0, MCP23S17_GPINTENA, PORTA_INT);
		_mcp23s17_setReg(0, MCP23S17_INTCONA, PORTA_INT_CON);
		_mcp23s17_setReg(0, MCP23S17_DEFVALA, PORTA_INT_DEFVAL);
		break;
	case 1:
		_mcp23s17_setReg(0, MCP23S17_GPINTENB, PORTB_INT);
		_mcp23s17_setReg(0, MCP23S17_INTCONB, PORTB_INT_CON);
		_mcp23s17_setReg(0, MCP23S17_DEFVALB, PORTB_INT_DEFVAL);
		break;
	case 2:
		_mcp23s17_setReg(1, MCP23S17_GPINTENA, PORTC_INT);
		_mcp23s17_setReg(1, MCP23S17_INTCONA, PORTC_INT_CON);
		_mcp23s17_setReg(1, MCP23S17_DEFVALA, PORTC_INT_DEFVAL);
		break;
	case 3:
		_mcp23s17_setReg(1, MCP23S17_GPINTENB, PORTD_INT);
		_mcp23s17_setReg(1, MCP23S17_INTCONB, PORTD_INT_CON);
		_mcp23s17_setReg(1, MCP23S17_DEFVALB, PORTD_INT_DEFVAL);
		break;
	}

	attachInterrupt(INT_GPIO, _gpio_expansion_interrupt_handler, ONLOW);

	xt_wsr_ps(savedPS);
}

void _gpio_expansion_detachInterrupt(uint8_t pin) {

	uint32_t savedPS = xt_rsil(15); // stop other interrupts
	uint32_t mask = 0;

	pin -= NUM_INTERNAL_PINS;

	if (pin >= NUM_EXTERNAL_DIGITAL_PINS) {
		xt_wsr_ps(savedPS);
		return;
	}

	mask = (1 << pin);

	if ( ! (PORT_DIR[0] & mask)) { // pin is OUTPUT
		xt_wsr_ps(savedPS);
		return;
	}

	if ( ! (PORT_INT[0] & mask)) { // not an interrupt pin
		xt_wsr_ps(savedPS);
		return;
	}

	interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
	handler->mode = 0;
	handler->fn = 0;

	PORT_INT[0] &= ~mask;

	_mcp23s17_transaction_start();

	switch(pin >> 3) {
	case 0:
		_mcp23s17_setReg(0, MCP23S17_GPINTENA, PORTA_INT);
		break;
	case 1:
		_mcp23s17_setReg(0, MCP23S17_GPINTENB, PORTB_INT);
		break;
	case 2:
		_mcp23s17_setReg(1, MCP23S17_GPINTENA, PORTC_INT);
		break;
	case 3:
		_mcp23s17_setReg(1, MCP23S17_GPINTENB, PORTD_INT);
		break;
	}

	if (( ! PORTA_INT) && ( ! PORTB_INT) && ( ! PORTC_INT) && ( ! PORTD_INT)) {
		detachInterrupt(INT_GPIO);
	}

	xt_wsr_ps(savedPS);
}

uint16_t _gpio_expansion_analogRead(uint8_t pin) {

	uint16_t retVal = 0;

	uint32_t savedPS = xt_rsil(15); // stop other interrupts

	_mcp3008_transaction_start();

	retVal = _mcp3008_read(pin);

	xt_wsr_ps(savedPS);

	return retVal;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

