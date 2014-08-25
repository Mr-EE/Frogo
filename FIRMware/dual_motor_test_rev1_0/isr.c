/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : isr.c
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 31 October 2010 ]
* Updated by        : Basel Zohny [ 31 October 2010 ]
*
* Description       : isr routines
*
* Change History:
* Rev 1.0	[Oct 31, 2010]	- initial
*
****************************************************************************/


#include "isr.h"


/***************************************************************************/
// Interrupt service routine for timer0 on port F overflow
ISR( TCF0_OVF_vect )
{
	sys_ticked = true;
}



/***************************************************************************/
// Interrupt service routine for RTC_16 overflow
/*
ISR( RTC_OVF_vect )
{
	sys_tick = true;
}
*/



/***************************************************************************/
// Interrupt service routine for RTC_16 overflow
/*
ISR( USARTD1_RXC_vect )
{
	uint8_t	tmp;

	tmp = USART_GetChar(USARTD1);

	if (tmp == SOF)
		rx_d1_buf_ptr++;

	if (rx_d1_buf_ptr == 1)



}
*/


/***************************************************************************/
// Interrupt service routine for RTC_16 overflow
/*
ISR( USARTD1_DRE_vect )
{

}
*/
