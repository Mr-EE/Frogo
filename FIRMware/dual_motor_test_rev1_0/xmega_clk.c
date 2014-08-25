/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : xmega_clk.c
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 17 October 2010 ]
* Updated by        : Basel Zohny [ 17 October 2010 ]
*
* Description       : Xmega clock system functional routines
*
* Change History:
* Rev 1.0	[Oct 17, 2010]	- initial
*
****************************************************************************/

#include "xmega_clk.h"



/***************************************************************************/
// CCP write helper function written in assembly. This function is written 
// in assembly because of the timecritial operation of writing to the registers.
void CCP_WR( volatile uint8_t * address, uint8_t value )
{
	AVR_ENTER_CRITICAL_REGION( );

	volatile uint8_t * tmpAddr = address;

#ifdef RAMPZ
	RAMPZ = 0;
#endif
	asm volatile(
		"movw r30,  %0"	      "\n\t"
		"ldi  r16,  %2"	      "\n\t"
		"out   %3, r16"	      "\n\t"
		"st     Z,  %1"       "\n\t"
		:
		: "r" (tmpAddr), "r" (value), "M" (CCP_IOREG_gc), "i" (&CCP)
		: "r16", "r30", "r31"
		);

	AVR_LEAVE_CRITICAL_REGION( );
}


/***************************************************************************/
// This function configures the internal high-frequency PLL.
void OSC_PLLConfig( OSC_PLLSRC_t clockSource, uint8_t factor )
{
	factor &= OSC_PLLFAC_gm;
	OSC.PLLCTRL = (uint8_t) clockSource | ( factor << OSC_PLLFAC_gp );
}


/***************************************************************************/
// This function selects and enables automatic calibration of the selected 
// internal oscillator.
void OSC_AutocalibEnable( uint8_t clkSource, bool extReference )
{
	OSC.DFLLCTRL = ( OSC.DFLLCTRL & ~clkSource ) | ( extReference ? clkSource : 0 );

	if (clkSource == OSC_RC2MCREF_bm) 
	{
		DFLLRC2M.CTRL |= DFLL_ENABLE_bm;
	} 
	else if (clkSource == OSC_RC32MCREF_bm) 
	{
		DFLLRC32M.CTRL |= DFLL_ENABLE_bm;
	}
}


/***************************************************************************/
// This function configures the external oscillator.
void XOSC_Config( OSC_FRQRANGE_t freqRange, bool lowPower32kHz, OSC_XOSCSEL_t xoscModeSelection )
{
	OSC.XOSCCTRL = (uint8_t) freqRange | ( lowPower32kHz ? OSC_X32KLPM_bm : 0 ) | xoscModeSelection;
}


/***************************************************************************/
// This function enables the External Oscillator Failure Detection (XOSCFD) feature.
void XOSC_FailureDetectEnable( void )
{
	CCP_WR( &OSC.XOSCFAIL, ( OSC_XOSCFDIF_bm | OSC_XOSCFDEN_bm ) );
}


/***************************************************************************/
// This function changes the clk system prescaler configuration.
void CLK_PreScalerConfig( CLK_PSADIV_t PSAfactor, CLK_PSBCDIV_t PSBCfactor )
{
	uint8_t PSconfig = (uint8_t) PSAfactor | PSBCfactor;
	CCP_WR( &CLK.PSCTRL, PSconfig );
}


/***************************************************************************/
// This function selects the main system clock source.
void CLK_Sel( CLK_SCLKSEL_t clockSource )
{
	uint8_t clkCtrl = ( CLK.CTRL & ~CLK_SCLKSEL_gm ) | clockSource;
	CCP_WR( &CLK.CTRL, clkCtrl );
}


/***************************************************************************/
// This function locks the entire clock system configuration.
void CLK_ConfigLock( void )
{
	CCP_WR( &CLK.LOCK, CLK_LOCK_bm );
}