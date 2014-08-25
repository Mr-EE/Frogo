/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : init.c
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 31 October 2010 ]
* Updated by        : Basel Zohny [ 31 October 2010 ]
*
* Description       : System init functions
*
* Change History:
* Rev 1.0	[Oct 31, 2010]	- initial
*
****************************************************************************/

#include "init.h"



/***************************************************************************/
// This function will initialize the clk system (main/perph/rtc for the Xmega
void Init_CLK( void )
{
// Set up main clock source
	// Enable 32 MHz internal oscialltor
	OSC_Enable(OSC_RC32MEN_bm);

	// Set prescaler to 1 for A, B, C prescalers. clk_sys = 32 MHz.
	//  This sets the clocks as follows:
	//  clk_per4 = 32 MHz
	//  clk_per2 = 32 Mhz
	//  clk_per/clk_sys = 32 MHz
	CLK_PreScalerConfig(CLK_PSADIV_1_gc, CLK_PSBCDIV_1_1_gc);

	// Wait until clock source is stable before enabling clock as main source
	do 
	{
	} while (OSC_IsReady( OSC_RC32MRDY_bm ) == 0);

	// Enable 32 Mhz stable clk source as the main clock
	CLK_Sel(CLK_SCLKSEL_RC32M_gc);

/*
// Set up RTC clock source
	// Enable 32.768KHz internal oscialltor
	OSC_Enable(OSC_RC32KEN_bm);

	// Wait until clock source is stable before enabling clock as RTC source
	do 
	{
	} while (OSC_IsReady(OSC_RC32KRDY_bm) == 0);

	// Enable 32.768 KHz stable clk source as the RTC clock
	OSC_RTC_Sel( CLK_RTCSRC_RCOSC_gc );

	// Enable Low level interrupts for the RTC Overflow
	RTC.INTCTRL = (RTC.INTCTRL & ~RTC_OVFINTLVL_gm) | RTC_OVFINTLVL_LO_gc;

	sys_tick = false;

	// Set initial period for RTC tick and start the RTC with no prescaler.
	RTC.PER = RTC_TICK_CNT;
	RTC.CTRL |= RTC_PRESCALER_DIV1_gc;
*/
}



/***************************************************************************/
// This function initializes the IOs for the Xmega
void Init_IO( void )
{
// LED outputs
	PORTE.DIR = 0xFF;
	PORTE.OUT = 0xFE;

// Motor outputs
	MOTOR_OUTPUT.DIRSET = MOTORS_STOP;								// PD2-PD5 set as outputs
	MOTOR_OUTPUT.OUTSET = MOTORS_STOP;								// PD2-PD5 set hi as deafult
											
}



/***************************************************************************/
// This function initializes system tick
void Init_SysTick( void )
{
	TC_SetPeriod(&TCF0, 124);										// 125 ticks at 31.25KHz = 4ms periods
	TC0_ConfigClockSource(&TCF0, TC_CLKSEL_DIV1024_gc);				// 32MHz/1024=31.25KHz
	TC0_SetOverflowIntLevel(&TCF0, TC_OVFINTLVL_LO_gc);				// Enable interrupts for overflow
}



/***************************************************************************/
// This function initializes the PWMs
void Init_PWM( void )
{

// Set PWM outputs
	MOTOR_OUTPUT.DIRSET = 0x03;										// PD0/PD1 set as outputs

// Configure timer
	TC0_ConfigWGM(&MOTOR_TIMER, TC_WGMODE_SS_gc);
	TC0_EnableCCChannels(&MOTOR_TIMER, TC0_CCAEN_bm|TC0_CCBEN_bm);
	TC_SetCompareA(&MOTOR_TIMER, 0);
	TC_SetCompareB(&MOTOR_TIMER, 0);
	TC_SetPeriod(&MOTOR_TIMER, MAX_PWM);
	TC0_ConfigClockSource(&MOTOR_TIMER, TC_CLKSEL_DIV1_gc);			// 32MHz
}



/***************************************************************************/
// This function initializes the usart1 on port d.
void Init_USARTD1( void )
{
	PORTD.OUTSET = PIN7_bm;											// Set TxD1 high
	PORTD.DIRSET = PIN7_bm;											// Set TxD1 as output
	PORTD.DIRCLR = PIN6_bm;											// Set RxD1 as input

	rx_d1_buf_ptr = 0;
	tx_d1_buf_ptr = 0;

	USART_Baud_Set(&USARTD1, USARTD1_BAUD, 0);

	USART_Format_Set(&USARTD1, USART_CHSIZE_8BIT_gc, USART_PMODE_DISABLED_gc, false);


	USART_DreIntLevel_Set(&USARTD1, USART_DREINTLVL_LO_gc);
	USART_TxdIntLevel_Set(&USARTD1, USART_TXCINTLVL_OFF_gc);
	USART_RxdIntLevel_Set(&USARTD1, USART_RXCINTLVL_LO_gc);

	USART_SetMode(&USARTD1, USART_CMODE_ASYNCHRONOUS_gc);

	USART_Rx_Enable(&USARTD1);
	USART_Tx_Enable(&USARTD1);
}



/***************************************************************************/
// This function initializes the quadrature decoder
void Init_QDEC( void )
{
	// Set PA0/PA1 as input
	PORTA.DIRCLR = 0b00000011;	
	
	// Set PA0/PA1 as level sense
	PORTA.PIN0CTRL = PORT_ISC_LEVEL_gc;
	PORTA.PIN1CTRL = PORT_ISC_LEVEL_gc;
								
	// Enable PortA pin 0 as source of event 0
	EVSYS.CH0MUX = EVSYS_CHMUX_PORTA_PIN0_gc;

	// Enable QDEC and 8 digital filter samples
	EVSYS.CH0CTRL = EVSYS_QDEN_bm | EVSYS_DIGFILT_8SAMPLES_gc;

	// Set event action as QDEC and source as channel 0
	TCC0.CTRLD = TC_EVACT_QDEC_gc | TC_EVSEL_CH0_gc;

	// Set period to (linecount*4-1)
//	TCC0.PER = (48*4-1);

	// Set clock source for TCC0 as clk_div1
	TCC0.CTRLA = TC_CLKSEL_DIV1_gc;



	// Set PD6/PD7 as input
	PORTD.DIRCLR = 0b11000000;
	
	// Set PD6/PD7 as level sense
	PORTD.PIN6CTRL = PORT_ISC_LEVEL_gc;
	PORTD.PIN7CTRL = PORT_ISC_LEVEL_gc;
								
	// Enable PortD pin 6 as source of event 2
	EVSYS.CH2MUX = EVSYS_CHMUX_PORTD_PIN6_gc;

	// Enable QDEC and 8 digital filter samples
	EVSYS.CH2CTRL = EVSYS_QDEN_bm | EVSYS_DIGFILT_8SAMPLES_gc;

	// Set event action as QDEC and source as channel 2
	TCC1.CTRLD = TC_EVACT_QDEC_gc | TC_EVSEL_CH2_gc;

	// Set period to (linecount*4-1)
//	TCC1.PER = (48*4-1);

	// Set clock source for TCC1 as clk_div1
	TCC1.CTRLA = TC_CLKSEL_DIV1_gc;
}

