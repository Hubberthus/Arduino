
#ifdef ARDUINO_ESP_EXTRA

#include "Arduino.h"
#include "gpio_expansion.h"
#include "gpio_exp_devs.h"

#ifdef __cplusplus
extern "C" {
#endif

volatile uint32_t PORT_VAL = 0;
volatile uint32_t PORT_DIR = 0xFFFFFFFF;
volatile uint32_t PORT_PUUP = 0;
volatile uint32_t PORT_INT = 0;
volatile uint32_t PORT_INT_CON = 0;
volatile uint32_t PORT_INT_DEFVAL = 0;

#define PORTA_INT ((uint8_t*)&PORT_INT)[0]
#define PORTB_INT ((uint8_t*)&PORT_INT)[1]
#define PORTC_INT ((uint8_t*)&PORT_INT)[2]
#define PORTD_INT ((uint8_t*)&PORT_INT)[3]

#define PORTA_INT_CON ((uint8_t*)&PORT_INT_CON)[0]
#define PORTB_INT_CON ((uint8_t*)&PORT_INT_CON)[1]
#define PORTC_INT_CON ((uint8_t*)&PORT_INT_CON)[2]
#define PORTD_INT_CON ((uint8_t*)&PORT_INT_CON)[3]

#define PORTA_INT_DEFVAL ((uint8_t*)&PORT_INT_DEFVAL)[0]
#define PORTB_INT_DEFVAL ((uint8_t*)&PORT_INT_DEFVAL)[1]
#define PORTC_INT_DEFVAL ((uint8_t*)&PORT_INT_DEFVAL)[2]
#define PORTD_INT_DEFVAL ((uint8_t*)&PORT_INT_DEFVAL)[3]

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

void gpio_expansion_flush() {

	uint32_t savedPS = xt_rsil(15); // stop other interrupts

	_mcp23s17_transaction_start();

	if (PORTA_DIR != 0xFF) _mcp23s17_setA(0, PORTA);
	if (PORTB_DIR != 0xFF) _mcp23s17_setB(0, PORTB);
	if (PORTC_DIR != 0xFF) _mcp23s17_setA(1, PORTC);
	if (PORTD_DIR != 0xFF) _mcp23s17_setB(1, PORTD);

	xt_wsr_ps(savedPS);
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
			PORT_DIR &= ~mask;
			PORT_INT &= ~mask;
			interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
			handler->mode = 0;
			handler->fn = NULL;
			_mcp23s17_setReg(0, MCP23S17_IODIRA, PORTA_DIR);
			_mcp23s17_setReg(0, MCP23S17_GPINTENA, PORTA_INT);
			_mcp23s17_setA(0, PORTA);
		} else {
			PORT_DIR |= mask;
			_mcp23s17_setReg(0, MCP23S17_IODIRA, PORTA_DIR);
			if (mode == INPUT_PULLUP) {
				PORT_PUUP |= mask;
			} else {
				PORT_PUUP &= ~mask;
			}
			_mcp23s17_setReg(0, MCP23S17_GPPUA, PORTA_PUUP);
			PORT_VAL &= ~mask;
			PORT_VAL |= (_mcp23s17_getA(0) & mask);
		}
		break;
	case 1:
		if (mode == OUTPUT) {
			PORT_DIR &= ~mask;
			PORT_INT &= ~mask;
			interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
			handler->mode = 0;
			handler->fn = NULL;
			_mcp23s17_setReg(0, MCP23S17_IODIRB, PORTB_DIR);
			_mcp23s17_setReg(0, MCP23S17_GPINTENB, PORTB_INT);
			_mcp23s17_setB(0, PORTB);
		} else {
			PORT_DIR |= mask;
			_mcp23s17_setReg(0, MCP23S17_IODIRB, PORTB_DIR);
			if (mode == INPUT_PULLUP) {
				PORT_PUUP |= mask;
			} else {
				PORT_PUUP &= ~mask;
			}
			_mcp23s17_setReg(0, MCP23S17_GPPUB, PORTB_PUUP);
			PORT_VAL &= ~mask;
			PORT_VAL |= ((_mcp23s17_getB(0) << 8) & mask);
		}
		break;
	case 2:
		if (mode == OUTPUT) {
			PORT_DIR &= ~mask;
			PORT_INT &= ~mask;
			interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
			handler->mode = 0;
			handler->fn = NULL;
			_mcp23s17_setReg(1, MCP23S17_IODIRA, PORTC_DIR);
			_mcp23s17_setReg(1, MCP23S17_GPINTENA, PORTC_INT);
			_mcp23s17_setA(1, PORTC);
		} else {
			PORT_DIR |= mask;
			_mcp23s17_setReg(1, MCP23S17_IODIRA, PORTC_DIR);
			if (mode == INPUT_PULLUP) {
				PORT_PUUP |= mask;
			} else {
				PORT_PUUP &= ~mask;
			}
			_mcp23s17_setReg(1, MCP23S17_GPPUA, PORTC_PUUP);
			PORT_VAL &= ~mask;
			PORT_VAL |= ((_mcp23s17_getA(1) << 16) & mask);
		}
		break;
	case 3:
		if (mode == OUTPUT) {
			PORT_DIR &= ~mask;
			PORT_INT &= ~mask;
			interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
			handler->mode = 0;
			handler->fn = NULL;
			_mcp23s17_setReg(1, MCP23S17_IODIRB, PORTD_DIR);
			_mcp23s17_setReg(1, MCP23S17_GPINTENB, PORTD_INT);
			_mcp23s17_setB(1, PORTD);
		} else {
			PORT_DIR |= mask;
			_mcp23s17_setReg(1, MCP23S17_IODIRB, PORTD_DIR);
			if (mode == INPUT_PULLUP) {
				PORT_PUUP |= mask;
			} else {
				PORT_PUUP &= ~mask;
			}
			_mcp23s17_setReg(1, MCP23S17_GPPUB, PORTD_PUUP);
			PORT_VAL &= ~mask;
			PORT_VAL |= ((_mcp23s17_getB(1) << 24) & mask);
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

	if ( ! (PORT_DIR & mask)) { // pin is OUTPUT, return it's value
		xt_wsr_ps(savedPS);
		return (PORT_VAL & mask);
	}

	_mcp23s17_transaction_start();

	switch(pin >> 3) {
	case 0:
		if ( ! (PORT_INT & mask)) {
			PORT_VAL &= ~mask;
			PORT_VAL |= (_mcp23s17_getA(0) & mask);
		}
		break;
	case 1:
		if ( ! (PORT_INT & mask)) {
			PORT_VAL &= ~mask;
			PORT_VAL |= ((_mcp23s17_getB(0) << 8) & mask);
		}
		break;
	case 2:
		if ( ! (PORT_INT & mask)) {
			PORT_VAL &= ~mask;
			PORT_VAL |= ((_mcp23s17_getA(1) << 16) & mask);
		}
		break;
	case 3:
		if ( ! (PORT_INT & mask)) {
			PORT_VAL &= ~mask;
			PORT_VAL |= ((_mcp23s17_getB(1) << 24) & mask);
		}
		break;
	}

	xt_wsr_ps(savedPS);

	return ((PORT_VAL & mask) != 0);
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

	if (PORT_DIR & mask) { // pin is INPUT, update pullup according to value
		if ((val == LOW) && (PORT_PUUP & mask)) {
			_gpio_expansion_pinMode(pin + NUM_INTERNAL_PINS, INPUT);
		} else if ((val == HIGH) && !(PORT_PUUP & mask)) {
			_gpio_expansion_pinMode(pin + NUM_INTERNAL_PINS, INPUT_PULLUP);
		}
		xt_wsr_ps(savedPS);
		return;
	}

	if(val) PORT_VAL |= mask;
	else PORT_VAL &= ~mask;

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
	uint32_t mask = 0;
	interrupt_handler_t *handler;

	if (PORTA_INT) {
		_mcp23s17_transaction_start();

		uint8_t port = _mcp23s17_getA(0);
		for (i = 0, mask = 1; i < 8; ++i, mask <<= 1) {
			if ((PORTA_INT & mask) && ((port & mask) != (PORTA & mask))) {
				handler = &PORT_INT_FUNC[i];
				if ((handler->mode == CHANGE ||
					 (handler->mode & 1) == (port & mask))) {
					PORT_VAL &= ~mask;
					PORT_VAL |= (port & mask);

				  if (handler->fn) handler->fn();
				}
			}
		}
	}

	if (PORTB_INT) {
		_mcp23s17_transaction_start();

		uint8_t port = _mcp23s17_getB(0);
		for (i = 0, mask = 1; i < 8; ++i, mask <<= 1) {
			if ((PORTB_INT & mask) && ((port & mask) != (PORTB & mask))) {
				handler = &PORT_INT_FUNC[i + 8];
				if ((handler->mode == CHANGE ||
					 (handler->mode & 1) == (port & mask))) {
					PORT_VAL &= ~(mask << 8);
					PORT_VAL |= ((uint32_t)port & mask) << 8;

				  if (handler->fn) handler->fn();
				}
			}
		}
	}

	if (PORTC_INT) {
		_mcp23s17_transaction_start();

		uint8_t port = _mcp23s17_getA(1);
		for (i = 0, mask = 1; i < 8; ++i, mask <<= 1) {
			if ((PORTC_INT & mask) && ((port & mask) != (PORTC & mask))) {
				handler = &PORT_INT_FUNC[i + 16];
				if ((handler->mode == CHANGE ||
					 (handler->mode & 1) == (port & mask))) {
					PORT_VAL &= ~(mask << 16);
					PORT_VAL |= ((uint32_t)port & mask) << 16;

				  if (handler->fn) handler->fn();
				}
			}
		}
	}

	if (PORTD_INT) {
		_mcp23s17_transaction_start();

		uint8_t port = _mcp23s17_getB(1);
		for (i = 0, mask = 1; i < 8; ++i, mask <<= 1) {
			if ((PORTD_INT & mask) && ((port & mask) != (PORTD & mask))) {
				handler = &PORT_INT_FUNC[i + 24];
				if ((handler->mode == CHANGE ||
					 (handler->mode & 1) == (port & mask))) {
					PORT_VAL &= ~(mask << 24);
					PORT_VAL |= ((uint32_t)port & mask) << 24;

				  if (handler->fn) handler->fn();
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

	if ( ! (PORT_DIR & mask)) { // pin is OUTPUT
		xt_wsr_ps(savedPS);
		return;
	}

	interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
	handler->mode = mode;
	handler->fn = userFunc;

	if (PORT_INT & mask) { // already an interrupt pin
		xt_wsr_ps(savedPS);
		return;
	}

	PORT_INT |= mask;
	if (mode & 0x3) { // FALLING, RISING, CHANGE
		PORT_INT_CON &= ~mask;
	} else if (mode & 0x1) {
		PORT_INT_CON |= mask;
		PORT_INT_DEFVAL &= ~mask;
	} else {
		PORT_INT_CON |= mask;
		PORT_INT_DEFVAL |= mask;
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

	if ( ! (PORT_DIR & mask)) { // pin is OUTPUT
		xt_wsr_ps(savedPS);
		return;
	}

	if ( ! (PORT_INT & mask)) { // not an interrupt pin
		xt_wsr_ps(savedPS);
		return;
	}

	interrupt_handler_t *handler = &PORT_INT_FUNC[pin];
	handler->mode = 0;
	handler->fn = 0;

	PORT_INT &= ~mask;

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

	if ( ! PORT_INT) {
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

