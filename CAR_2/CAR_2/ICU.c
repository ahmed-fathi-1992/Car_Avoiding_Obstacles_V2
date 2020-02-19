/*
 * ICU.c
 *
 * Created: 18/02/2020 12:05:41
 *  Author: FATHI
 */ 





/************************************************************************/
/*				               Includes                                 */
/************************************************************************/

#include "ICU.h"



/************************************************************************/
/*		        ICU  static FUNCTIONS' PROTOTYPES		        */
/************************************************************************/

static void SwICU_SetCfgEdge(uint8_t a_en_inputCaptureEdgeedge);


/************************************************************************/
/*                GLOBAL STATIC VARIABLES                           */
/************************************************************************/

static volatile uint8_t  gu8_ICU_R_TO_R= 0;
static volatile uint8_t  gu8_ICU_R     = 0;
static volatile uint8_t   gu8_INT_Edge   = SwICU_EdgeRisiging;

//static uint8_t  gu8_Timer2_Prescaler= T2_NO_CLOCK;


/************************************************************************/
/*		                     ICU FUNCTIONS		        */
/************************************************************************/


/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{
	Timer_cfg_s Str_Timer0_cfg = {TIMER_0,TIMER_MODE,TIMER_PRESCALER_1024,TIMER_POLLING_MODE};
	Timer_cfg_s Str_Timer2_cfg = {TIMER_2,TIMER_MODE,TIMER_PRESCALER_1024,TIMER_POLLING_MODE};	
		
	DIO_Cfg_s 	Str_DIO_Cfg_INT2 = {GPIOB,PIN2,INPUT};
	if (Icu_Cfg == NULL)
	{
		return E_NOK;
	}else
	{			
		switch (Icu_Cfg->ICU_Ch_No)
		{
			case ICU_CH0:
			return E_NOK;
			break;			
			case ICU_CH1:	
			return E_NOK;		
			break;
			
			case ICU_CH2:
            		switch (Icu_Cfg->ICU_Ch_Timer)
            		{
	            		case ICU_TIMER_CH0:
	            		Timer_Init(&Str_Timer0_cfg);
						Timer_Start(TIMER_0,0);
	            		break;
						
	            		case ICU_TIMER_CH1:
	            		return E_NOK;
	            		break;
	            		
	            		case ICU_TIMER_CH2:
                        Timer_Init(&Str_Timer2_cfg);
						Timer_Start(TIMER_2,0);
	            		break;
	            		
	            		default:
	            		return E_NOK;
	            		break;
            		}
					DIO_init (&Str_DIO_Cfg_INT2); //configure the external interrupt T2 PIN to be INPUT
					MCUCSR_ = MCUCSR_ |INT2_Edge_MASK;  //configure the external interrupt T2 to be at Risiging edge
					GICR_ = GICR_ | INT2_En_MASK;	//start interrupt T2
					SREG = SREG | BIT7;// enable global interrupt 0x80
			break;
			
			default:
			return E_NOK;
			break;
		}
	}
		return E_OK;
			
	
}

/***************************************************************************
 * Function		: Icu_ReadTime
 * Input		: 
 *				Icu_Channel --> ICU timer channel
 *									- ICU_TIMER_CH0
 *									- ICU_TIMER_CH1
 *									- ICU_TIMER_CH2
 *				Icu_EdgeToEdge -- > edges to calculate pusle time between:
 *									- ICU_RISE_TO_RISE
 *									- ICU_RISE_TO_FALL
 *									- ICU_FALE_TO_RISE					   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from falling edge to rising edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between 2 edges				       *
 ***************************************************************************/
ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time)
{
	if (Icu_Time == NULL)
	{
		return E_NOK;
	}else
	{
		switch (Icu_Channel)
		{
			case ICU_CH0:
			return E_NOK;
			break;
			
			case ICU_CH1:
			return E_NOK;
			break;
			
			case ICU_CH2:
			switch (Icu_EdgeToEdge)
			{
				case ICU_RISE_TO_RISE:
                *Icu_Time= gu8_ICU_R_TO_R * Tick_Time_In_Us; // Rise to Rise time 
				break;
				
				case ICU_RISE_TO_FALL:
                *Icu_Time= gu8_ICU_R * Tick_Time_In_Us ; // Rise to Falling time
				break;
				
				case ICU_FALE_TO_RISE:
                *Icu_Time= (gu8_ICU_R_TO_R - gu8_ICU_R) * Tick_Time_In_Us; // Falling To Rise time
				break;
				
				default:
				return E_NOK;
				break;
			}
			
			default:
			return E_NOK;
			break;
			
		}
	}
      return E_OK;	
}


static void SwICU_SetCfgEdge(uint8_t a_en_inputCaptureEdgeedge)
{
	switch (a_en_inputCaptureEdgeedge)
	{
		case SwICU_EdgeRisiging:
		MCUCSR_ = MCUCSR_ |INT2_Edge_MASK;    //configure the external interrupt T2 to be at Risiging edge
		break;
		
		case SwICU_EdgeFalling:
		MCUCSR_ = MCUCSR_ & (~INT2_Edge_MASK);   //configure the external interrupt T2 to be at falling edge
		break;

		default:
		break;
	}
	
}




ISR(INT2_vector)
{

	switch (gu8_INT_Edge)
	{
		case SwICU_EdgeRisiging:
		gu8_ICU_R_TO_R = TCNT2;
		TCNT2=0;
		SwICU_SetCfgEdge( SwICU_EdgeFalling);// set edge to Falling
		gu8_INT_Edge=SwICU_EdgeFalling;
		break;
		
		case SwICU_EdgeFalling:
		gu8_ICU_R = TCNT2;
		ICR1L=gu8_ICU_R	;	
		SwICU_SetCfgEdge( SwICU_EdgeRisiging);// set edge to rising
		gu8_INT_Edge=SwICU_EdgeRisiging;
		break;

		default:
		break;
	}
	
}
