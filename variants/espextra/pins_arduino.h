/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis
  Modified for ESPExtra variant by Norbert Fekete, 2016.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "../generic/common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_EXTERNAL_DIGITAL_PINS  32
#define NUM_INTERNAL_DIGITAL_PINS  17
#define NUM_DIGITAL_PINS           (NUM_INTERNAL_DIGITAL_PINS + NUM_EXTERNAL_DIGITAL_PINS)
#define NUM_EXTERNAL_ANALOG_INPUTS 8
#define NUM_INTERNAL_ANALOG_INPUTS 1
#define NUM_ANALOG_INPUTS          (NUM_INTERNAL_ANALOG_INPUTS + NUM_EXTERNAL_ANALOG_INPUTS)
#define NUM_INTERNAL_PINS          (NUM_INTERNAL_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS)

#define digitalPinHasPWM(p)        (((p) >= NUM_INTERNAL_PINS && (p) < NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS)? 1 : 0)
#define digitalPinToInterrupt(p)   (((p) < EXTERNAL_NUM_INTERRUPTS) || digitalPinHasPWM(p)? (p) : NOT_AN_INTERRUPT)

#define digitalPinToPort(pin)       (((pin) < NUM_INTERNAL_PINS ? 0 : \
		((pin) < NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS ? PORT_LIST[0] : 0)))
#define digitalPinToBitMask(pin)    ((pin) < NUM_INTERNAL_PINS ? 1UL << (pin) : 1 << (pin - NUM_INTERNAL_PINS))
#define digitalPinToTimer(pin)      ((pin) < NUM_INTERNAL_PINS ? 0 : -1)
#define portOutputRegister(port)    ((pin) < NUM_INTERNAL_PINS ? (volatile uint32_t*) &GPO : PORT_LIST[0])
#define portInputRegister(port)     ((pin) < NUM_INTERNAL_PINS ? (volatile uint32_t*) &GPI : PORT_LIST[0])
#define portModeRegister(port)      ((pin) < NUM_INTERNAL_PINS ? (volatile uint32_t*) &GPE : PORT_LIST[0])

// ESP8266 pins

#define CS_MCP23S17  15  // D8: TX1/HCS (pull down on boot)
#define CS_MCP3008    2  // D4: bootstrap TX/blue LED (pull up on boot)
#define CS_0          4  // D2
#define CS_1          0  // D3: flash (pull up on boot)
#define CS_2         16  // D0: user/wake/red LED

#define INT_GPIO      5  // D1

#define SDA           4  // CS_0 / D2
#define SCL           0  // CS_1 / D3

// Expanded pins

#define LED_BUILTIN  (NUM_INTERNAL_PINS)
#define BUILTIN_LED  (NUM_INTERNAL_PINS)

// PORTA
#define D0  (NUM_INTERNAL_PINS)
#define D1  (NUM_INTERNAL_PINS + 1)
#define D2  (NUM_INTERNAL_PINS + 2)
#define D3  (NUM_INTERNAL_PINS + 3)
#define D4  (NUM_INTERNAL_PINS + 4)
#define D5  (NUM_INTERNAL_PINS + 5)
#define D6  (NUM_INTERNAL_PINS + 6)
#define D7  (NUM_INTERNAL_PINS + 7)
// PORTB
#define D8   (NUM_INTERNAL_PINS + 8)
#define D9   (NUM_INTERNAL_PINS + 9)
#define D10  (NUM_INTERNAL_PINS + 10)
#define D11  (NUM_INTERNAL_PINS + 11)
#define D12  (NUM_INTERNAL_PINS + 12)
#define D13  (NUM_INTERNAL_PINS + 13)
#define D14  (NUM_INTERNAL_PINS + 14)
#define D15  (NUM_INTERNAL_PINS + 15)
// PORTC
#define D16  (NUM_INTERNAL_PINS + 16)
#define D17  (NUM_INTERNAL_PINS + 17)
#define D18  (NUM_INTERNAL_PINS + 18)
#define D19  (NUM_INTERNAL_PINS + 19)
#define D20  (NUM_INTERNAL_PINS + 20)
#define D21  (NUM_INTERNAL_PINS + 21)
#define D22  (NUM_INTERNAL_PINS + 22)
#define D23  (NUM_INTERNAL_PINS + 23)
// PORTD
#define D24  (NUM_INTERNAL_PINS + 24)
#define D25  (NUM_INTERNAL_PINS + 25)
#define D26  (NUM_INTERNAL_PINS + 26)
#define D27  (NUM_INTERNAL_PINS + 27)
#define D28  (NUM_INTERNAL_PINS + 28)
#define D29  (NUM_INTERNAL_PINS + 29)
#define D30  (NUM_INTERNAL_PINS + 30)
#define D31  (NUM_INTERNAL_PINS + 31)

#define A1  (NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS)
#define A2  (NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 1)
#define A3  (NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 2)
#define A4  (NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 3)
#define A5  (NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 4)
#define A6  (NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 5)
#define A7  (NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 6)
#define A8  (NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 7)

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* Pins_Arduino_h */
