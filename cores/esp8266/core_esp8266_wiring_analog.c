/*
  analog.c - analogRead implementation for esp8266

  Copyright (c) 2015 Hristo Gochkov. All rights reserved.
  This file is part of the esp8266 core for Arduino environment.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


  18/06/2015 analogRead bugfix by Testato
*/

#include "wiring_private.h"
#include "pins_arduino.h"
#include "gpio_exp_devs.h"


extern int __analogRead(uint8_t pin)
{
    // accept both A0 - A8 constants and ADC channel numbers
    if(pin == 17 || pin == 0) {
        return system_adc_read();
    }

#ifdef ARDUINO_ESP_EXTRA
    else if(pin < A1) {
        return _mcp3008_read(pin - 1);
    } else if(pin <= A8) {
        return _mcp3008_read(pin - A1);
    }
#endif

    return digitalRead(pin) * 1023;
}

extern int analogRead(uint8_t pin) __attribute__ ((weak, alias("__analogRead")));
