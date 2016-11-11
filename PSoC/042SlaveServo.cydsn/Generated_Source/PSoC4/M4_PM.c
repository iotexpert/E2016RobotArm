/*******************************************************************************
* File Name: M4.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "M4.h"

static M4_BACKUP_STRUCT  M4_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: M4_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet M4_SUT.c usage_M4_Sleep_Wakeup
*******************************************************************************/
void M4_Sleep(void)
{
    #if defined(M4__PC)
        M4_backup.pcState = M4_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            M4_backup.usbState = M4_CR1_REG;
            M4_USB_POWER_REG |= M4_USBIO_ENTER_SLEEP;
            M4_CR1_REG &= M4_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(M4__SIO)
        M4_backup.sioState = M4_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        M4_SIO_REG &= (uint32)(~M4_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: M4_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to M4_Sleep() for an example usage.
*******************************************************************************/
void M4_Wakeup(void)
{
    #if defined(M4__PC)
        M4_PC = M4_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            M4_USB_POWER_REG &= M4_USBIO_EXIT_SLEEP_PH1;
            M4_CR1_REG = M4_backup.usbState;
            M4_USB_POWER_REG &= M4_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(M4__SIO)
        M4_SIO_REG = M4_backup.sioState;
    #endif
}


/* [] END OF FILE */