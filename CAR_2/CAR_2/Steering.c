/*
 * Steering.c
 *
 * Created: 19/02/2020 00:44:25
 *  Author: ahmed_pc
 */ 



/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "Steering.h"


/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

ERROR_STATUS Steering_Init(void)
{
	Motor_Init(MOTOR_1);
	Motor_Init(MOTOR_2);
	Motor_Direction (MOTOR_1, MOTOR_STOP);	
	Motor_Direction (MOTOR_2, MOTOR_STOP);
	Motor_Start(MOTOR_1, 40);
	Motor_Start(MOTOR_2, 40);	
	return E_OK;
}

/**
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This funtion controls the command and the speed of the car.
 * 							
 */
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	uint8_t Ret = E_OK;
switch (Steering_CarCmd)
{
	case CAR_STOP:
	Motor_Direction (MOTOR_1, MOTOR_STOP);
	Motor_Direction (MOTOR_2, MOTOR_STOP);	
	break;
	
	case CAR_FORWARD:
	Motor_Direction (MOTOR_1, MOTOR_FORWARD);
	Motor_Direction (MOTOR_2, MOTOR_FORWARD);
	break;
	
	case CAR_BACKWARD:
	Motor_Direction (MOTOR_1, MOTOR_BACKWARD);
	Motor_Direction (MOTOR_2, MOTOR_BACKWARD);
	break;

	case CAR_RIGHT:
	Motor_Direction (MOTOR_1, MOTOR_FORWARD);
	Motor_Direction (MOTOR_2, MOTOR_BACKWARD);
	break;

	case CAR_LEFT:
	Motor_Direction (MOTOR_1, MOTOR_BACKWARD);
	Motor_Direction (MOTOR_2, MOTOR_FORWARD);
	break;
	
	default:
	Ret = E_NOK;
	break;
	
}

Motor_SpeedUpdate(MOTOR_1,speed);

Motor_SpeedUpdate(MOTOR_2,speed);

return Ret ;	
	
}


