
#ifdef ARDUINO_ESP_EXTRA

#ifdef __cplusplus
extern "C" {
#endif

#include "Arduino.h"
#include "gpio_exp_devs.h"

uint8_t _mcp23s17_cs_pin = -1;
uint8_t _mcp3008_cs_pin = -1;

void _mcp23s17_init(uint8_t mcp23s17_cs_pin) {

	_mcp23s17_cs_pin = mcp23s17_cs_pin;

	//init SPI bus
	pinMode(_mcp23s17_cs_pin, OUTPUT);
	digitalWrite(_mcp23s17_cs_pin, HIGH);
	pinMode(SCK, SPECIAL);
	pinMode(MISO, SPECIAL);
	pinMode(MOSI, SPECIAL);

	_mcp23s17_init_regs();

	//Enable hardware addressing, byte addressing, interrupt mirroring+open drain on all devices
	_mcp23s17_setReg(0, MCP23S17_IOCONA, MCP23S17_SEQOP|MCP23S17_HAEN|MCP23S17_MIRROR|MCP23S17_ODR);

	_mcp23s17_setReg(0, MCP23S17_IODIRA, 0xFF);
	_mcp23s17_setReg(0, MCP23S17_GPPUA, 0x00);
	_mcp23s17_setReg(0, MCP23S17_GPINTENA, 0xFF);
	_mcp23s17_setReg(0, MCP23S17_INTCONA, 0x00);
	_mcp23s17_getReg(0, MCP23S17_GPIOA);

	_mcp23s17_setReg(0, MCP23S17_IODIRB, 0xFF);
	_mcp23s17_setReg(0, MCP23S17_GPPUB, 0x00);
	_mcp23s17_setReg(0, MCP23S17_GPINTENB, 0xFF);
	_mcp23s17_setReg(0, MCP23S17_INTCONB, 0x00);
	_mcp23s17_getReg(0, MCP23S17_GPIOB);

	_mcp23s17_setReg(1, MCP23S17_IODIRA, 0xFF);
	_mcp23s17_setReg(1, MCP23S17_GPPUA, 0x00);
	_mcp23s17_setReg(1, MCP23S17_GPINTENA, 0xFF);
	_mcp23s17_setReg(1, MCP23S17_INTCONA, 0x00);
	_mcp23s17_getReg(1, MCP23S17_GPIOA);

	_mcp23s17_setReg(1, MCP23S17_IODIRB, 0xFF);
	_mcp23s17_setReg(1, MCP23S17_GPPUB, 0x00);
	_mcp23s17_setReg(1, MCP23S17_GPINTENB, 0xFF);
	_mcp23s17_setReg(1, MCP23S17_INTCONB, 0x00);
	_mcp23s17_getReg(1, MCP23S17_GPIOB);
};

void ICACHE_RAM_ATTR _mcp23s17_init_regs() {
	SPI1C = 0;
	GPMUX &= ~(1 << 9);
	SPI1CLK = SPI_CLOCK_DIV4;
	SPI1U = SPIUMOSI | SPIUDUPLEX | SPIUSSE;
	SPI1U1 = (7 << SPILMOSI) | (7 << SPILMISO);
	SPI1C1 = 0;

	//  MSBFIRST bit order
	SPI1C &= ~(SPICWBO | SPICRBO);

	// SPI_MODE0 data mode:  CPOL: 0  CPHA: 0
	SPI1U &= ~(SPIUSME);
	SPI1P &= ~(1<<29);
}

uint8_t ICACHE_RAM_ATTR _mcp23s17_reg(uint8_t chip, uint8_t ctrl_reg, uint8_t value) {

	digitalWrite(_mcp23s17_cs_pin, LOW);

	while(SPI1CMD & SPIBUSY) {}

	SPI1W0 = chip;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	SPI1W0 = ctrl_reg;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	SPI1W0 = value;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}
	
	digitalWrite(_mcp23s17_cs_pin, HIGH);
	
	return SPI1W0;
};

_mcp3008_init(uint8_t mcp3008_cs_pin) {

	_mcp3008_cs_pin = mcp3008_cs_pin;

	//init SPI bus
	pinMode(_mcp3008_cs_pin, OUTPUT);
	digitalWrite(_mcp3008_cs_pin, HIGH);
	pinMode(SCK, SPECIAL);
	pinMode(MISO, SPECIAL);
	pinMode(MOSI, SPECIAL);

	_mcp3008_init_regs();
}

void ICACHE_RAM_ATTR _mcp3008_init_regs() {
	SPI1C = 0;
	GPMUX &= ~(1 << 9);
	SPI1CLK = SPI_CLOCK_DIV4;
	SPI1U = SPIUMOSI | SPIUDUPLEX | SPIUSSE;
	SPI1U1 = (7 << SPILMOSI) | (7 << SPILMISO);
	SPI1C1 = 0;

	//  MSBFIRST bit order
	SPI1C &= ~(SPICWBO | SPICRBO);

	// SPI_MODE0 data mode:  CPOL: 0  CPHA: 0
	SPI1U &= ~(SPIUSME);
	SPI1P &= ~(1<<29);
}

uint16_t ICACHE_RAM_ATTR _mcp3008_read(uint8_t pin) {

	uint16_t retVal = -1;

	digitalWrite(_mcp3008_cs_pin, LOW);

	while(SPI1CMD & SPIBUSY) {}

	SPI1W0 = (pin << 2) + 0x60;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	SPI1W0 = 0;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	retVal = SPI1W0 << 2;

	SPI1W0 = 0;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	retVal += (SPI1W0 & 0xC0) >> 6;

	digitalWrite(_mcp3008_cs_pin, HIGH);

	return retVal;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
