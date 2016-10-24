#ifndef GPIO_EXP_REGS_H
#define GPIO_EXP_REGS_H

// 0x40 = start + (chip address << 1) + get

#define MCP23S17_CHIP0_GET  0x41
#define MCP23S17_CHIP1_GET  0x43
#define MCP23S17_CHIP2_GET  0x45
#define MCP23S17_CHIP3_GET  0x47
#define MCP23S17_CHIP4_GET  0x49
#define MCP23S17_CHIP5_GET  0x4B
#define MCP23S17_CHIP6_GET  0x4D
#define MCP23S17_CHIP7_GET  0x4F

#define MCP23S17_CHIP0_SET  0x40
#define MCP23S17_CHIP1_SET  0x42
#define MCP23S17_CHIP2_SET  0x44
#define MCP23S17_CHIP3_SET  0x46
#define MCP23S17_CHIP4_SET  0x48
#define MCP23S17_CHIP5_SET  0x4A
#define MCP23S17_CHIP6_SET  0x4C
#define MCP23S17_CHIP7_SET  0x4E

//IOCON.Bank = 0!

#define MCP23S17_IODIRA      0x00
#define MCP23S17_IODIRB      0x01
#define MCP23S17_IPOLA       0x02
#define MCP23S17_IPOLB       0x03
#define MCP23S17_GPINTENA    0x04
#define MCP23S17_GPINTENB    0x05
#define MCP23S17_DEFVALA     0x06
#define MCP23S17_DEFVALB     0x07
#define MCP23S17_INTCONA     0x08
#define MCP23S17_INTCONB     0x09
#define MCP23S17_IOCONA      0x0A
#define MCP23S17_IOCONB      0x0B
#define MCP23S17_GPPUA       0x0C
#define MCP23S17_GPPUB       0x0D
#define MCP23S17_INTFA       0x0E
#define MCP23S17_INTFB       0x0F
#define MCP23S17_INTCAPA     0x10
#define MCP23S17_INTCAPB     0x11
#define MCP23S17_GPIOA       0x12
#define MCP23S17_GPIOB       0x13
#define MCP23S17_OLATA       0x14
#define MCP23S17_OLATB       0x15


//IOCON bits
#define MCP23S17_INTPOL  0x02
#define MCP23S17_ODR     0x04
#define MCP23S17_HAEN    0x08
#define MCP23S17_DISSLW  0x10
#define MCP23S17_SEQOP   0x20
#define MCP23S17_MIRROR  0x40
#define MCP23S17_BANK    0x80

#endif /* GPIO_EXP_REGS_H */

