/*******************************************************************************
* File Name: M3.h  
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

#if !defined(CY_PINS_M3_ALIASES_H) /* Pins M3_ALIASES_H */
#define CY_PINS_M3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define M3_0			(M3__0__PC)
#define M3_0_PS		(M3__0__PS)
#define M3_0_PC		(M3__0__PC)
#define M3_0_DR		(M3__0__DR)
#define M3_0_SHIFT	(M3__0__SHIFT)
#define M3_0_INTR	((uint16)((uint16)0x0003u << (M3__0__SHIFT*2u)))

#define M3_INTR_ALL	 ((uint16)(M3_0_INTR))


#endif /* End Pins M3_ALIASES_H */


/* [] END OF FILE */
