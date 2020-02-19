/*
 * motor.c
 *
 * Created: 18/02/2020 19:08:19
 *  Author: FATHI
 */ 


/*********************************************
 *				Includes  					 *
 ********************************************/
#include "motor.h"
#include "PWM.h"



/**
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
 ERROR_STATUS Motor_Init(uint8_t Motor_Number)
 {
	 Pwm_Cfg_s   Pwm_Cfg_PWM_CH1A	= {PWM_CH1A,PWM_PRESCALER_256};
 	 Pwm_Cfg_s   Pwm_Cfg_PWM_CH1B	= {PWM_CH1B,PWM_PRESCALER_256};
	  
	 DIO_Cfg_s 	DIO_MOTOR_1A_Cfg = {MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_PIN,OUTPUT};
	 DIO_Cfg_s 	DIO_MOTOR_1B_Cfg = {MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_PIN,OUTPUT};
		 
	 DIO_Cfg_s 	DIO_MOTOR_2A_Cfg = {MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_PIN,OUTPUT};
	 DIO_Cfg_s 	DIO_MOTOR_2B_Cfg = {MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_PIN,OUTPUT};
		 	 	 
		switch (Motor_Number)
		{
			case MOTOR_1:
             DIO_init (&DIO_MOTOR_1A_Cfg);
			 DIO_init (&DIO_MOTOR_1B_Cfg);
			 Pwm_Init(&Pwm_Cfg_PWM_CH1A);
			 
			break;
			
			case MOTOR_2:
             DIO_init (&DIO_MOTOR_2A_Cfg);
             DIO_init (&DIO_MOTOR_2B_Cfg);
			 Pwm_Init(&Pwm_Cfg_PWM_CH1B);
			
			break;

			default:
			return E_NOK;
			break;
		}
		
	return E_OK;		 
	 
 }
 
/**
 * Fun		 : Motor_Direction
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2

			   @param Motor_Direction
			   #define
			   Stop, Forward, Backword
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor direction from getting the motor number and the direction.
*/
ERROR_STATUS Motor_Direction (uint8_t Motor_Number, uint8_t Mot_Direction)
{

switch (Motor_Number)
{
	//////////motor1///////////
	case MOTOR_1:
	switch (Mot_Direction)
	{
		case MOTOR_STOP:
        DIO_Write (MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_PIN, LOW);
		DIO_Write (MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_PIN, LOW);
		break;
		case MOTOR_FORWARD:
        DIO_Write (MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_PIN, HIGH);
        DIO_Write (MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_PIN, LOW);
		break;
		case MOTOR_BACKWARD:
        DIO_Write (MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_PIN, LOW);
        DIO_Write (MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_PIN, HIGH);
		break;
		default:
		break;
	}
	break;
	
	////////motor2//////////
	case MOTOR_2:
	switch (Mot_Direction)
	{
		case MOTOR_STOP:
		DIO_Write (MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_PIN, LOW);
		DIO_Write (MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_PIN, LOW);
		break;
		case MOTOR_FORWARD:
		DIO_Write (MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_PIN, HIGH);
		DIO_Write (MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_PIN, LOW);
		break;
		case MOTOR_BACKWARD:
		DIO_Write (MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_PIN, LOW);
		DIO_Write (MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_PIN, HIGH);
		break;
		default:
		break;
	}
	break;
	
	default:
	return E_NOK;
	break;	
}

	return E_OK;	
	
}

/**
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Start the motor.
*/
ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed)
{

switch (Motor_Number)
{
	//////////motor1///////////
	case MOTOR_1:
	Pwm_Start(PWM_CH1A,Mot_Speed,0);
	break;
	
	////////motor2//////////
	case MOTOR_2:
	Pwm_Start(PWM_CH1B,Mot_Speed,0);
	break;
	
	default:
	return E_NOK;
	break;
	
}
	return E_OK;
}

/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor speed from getting the motor number and the speed.
*/
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed)
{
switch (Motor_Number)
{
	//////////motor1///////////
	case MOTOR_1:
	//Pwm_Start(PWM_CH1A,Mot_Speed,0);
	Pwm_Update(PWM_CH1A,Speed,0);
	break;
	
	////////motor2//////////
	case MOTOR_2:
	//Pwm_Start(PWM_CH1B,Mot_Speed,0);
	Pwm_Update(PWM_CH1B,Speed,0);
	break;
	
	default:
	return E_NOK;
	break;
	
}
return E_OK;	
	
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: stop the motor.
*/
ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
switch (Motor_Number)
{
	//////////motor1///////////
	case MOTOR_1:
	Pwm_Stop(PWM_CH1A);
	break;
	
	////////motor2//////////
	case MOTOR_2:
	Pwm_Stop(PWM_CH1B);
	break;
	
	default:
	return E_NOK;
	break;
	
}
return E_OK;	
	
}

 /**
 * Func			: Motor_GetStatus
 * Input		: Motor_Number
 *	  	  		 #def
 *	  	  		 number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: Initialization_STATUS
 * Description	: Returns status of the motor whether intialized or not
 */
 ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status)
 {

	return E_OK;	 
	 
 }
