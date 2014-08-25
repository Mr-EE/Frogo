/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : init.h
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 31 October 2010 ]
* Updated by        : Basel Zohny [ 31 October 2010 ]
*
* Description       : Header file for init.c
*
* Change History:
* Rev 1.0	[Oct 31, 2010]	- initial
*
****************************************************************************/

#ifndef init_h
#define init_h

#include "platform.h"
#include "xmega_clk.h"
#include "xmega_tc.h"
#include "xmega_usart.h"



/****************************************************************************
  Macro definitions
****************************************************************************/



/****************************************************************************
  Function definitions. Detailed information is found in source file
****************************************************************************/
void Init_CLK( void );
void Init_IO( void );
void Init_SysTick( void );
void Init_PWM( void );
void Init_USARTD1( void );
#endif
