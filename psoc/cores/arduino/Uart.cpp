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

#include "Uart.h"
#include "Arduino.h"
#include "wiring_private.h"
#include "UART_SPI_UART.h"


/*******************************************************************************
* UART Configuration
*******************************************************************************/
/*******************************************************************************
* Common Definitions
*******************************************************************************/
/* Constants */
#define ENABLED         (1u)
#define DISABLED        (0u)
#define NON_APPLICABLE  (DISABLED)

/* Common RX and TX buffers for I2C and UART operation */
#define COMMON_BUFFER_SIZE     (16u)
uint8 bufferTx[COMMON_BUFFER_SIZE];

/* UART RX buffer requires one extra element for proper operation. One element
* remains empty while operation. Keeping this element empty simplifies
* circular buffer operation.
*/
uint8 bufferRx[COMMON_BUFFER_SIZE + 1u];


#define UART_OVERSAMPLING       (13u)
#define UART_DATA_WIDTH         (8u)
#define UART_RX_INTR_MASK       (UART_INTR_RX_NOT_EMPTY)
#define UART_TX_INTR_MASK       (0u)

#define UART_RX_BUFFER_SIZE     (COMMON_BUFFER_SIZE)
#define UART_TX_BUFFER_SIZE     (COMMON_BUFFER_SIZE)
#define UART_RX_BUFER_PTR       bufferRx
#define UART_TX_BUFER_PTR       bufferTx

/* UART desired baud rate is 115200 bps. The selected Oversampling parameter is
* 16. The CommCLK = Baud rate * Oversampling = 115200 * 13 = 1.4976 MHz.
* The clock divider has to be calculated to control clock frequency as clock
* component provides interface to it.
* Divider = (HFCLK / CommCLK) = (24 MHz / 1.4976 MHz) = 16. But the devider 
* value written into the register has to decremented by 1 therefore end value 
* is 15.
* The clock accuracy is important for UART operation. The actual CommCLK equal:
* CommCLK(actual) = (24 MHz / 16) = 1.5 MHz
* The deviation of actual CommCLK from desired must be calculated:
* Deviation = (1.5 MHz – 1.4976 MHz) / 1.4976 MHz = ~0.16%
* Taking into account HFCLK accuracy ±2%, the total error is:0.2 + 0.16 = 2.16%.
* The total error value is less than 5% and it is enough for correct
* UART operation.
* The divider to create CommCLK for HFCLK = 12 MHz is two times less than for 
* HFCLK = 24 MHz and equal to 8. The value written into the register is 7.
*/
/* #if (24u == CYDEV_BCLK__HFCLK__MHZ)
    #define UART_CLK_DIVIDER        (15u)
#elif (12u == CYDEV_BCLK__HFCLK__MHZ)
    #define UART_CLK_DIVIDER        (7u)
#else
    #error For correct SCB_UnconfiguredComm code example operation the HFCLK \
           frequency must be 24 or 12 MHz. Open Design Wide Resources file   \
           Clocks tab and change HFCLK to match requirement.
    
    #define UART_CLK_DIVIDER        (0u)
#endif /* (24u == CYDEV_BCLK__HFCLK__MHZ) */
 
/* Comm_UART_INIT_STRUCT provides the fields which match the selections
* available in the customizer. Refer to the I2C customizer for detailed
* description of the settings.
*/

///////////////////////////////////////////////////////////////////////////////////////////

#define SERIAL_5N1	1
#define SERIAL_6N1	2
#define SERIAL_7N1	3
#define SERIAL_8N1	4
#define SERIAL_5N2	5
#define SERIAL_6N2	6
#define SERIAL_7N2	7
#define SERIAL_8N2	8
#define SERIAL_5E1	9
#define SERIAL_6E1	10
#define SERIAL_7E1	11
#define SERIAL_8E1	12
#define SERIAL_5E2	13
#define SERIAL_6E2	14
#define SERIAL_7E2	15
#define SERIAL_8E2	16
#define SERIAL_5O1	17
#define SERIAL_6O1	18
#define SERIAL_7O1	19
#define SERIAL_8O1	20
#define SERIAL_5O2	21
#define SERIAL_6O2	22
#define SERIAL_7O2	23
#define SERIAL_8O2	24


//UART_UART_INIT_STRUCT configUart1;
UART_UART_INIT_STRUCT configUart1 =
{
    UART_UART_MODE_STD,     /* mode: Standard */
    UART_UART_TX_RX,        /* direction: RX + TX */
    UART_DATA_WIDTH,        /* dataBits: 8 bits */
    UART_UART_PARITY_NONE,  /* parity: None */
    UART_UART_STOP_BITS_1,  /* stopBits: 1 bit */
    UART_OVERSAMPLING,      /* oversample: 16 */
    DISABLED,               /* enableIrdaLowPower: disabled */
    DISABLED,               /* enableMedianFilter: disabled */
    DISABLED,               /* enableRetryNack: disabled */
    DISABLED,               /* enableInvertedRx: disabled */
    DISABLED,               /* dropOnParityErr: disabled */
    DISABLED,               /* dropOnFrameErr: disabled */
    NON_APPLICABLE,         /* enableWake: disabled */
    UART_RX_BUFFER_SIZE,    /* rxBufferSize: TX software buffer size */
    UART_RX_BUFER_PTR,      /* rxBuffer: pointer to RX software buffer */
    UART_TX_BUFFER_SIZE,    /* txBufferSize: TX software buffer size */
    UART_TX_BUFER_PTR,      /* txBuffer: pointer to TX software buffer */
    DISABLED,               /* enableMultiproc: disabled */
    DISABLED,               /* multiprocAcceptAddr: disabled */
    NON_APPLICABLE,         /* multiprocAddr: N/A */
    NON_APPLICABLE,         /* multiprocAddrMask: N/A */
    ENABLED,                /* enableInterrupt: enable internal interrupt
                             * handler for the software buffer */
    UART_RX_INTR_MASK,      /* rxInterruptMask: enable INTR_RX.NOT_EMPTY to
                             * handle RX software buffer operations */
    NON_APPLICABLE,         /* rxTriggerLevel: N/A */
    UART_TX_INTR_MASK,      /* txInterruptMask: no TX interrupts on start up */
    NON_APPLICABLE,         /* txTriggerLevel: N/A */
    DISABLED,               /* enableByteMode: disabled */
    DISABLED,               /* enableCts: disabled */
    DISABLED,               /* ctsPolarity: disabled */
    DISABLED,               /* rtsRxFifoLevel: disabled */
    DISABLED,               /* rtsPolarity: disabled */
};

void Uart::begin(unsigned long baudrate)
{
  begin(baudrate,SERIAL_8N1);
}

void Uart::begin(unsigned long baudrate, uint16_t config)
{
  /* Disable component before re-configuration */
        
        UART_Stop();   
    /* Set clock divider to provide clock frequency to the SCB component
     * to operated with desired data rate.
     */
    int i=0;
    uint32 baud[]={115200,57600,38400,19200,9600,4800,2400,1200};
    uint32 divisor[]={15,30,46,92,185,370,741,1483};
    while (baud[i]!=baudrate)
    {
        i++;
    };
    
    UARTclock_SetFractionalDividerRegister(divisor[i], 0u);
    
    switch (config)
    {
        case 1:{configUart1.dataBits=(5);
                configUart1.parity=UART_UART_PARITY_NONE;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 2:{configUart1.dataBits=(6);
                configUart1.parity=UART_UART_PARITY_NONE;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 3:{configUart1.dataBits=(7);
                configUart1.parity=UART_UART_PARITY_NONE;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 4:{configUart1.dataBits=8;
                configUart1.parity=UART_UART_PARITY_NONE;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 5:{configUart1.dataBits=5;
                configUart1.parity=UART_UART_PARITY_NONE;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 6:{configUart1.dataBits=6;
                configUart1.parity=UART_UART_PARITY_NONE;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 7:{configUart1.dataBits=7;
                configUart1.parity=UART_UART_PARITY_NONE;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 8:{configUart1.dataBits=8;
                configUart1.parity=UART_UART_PARITY_NONE;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 9:{configUart1.dataBits=5;
                configUart1.parity=UART_UART_PARITY_EVEN;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 10:{configUart1.dataBits=6;
                configUart1.parity=UART_UART_PARITY_EVEN;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 11:{configUart1.dataBits=7;
                configUart1.parity=UART_UART_PARITY_EVEN;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 12:{configUart1.dataBits=8;
                configUart1.parity=UART_UART_PARITY_EVEN;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 13:{configUart1.dataBits=5;
                configUart1.parity=UART_UART_PARITY_EVEN;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 14:{configUart1.dataBits=6;
                configUart1.parity=UART_UART_PARITY_EVEN;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 15:{configUart1.dataBits=7;
                configUart1.parity=UART_UART_PARITY_EVEN;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 16:{configUart1.dataBits=8;
                configUart1.parity=UART_UART_PARITY_EVEN;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 17:{configUart1.dataBits=5;
                configUart1.parity=UART_UART_PARITY_ODD;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 18:{configUart1.dataBits=6;
                configUart1.parity=UART_UART_PARITY_ODD;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 19:{configUart1.dataBits=7;
                configUart1.parity=UART_UART_PARITY_ODD;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 20:{configUart1.dataBits=8;
                configUart1.parity=UART_UART_PARITY_ODD;
                configUart1.stopBits=UART_UART_STOP_BITS_1;break;}
        case 21:{configUart1.dataBits=5;
                configUart1.parity=UART_UART_PARITY_ODD;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 22:{configUart1.dataBits=6;
                configUart1.parity=UART_UART_PARITY_ODD;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 23:{configUart1.dataBits=7;
                configUart1.parity=UART_UART_PARITY_ODD;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
        case 24:{configUart1.dataBits=8;
                configUart1.parity=UART_UART_PARITY_ODD;
                configUart1.stopBits=UART_UART_STOP_BITS_2;break;}
		
		break;
    }
    
     /* Configure SCB component. The configuration is stored in the UART
        * configuration structure.
        */
        UART_UartInit(&configUart1);
        
         /* Start component after re-configuration is complete */
        UART_Start();
}

void Uart::print(const char8 wordp[])
{
		UART_UartInit(&configUart1);
	    UART_Start();
        UART_UartPutString(wordp);
         
}


