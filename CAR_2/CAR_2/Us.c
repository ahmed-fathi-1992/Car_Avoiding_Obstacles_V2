/*
 * Us.c
 *
 * Created: 18/02/2020 17:24:38
 *  Author: FATHI
 */ 


/************************************************************************/
/*				        INCLUDES			        */
/************************************************************************/

#include "Us.h"

/************************************************************************/
/*		               US FUNCTIONS		        */
/************************************************************************/



/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/

ERROR_STATUS Us_Init(void)
{
	DIO_Cfg_s 	Str_DIO_Cfg = {GPIOA,0x02,OUTPUT};
	Icu_cfg_s   Str_Icu_Cfg = {ICU_CH2,ICU_TIMER_CH2};
	
	if (DIO_init (&Str_DIO_Cfg))
      return E_NOK;
	
	if (DIO_Write (GPIOA, PIN1, LOW) )
	 return E_NOK;
	 
	if (Icu_Init(&Str_Icu_Cfg) )
	 return E_NOK;
	 
	 
return E_OK;	
}




/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


ERROR_STATUS Us_Trigger(void)
{

	DIO_Write (GPIOA, PIN1, HIGH);
	
	softwareDelayMs(10);
	
	DIO_Write (GPIOA, PIN1, LOW);	
	
	return E_OK;
}





/**************************************************************************************************
 * Function Name    : Us_GetDistance.                                                             *
 * Input Parameters : pointer to uint16 that will return the distance on it.                      *                                                                                              *                                                                                                *
 * Output Parameters: Distance.                                                                   *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS.                                                               *
 * Description      : This function get the time of high signal of ECUO pulse, then               *
 *                    use it to calculate the distance, then return the value in the              *
 *                    Distance parameter.                                                         *
 *************************************************************************************************/


ERROR_STATUS Us_GetDistance(uint16_t *Distance)
{
	uint32_t u32_Icu_Time=0;

 Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL,&u32_Icu_Time);

 *Distance = (uint16_t) (u32_Icu_Time /Cm_Per_Us); 
 
 return E_OK;
}
