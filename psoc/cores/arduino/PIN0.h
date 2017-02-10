/*******************************************************************************
* File Name: PIN0.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PIN0_H) /* Pins PIN0_H */
#define CY_PINS_PIN0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN0_Write(uint8 value) ;
void    PIN0_SetDriveMode(uint8 mode) ;
uint8   PIN0_ReadDataReg(void) ;
uint8   PIN0_Read(void) ;
uint8   PIN0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN0_DRIVE_MODE_BITS        (3)
#define PIN0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN0_DRIVE_MODE_BITS))

#define PIN0_DM_ALG_HIZ         (0x00u)
#define PIN0_DM_DIG_HIZ         (0x01u)
#define PIN0_DM_RES_UP          (0x02u)
#define PIN0_DM_RES_DWN         (0x03u)
#define PIN0_DM_OD_LO           (0x04u)
#define PIN0_DM_OD_HI           (0x05u)
#define PIN0_DM_STRONG          (0x06u)
#define PIN0_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN0_MASK               PIN0__MASK
#define PIN0_SHIFT              PIN0__SHIFT
#define PIN0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN0_PS                     (* (reg32 *) PIN0__PS)
/* Port Configuration */
#define PIN0_PC                     (* (reg32 *) PIN0__PC)
/* Data Register */
#define PIN0_DR                     (* (reg32 *) PIN0__DR)
/* Input Buffer Disable Override */
#define PIN0_INP_DIS                (* (reg32 *) PIN0__PC2)


#if defined(PIN0__INTSTAT)  /* Interrupt Registers */

    #define PIN0_INTSTAT                (* (reg32 *) PIN0__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN0_DRIVE_MODE_SHIFT       (0x00u)
#define PIN0_DRIVE_MODE_MASK        (0x07u << PIN0_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN0_H */


/* [] END OF FILE */
