/*
 * PWM.c
 *
 * Created: 17/02/2020 23:53:02
 *  Author: FATHI
 */ 


/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/
#include "PWM.h"

/************************************************************************/
/*                GLOBAL STATIC VARIABLES                           */
/************************************************************************/

//static uint8_t   gu8_PWM_CH0_Prescaler= T0_NO_CLOCK;
static uint16_t  gu16_PWM_CH1A_Prescaler= T1_NO_CLOCK;
static uint16_t  gu16_PWM_CH1B_Prescaler= T1_NO_CLOCK;
//static uint8_t   gu8_PWM_CH2_Prescaler= T2_NO_CLOCK;


/************************************************************************/
/*		         PWM FUNCTIONS		        */
/************************************************************************/


/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                         */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg)
{
	uint8_t Ret = E_OK;
	DIO_Cfg_s 	DIO_Cfg_PWM_CH1A = {GPIOD,PIN5,OUTPUT};
	DIO_Cfg_s 	DIO_Cfg_PWM_CH1B = {GPIOD,PIN4,OUTPUT};	
		
	if (Pwm_Cfg == NULL)
	{
		Ret = E_NOK;
	}else
	{		
		switch (Pwm_Cfg->Channel)
		{
			case PWM_CH0:
			Ret = E_NOK;
			break;
			
			case PWM_CH1A:
				   	switch (Pwm_Cfg->Prescaler)
				   	{
					   	case PWM_PRESCALER_NO:
					   	gu16_PWM_CH1A_Prescaler = T1_NO_CLOCK;
					   	break;
					   	case PWM_PRESCALER_8:
					   	gu16_PWM_CH1A_Prescaler = T1_PRESCALER_NO ;
					   	break;
					   	case PWM_PRESCALER_64:
					   	gu16_PWM_CH1A_Prescaler = T1_PRESCALER_64 ;
					   	break;
					   	case PWM_PRESCALER_256:
					    gu16_PWM_CH1A_Prescaler = T1_PRESCALER_256 ;
					   	break;
					   	case PWM_PRESCALER_1024:
					   	gu16_PWM_CH1A_Prescaler = T1_PRESCALER_1024 ;
					   	break;
					   	default:
					   	Ret = E_NOK;
					   	break;
				   	}// end of switch (Pwm_Cfg->Prescaler)
					   
					TCCR1= TCCR1 | T1_Fast_PWM_8_bit; //set PWM mode
					
					TCCR1= TCCR1 | T1_OC1A_CLEAR; //configure OC1A channel 
					
					DIO_init (&DIO_Cfg_PWM_CH1A);					   			
			 break;
			
			case PWM_CH1B:
				   	switch (Pwm_Cfg->Prescaler)
				   	{
					   	case PWM_PRESCALER_NO:
					   	gu16_PWM_CH1B_Prescaler = T1_NO_CLOCK;
					   	break;
					   	case PWM_PRESCALER_8:
					   	gu16_PWM_CH1B_Prescaler = T1_PRESCALER_NO ;
					   	break;
					   	case PWM_PRESCALER_64:
					   	gu16_PWM_CH1B_Prescaler = T1_PRESCALER_64 ;
					   	break;
					   	case PWM_PRESCALER_256:
					   	gu16_PWM_CH1B_Prescaler = T1_PRESCALER_256 ;
					   	break;
					   	case PWM_PRESCALER_1024:
					   	gu16_PWM_CH1B_Prescaler = T1_PRESCALER_1024 ;
					   	break;
					   	default:
					   	Ret = E_NOK;
					   	break;
				   	}// end of  switch (Pwm_Cfg->Prescaler)
					   
					TCCR1= TCCR1 | T1_Fast_PWM_8_bit; //set PWM mode
									
					TCCR1= TCCR1 | T1_OC1B_CLEAR; //configure OC1B channel	   
					 
					DIO_init (&DIO_Cfg_PWM_CH1B);   
			break;
			
			case PWM_CH2:
			Ret = E_NOK;
			break;
			
			default:
			Ret = E_NOK;
			break;
		}// end of switch
     }// end of else
		return Ret ;	
	
}


/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*-------------------------------------------------------                        */
/*(IN timer 0) there are only 5 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*--------------------------------------------------------                       */
/*(IN timer 2) there are only 7 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 32) --> 980HZ                                             */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 128) --> 245HZ                                            */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy)
{
	uint8_t Ret = E_OK;
	
	switch (Channel)
	{
		case PWM_CH0:
		Ret = E_NOK;
		break;
		
		case PWM_CH1A:
		TCCR1= TCCR1 | gu16_PWM_CH1A_Prescaler ;
		OCR1A = ((uint16_t)Duty*255)/100; //set OCR1A to duty cycle 
		break;
		
		case PWM_CH1B:
		TCCR1= TCCR1 | gu16_PWM_CH1B_Prescaler ;
		OCR1B = ((uint16_t)Duty*255)/100; //set OCR1B to duty cycle
		break;
		
		case PWM_CH2:
		Ret = E_NOK;
		break;
		
		default:
		Ret = E_NOK;
		break;
	}// end of switch
	
	 return Ret ;	
}

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy)
{
	uint8_t Ret = E_OK;
	switch (Channel)
	{
		case PWM_CH0:
		Ret = E_NOK;
		break;
		
		case PWM_CH1A:
		OCR1A = ((uint16_t)Duty*255)/100; //set OCR1A to duty cycle
		break;
		
		case PWM_CH1B:
		OCR1B = ((uint16_t)Duty*255)/100; //set OCR1B to duty cycle
		break;
		
		case PWM_CH2:
		Ret = E_NOK;
		break;
		
		default:
		Ret = E_NOK;
		break;
	}// end of switch
	
	return Ret ;	
}

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Stop(uint8_t Channel)
{
	uint8_t Ret = E_OK;
	
	switch (Channel)
	{
		case PWM_CH0:
		Ret = E_NOK;
		break;
		
		case PWM_CH1A:
		TCCR1= TCCR1 & ~gu16_PWM_CH1A_Prescaler ;
		break;
		
		case PWM_CH1B:
		TCCR1= TCCR1 & ~gu16_PWM_CH1B_Prescaler ;
		break;
		
		case PWM_CH2:
		Ret = E_NOK;
		break;
		
		default:
		Ret = E_NOK;
		break;
	}// end of switch
	
	return Ret ;	
}
