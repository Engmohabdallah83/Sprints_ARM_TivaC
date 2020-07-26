/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <ADC_cfg.H>
 *       Module:  Analog to Digital Converter
 *
 *  Description:  <This file is to take configuration from user required for operating the peripheral>     
 *  
 *********************************************************************************************************************/
#ifndef <ADC_cfg_H>
#define <ADC_cfg_H>

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define CHANNEL_GROUP_SIZE	2	/* Note you have Max of 4 channel group Maximim */
#define DataBuffer_Size		100	/* Data Buffer Size length */
				
				/* #Channel */
#define SS0NO_CH		8		/* Please enter Number of Channel needed in channel group of Sample Sequencer0	 Note: 8 Max */
#define SS1NO_CH		4       /* Please enter Number of Channel needed in channel group of Sample Sequencer1	 Note: 4 Max */
#define SS2NO_CH		4       /* Please enter Number of Channel needed in channel group of Sample Sequencer2	 Note: 4 Max */


/* Use this Macros to fill configuration Channel group Array */
#define		AIN0           0x1		
#define		AIN1           0x2
#define		AIN2           0x3
#define		AIN3           0x4 
#define		AIN4           0x5 
#define		AIN5           0x6 
#define		AIN6           0x7 
#define		AIN7           0x8 
#define		AIN8           0x9 
#define		AIN9           0xA
#define		AIN10          0xB 
#define		AIN11          0xC 
#define		AIN12          0xD 

/* This field selects the trigger source for Sample Sequencer .
	The valid configurations for this field are: */
#define		ADC_SW_SRC				0x1
#define		ADC_AC0_SRC				0x2
#define		ADC_AC1_SRC				0x3
#define		ADC_GPIO_SRC			0x4
#define		ADC_TIMER_SRC			0x5
#define		ADC_PWM0_SRC			0x6
#define		ADC_PWM1_SRC			0x7
#define		ADC_PWM2_SRC			0x8
#define		ADC_PWM3_SRC			0x9
#define		ADC_CW_SRC				0xF

/* This field contains a binary-encoded value that specifies the priority
   encoding of Sample Sequencer */
#define FIRST_PRIORITY		0x0
#define SECOND_PRIORITY     0x1							
#define THIRD_PRIORITY     	0x2							
#define FOURTH_PRIORITY     0x3	

/* ADC Group Conversion Mode Select OneShot or Continous */								
#define ADC_MODE_ONESHOT		0x0
#define ADC_MODE_CONTINUOUS		0xF

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* ADC_cfg.H */

/**********************************************************************************************************************
 *  END OF FILE: ADC_cfg.h
 *********************************************************************************************************************/
