/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : xmega_clk.h
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 17 October 2010 ]
* Updated by        : Basel Zohny [ 03 October 2010 ]
*
* Description       : Main code
*
* Change History:
* Rev 1.1	[Oct 17, 2010]	- added support xmega clocks
* Rev 1.0	[Oct 03, 2010]	- initial
*
****************************************************************************/

#include "platform.h"

#include "xmega_clk.h"
#include "xmega_tc.h"
#include "xmega_usart.h"

#include "init.h"
#include "motor_control.h"
#include "isr.h"



/***************************************************************************/
int main(void)
{
	bool motor_stop_flag = false;

// Init System
	// Initialize the clocks
	Init_CLK();

	// Initialize I/Os
	Init_IO();

	// Initialize the system tick
	Init_SysTick();

	// Initialize the PWMs
	Init_PWM();

	// Init QDEC
	Init_QDEC();

	// Initialize USARTD1
//	Init_USARTD1();

	// Init variables
	led0_tick = 0;
	motor_tick = 0;

	// Enable low level interrupts in the programmable interrupt controller
	PMIC.CTRL |= PMIC_LOLVLEN_bm;

	
	// Delay before anything happens
	delay_ms(6000);

	// Enable interrupts.
	sei();


	// Start motors moving forward
	pwm_duty = 800;
//	turn_left = false;
//	turn_right = false;
	direction = FORWARD;

	Set_Motor_Speed(M0, pwm_duty, direction);
	Set_Motor_Speed(M1, pwm_duty, direction);


	TCC0.CNT = 0;
	TCC1.CNT = 0;

	// An eternal loop to handle tasks.
	while(1)
	{
		do
		{
		} while(!sys_ticked);

		
		// Increment ticks here
		led0_tick ++;
		
// Process system here...

		// Move forward for 48 encoder counts
		//-----------------------------------------------------------------------
		if (motor_stop_flag != true)
		{

			if (TCC1.CNT >= 400)
				Set_Motor_Speed(M0, 0, FORWARD);

			if (TCC0.CNT >= 400)
				Set_Motor_Speed(M1, 0, FORWARD);

			if ( (TCC1.CNT >= 400) & (TCC0.CNT >= 400) )	
				motor_stop_flag = true;
		}


		// Flash LED0 at 500ms intervals
		//-----------------------------------------------------------------------
		if (led0_tick == LED0_TIME)
		{
			PORTE.OUTTGL = 0x01;
			led0_tick = 0;
		}


		// Rest of processing
		//-----------------------------------------------------------------------
		sys_ticked = false;

	};

}
