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
// Init System
	// Initialize the clocks
	Init_CLK();

	// Initialize I/Os
	Init_IO();

	// Initialize the system tick
	Init_SysTick();

	// Initialize the PWMs
	Init_PWM();

	// Initialize USARTD1
//	Init_USARTD1();

	// Initialize motor profile state and pwm duty
	motor_state = MOTOR_STATE_STOP;
	pwm_duty = 0;
	motor_tick = 0;
	motor_state_tick = 0;
	turn_left = false;
	turn_right = false;
	direction = FORWARD;

	// Enable low level interrupts in the programmable interrupt controller
	PMIC.CTRL |= PMIC_LOLVLEN_bm;


// Emulate uart reciveing commands
//	speed = 320;													// 275 mm/s
//	accel_step = 1;													// 215 mm/s^2
//	deaccel_step = 1;												// 215 mm/s^2
//	cruise_stop = SYS_TICK_1S;										// 2*(0.5*215*1.28^2) + 275*1 = 627mm
	
	// This command starts the motor profile
//	motor_state = MOTOR_STATE_ACCEL;

	delay_ms(6000);


	// Enable interrupts.
	sei();

	// An eternal loop to handle tasks.
	while(1)
	{
		do
		{
		} while(!sys_ticked);


		// Increment ticks here
		led0_tick ++;


// Process system here...

		// Process the motors
		//-----------------------------------------------------------------------
		Process_Motor();

		if (motor_state == MOTOR_STATE_STOP)
		{
			switch(motor_state_tick)
			{			
				//-------------------------------------------------------
				case 0:
					// Go forwards
					speed = 520;
					accel_step = 20;	
					deaccel_step = 20;
					cruise_stop = SYS_TICK_800MS;
					turn_left = true;
					turn_right = false;
					direction = FORWARD;

					motor_state = MOTOR_STATE_ACCEL;

					break;

				//-------------------------------------------------------
				case 1:
					// Turn 90 degres right
					speed = 520;
					accel_step = 20;	
					deaccel_step = 20;
					cruise_stop = SYS_TICK_800MS;
					turn_left = false;
					turn_right = true;
					direction = FORWARD;

					motor_state = MOTOR_STATE_ACCEL;

					break;

				//-------------------------------------------------------
				default:

					break;
			}	
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
