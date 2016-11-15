
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

	_mcp23s17_transaction_start();

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

void ICACHE_RAM_ATTR _mcp23s17_transaction_start() {
	SPI1C = 0;
	GPMUX &= ~(1 << 9);
	SPI1CLK = SPI_CLOCK_10MHz;
	SPI1U = SPIUMOSI | SPIUDUPLEX | SPIUSSE;
	SPI1U1 = (23 << SPILMOSI) | (23 << SPILMISO);
	SPI1C1 = 0;

	//  MSBFIRST bit order
	SPI1C &= ~(SPICWBO | SPICRBO);

	// SPI_MODE0 data mode:  CPOL: 0  CPHA: 0
	SPI1U &= ~(SPIUSME);
	SPI1P &= ~(1<<29);
}

uint8_t ICACHE_RAM_ATTR _mcp23s17_reg(uint8_t chip, uint8_t ctrl_reg, uint8_t value) {

	digitalWrite(_mcp23s17_cs_pin, LOW);

	SPI1W0 = (value << 16) | (ctrl_reg << 8) | (chip);
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}
	
	digitalWrite(_mcp23s17_cs_pin, HIGH);
	
	return (SPI1W0 >> 16);
};

_mcp3008_init(uint8_t mcp3008_cs_pin) {

	_mcp3008_cs_pin = mcp3008_cs_pin;

	//init SPI bus
	pinMode(_mcp3008_cs_pin, OUTPUT);
	digitalWrite(_mcp3008_cs_pin, HIGH);
	pinMode(SCK, SPECIAL);
	pinMode(MISO, SPECIAL);
	pinMode(MOSI, SPECIAL);
}

void ICACHE_RAM_ATTR _mcp3008_transaction_start() {
	SPI1C = 0;
	GPMUX &= ~(1 << 9);
	SPI1CLK = SPI_CLOCK_DIV4;
	SPI1U = SPIUMOSI | SPIUDUPLEX | SPIUSSE;
	SPI1U1 = (23 << SPILMOSI) | (23 << SPILMISO);
	SPI1C1 = 0;

	//  MSBFIRST bit order
	SPI1C &= ~(SPICWBO | SPICRBO);

	// SPI_MODE0 data mode:  CPOL: 0  CPHA: 0
	SPI1U &= ~(SPIUSME);
	SPI1P &= ~(1<<29);
}

uint16_t ICACHE_RAM_ATTR _mcp3008_read(uint8_t pin) {

	digitalWrite(_mcp3008_cs_pin, LOW);

	SPI1W0 = (0x60) | (pin << 2);
	SPI1CMD |= SPIBUSY;
	while(SPI1CMD & SPIBUSY) {}

	digitalWrite(_mcp3008_cs_pin, HIGH);

	return ((SPI1W0 >> 6) & 0x3FC) | ((SPI1W0 >> 16) & 0x3);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
