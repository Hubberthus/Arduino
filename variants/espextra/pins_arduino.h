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

// ESP8266 pins

static const uint8_t CS_MCP23S17 = 15;  // D8: TX1/HCS (pull down on boot)
static const uint8_t CS_MCP3008  =  2;  // D4: bootstrap TX/blue LED (pull up on boot)
static const uint8_t CS_0        =  4;  // D2
static const uint8_t CS_1        =  0;  // D3: flash (pull up on boot)
static const uint8_t CS_2        = 16;  // D0: user/wake/red LED

static const uint8_t INT_GPIO    =  5;  // D1

// Expanded pins

static const uint8_t LED_BUILTIN = NUM_INTERNAL_PINS;
static const uint8_t BUILTIN_LED = NUM_INTERNAL_PINS;

// PORTA
static const uint8_t D0  = NUM_INTERNAL_PINS;
static const uint8_t D1  = NUM_INTERNAL_PINS + 1;
static const uint8_t D2  = NUM_INTERNAL_PINS + 2;
static const uint8_t D3  = NUM_INTERNAL_PINS + 3;
static const uint8_t D4  = NUM_INTERNAL_PINS + 4;
static const uint8_t D5  = NUM_INTERNAL_PINS + 5;
static const uint8_t D6  = NUM_INTERNAL_PINS + 6;
static const uint8_t D7  = NUM_INTERNAL_PINS + 7;
// PORTB
static const uint8_t D8  = NUM_INTERNAL_PINS + 8;
static const uint8_t D9  = NUM_INTERNAL_PINS + 9;
static const uint8_t D10 = NUM_INTERNAL_PINS + 10;
static const uint8_t D11 = NUM_INTERNAL_PINS + 11;
static const uint8_t D12 = NUM_INTERNAL_PINS + 12;
static const uint8_t D13 = NUM_INTERNAL_PINS + 13;
static const uint8_t D14 = NUM_INTERNAL_PINS + 14;
static const uint8_t D15 = NUM_INTERNAL_PINS + 15;
// PORTC
static const uint8_t D16 = NUM_INTERNAL_PINS + 16;
static const uint8_t D17 = NUM_INTERNAL_PINS + 17;
static const uint8_t D18 = NUM_INTERNAL_PINS + 18;
static const uint8_t D19 = NUM_INTERNAL_PINS + 19;
static const uint8_t D20 = NUM_INTERNAL_PINS + 20;
static const uint8_t D21 = NUM_INTERNAL_PINS + 21;
static const uint8_t D22 = NUM_INTERNAL_PINS + 22;
static const uint8_t D23 = NUM_INTERNAL_PINS + 23;
// PORTD
static const uint8_t D24 = NUM_INTERNAL_PINS + 24;
static const uint8_t D25 = NUM_INTERNAL_PINS + 25;
static const uint8_t D26 = NUM_INTERNAL_PINS + 26;
static const uint8_t D27 = NUM_INTERNAL_PINS + 27;
static const uint8_t D28 = NUM_INTERNAL_PINS + 28;
static const uint8_t D29 = NUM_INTERNAL_PINS + 29;
static const uint8_t D30 = NUM_INTERNAL_PINS + 30;
static const uint8_t D31 = NUM_INTERNAL_PINS + 31;

static const uint8_t A1 = NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS;
static const uint8_t A2 = NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 1;
static const uint8_t A3 = NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 2;
static const uint8_t A4 = NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 3;
static const uint8_t A5 = NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 4;
static const uint8_t A6 = NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 5;
static const uint8_t A7 = NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 6;
static const uint8_t A8 = NUM_DIGITAL_PINS + NUM_INTERNAL_ANALOG_INPUTS + 7;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* Pins_Arduino_h */
