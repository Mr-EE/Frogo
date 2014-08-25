/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : xmega_usart.h
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 2 November 2010 ]
* Updated by        : Basel Zohny [ 2 November 2010 ]
*
* Description       : Header file for xmega_usart.c
*
* Change History:
* Rev 1.0	[NOC 2, 2010]	- initial
*
****************************************************************************/

#ifndef xmega_usart_h
#define xmega_usart_h

#include "platform.h"



/****************************************************************************
  Macro definitions
****************************************************************************/


// Macro that sets the USART frame format.
#define USART_Format_Set(_usart, _charSize, _parityMode, _twoStopBits)\
	(_usart)->CTRLC = (uint8_t) _charSize | _parityMode |             \
	                  (_twoStopBits ? USART_SBMODE_bm : 0)

// Set USART baud rate.
#define USART_Baud_Set(_usart, _bselValue, _bScaleFactor)         \
	(_usart)->BAUDCTRLA =(uint8_t)(_bselValue);                   \
	(_usart)->BAUDCTRLB =(_bScaleFactor << USART_BSCALE0_bp)|(_bselValue >> 8)

// Set USART RXD interrupt level.
#define USART_RxdIntLevel_Set(_usart, _rxdIntLevel)               \
	((_usart)->CTRLA = ((_usart)->CTRLA & ~USART_RXCINTLVL_gm) | _rxdIntLevel)

// Set USART TXD interrupt level.
#define USART_TxdIntLevel_Set(_usart, _txdIntLevel)               \
	(_usart)->CTRLA = ((_usart)->CTRLA & ~USART_TXCINTLVL_gm) | _txdIntLevel

// Set USART DRE interrupt level.
#define USART_DreIntLevel_Set(_usart, _dreIntLevel)                \
	(_usart)->CTRLA = ((_usart)->CTRLA & ~USART_DREINTLVL_gm) | _dreIntLevel

// Set the mode the USART run in.
#define USART_SetMode(_usart, _usartMode)                          \
	((_usart)->CTRLC = ((_usart)->CTRLC & (~USART_CMODE_gm)) | _usartMode)

// Enable USART receiver.
#define USART_Rx_Enable(_usart) ((_usart)->CTRLB |= USART_RXEN_bm)

// Disable USART receiver.
#define USART_Rx_Disable(_usart) ((_usart)->CTRLB &= ~USART_RXEN_bm)

// Enable USART transmitter.
#define USART_Tx_Enable(_usart)	((_usart)->CTRLB |= USART_TXEN_bm)

// Disable USART transmitter.
#define USART_Tx_Disable(_usart) ((_usart)->CTRLB &= ~USART_TXEN_bm)

// Check if data register empty flag is set.
#define USART_IsTXDataRegisterEmpty(_usart) (((_usart)->STATUS & USART_DREIF_bm) != 0)

// Put data (5-8 bit character).
#define USART_PutChar(_usart, _data) ((_usart)->DATA = _data)

// Get received data (5-8 bit character).
#define USART_GetChar(_usart)  ((_usart)->DATA)

// Checks if the RX complete interrupt flag is set.
#define USART_IsRXComplete(_usart) (((_usart)->STATUS & USART_RXCIF_bm) != 0)



/****************************************************************************
  Function definitions. Detailed information is found in source file
****************************************************************************/


#endif
