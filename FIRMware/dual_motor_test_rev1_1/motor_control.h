/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : Motor_Control.h
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 31 October 2010 ]
* Updated by        : Basel Zohny [ 31 October 2010 ]
*
* Description       : Header file for Motor_Control.c
*
* Change History:
* Rev 1.0	[Oct 31, 2010]	- initial
*
****************************************************************************/

#ifndef motor_control_h
#define motor_control_h

#include "platform.h"
#include "xmega_tc.h"



/****************************************************************************
  Macro definitions
****************************************************************************/



/****************************************************************************
  Function definitions. Detailed information is found in source file
****************************************************************************/
void Process_Motor( void );
void Set_Motor_Speed( uint8_t motor_sel, int16_t pwm_duty, uint8_t dir );

#endif
