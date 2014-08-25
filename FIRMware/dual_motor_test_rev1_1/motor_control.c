/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : motor_control.c
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 31 October 2010 ]
* Updated by        : Basel Zohny [ 31 October 2010 ]
*
* Description       : Motor control functions
*
* Change History:
* Rev 1.1	[Nov 13, 2010]  - Changed pwm_duty to int16 for better PWM steps
* Rev 1.0	[Oct 31, 2010]	- Initial
*
****************************************************************************/

#include "motor_control.h"



/***************************************************************************/
// Set Motor speed and direction
/***************************************************************************/
void Set_Motor_Speed( uint8_t motor_sel, int16_t pwm_duty, uint8_t dir )
{
	uint16_t	pwm_duty_tmp = 0;								// duty cycle

	// Check to make sure we are above zero
	if (pwm_duty < 0)
		pwm_duty = 0; 


	if (pwm_duty >= MAX_PWM)
		pwm_duty_tmp = MAX_PWM;
	else
		pwm_duty_tmp = pwm_duty;

	
	switch (motor_sel)
	{
		case M0:
			TC_SetCompareA(&MOTOR_TIMER, pwm_duty_tmp);
			if (dir == FORWARD)
			{
				MOTOR_OUTPUT.OUTSET = M0_STOP;
				MOTOR_OUTPUT.OUTCLR = M0_FORWARD;
			}
			else
			{
				MOTOR_OUTPUT.OUTSET = M0_STOP;
				MOTOR_OUTPUT.OUTCLR = M0_BACKWARD;
			}
			break;
		
		case M1:
			TC_SetCompareB(&MOTOR_TIMER, pwm_duty_tmp);
			if (dir == FORWARD)
			{
				MOTOR_OUTPUT.OUTSET = M1_STOP;
				MOTOR_OUTPUT.OUTCLR = M1_FORWARD;
			}
			else
			{
				MOTOR_OUTPUT.OUTSET = M1_STOP;
				MOTOR_OUTPUT.OUTCLR = M1_BACKWARD;
			}
			break;
		
		default:
			break;
	}
}
