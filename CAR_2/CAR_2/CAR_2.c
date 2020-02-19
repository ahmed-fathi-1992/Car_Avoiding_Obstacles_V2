/*
 * CAR_2.c
 *
 * Created: 17/02/2020 00:59:51
 *  Author: ahmed_pc
 */ 


//#include <avr/io.h>
#include "std_types.h"
#include "registers.h"
#include "Timer.h"
#include "DIO.h"
#include "PWM.h"
#include "interrupt.h"
#include "softwareDelay.h"
#include "ICU.h"
#include "Us.h"
#include "motor.h"
#include "Steering.h"
#include "car_sm.h"


int main(void)
{
	softwareDelayMs(100);
    Car_SM_Init();
	softwareDelayMs(100);
	while(1)
	{
		Car_SM_Update();
	}
}

/*
int main(void)
{
	//uint16_t Distance=0;
	//uint32_t Icu_Time=0;
	//PORTA_DIR = 0xFF;
	//PORTA_DATA = 0xF0;
// 	Timer_cfg_s Timer_cfg= {TIMER_0,TIMER_MODE,TIMER_PRESCALER_256,TIMER_POLLING_MODE};
// 	DIO_Cfg_s 	DIO_Cfg = {GPIOA,0x02,INPUT};
// 	Pwm_Cfg_s   Pwm_Cfg_PWM_CH1A	= {PWM_CH1A,PWM_PRESCALER_256};
// 	Pwm_Cfg_s   Pwm_Cfg_PWM_CH1B	= {PWM_CH1B,PWM_PRESCALER_256};	
	
	//Icu_cfg_s   Icu_Cfg = {ICU_CH2,ICU_TIMER_CH2};
			softwareDelayMs(1000);
	//Us_Init();
// 	Car_SM_Init();	
// 	Us_Trigger();
// 	softwareDelayMs(1000);
// 	Us_GetDistance(&Distance);
// 	ICR1H=(uint8_t)Distance	;
// 	
// 	Motor_Init(MOTOR_1);
// 	 Motor_Direction (MOTOR_1, MOTOR_BACKWARD);
// 	 Motor_Start(MOTOR_1, 70);
// 	 
// 	 	Motor_Init(MOTOR_2);
// 	 	Motor_Direction (MOTOR_2, MOTOR_BACKWARD);
// 	 	Motor_Start(MOTOR_2, 70);
//	Steering_Init();	 
		 
// 	Timer_Init(&Timer_cfg);
// 	Timer_Start(TIMER_0, 100);	
// 	DIO_init (&DIO_Cfg);
// 	DIO_Write (GPIOA, 0x02, HIGH);
// 	Pwm_Init(&Pwm_Cfg_PWM_CH1A);
// 	Pwm_Init(&Pwm_Cfg_PWM_CH1B);
// 	Pwm_Start(PWM_CH1A,60,1000);
// 	Pwm_Start(PWM_CH1B,20,1000);
// 	Pwm_Update(PWM_CH1A,10,1000);
// 	Pwm_Update(PWM_CH1B,10,1000);
	
	//Icu_Init(& Icu_Cfg);

    while(1)
    {

		//Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL,&Icu_Time);
// 		Us_Trigger();
// 		softwareDelayMs(100);	
// 	    Us_GetDistance(&Distance);
// 		ICR1H=(uint8_t)Distance	;
// 		
// 		if (Distance<40)
// 		{
// // 			Motor_Direction (MOTOR_1, MOTOR_FORWARD);
// // 		    Motor_Direction (MOTOR_2, MOTOR_FORWARD);
// 			Steering_SteerCar(CAR_RIGHT, 70);
// 			softwareDelayMs(100);
// 			
// 		}else
// 		{
// // 			Motor_Direction (MOTOR_1, MOTOR_BACKWARD);
// // 			Motor_Direction (MOTOR_2, MOTOR_BACKWARD);
// 			
// 			Steering_SteerCar(CAR_FORWARD, 70);
// 		}
		
// 		Timer_GetValue(TIMER_0, &data);
// 		if (data>150 && data<200)
// 		{//PORTA_DATA = 0xFF;
// 		}
// 				if (data>200)
// 				{//PORTA_DATA = 0xF0;
// 					Timer_Stop(TIMER_0);
// 				}
// 
		
        //TODO:: Please write your application code 
    }
}
*/