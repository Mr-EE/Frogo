/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : xmega_tc.h
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 17 October 2010 ]
* Updated by        : Basel Zohny [ 17 October 2010 ]
*
* Description       : Header file for xmega_tc.c
*
* Change History:
* Rev 1.0	[Oct 23, 2010]	- initial
*
****************************************************************************/

#ifndef xmega_tc_h
#define xmega_tc_h

#include "platform.h"



/****************************************************************************
  Macro definitions
****************************************************************************/

// This macro enables the event delay for this TC.
#define TC_EnableEventDelay( _tc )  ( (_tc)->CTRLD |= TC0_EVDLY_bm )
// This macro disables the event delay for this TC.
#define TC_DisableEventDelay( _tc ) ( (_tc)->CTRLD &= ~TC0_EVDLY_bm )



// This macro locks automatic updating of compare and period registers.
#define TC_LockCompareUpdate( _tc ) ( (_tc)->CTRLFSET = TC0_LUPD_bm )
// This macro unlocks automatic updating of compare and period registers.
#define TC_UnlockCompareUpdate( _tc ) ( (_tc)->CTRLFCLR = TC0_LUPD_bm )
// This macro forces an update of the output compare and period registers.
#define TC_ForceUpdate( _tc ) ( (_tc)->CTRLFSET = TC_CMD_UPDATE_gc )
// This macro restarts the Timer/Counter.
#define TC_Restart( _tc ) ( (_tc)->CTRLFSET = TC_CMD_RESTART_gc )



// This macro manually sets the count.
#define TC_SetCount( _tc, _count ) ( (_tc)->CNT = (_count) )
// This macro sets the timer period.
#define TC_SetPeriod( _tc, _period ) ( (_tc)->PER = (_period) )
// This macro sets the timer period ( double buffered ).
#define TC_SetPeriodBuffered( _tc, _period ) ( (_tc)->PERBUF = (_period) )



// This macro sets new compare value for compare channel A. ( Double buffered )
#define TC_SetCompareA( _tc, _compareValue ) ( (_tc)->CCABUF = (_compareValue) )
// This macro sets new compare value for compare channel B. ( Double buffered )
#define TC_SetCompareB( _tc, _compareValue ) ( (_tc)->CCBBUF = (_compareValue) )
// This macro sets new compare value for compare channel C. ( Double buffered )
#define TC_SetCompareC( _tc, _compareValue ) ( (_tc)->CCCBUF = (_compareValue) )
// This macro sets new compare value for compare channel D. ( Double buffered )
#define TC_SetCompareD( _tc, _compareValue ) ( (_tc)->CCDBUF = (_compareValue) )



// This macro test whether an overflow has occurred.
#define TC_GetOverflowFlag( _tc ) ( (_tc)->INTFLAGS & TC0_OVFIF_bm )
// This macro test whether an error has occurred.
#define TC_GetErrorFlag( _tc ) ( (_tc)->INTFLAGS & TC0_ERRIF_bm )
// This macro gets the status for Compare or Capture channel A.
#define TC_GetCCAFlag( _tc ) ( (_tc)->INTFLAGS & TC0_CCAIF_bm )
// This macro gets the status for Compare or Capture channel B.
#define TC_GetCCBFlag( _tc ) ( (_tc)->INTFLAGS & TC0_CCBIF_bm )
// This macro gets the status for Compare or Capture channel C.
#define TC_GetCCCFlag( _tc ) ( (_tc)->INTFLAGS & TC0_CCCIF_bm )
// This macro gets the status for Compare or Capture channel D.
#define TC_GetCCDFlag( _tc ) ( (_tc)->INTFLAGS & TC0_CCDIF_bm )

// This macro clears the Timer/Counter compare or capture A interrupt flag.
#define TC_ClearCCAFlag( _tc ) ( (_tc)->INTFLAGS = TC0_CCAIF_bm )
// This macro clears the Timer/Counter compare or capture B interrupt flag.
#define TC_ClearCCBFlag( _tc ) ( (_tc)->INTFLAGS = TC0_CCBIF_bm )
// This macro clears the Timer/Counter compare or capture C interrupt flag.
#define TC_ClearCCCFlag( _tc ) ( (_tc)->INTFLAGS = TC0_CCCIF_bm )
// This macro clears the Timer/Counter compare or capture D interrupt flag.
#define TC_ClearCCDFlag( _tc ) ( (_tc)->INTFLAGS = TC0_CCDIF_bm )
// This macro clears the Timer/Counter overflow flag.
#define TC_ClearOverflowFlag( _tc ) ( (_tc)->INTFLAGS = TC0_OVFIF_bm )
// This macro clears the Timer/Counter error flag.
#define TC_ClearErrorFlag( _tc ) ( (_tc)->INTFLAGS = TC0_ERRIF_bm )



// This macro reads the first available input capture value for channel A.
#define TC_GetCaptureA( _tc ) ( (_tc)->CCA )
// This macro reads the first available input capture value for channel B.
#define TC_GetCaptureB( _tc ) ( (_tc)->CCB )
// This macro reads the first available input capture value for channel C.
#define TC_GetCaptureC( _tc ) ( (_tc)->CCC )
// This macro reads the first available input capture value for channel D.
#define TC_GetCaptureD( _tc ) ( (_tc)->CCD )



/****************************************************************************
  Function definitions. Detailed information is found in source file
****************************************************************************/
// TC0 functions
void TC0_ConfigClockSource( volatile TC0_t * tc, TC_CLKSEL_t clockSelection );
void TC0_ConfigWGM( volatile TC0_t * tc, TC_WGMODE_t wgm );
void TC0_ConfigInputCapture( volatile TC0_t * tc, TC_EVSEL_t eventSource );
void TC0_EnableCCChannels( volatile TC0_t * tc, uint8_t enableMask );
void TC0_DisableCCChannels( volatile TC0_t * tc, uint8_t disableMask );
void TC0_SetOverflowIntLevel( volatile TC0_t * tc, TC_OVFINTLVL_t intLevel );
void TC0_SetErrorIntLevel( volatile TC0_t * tc, TC_ERRINTLVL_t intLevel );
void TC0_SetCCAIntLevel( volatile TC0_t * tc, TC_CCAINTLVL_t intLevel );
void TC0_SetCCBIntLevel( volatile TC0_t * tc, TC_CCBINTLVL_t intLevel );
void TC0_SetCCCIntLevel( volatile TC0_t * tc, TC_CCCINTLVL_t intLevel );
void TC0_SetCCDIntLevel( volatile TC0_t * tc, TC_CCDINTLVL_t intLevel );
void TC0_Reset( volatile TC0_t * tc );


/*
// TC1 functions
void TC1_ConfigClockSource( volatile TC1_t * tc, TC_CLKSEL_t clockSelection );
void TC1_ConfigWGM( volatile TC1_t * tc, TC_WGMODE_t wgm );
void TC1_ConfigInputCapture( volatile TC1_t * tc, TC_EVSEL_t eventSource );
void TC1_EnableCCChannels( volatile TC1_t * tc, uint8_t enableMask );
void TC1_DisableCCChannels( volatile TC1_t * tc, uint8_t disableMask );
void TC1_SetOverflowIntLevel( volatile TC1_t * tc, TC_OVFINTLVL_t intLevel );
void TC1_SetErrorIntLevel( volatile TC1_t * tc, TC_ERRINTLVL_t intLevel );
void TC1_SetCCAIntLevel( volatile TC1_t * tc, TC_CCAINTLVL_t intLevel );
void TC1_SetCCBIntLevel( volatile TC1_t * tc, TC_CCBINTLVL_t intLevel );
void TC1_SetCCCIntLevel( volatile TC1_t * tc, TC_CCCINTLVL_t intLevel );
void TC1_SetCCDIntLevel( volatile TC1_t * tc, TC_CCDINTLVL_t intLevel );
void TC1_Reset( volatile TC1_t * tc );
*/

#endif
