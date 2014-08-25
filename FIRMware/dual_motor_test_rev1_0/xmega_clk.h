/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : xmega_clk.h
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 17 October 2010 ]
* Updated by        : Basel Zohny [ 17 October 2010 ]
*
* Description       : Header file for xmega_clk.c
*
* Change History:
* Rev 1.0	[Oct 17, 2010]	- initial
*
****************************************************************************/

#ifndef xmega_clk_h
#define xmega_clk_h

#include "platform.h"



/****************************************************************************
  Macro definitions
****************************************************************************/

// This macro enables the selected oscillator.
#define OSC_Enable( _oscSel ) ( OSC.CTRL |= (_oscSel) )

// This macro disables the selected oscillator.
#define OSC_Disable( _oscSel ) ( OSC.CTRL &= ~(_oscSel) )

// This macro checks if selected oscillator is ready.
#define OSC_IsReady( _oscSel ) ( OSC.STATUS & (_oscSel) )

// This macro selects a Real-Time Counter clock source and enables it.
#define OSC_RTC_Sel( _rtcSel ) ( CLK.RTCCTRL = ( CLK.RTCCTRL & ~CLK_RTCSRC_gm ) | _rtcSel | CLK_RTCEN_bm )

// This macro disables routing of clock signals to the Real-Time Counter.
#define OSC_RTC_Disable() ( CLK.RTCCTRL &= ~CLK_RTCEN_bm )

// This macro disables the automatic calibration of the selected internal oscillator.
#define OSC_Autocalib_Disable( _clk ) ( (_clk).CTRL &= ~DFLL_ENABLE_bm )



/****************************************************************************
  Function definitions. Detailed information is found in source file
****************************************************************************/
void CCP_WR( volatile uint8_t * address, uint8_t value );

// Oscialltor related functions
void OSC_PLLConfig( OSC_PLLSRC_t clockSource, uint8_t factor );
void OSC_AutocalibEnable( uint8_t clkSource, bool extReference );
void XOSC_Config( OSC_FRQRANGE_t freqRange, bool lowPower32kHz, OSC_XOSCSEL_t xoscModeSelection );
void XOSC_FailureDetectEnable( void );

// Clk system related functions
void CLK_PreScalerConfig( CLK_PSADIV_t PSAfactor, CLK_PSBCDIV_t PSBCfactor );
void CLK_Sel( CLK_SCLKSEL_t clockSource );
void CLK_ConfigLock( void );


#endif
