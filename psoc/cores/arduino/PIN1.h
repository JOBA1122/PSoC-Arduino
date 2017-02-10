/*******************************************************************************
* File Name: PIN1.h  
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

#if !defined(CY_PINS_PIN1_H) /* Pins PIN1_H */
#define CY_PINS_PIN1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN1_Write(uint8 value) ;
void    PIN1_SetDriveMode(uint8 mode) ;
uint8   PIN1_ReadDataReg(void) ;
uint8   PIN1_Read(void) ;
uint8   PIN1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN1_DRIVE_MODE_BITS        (3)
#define PIN1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN1_DRIVE_MODE_BITS))

#define PIN1_DM_ALG_HIZ         (0x00u)
#define PIN1_DM_DIG_HIZ         (0x01u)
#define PIN1_DM_RES_UP          (0x02u)
#define PIN1_DM_RES_DWN         (0x03u)
#define PIN1_DM_OD_LO           (0x04u)
#define PIN1_DM_OD_HI           (0x05u)
#define PIN1_DM_STRONG          (0x06u)
#define PIN1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN1_MASK               PIN1__MASK
#define PIN1_SHIFT              PIN1__SHIFT
#define PIN1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN1_PS                     (* (reg32 *) PIN1__PS)
/* Port Configuration */
#define PIN1_PC                     (* (reg32 *) PIN1__PC)
/* Data Register */
#define PIN1_DR                     (* (reg32 *) PIN1__DR)
/* Input Buffer Disable Override */
#define PIN1_INP_DIS                (* (reg32 *) PIN1__PC2)


#if defined(PIN1__INTSTAT)  /* Interrupt Registers */

    #define PIN1_INTSTAT                (* (reg32 *) PIN1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN1_DRIVE_MODE_SHIFT       (0x00u)
#define PIN1_DRIVE_MODE_MASK        (0x07u << PIN1_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN1_H */


/* [] END OF FILE */
