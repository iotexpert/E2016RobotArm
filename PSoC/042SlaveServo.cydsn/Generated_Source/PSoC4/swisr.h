/*******************************************************************************
* File Name: swisr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_swisr_H)
#define CY_ISR_swisr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void swisr_Start(void);
void swisr_StartEx(cyisraddress address);
void swisr_Stop(void);

CY_ISR_PROTO(swisr_Interrupt);

void swisr_SetVector(cyisraddress address);
cyisraddress swisr_GetVector(void);

void swisr_SetPriority(uint8 priority);
uint8 swisr_GetPriority(void);

void swisr_Enable(void);
uint8 swisr_GetState(void);
void swisr_Disable(void);

void swisr_SetPending(void);
void swisr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the swisr ISR. */
#define swisr_INTC_VECTOR            ((reg32 *) swisr__INTC_VECT)

/* Address of the swisr ISR priority. */
#define swisr_INTC_PRIOR             ((reg32 *) swisr__INTC_PRIOR_REG)

/* Priority of the swisr interrupt. */
#define swisr_INTC_PRIOR_NUMBER      swisr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable swisr interrupt. */
#define swisr_INTC_SET_EN            ((reg32 *) swisr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the swisr interrupt. */
#define swisr_INTC_CLR_EN            ((reg32 *) swisr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the swisr interrupt state to pending. */
#define swisr_INTC_SET_PD            ((reg32 *) swisr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the swisr interrupt. */
#define swisr_INTC_CLR_PD            ((reg32 *) swisr__INTC_CLR_PD_REG)



#endif /* CY_ISR_swisr_H */


/* [] END OF FILE */
