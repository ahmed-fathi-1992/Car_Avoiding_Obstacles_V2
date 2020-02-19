/*
 * Timer.c
 *
 * Created: 17/02/2020 10:31:03
 *  Author: FATHI
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "Timer.h"

/************************************************************************/
/*		         TIMER static FUNCTIONS' PROTOTYPES		        */
/************************************************************************/

static ERROR_STATUS Timer0_Init(Timer_cfg_s* Timer_cfg);
static ERROR_STATUS Timer1_Init(Timer_cfg_s* Timer_cfg);
static ERROR_STATUS Timer2_Init(Timer_cfg_s* Timer_cfg);

/************************************************************************/
 /*                GLOBAL STATIC VARIABLES                           */
/************************************************************************/

static uint8_t  gu8_Timer0_Prescaler= T0_NO_CLOCK;
static uint16_t gu16_Timer1_Prescaler= T1_NO_CLOCK;
static uint8_t  gu8_Timer2_Prescaler= T2_NO_CLOCK;


/************************************************************************/
/*		         TIMER FUNCTIONS		        */
/************************************************************************/


/**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	uint8_t Ret = E_OK;
	if (Timer_cfg == NULL)
	{
	  Ret = E_NOK;
	}else
	{
	   switch (Timer_cfg->Timer_CH)
		{
	       case TIMER_0:
           return Timer0_Init(Timer_cfg);
		   break; 	   
		   case TIMER_1:
           return Timer1_Init( Timer_cfg);
		   break;
		   case TIMER_2:
	       return Timer2_Init( Timer_cfg);
		   break;
		   default:
		   Ret = E_NOK;
		   break;
		}//end of switch.
	}//end of else
	return Ret ;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function strats the needed timer.
 * 							
 */
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{
	uint8_t Ret = E_OK;
		switch (Timer_CH_NO)
		{
			case TIMER_0:
			 TCNT0=(uint8_t)Timer_Count;
			 TCCR0= TCCR0 | gu8_Timer0_Prescaler;						
			break;
			
			case TIMER_1:			
			 TCNT1=Timer_Count;
			 TCCR1= TCCR1 | gu16_Timer1_Prescaler;
			break;
			
			case TIMER_2:		
			TCNT2=(uint8_t)Timer_Count;
			TCCR2= TCCR2 | gu8_Timer2_Prescaler;
			break;
			
			default:
			Ret = E_NOK;
			break;
		}//end of switch.
	
return Ret ;	
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function stops the needed timer.
 * 							
 */
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO)
{
	uint8_t Ret = E_OK;
		switch (Timer_CH_NO)
		{
			case TIMER_0:
			TCCR0= TCCR0 & ~gu8_Timer0_Prescaler;
			break;
			
			case TIMER_1:
			TCCR1= TCCR1 & ~gu16_Timer1_Prescaler;
			break;
			
			case TIMER_2:
			TCCR2= TCCR2 & ~gu8_Timer2_Prescaler;
			break;
			
			default:
			Ret = E_NOK;
			break;
		}//end of switch.
		
		return Ret ;	
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 */
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t* Data)
{
	uint8_t Ret = E_OK;
	if (Data == NULL)
	{
		Ret = E_NOK;
	}else
	{
		switch (Timer_CH_NO)
		{
			case TIMER_0:
			*Data = TIFR ;			
			break;
			
			case TIMER_1:
			*Data = TIFR;
			break;
			
			case TIMER_2:
			*Data = TIFR;
			break;
			
			default:
			Ret = E_NOK;
			break;
		}//end of switch
		
	}//end of else
	
		return Ret ;	
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return the value of the timer.
 * 							
 */
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data)
{
	uint8_t Ret = E_OK;
	
	if (Data == NULL)
	{
		Ret = E_NOK;
	}else
	{	
		switch (Timer_CH_NO)
		{
			case TIMER_0:
			*Data = TCNT0 ;
			break;
			
			case TIMER_1:
			*Data = TCNT1;
			break;
			
			case TIMER_2:
			*Data = TCNT2 ;
			break;
			
			default:
			Ret = E_NOK;
			break;
		}//end of switch
	}//end of else
		return Ret ;	
}


/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * 	Data: This is the Input variable of the function which holds the value of the timer needed to be set .
 * Output
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return the value of the timer.
 * 							
 */
ERROR_STATUS Timer_SetValue(uint8_t Timer_CH_NO, uint16_t Data)
{
	uint8_t Ret = E_OK;
	
		switch (Timer_CH_NO)
		{
			case TIMER_0:
			TCNT0=(uint8_t)Data ;
			break;
			
			case TIMER_1:
			TCNT1= Data  ;
			break;
			
			case TIMER_2:
			TCNT2= (uint8_t)Data ;
			break;
			
			default:
			Ret =  E_NOK;
			break;
		}//end of switch
		
		return Ret ;
}

/**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates Timer0.
 * 							
 */


static ERROR_STATUS Timer0_Init(Timer_cfg_s* Timer_cfg)
{
	uint8_t Ret = E_OK;
	
			   	switch (Timer_cfg->Timer_Mode)
			   	{
				   	case TIMER_MODE:
					   TCCR0= TCCR0 | T0_NO_CLOCK;
				   	switch (Timer_cfg->Timer_Prescaler)
				   	{
					   	case TIMER_NO_CLOCK:
					   	gu8_Timer0_Prescaler= T0_NO_CLOCK;
					   	break;
					   	case TIMER_PRESCALER_NO:
					   	gu8_Timer0_Prescaler= T0_PRESCALER_NO ;
					   	break;
					   	case TIMER_PRESCALER_8:
					   	gu8_Timer0_Prescaler=  T0_PRESCALER_8 ;
					   	break;
					   	case TIMER_PRESCALER_64:
					   	gu8_Timer0_Prescaler=  T0_PRESCALER_64 ;
					   	break;
					   	case TIMER_PRESCALER_256:
					   	gu8_Timer0_Prescaler=  T0_PRESCALER_256 ; 
					   	break;
					   	case TIMER_PRESCALER_1024:
					   	gu8_Timer0_Prescaler=  T0_PRESCALER_1024 ; 
					   	break;
					   	default:
					   	Ret = E_NOK;
					   	break;
				   	}//end of switch ( end of Timer_cfg->Timer_Prescaler	)			   	
				   	break;// end of Timer_mode
				   	
				   	case COUNTER_RISING_MODE:
				   	TCCR0= TCCR0 | T0_Ex_CLOCK_RISING_EDGE ;  // configure timer as counter mode on rising edge
					gu8_Timer0_Prescaler= T0_Ex_CLOCK_RISING_EDGE;  // save timer prescaler configuration to be set later on start function
				   	break;// end of COUNTER_RISING_MODE
					   
				   	default:
				   	Ret = E_NOK;
				   	break;
			   	} // end of switch (Timer_cfg->Timer_Mode)
			   	
			   	/////
			   	
			   	switch (Timer_cfg->Timer_Polling_Or_Interrupt)
			   	{
				   	case TIMER_POLLING_MODE:
				   	TIMSK = TIMSK | T0_POLLING; //Disable interrupt  
				   	break;
					   
				   	case TIMER_INTERRUPT_MODE:
				   	TIMSK = TIMSK | T0_INTERRUPT_NORMAL; // enable interrupt 
				   	break;
					   
				   	default:
				   	Ret = E_NOK;
				   	break;
			   	}	
	return Ret ;
	
}


/**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates Timer1.
 * 							
 */

static ERROR_STATUS Timer1_Init(Timer_cfg_s* Timer_cfg)
{
	uint8_t Ret = E_OK;
			   	switch (Timer_cfg->Timer_Mode)
			   	{
				   	case TIMER_MODE:
					   TCCR1= TCCR1 | T1_NO_CLOCK;
				   	switch (Timer_cfg->Timer_Prescaler)
				   	{
					   	case TIMER_NO_CLOCK:
					   	gu16_Timer1_Prescaler= T1_NO_CLOCK; 
					   	break;
					   	case TIMER_PRESCALER_NO:
					   	gu16_Timer1_Prescaler= T1_PRESCALER_NO ;
					   	break;
					   	case TIMER_PRESCALER_8:
					   	gu16_Timer1_Prescaler= T1_PRESCALER_8 ;
					   	break;
					   	case TIMER_PRESCALER_64:
					   	gu16_Timer1_Prescaler= T1_PRESCALER_64 ;
					   	break;
					   	case TIMER_PRESCALER_256:
					   	gu16_Timer1_Prescaler= T1_PRESCALER_256 ;
					   	break;
					   	case TIMER_PRESCALER_1024:
					   	gu16_Timer1_Prescaler= T1_PRESCALER_1024 ;
					   	break;
						   
					   	default:
					   	Ret = E_NOK;
					   	break;
				   	}// end of Timer_cfg->Timer_Prescaler
				   	break;// end of Timer_mode
				   	
				   	case COUNTER_RISING_MODE:
				   	TCCR1= TCCR1 | T1_Ex_CLOCK_RISING_EDGE ;
					gu16_Timer1_Prescaler= T1_Ex_CLOCK_RISING_EDGE;
				   	break;
					   
				   	default:
				   	Ret = E_NOK;
				   	break;
			   	} // end of switch ( Timer_cfg->Timer_Mode)
			   	
			   	/////
			   	
			   	switch (Timer_cfg->Timer_Polling_Or_Interrupt)
			   	{
				   	case TIMER_POLLING_MODE:
				   	TIMSK = TIMSK | T1_POLLING;//Disable  interrupt 
				   	break;
					   
				   	case TIMER_INTERRUPT_MODE:
				   	TIMSK = TIMSK | T1_INTERRUPT_NORMAL;// enable interrupt
				   	break;
					   
				   	default:
				   	Ret = E_NOK;
				   	break;
			   	}
			   	
		   
	return Ret ;
	
}


/**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates Timer2.
 * 							
 */

static ERROR_STATUS Timer2_Init(Timer_cfg_s* Timer_cfg)
{
	uint8_t Ret = E_OK;
		       switch (Timer_cfg->Timer_Mode)
		       {
			       case TIMER_MODE:
				       TCCR2= TCCR2 | T2_NO_CLOCK;
				       switch (Timer_cfg->Timer_Prescaler)
				       {
					       case TIMER_NO_CLOCK:						   
					       gu8_Timer2_Prescaler= T2_NO_CLOCK ;
					       break;
					       case TIMER_PRESCALER_NO:
					       gu8_Timer2_Prescaler= T2_PRESCALER_NO ;
					       break;
					       case TIMER_PRESCALER_8:
					       gu8_Timer2_Prescaler= T2_PRESCALER_8 ;
					       break;
					       case TIMER_PRESCALER_32:
					       gu8_Timer2_Prescaler= T2_PRESCALER_32 ;
					       break;
					       case TIMER_PRESCALER_64:
					       gu8_Timer2_Prescaler= T2_PRESCALER_64 ;
					       break;	
					       case TIMER_PRESCALER_128:
					       gu8_Timer2_Prescaler= T2_PRESCALER_128 ;
					       break;						   					   
					       case TIMER_PRESCALER_256:
					       gu8_Timer2_Prescaler= T2_PRESCALER_256 ;
					       break;
					       case TIMER_PRESCALER_1024:
					       gu8_Timer2_Prescaler= T2_PRESCALER_1024 ;
					       break;
						   
					       default:
					       Ret = E_NOK;
					       break;
				       }// end of switch (Timer_cfg->Timer_Prescaler)
					   			       
			       break; // end of Timer_mode
				   
			       case COUNTER_RISING_MODE:
				   Ret = E_NOK;
			       break;
				   
			       default:
			       Ret = E_NOK;
			       break;
		       } // end of switch (Timer_cfg->Timer_Mode)

/////////////  configur  interrupt //////////////////
		       	       
		       switch (Timer_cfg->Timer_Polling_Or_Interrupt)
		       {
			       case TIMER_POLLING_MODE:
			       TIMSK = TIMSK | T2_POLLING; //Disable  interrupt
			       break;
				   
			       case TIMER_INTERRUPT_MODE:
			       TIMSK = TIMSK | T2_INTERRUPT_CMP; // enable interrupt
			       break;
				   
			       default:
			       Ret = E_NOK;
			       break;
		       }// end of switch
	
	return Ret ;
}