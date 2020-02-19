/*
 * car_sm.c
 *
 * Created: 19/02/2020 01:32:04
 *  Author: FATHI

*/ 
 /*************************************************************/
 /*                     INCLUDES                              */
 /*************************************************************/
#include "car_sm.h"
 #include "std_types.h"

 
/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 80%",
 * -------------- And initiate steering and ultrasonic functions
*/
ERROR_STATUS Car_SM_Init(void)
{	
	Us_Init();
	Steering_Init();
	return E_OK;
}

/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/
ERROR_STATUS Car_SM_Update(void)
{
	uint16_t Distance=0;
	Car_states state = Start_state;

	while(1){
		switch(state) {
			case Start_state:  {
				               Us_Trigger();
				               softwareDelayMs(50); 
							   Us_GetDistance(& Distance);
							   ICR1H=(uint8_t)Distance	;
							   if (Distance>50)
							   {
								   Steering_SteerCar(CAR_FORWARD, 70);
							   }else
							   {
								   if (Distance<=50 && Distance>30  )
								   {
										state = Right_state;
								   }else
								   {
									   state = Back_state; 
								   }
								   
							   }
 
							  break;
							 }
			case Back_state: {
							   Steering_SteerCar(CAR_BACKWARD, 80);
							   softwareDelayMs(80);
				               state=Start_state; 
							   break;
							  }
			case Right_state: {
								Steering_SteerCar(CAR_RIGHT, 80);
								softwareDelayMs(80);
								state=Start_state;
							    break;
							  }				
		}//end of switch.
	}//end of while
		
	
	return E_NOK;
}
