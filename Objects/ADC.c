/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  ADC.c
 *        \This file contain all required functions to operate and initialize ADC Module of Tiva C
 *
 *      \initialization function and others
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "mcu_hw.h"
#include "ADC.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define SS1_BitOffset			4
#define SS2_BitOffset			8
#define SS3_BitOffset			12

#define ASENn_ByteOffset		0
#define SSn_ByteOffset			0

#define ASEN0_BitOffset			0
#define ASEN1_BitOffset			1
#define ASEN2_BitOffset			2
#define ASEN3_BitOffset			3

#define SS0_Initiate_BitOffset			0
#define SS1_Initiate_BitOffset			1
#define SS2_Initiate_BitOffset			2
#define SS3_Initiate_BitOffset			3




/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* pointer to be initialized by user in set up buffer function */
static uint32 * ptrGroup_0_Buffer;
static uint32 * ptrGroup_1_Buffer;
static uint32 * ptrGroup_2_Buffer;
static uint32 * ptrGroup_3_Buffer;


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void ADC_Init( const ADC_ConfigType* ConfigPtr)        
* \Description     : Initialize ADC Module                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr   Pointer to the configuration array from user                    
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void ADC_Init( const ADC_ConfigType* ConfigPtr)
{
	ADC_GroupType *		loc_ADCCHgroup;
	ADCGrpPriorityType		loc_ADCGrpPriority;
	ADCGrpTriggSrcType		loc_ADCTriggerSrc;
	ADCGrpConvModeType		loc_ADCGrpConvMode;
	ADC_PtrToFunType		loc_ADC_Notification;
	
	
	for(uint8 i ; i< CHANNEL_GROUP_SIZE ; i++)
	{
		/* Fill all configuration parameters */
		
		loc_ADCCHgroup 			= ConfigPtr[i].adcCHgroup;
		loc_ADCGrpPriority 		= ConfigPtr[i].adcGrpPriority;
		loc_ADCTriggerSrc 		= ConfigPtr[i].adcTriggerSrc;
		loc_ADCGrpConvMode 		= ConfigPtr[i].adcGrpConvMode;
		loc_ADC_Notification 	= ConfigPtr[i].adc_Notification;
		
		/* TODO: Assign Channel Group and channels*/
		
			switch ((uint32)loc_ADCCHgroup)
			{
				
				case (uint32)ChGroup.Group0 :		/* Adreess of the array Group[0] which is member of CHGroup struct casted to uint32 */
					
					/* SS0 Channel Adjust */
					for(uint8 j = 0 ; j<SS0NO_CH ; j++ )
					{
						
						 ADCSSMUX0(ADC0_BASE) |= (loc_ADCCHgroup[j] << (4*j));
					}
					/* Assign Priority for SS0 */
					ADCSSPRI(ADC0_BASE) |= loc_ADCGrpPriority;
					
					/* Assign Evevt Source for SS0, Also Group Conversion Mode Assigned here */
					ADCEMUX(ADC0_BASE) |= loc_ADCTriggerSrc;
				
				break;
				
				
				case (uint32)ChGroup.Group1:		/* Adreess of the array Group[1] which is member of CHGroup struct casted to uint32 */
				
					/* SS1 Channel Adjust */
					for(uint8 j = 0 ; j<SS1NO_CH ; j++ )
					{
						
						ADCSSMUX1(ADC0_BASE) |= ( loc_ADCCHgroup[j] << (4*j) );
					}
					/* Assign Priorityfor SS1 */
					ADCSSPRI(ADC0_BASE) |= (loc_ADCGrpPriority << SS1_BitOffset);
					
					/* Assign Event Source for SS1, Also Group Conversion Mode Assigned here */
					ADCEMUX(ADC0_BASE) |= loc_ADCTriggerSrc << SS1_BitOffset;
					
				break;
				
				case (uint32)ChGroup.Group2:		/* Adreess of the array Group[2] which is member of CHGroup struct casted to uint32 */
				
					/* SS2 Channel Adjust */
					for(uint8 j = 0 ; j<SS1NO_CH ; j++ )
					{
						ADCSSMUX1(ADC0_BASE)|= (loc_ADCCHgroup[j] << (4*j));
					}
					/* Assign Priority for SS2 */
					ADCSSPRI(ADC0_BASE) |= (loc_ADCGrpPriority << SS2_BitOffset);
					
					/* Assign Event Source for SS1, Also Group Conversion Mode Assigned here */
					ADCEMUX(ADC0_BASE) |= (loc_ADCTriggerSrc << SS2_BitOffset);
					
				break;
				
				case (uint32)ChGroup.Group3:		/* Adreess of the array Group[3] which is member of CHGroup struct casted to uint32 */
					
					/* SS3 Channel Adjust */
					/* Assert SS3 Directly as it is only one channel */
					ADCSSMUX3(ADC0_BASE) = loc_ADCCHgroup[0];
					
					/* Assign Priority for SS3 */
					ADCSSPRI(ADC0_BASE) |= (loc_ADCGrpPriority << SS3_BitOffset);
					
					/* Assign Event Source for SS1, Also Group Conversion Mode Assigned here */
					ADCEMUX(ADC0_BASE) |= (loc_ADCTriggerSrc << SS3_BitOffset);
					
				break;
				
			}/* switch channel group END */
			
		
		/* Assign the Group Conversion Mode */
		
	}/* For of Initialization END */
	
}

/******************************************************************************
* \Syntax          : Std_ReturnType ADC_SetupResultBuffer( Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr)      
* \Description     : Setup each Result to each desired group sent from user                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : DataBufferPtr   Pointer the user buffer array
*			  (in) : Group			 The Group user want to be assigned to this buffer                   
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
Std_ReturnType ADC_SetupResultBuffer( ADC_GroupType Group, Adc_ValueGroupType* DataBufferPtr)
{
	switch (Group)
		{
				/* Assign sent buffer to the desired group buffer */
				
			case (uint32)ChGroup.Group0 :
				
				DataBufferPtr = ptrGroup_0_Buffer;		
			
			break;
			
			case (uint32)ChGroup.Group1:
			
				DataBufferPtr = ptrGroup_1_Buffer;
				
			break;
			
			case (uint32)ChGroup.Group2:
			
				DataBufferPtr = ptrGroup_2_Buffer
								
			break;
			
			case (uint32)ChGroup.Group3:
			
				DataBufferPtr =	ptrGroup_3_Buffer;
				
			break;
			
		}/* switch channel group END */
	
	
}/* SetupResultBuffer function END */


/******************************************************************************
* \Syntax          : void Adc_StartGroupConversion( Adc_GroupTypeGroup )         
* \Description     : Start conversion of the desired group sent by user                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : group   Adc_GroupType to identify which group user want to start                   
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/

void Adc_StartGroupConversion( ADC_GroupType Group )
{
	/* Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS register. and SSn in  */
	
	switch (Group)
		{
				/* Enable the desired Group sent by user */
				
			case (uint32)ChGroup.Group0 :
				
				/* Acssessing by bit banding -->> AliasPer_BitWordAddr(Byte_OFFSET,Per_BaseAddr,bit_number) */
				AliasPer_BitWordAddr(ASENn_ByteOffset,(ADCACTSS(ADC0_BASE)),ASEN0_BitOffset) = ENABLE;
				/* Begin sampling on Sample Sequencer 0, if the sequencer is enabled in the ADCACTSS register. */
				AliasPer_BitWordAddr(SSn_ByteOffset,(ADCPSSI(ADC0_BASE)),SS0_Initiate_BitOffset) = ENABLE;
			
			break;
			
			case (uint32)ChGroup.Group1:
			
				/* Acssessing by bit banding -->> AliasPer_BitWordAddr(Byte_OFFSET,Per_BaseAddr,bit_number) */
				AliasPer_BitWordAddr(ASENn_ByteOffset,(ADCACTSS(ADC0_BASE)),ASEN1_BitOffset) = ENABLE;
				/* Begin sampling on Sample Sequencer 1, if the sequencer is enabled in the ADCACTSS register. */
				AliasPer_BitWordAddr(SSn_ByteOffset,(ADCPSSI(ADC0_BASE)),SS1_Initiate_BitOffset) = ENABLE;
				
			break;
			
			case (uint32)ChGroup.Group2:
				
				/* Acssessing by bit banding -->> AliasPer_BitWordAddr(Byte_OFFSET,Per_BaseAddr,bit_number) */
				AliasPer_BitWordAddr(ASENn_ByteOffset,(ADCACTSS(ADC0_BASE)),ASEN2_BitOffset) = ENABLE;
				/* Begin sampling on Sample Sequencer 2, if the sequencer is enabled in the ADCACTSS register. */
				AliasPer_BitWordAddr(SSn_ByteOffset,(ADCPSSI(ADC0_BASE)),SS2_Initiate_BitOffset) = ENABLE;
				
			break;
			
			case (uint32)ChGroup.Group3:
			
				/* Acssessing by bit banding -->> AliasPer_BitWordAddr(Byte_OFFSET,Per_BaseAddr,bit_number) */
				AliasPer_BitWordAddr(ASENn_ByteOffset,(ADCACTSS(ADC0_BASE)),ASEN3_BitOffset) = ENABLE;
				/* Begin sampling on Sample Sequencer 3, if the sequencer is enabled in the ADCACTSS register. */
				AliasPer_BitWordAddr(SSn_ByteOffset,(ADCPSSI(ADC0_BASE)),SS3_Initiate_BitOffset) = ENABLE;
				
			break;
			
		}/* switch channel group END */
	
}





/******************************************************************************
* \Syntax          : void Adc_StopGroupConversion( Adc_GroupTypeGroup )         
* \Description     : Stop conversion of the desired group sent by user                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : group   Adc_GroupType to identify which group user want to stop                    
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/

void Adc_StopGroupConversion( ADC_GroupType Group )
{
	/* Disable the sample sequencer logic by clearing the corresponding ASENn bit in the ADCACTSS register. */
	
	switch (Group)
		{
				/* DISABLE the desired Group sent by user */
				
			case (uint32)ChGroup.Group0 :
				
				/* Acssessing by bit banding -->> AliasPer_BitWordAddr(Byte_OFFSET,Per_BaseAddr,bit_number) */
				AliasPer_BitWordAddr(ASENn_ByteOffset,ADC0_BASE,ASEN0_BitOffset) = DISABLE;
				/* Stop sampling on Sample Sequencer 0 */
				AliasPer_BitWordAddr(SSn_ByteOffset,(ADCPSSI(ADC0_BASE)),SS0_Initiate_BitOffset) = DISABLE;
			
			break;
			
			case (uint32)ChGroup.Group1:
			
				/* Acssessing by bit banding -->> AliasPer_BitWordAddr(Byte_OFFSET,Per_BaseAddr,bit_number) */
				AliasPer_BitWordAddr(ASENn_ByteOffset,ADC0_BASE,ASEN1_BitOffset) = DISABLE;
				/* stop sampling on Sample Sequencer 1 */
				AliasPer_BitWordAddr(SSn_ByteOffset,(ADCPSSI(ADC0_BASE)),SS1_Initiate_BitOffset) = DISABLE;
				
			break;
			
			case (uint32)ChGroup.Group2:
				
				/* Acssessing by bit banding -->> AliasPer_BitWordAddr(Byte_OFFSET,Per_BaseAddr,bit_number) */
				AliasPer_BitWordAddr(ASENn_ByteOffset,ADC0_BASE,ASEN2_BitOffset) = DISABLE;
				/* Stop sampling on Sample Sequencer 2 */
				AliasPer_BitWordAddr(SSn_ByteOffset,(ADCPSSI(ADC0_BASE)),SS2_Initiate_BitOffset) = DISABLE;
				
			break;
			
			case (uint32)ChGroup.Group3:
			
				/* Acssessing by bit banding -->> AliasPer_BitWordAddr(Byte_OFFSET,Per_BaseAddr,bit_number) */
				AliasPer_BitWordAddr(ASENn_ByteOffset,ADC0_BASE,ASEN3_BitOffset) = DISABLE;
				/* Stop sampling on Sample Sequencer 3 */
				AliasPer_BitWordAddr(SSn_ByteOffset,(ADCPSSI(ADC0_BASE)),SS3_Initiate_BitOffset) = DISABLE;
				
			break;
			
		}/* switch channel group END */
}

/**********************************************************************************************************************************************
* \Syntax          : Std_ReturnType Adc_ReadGroup( ADC_GroupType Group, Adc_ValueGroupType* DataBufferPtr)         
* \Description     : Reads the group conversion result of the last completed conversion round of the requested group and stores
*					 the channel values starting at the DataBufferPtr address. The group channel values are stored in ascending channel
*					 number order( in contrast to the storage layout of the result buffer if streaming access is configured).                                                                                     
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : group   Adc_GroupType to identify which group user want to Read                   
* \Parameters (out): DataBufferPtr  ADC results of all channels of the selected group are stored in the data buffer addressed with the pointer.                                               
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
************************************************************************************************************************************************/
Std_ReturnType Adc_ReadGroup( ADC_GroupType Group, Adc_ValueGroupType* DataBufferPtr)
{
	
		switch (Group)
		{
				
				
			case (uint32)ChGroup.Group0 :
			
				/* Copy data of Sample Sequencer 0 array to user array limited by num of channel assigned by user */
				for(uint8 i = 0; i < SS0NO_CH ; i++)
				{
					DataBufferPtr[i] = ptrGroup_0_Buffer[i];
				}
				
				return E_OK;
			
			break;
			
			case (uint32)ChGroup.Group1:
			
				/* Copy data of Sample Sequencer 1 array to user array limited by num of channel assigned by user */
				for(uint8 i = 0; i < SS1NO_CH ; i++)
				{
					DataBufferPtr[i] = ptrGroup_1_Buffer[i];
				}
				
				return E_OK;
				
			break;
			
			case (uint32)ChGroup.Group2:
				/* Copy data of Sample Sequencer 2 array to user array limited by num of channel assigned by user */
				for(uint8 i = 0; i < SS2NO_CH ; i++)
				{
					DataBufferPtr[i] = ptrGroup_2_Buffer[i];
				}
				
				return E_OK;

			break;
			
			case (uint32)ChGroup.Group3:
				/* Copy data of Sample Sequencer 3 array to user array limited by num of channel assigned by user */
				for(uint8 i = 0; i < SS3NO_CH ; i++)
				{
					DataBufferPtr[i] = ptrGroup_3_Buffer[i];
				}
				
				return E_OK;

			break;
			
			default:
				return E_NOT_OK;
			break;
			
		}/* switch channel group END */
	
}


/**********************************************************************************************************************
 *  END OF FILE: ADC.c
 *********************************************************************************************************************/
