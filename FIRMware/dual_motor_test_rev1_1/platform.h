/***************************************************************************
*
* Company			: BAZ Inc.
*
* File              : platform.h
* Compiler          : AVR-GCC
* Created by        : Basel Zohny [ 31 October 2010 ]
* Updated by        : Basel Zohny [ 31 October 2010 ]
*
* Description       : Global defines/variable and other project specific
*					  macros.
*
* Change History:
* Rev 1.0	[Oct 31, 2010]	- initial
*
****************************************************************************/


#include <baz_avr.h>



/****************************************************************************
  Define Definitions
****************************************************************************/
//#define	F_CPU				32000000					// 32 MHz

#define PWM_FREQ			20000						// 20 KHz
#define MAX_PWM				(F_CPU/PWM_FREQ)			// 32Mhz/20Khz = 1600

#define SYS_TICK			4							// 4 ms
#define SYS_TICK_4MS		4/SYS_TICK					// 1 system tick = 4ms
#define SYS_TICK_12MS		12/SYS_TICK					// 3 system ticks = 8ms
#define SYS_TICK_48MS		48/SYS_TICK					// 12 system ticks = 48ms
#define SYS_TICK_100MS		100/SYS_TICK				// 25 system ticks = 100ms
#define SYS_TICK_200MS		200/SYS_TICK				// 50 system ticks = 200ms
#define SYS_TICK_400MS		400/SYS_TICK				// 100 system ticks = 400ms
#define SYS_TICK_500MS		500/SYS_TICK				// 125 system ticks = 500ms
#define SYS_TICK_800MS		800/SYS_TICK				// 200 system ticks = 800ms
#define SYS_TICK_1S			1000/SYS_TICK				// 250 system ticks = 1 second
#define SYS_TICK_2S			2000/SYS_TICK				// 500 system ticks = 2 seconds
#define SYS_TICK_5S			5000/SYS_TICK				// 1250 system ticks = 5 seconds
#define SYS_TICK_10S		10000/SYS_TICK				// 2500 system ticks = 10 seconds

//#define MOTOR_STATE_STOP	0
//#define MOTOR_STATE_ACCEL	1
//#define MOTOR_STATE_CRUISE	2
//#define MOTOR_STATE_DEACCEL	3

#define M0					0
#define M1					1

#define MOTOR_TIMER			TCD0
#define MOTOR_OUTPUT		PORTD

#define MOTORS_STOP			0x3C

#define M0_STOP				0x14
#define M0_FORWARD			0x04
#define M0_BACKWARD			0x10

#define M1_STOP				0x28
#define M1_FORWARD			0x08
#define M1_BACKWARD			0x20

#define FORWARD				0
#define BACKWARD			1

#define LED0_TIME			SYS_TICK_500MS

#define USARTD1_BAUDRATE	9600
#define USARTD1_BAUD		(uint16_t)((F_CPU/(16.0*USARTD1_BAUDRATE))-1)
// Need to put 16.0 since pre-processor won't calculate 32bit results correctly

#define SOF					7E


// Uart TX and RX buffer size
#define USART_RX_BUFF_SIZE	16
#define USART_TX_BUFF_SIZE	16


/****************************************************************************
  Variable Definitions
****************************************************************************/
volatile bool				sys_ticked;

//volatile bool				turn_left;
//volatile bool				turn_right;
volatile uint8_t			direction;

volatile uint16_t			led0_tick;
volatile uint16_t			motor_tick;
//volatile uint8_t			motor_state_tick;

//volatile uint8_t			motor_state;
volatile int16_t			pwm_duty;

volatile uint16_t			speed;
//volatile uint16_t			accel_step;
//volatile uint16_t			deaccel_step;
//volatile uint16_t			cruise_stop;

volatile uint8_t			tx_d1_buf_ptr;
volatile uint8_t			rx_d1_buf_ptr;
volatile uint8_t			tx_d1_buf[USART_TX_BUFF_SIZE];
volatile uint8_t			rx_d1_buf[USART_RX_BUFF_SIZE];
