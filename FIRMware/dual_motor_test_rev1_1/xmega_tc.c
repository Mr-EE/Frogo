/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : xmega_tc.c
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 17 October 2010 ]
* Updated by        : Basel Zohny [ 17 October 2010 ]
*
* Description       : Xmega timer/counter driver routines
*
* Change History:
* Rev 1.0	[Oct 23, 2010]	- initial
*
****************************************************************************/

#include "xmega_tc.h"



/***************************************************************************/
// This function configures the clock source for the Timer/Counter 0
void TC0_ConfigClockSource( volatile TC0_t * tc, TC_CLKSEL_t clockSelection )
{
	tc->CTRLA = ( tc->CTRLA & ~TC0_CLKSEL_gm ) | clockSelection;
}


/***************************************************************************/
// This function configures the Waveform Generation Mode for the Timer/Counter 0.
void TC0_ConfigWGM( volatile TC0_t * tc, TC_WGMODE_t wgm )
{
	tc->CTRLB = ( tc->CTRLB & ~TC0_WGMODE_gm ) | wgm;
}


/***************************************************************************/
// This function configures the Timer/Counter 0 for input capture operation.
void TC0_ConfigInputCapture( volatile TC0_t * tc, TC_EVSEL_t eventSource )
{
	tc->CTRLD = ( tc->CTRLD & ~( TC0_EVSEL_gm | TC0_EVACT_gm ) ) | eventSource | TC_EVACT_CAPT_gc;
}


/***************************************************************************/
// This function enables compare/capture channels for Timer/Counter 0.
void TC0_EnableCCChannels( volatile TC0_t * tc, uint8_t enableMask )
{
	// Make sure only CCxEN bits are set in enableMask.
	enableMask &= ( TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm );

	// Enable channels
	tc->CTRLB |= enableMask;
}


/***************************************************************************/
// This function disables compare/capture channels on Timer/Counter 0.
void TC0_DisableCCChannels( volatile TC0_t * tc, uint8_t disableMask )
{
	// Make sure only CCxEN bits are set in disableMask
	disableMask &= ( TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm );

	// Disable channels
	tc->CTRLB &= ~disableMask;
}


/***************************************************************************/
// This function sets the overflow interrupt level.
void TC0_SetOverflowIntLevel( volatile TC0_t * tc, TC_OVFINTLVL_t intLevel )
{
	tc->INTCTRLA = ( tc->INTCTRLA & ~TC0_OVFINTLVL_gm ) | intLevel;
}


/***************************************************************************/
// This function sets the Error interrupt level.
void TC0_SetErrorIntLevel( volatile TC0_t * tc, TC_ERRINTLVL_t intLevel )
{
	tc->INTCTRLA = ( tc->INTCTRLA & ~TC0_ERRINTLVL_gm ) | intLevel;
}


/***************************************************************************/
// This function sets the interrupt level for compare/capture channel A interrupt.
void TC0_SetCCAIntLevel( volatile TC0_t * tc, TC_CCAINTLVL_t intLevel )
{
	tc->INTCTRLB = ( tc->INTCTRLB & ~TC0_CCAINTLVL_gm ) | intLevel;
}


/***************************************************************************/
// This function sets the interrupt level for compare/capture channel B interrupt.
void TC0_SetCCBIntLevel( volatile TC0_t * tc, TC_CCBINTLVL_t intLevel )
{
	tc->INTCTRLB = ( tc->INTCTRLB & ~TC0_CCBINTLVL_gm ) | intLevel;
}


/***************************************************************************/
// This function sets the interrupt level for compare/capture channel C interrupt.
void TC0_SetCCCIntLevel( volatile TC0_t * tc, TC_CCCINTLVL_t intLevel )
{
	tc->INTCTRLB = ( tc->INTCTRLB & ~TC0_CCCINTLVL_gm ) | intLevel;
}


/***************************************************************************/
// This function sets the interrupt level for compare/capture channel D interrupt.
void TC0_SetCCDIntLevel( volatile TC0_t * tc, TC_CCDINTLVL_t intLevel )
{
	tc->INTCTRLB = ( tc->INTCTRLB & ~TC0_CCDINTLVL_gm ) | intLevel;
}


/***************************************************************************/
// Resets the Timer/Counter 0.
void TC0_Reset( volatile TC0_t * tc )
{
	/* TC must be turned off before a Reset command. */
	tc->CTRLA = ( tc->CTRLA & ~TC0_CLKSEL_gm ) | TC_CLKSEL_OFF_gc;

	/* Issue Reset command. */
	tc->CTRLFSET = TC_CMD_RESET_gc;
}