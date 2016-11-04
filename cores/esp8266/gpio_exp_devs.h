#ifndef GPIO_EXP_DEVS_H
#define GPIO_EXP_DEVS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio_exp_regs.h"

// This defines are not representing the real Divider of the ESP8266
// the Defines match to an AVR Arduino on 16MHz for better compatibility
// (Copied from SPI library)
#define SPI_CLOCK_DIV2 		0x00101001 //8 MHz
#define SPI_CLOCK_DIV4 		0x00241001 //4 MHz
#define SPI_CLOCK_DIV8 		0x004c1001 //2 MHz
#define SPI_CLOCK_DIV16 	0x009c1001 //1 MHz
#define SPI_CLOCK_DIV32 	0x013c1001 //500 KHz
#define SPI_CLOCK_DIV64 	0x027c1001 //250 KHz
#define SPI_CLOCK_DIV128 	0x04fc1001 //125 KHz

#define SPI_CLOCK_10MHz 	0x000C1001

extern uint8_t _mcp23s17_cs_pin;
extern uint8_t _mcp3008_cs_pin;

void _mcp23s17_init(uint8_t chipSelectPin);
void _mcp23s17_init_regs();
uint8_t _mcp23s17_reg(uint8_t chip, uint8_t ctrl_reg, uint8_t value);
#define _mcp23s17_setReg(ID, ctrl_reg, value) _mcp23s17_reg(MCP23S17_CHIP ## ID ## _SET, ctrl_reg, value)
#define _mcp23s17_getReg(ID, ctrl_reg) _mcp23s17_reg(MCP23S17_CHIP ## ID ## _GET, ctrl_reg, 0)

#define _mcp23s17_setA(ID, value) _mcp23s17_reg(MCP23S17_CHIP ## ID ## _SET, MCP23S17_OLATA, value)
#define _mcp23s17_setB(ID, value) _mcp23s17_reg(MCP23S17_CHIP ## ID ## _SET, MCP23S17_OLATB, value)

#define _mcp23s17_getA(ID) _mcp23s17_reg(MCP23S17_CHIP ## ID ## _GET, MCP23S17_GPIOA, 0)
#define _mcp23s17_getB(ID) _mcp23s17_reg(MCP23S17_CHIP ## ID ## _GET, MCP23S17_GPIOB, 0)

void _mcp3008_init(uint8_t mcp3008_cs_pin);
void _mcp3008_init_regs();
uint16_t _mcp3008_read(uint8_t pin);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* GPIO_EXP_DEVS_H */

