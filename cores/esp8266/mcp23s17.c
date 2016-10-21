#ifdef ARDUINO_ESP_EXTRA

#ifdef __cplusplus
extern "C" {
#endif

#include "Arduino.h"
#include "mcp23s17.h"

uint8_t _mcp23s17_cs_pin = -1;

void _mcp23s17_init(uint8_t chipSelectPin) {

	_mcp23s17_cs_pin = chipSelectPin;

	//init SPI bus
	pinMode(_mcp23s17_cs_pin, OUTPUT);
	digitalWrite(_mcp23s17_cs_pin, HIGH);
	pinMode(SCK, SPECIAL);
	pinMode(MISO, SPECIAL);
	pinMode(MOSI, SPECIAL);

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

	//Enable hardware addressing, byte addressing, interrupt mirroring+open drain on all devices
	_mcp23s17_setReg(MCP23S17_IOCONA, MCP23S17_CHIP0, MCP23S17_SEQOP|MCP23S17_HAEN|MCP23S17_MIRROR|MCP23S17_ODR);

	_mcp23s17_setReg(MCP23S17_IODIRA, MCP23S17_CHIP0, 0xFF);
	_mcp23s17_setReg(MCP23S17_GPPUA, MCP23S17_CHIP0, 0x00);
	_mcp23s17_setReg(MCP23S17_GPINTENA, MCP23S17_CHIP0, 0xFF);
	_mcp23s17_setReg(MCP23S17_INTCONA, MCP23S17_CHIP0, 0x00);
	_mcp23s17_getReg(MCP23S17_GPIOA, MCP23S17_CHIP0);

	_mcp23s17_setReg(MCP23S17_IODIRB, MCP23S17_CHIP0, 0xFF);
	_mcp23s17_setReg(MCP23S17_GPPUB, MCP23S17_CHIP0, 0x00);
	_mcp23s17_setReg(MCP23S17_GPINTENB, MCP23S17_CHIP0, 0xFF);
	_mcp23s17_setReg(MCP23S17_INTCONB, MCP23S17_CHIP0, 0x00);
	_mcp23s17_getReg(MCP23S17_GPIOB, MCP23S17_CHIP0);

	_mcp23s17_setReg(MCP23S17_IODIRA, MCP23S17_CHIP1, 0xFF);
	_mcp23s17_setReg(MCP23S17_GPPUA, MCP23S17_CHIP1, 0x00);
	_mcp23s17_setReg(MCP23S17_GPINTENA, MCP23S17_CHIP1, 0xFF);
	_mcp23s17_setReg(MCP23S17_INTCONA, MCP23S17_CHIP1, 0x00);
	_mcp23s17_getReg(MCP23S17_GPIOA, MCP23S17_CHIP1);

	_mcp23s17_setReg(MCP23S17_IODIRB, MCP23S17_CHIP1, 0xFF);
	_mcp23s17_setReg(MCP23S17_GPPUB, MCP23S17_CHIP1, 0x00);
	_mcp23s17_setReg(MCP23S17_GPINTENB, MCP23S17_CHIP1, 0xFF);
	_mcp23s17_setReg(MCP23S17_INTCONB, MCP23S17_CHIP1, 0x00);
	_mcp23s17_getReg(MCP23S17_GPIOB, MCP23S17_CHIP1);
};

void ICACHE_RAM_ATTR _mcp23s17_setReg(uint8_t ctrl_reg, uint8_t chip, uint8_t value) {

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
};

uint8_t ICACHE_RAM_ATTR _mcp23s17_getReg(uint8_t ctrl_reg, uint8_t chip) {

	digitalWrite(_mcp23s17_cs_pin, LOW);
	
	while(SPI1CMD & SPIBUSY) {}

	SPI1W0 = chip | 1;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	SPI1W0 = ctrl_reg;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	SPI1W0 = 0;
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	digitalWrite(_mcp23s17_cs_pin, HIGH);

	return SPI1W0;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif
