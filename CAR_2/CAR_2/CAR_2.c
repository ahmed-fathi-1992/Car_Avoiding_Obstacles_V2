/*
 * CAR_2.c
 *
 * Created: 17/02/2020 00:59:51
 *  Author: FATHI
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
	softwareDelayMs(100);  //for stabilization
    Car_SM_Init();
	softwareDelayMs(100); //for stabilization
	
	while(1)
	{
		Car_SM_Update();
	}
}

