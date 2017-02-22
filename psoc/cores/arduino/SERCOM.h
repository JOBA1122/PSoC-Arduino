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

#ifndef _SERCOM_CLASS_
#define _SERCOM_CLASS_

//#include "sam.h"
#ifdef __cplusplus

class SERCOM
{
	public:
		//SERCOM(Sercom* s) ;

		/* ========== UART ========== */
		void initUART() ;
		/* void initFrame(SercomUartCharSize charSize, SercomDataOrder dataOrder, SercomParityMode parityMode, SercomNumberStopBit nbStopBits) ;
		void initPads(SercomUartTXPad txPad, SercomRXPad rxPad) ;

		void resetUART( void ) ;
		void enableUART( void ) ;
		void flushUART( void ) ;
		void clearStatusUART( void ) ;
		bool availableDataUART( void ) ;
		bool isBufferOverflowErrorUART( void ) ;
		bool isFrameErrorUART( void ) ;
		bool isParityErrorUART( void ) ;
		bool isDataRegisterEmptyUART( void ) ;
		uint8_t readDataUART( void ) ;
		int writeDataUART(uint8_t data) ;
		bool isUARTError() ;
		void acknowledgeUARTError() ;

		 //========== SPI ========== 
		void initSPI(SercomSpiTXPad mosi, SercomRXPad miso, SercomSpiCharSize charSize, SercomDataOrder dataOrder) ;
		void initSPIClock(SercomSpiClockMode clockMode, uint32_t baudrate) ;

		void resetSPI( void ) ;
		void enableSPI( void ) ;
		void disableSPI( void ) ;
		void setDataOrderSPI(SercomDataOrder dataOrder) ;
		SercomDataOrder getDataOrderSPI( void ) ;
		void setBaudrateSPI(uint8_t divider) ;
		void setClockModeSPI(SercomSpiClockMode clockMode) ;
		uint8_t transferDataSPI(uint8_t data) ;
		bool isBufferOverflowErrorSPI( void ) ;
		bool isDataRegisterEmptySPI( void ) ;
		bool isTransmitCompleteSPI( void ) ;
		bool isReceiveCompleteSPI( void ) ;

		// ========== WIRE ========== 
		void initSlaveWIRE(uint8_t address) ;
		void initMasterWIRE(uint32_t baudrate) ;

		void resetWIRE( void ) ;
		void enableWIRE( void ) ;
    void disableWIRE( void );
    void prepareNackBitWIRE( void ) ;
    void prepareAckBitWIRE( void ) ;
    void prepareCommandBitsWire(uint8_t cmd);
		bool startTransmissionWIRE(uint8_t address, SercomWireReadWriteFlag flag) ;
		bool sendDataMasterWIRE(uint8_t data) ;
		bool sendDataSlaveWIRE(uint8_t data) ;
		bool isMasterWIRE( void ) ;
		bool isSlaveWIRE( void ) ;
		bool isBusIdleWIRE( void ) ;
		bool isBusOwnerWIRE( void ) ;
		bool isDataReadyWIRE( void ) ;
		bool isStopDetectedWIRE( void ) ;
		bool isRestartDetectedWIRE( void ) ;
		bool isAddressMatch( void ) ;
		bool isMasterReadOperationWIRE( void ) ;
    bool isRXNackReceivedWIRE( void ) ;
		int availableWIRE( void ) ;
		uint8_t readDataWIRE( void ) ; */

	private:
		//Sercom* sercom;
		//uint8_t calculateBaudrateSynchronous(uint32_t baudrate) ;
		//uint32_t division(uint32_t dividend, uint32_t divisor) ;
		//void initClockNVIC( void ) ;
};
#endif
#endif
