/*******************************************************************************
* File Name: PIN6.h  
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

#if !defined(CY_PINS_PIN6_H) /* Pins PIN6_H */
#define CY_PINS_PIN6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN6_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN6_Write(uint8 value) ;
void    PIN6_SetDriveMode(uint8 mode) ;
uint8   PIN6_ReadDataReg(void) ;
uint8   PIN6_Read(void) ;
uint8   PIN6_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN6_DRIVE_MODE_BITS        (3)
#define PIN6_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN6_DRIVE_MODE_BITS))

#define PIN6_DM_ALG_HIZ         (0x00u)
#define PIN6_DM_DIG_HIZ         (0x01u)
#define PIN6_DM_RES_UP          (0x02u)
#define PIN6_DM_RES_DWN         (0x03u)
#define PIN6_DM_OD_LO           (0x04u)
#define PIN6_DM_OD_HI           (0x05u)
#define PIN6_DM_STRONG          (0x06u)
#define PIN6_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN6_MASK               PIN6__MASK
#define PIN6_SHIFT              PIN6__SHIFT
#define PIN6_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN6_PS                     (* (reg32 *) PIN6__PS)
/* Port Configuration */
#define PIN6_PC                     (* (reg32 *) PIN6__PC)
/* Data Register */
#define PIN6_DR                     (* (reg32 *) PIN6__DR)
/* Input Buffer Disable Override */
#define PIN6_INP_DIS                (* (reg32 *) PIN6__PC2)


#if defined(PIN6__INTSTAT)  /* Interrupt Registers */

    #define PIN6_INTSTAT                (* (reg32 *) PIN6__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN6_DRIVE_MODE_SHIFT       (0x00u)
#define PIN6_DRIVE_MODE_MASK        (0x07u << PIN6_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN6_H */


/* [] END OF FILE */
