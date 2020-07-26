/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "mcu_hw.h"
#include "WDT.h"
#include "WDT_cfg.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define WDT1_ASSERTED_VAL 0x80000000
#define INTEN			0u
#define RESEN			1u
#define	INTTYPE			2u
#define	WRC				31u
#define	Locked			0x00000001
#define milli_Sec		1000u
#define PIOSC_Time_SEC	(1/PIOSC_FREQ)
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static uint32		loc_ConfigVar = 0u;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern const WDT_ConfigType	WDT_Config[];
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void WDT_Init( const WDT_ConfigType* ConfigPtr)       
* \Description     : Initialize Watchdog Timer                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr   Configuration array include all desired configuration parameters                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void WDT_Init( const WDT_ConfigType* ConfigPtr)
{
	NotEnableType	loc_Notification;
	InterruptType	loc_Intp_Type;
	WDTInitTimeType	loc_InitialTimeOut;
	WDTMaxTimeType	loc_MaxTimeOut;
	WDTChannelType	loc_WDTChannelBaseAddr;
	
	
	for( uint8 i=0 ; i < WDT_ACTIVATED_CHANNELS_SIZE ; i++ )
	{
		loc_WDTChannelBaseAddr	= ConfigPtr[i].wdtChannelSelected;
		loc_Notification 		= ConfigPtr[i].notificationEN;
		loc_Intp_Type	 		= ConfigPtr[i].wdtInterrType;
		loc_InitialTimeOut 		= ConfigPtr[i].wdtInitialTimeout;
		loc_MaxTimeOut			= ConfigPtr[i].wdtMaxTimeout;
		
		/* 1. Load the WDTLOAD register with the desired timer load value. */
		WDTLOAD(loc_WDTChannelBaseAddr)	= loc_InitialTimeOut;
				
		/* 2. If WDT1, wait for the WRC bit in the WDTCTL register to be set. */

		while( (WDTCTL(loc_WDTChannelBaseAddr)) != WDT1_ASSERTED_VAL );
		
		/* Prepare Configuration Variable of WDT */
		/* 3. If the Watchdog is configured to trigger system resets, set the RESEN bit in the WDTCTL register. */
		/* 	  Reset always Enabled According to AUTOSAR */
		
		loc_ConfigVar |= ENABLE<<RESEN;
		
		/* 5. Set the INTEN bit in the WDTCTL register to enable the Watchdog, enable interrupts, and lock the control register. */
		
		if(loc_Notification == ENABLE)
		{
				SET_BIT(loc_ConfigVar,INTEN);
				/* Assign Desired Interrupt (STD/NMI) */
				loc_ConfigVar |= loc_Intp_Type<<INTTYPE;
		}
		else{
				CLR_BIT(loc_ConfigVar,INTEN)
			}
		
		SET_BIT(loc_ConfigVar,WRC);
		
		WDTCTL(loc_WDTChannelBaseAddr) = loc_ConfigVar;
		
		/* 2. If WDT1, wait for the WRC bit in the WDTCTL register to be set. */

		while( (WDTCTL(loc_WDTChannelBaseAddr)) != loc_ConfigVar );
		
		/* lock the control register. */
		
		WDTLOCK(loc_WDTChannelBaseAddr) = Locked;
		
		/* Wait for Lock Asserted by Match the value of WDTLOCK with Locked value given */
		while( ( WDTLOCK(loc_WDTChannelBaseAddr) ) != Locked);
		
	}/* For END */

}   


/******************************************************************************
* \Syntax          : void WDT_SetTriggerCondition( uint16 timeout )        
* \Description     : It Set WDT time out                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : timeout   time in milli second                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void WDT_SetTriggerCondition( uint16 timeout )
{
	static uint32 loc_WDT_Tick = 0;			/* WDT One Tick Time */
	static uint32 loc_NOF_Tick = 0;			/* WDT Number of Tick Needed to achieve desired time out */
	
	if(timeout < wdtMaxTimeout)
	{
		if(timeout != NULL)
		{
			/* Convert WDT Tick time to milli second */
			loc_WDT_Tick =(uint32)( PIOSC_Time_SEC * milli_Sec ) ;	/* Convert WDT Time to milli sec */
			
			/* Get Number of Tick needed */
			loc_NOF_Tick = (uint32)( timeout / loc_WDT_Tick );		
			
			WDTLOAD(WDT1_BASEADDRESS)	= loc_NOF_Tick ;
			
			/* 2. If WDT1, wait for the WRC bit in the WDTCTL register to be set. */
		
			while( (WDTCTL(loc_WDTChannelBaseAddr)) != loc_ConfigVar );
		}
		else{
			/* Rest MCU Immediately without any update to WDTLOAD */
			Mcu_PerformReset();		/* Perform Reset immediately through MCU driver */
		}
	}

}


/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
