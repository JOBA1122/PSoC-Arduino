/*******************************************************************************
* File Name: PIN5.h  
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

#if !defined(CY_PINS_PIN5_H) /* Pins PIN5_H */
#define CY_PINS_PIN5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN5_Write(uint8 value) ;
void    PIN5_SetDriveMode(uint8 mode) ;
uint8   PIN5_ReadDataReg(void) ;
uint8   PIN5_Read(void) ;
uint8   PIN5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN5_DRIVE_MODE_BITS        (3)
#define PIN5_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN5_DRIVE_MODE_BITS))

#define PIN5_DM_ALG_HIZ         (0x00u)
#define PIN5_DM_DIG_HIZ         (0x01u)
#define PIN5_DM_RES_UP          (0x02u)
#define PIN5_DM_RES_DWN         (0x03u)
#define PIN5_DM_OD_LO           (0x04u)
#define PIN5_DM_OD_HI           (0x05u)
#define PIN5_DM_STRONG          (0x06u)
#define PIN5_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN5_MASK               PIN5__MASK
#define PIN5_SHIFT              PIN5__SHIFT
#define PIN5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN5_PS                     (* (reg32 *) PIN5__PS)
/* Port Configuration */
#define PIN5_PC                     (* (reg32 *) PIN5__PC)
/* Data Register */
#define PIN5_DR                     (* (reg32 *) PIN5__DR)
/* Input Buffer Disable Override */
#define PIN5_INP_DIS                (* (reg32 *) PIN5__PC2)


#if defined(PIN5__INTSTAT)  /* Interrupt Registers */

    #define PIN5_INTSTAT                (* (reg32 *) PIN5__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN5_DRIVE_MODE_SHIFT       (0x00u)
#define PIN5_DRIVE_MODE_MASK        (0x07u << PIN5_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN5_H */


/* [] END OF FILE */
