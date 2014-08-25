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
// Motor profile
//-----------------------------------------------------------------------
void Process_Motor( void )
{
	switch(motor_state)
	{			
		//-------------------------------------------------------
		case MOTOR_STATE_STOP:
		
			pwm_duty = 0;
			motor_tick = 0;

			MOTOR_OUTPUT.OUTSET = MOTORS_STOP;

			motor_state = MOTOR_STATE_STOP;

//			Set_Motor_Speed(M0, pwm_duty, direction);
//			Set_Motor_Speed(M1, pwm_duty, direction);

			break;

		//-------------------------------------------------------
		case MOTOR_STATE_ACCEL:

			if (pwm_duty >= speed)
			{	
				pwm_duty = speed;
				motor_state = MOTOR_STATE_CRUISE;
			}
			else
			{
				pwm_duty += accel_step;
				motor_state = MOTOR_STATE_ACCEL;
			}
			
			if (turn_left)
			{
				Set_Motor_Speed(M0, pwm_duty, FORWARD);
				Set_Motor_Speed(M1, pwm_duty, BACKWARD);
			}
			else if (turn_right)
			{
				Set_Motor_Speed(M0, pwm_duty, BACKWARD);
				Set_Motor_Speed(M1, pwm_duty, FORWARD);
			}
			else
			{
				Set_Motor_Speed(M0, pwm_duty, direction);
				Set_Motor_Speed(M1, pwm_duty, direction);
			}

			break;


		//-------------------------------------------------------
		case MOTOR_STATE_CRUISE:

			motor_tick ++;

			if (motor_tick >= cruise_stop)
			{
				motor_state = MOTOR_STATE_DEACCEL;
				motor_tick = 0;
			}
			else
			{
				pwm_duty = speed;

				if (turn_left)
				{
					Set_Motor_Speed(M0, pwm_duty, FORWARD);
					Set_Motor_Speed(M1, pwm_duty, BACKWARD);
				}
				else if (turn_right)
				{
					Set_Motor_Speed(M0, pwm_duty, BACKWARD);
					Set_Motor_Speed(M1, pwm_duty, FORWARD);
				}
				else
				{
					Set_Motor_Speed(M0, pwm_duty, direction);
					Set_Motor_Speed(M1, pwm_duty, direction);
				}

				motor_state = MOTOR_STATE_CRUISE;
			}	

			break;

		//-------------------------------------------------------
		case MOTOR_STATE_DEACCEL:

			if (pwm_duty <= 0)
			{
				pwm_duty = 0;
				motor_state = MOTOR_STATE_STOP;

//				if (motor_state_tick < 1)
					motor_state_tick ++;
//				else
//					motor_state_tick = 0;
			}
			else
			{
				pwm_duty -= deaccel_step;
				motor_state = MOTOR_STATE_DEACCEL;
			}

			if (turn_left)
			{
				Set_Motor_Speed(M0, pwm_duty, FORWARD);
				Set_Motor_Speed(M1, pwm_duty, BACKWARD);
			}
			else if (turn_right)
			{
				Set_Motor_Speed(M0, pwm_duty, BACKWARD);
				Set_Motor_Speed(M1, pwm_duty, FORWARD);
			}
			else
			{
				Set_Motor_Speed(M0, pwm_duty, direction);
				Set_Motor_Speed(M1, pwm_duty, direction);
			}

			break;

		//-------------------------------------------------------
		default:

			motor_state = MOTOR_STATE_STOP;

			break;
	}
}



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
