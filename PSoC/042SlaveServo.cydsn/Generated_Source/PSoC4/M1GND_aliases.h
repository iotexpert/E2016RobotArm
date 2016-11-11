/*******************************************************************************
* File Name: M1GND.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_M1GND_ALIASES_H) /* Pins M1GND_ALIASES_H */
#define CY_PINS_M1GND_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define M1GND_0			(M1GND__0__PC)
#define M1GND_0_PS		(M1GND__0__PS)
#define M1GND_0_PC		(M1GND__0__PC)
#define M1GND_0_DR		(M1GND__0__DR)
#define M1GND_0_SHIFT	(M1GND__0__SHIFT)
#define M1GND_0_INTR	((uint16)((uint16)0x0003u << (M1GND__0__SHIFT*2u)))

#define M1GND_INTR_ALL	 ((uint16)(M1GND_0_INTR))


#endif /* End Pins M1GND_ALIASES_H */


/* [] END OF FILE */