/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include "HardwareSerial.h"
#include "SERCOM.h"


#include <cstddef>

class Uart : public HardwareSerial
{
  public:
    Uart(SERCOM *_s);
    void begin(unsigned long baudRate);
    void begin(unsigned long baudrate, uint16_t config);
     

  private:
    SERCOM *sercom;
   
    uint8_t bufferTx[16u];

	/* 
	UART RX buffer requires one extra element for proper operation. One element
	* remains empty while operation. Keeping this element empty simplifies
	* circular buffer operation.
	*/
	uint8_t bufferRx[17u];
    
};
