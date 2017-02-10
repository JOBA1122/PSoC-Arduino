/*
  Copyright (c) 2014 Arduino.  All right reserved.

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

#include "SERCOM.h"
#include "variant.h"

SERCOM::SERCOM(Sercom* s)
{
  sercom = s;
}

/* 	=========================
 *	===== Sercom UART
 *	=========================
*/
void SERCOM::Uartinit(uint32_t baudrate, uint32_t config)
{
  /* Disable component before re-configuration */
        
        stopUART();    
    /* Set clock divider to provide clock frequency to the SCB component
     * to operated with desired data rate.
     */
    int i=0;
    uint32 baud[]={115200,57600,38400,19200,9600,4800,2400,1200};
    uint32 divisor[]={15,30,45,92,185,370,741,1483};
    while (baud[i]!=speed)
    {
        i++;
    };
    
    UARTclock_SetFractionalDividerRegister(divisor[i], 0u);
    
    switch (conf)
    {
        case 1:{configUart.dataBits=(5);
                configUart.parity=UART_UART_PARITY_NONE;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 2:{configUart.dataBits=(6);
                configUart.parity=UART_UART_PARITY_NONE;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 3:{configUart.dataBits=(7);
                configUart.parity=UART_UART_PARITY_NONE;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 4:{configUart.dataBits=8;
                configUart.parity=UART_UART_PARITY_NONE;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 5:{configUart.dataBits=5;
                configUart.parity=UART_UART_PARITY_NONE;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 6:{configUart.dataBits=6;
                configUart.parity=UART_UART_PARITY_NONE;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 7:{configUart.dataBits=7;
                configUart.parity=UART_UART_PARITY_NONE;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 8:{configUart.dataBits=8;
                configUart.parity=UART_UART_PARITY_NONE;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 9:{configUart.dataBits=5;
                configUart.parity=UART_UART_PARITY_EVEN;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 10:{
                configUart.dataBits=6;
                configUart.parity=UART_UART_PARITY_EVEN;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 11:{configUart.dataBits=7;
                configUart.parity=UART_UART_PARITY_EVEN;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 12:{configUart.dataBits=8;
                configUart.parity=UART_UART_PARITY_EVEN;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 13:{configUart.dataBits=5;
                configUart.parity=UART_UART_PARITY_EVEN;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 14:{configUart.dataBits=6;
                configUart.parity=UART_UART_PARITY_EVEN;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 15:{configUart.dataBits=7;
                configUart.parity=UART_UART_PARITY_EVEN;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 16:{configUart.dataBits=8;
                configUart.parity=UART_UART_PARITY_EVEN;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 17:{configUart.dataBits=5;
                configUart.parity=UART_UART_PARITY_ODD;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 18:{configUart.dataBits=6;
                configUart.parity=UART_UART_PARITY_ODD;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 19:{configUart.dataBits=7;
                configUart.parity=UART_UART_PARITY_ODD;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 20:{configUart.dataBits=8;
                configUart.parity=UART_UART_PARITY_ODD;
                configUart.stopBits=UART_UART_STOP_BITS_1;break;}
        case 21:{configUart.dataBits=5;
                configUart.parity=UART_UART_PARITY_ODD;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 22:{configUart.dataBits=6;
                configUart.parity=UART_UART_PARITY_ODD;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 23:{configUart.dataBits=7;
                configUart.parity=UART_UART_PARITY_ODD;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        case 24:{configUart.dataBits=8;
                configUart.parity=UART_UART_PARITY_ODD;
                configUart.stopBits=UART_UART_STOP_BITS_2;break;}
        break;
    }
    
     /* Configure SCB component. The configuration is stored in the UART
        * configuration structure.
        */
        UART_UartInit(&configUart);
        
         /* Start component after re-configuration is complete */
        startUART();
    
}


void SERCOM::stopUART()
{
  UART_Stop();
}

void SERCOM::startUART()
{
  UART_Start();
}


}
