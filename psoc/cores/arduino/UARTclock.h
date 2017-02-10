/*******************************************************************************
* File Name: UARTclock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_UARTclock_H)
#define CY_CLOCK_UARTclock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void UARTclock_StartEx(uint32 alignClkDiv);
#define UARTclock_Start() \
    UARTclock_StartEx(UARTclock__PA_DIV_ID)

#else

void UARTclock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void UARTclock_Stop(void);

void UARTclock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 UARTclock_GetDividerRegister(void);
uint8  UARTclock_GetFractionalDividerRegister(void);

#define UARTclock_Enable()                         UARTclock_Start()
#define UARTclock_Disable()                        UARTclock_Stop()
#define UARTclock_SetDividerRegister(clkDivider, reset)  \
    UARTclock_SetFractionalDividerRegister((clkDivider), 0u)
#define UARTclock_SetDivider(clkDivider)           UARTclock_SetDividerRegister((clkDivider), 1u)
#define UARTclock_SetDividerValue(clkDivider)      UARTclock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define UARTclock_DIV_ID     UARTclock__DIV_ID

#define UARTclock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define UARTclock_CTRL_REG   (*(reg32 *)UARTclock__CTRL_REGISTER)
#define UARTclock_DIV_REG    (*(reg32 *)UARTclock__DIV_REGISTER)

#define UARTclock_CMD_DIV_SHIFT          (0u)
#define UARTclock_CMD_PA_DIV_SHIFT       (8u)
#define UARTclock_CMD_DISABLE_SHIFT      (30u)
#define UARTclock_CMD_ENABLE_SHIFT       (31u)

#define UARTclock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << UARTclock_CMD_DISABLE_SHIFT))
#define UARTclock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << UARTclock_CMD_ENABLE_SHIFT))

#define UARTclock_DIV_FRAC_MASK  (0x000000F8u)
#define UARTclock_DIV_FRAC_SHIFT (3u)
#define UARTclock_DIV_INT_MASK   (0xFFFFFF00u)
#define UARTclock_DIV_INT_SHIFT  (8u)

#else 

#define UARTclock_DIV_REG        (*(reg32 *)UARTclock__REGISTER)
#define UARTclock_ENABLE_REG     UARTclock_DIV_REG
#define UARTclock_DIV_FRAC_MASK  UARTclock__FRAC_MASK
#define UARTclock_DIV_FRAC_SHIFT (16u)
#define UARTclock_DIV_INT_MASK   UARTclock__DIVIDER_MASK
#define UARTclock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_UARTclock_H) */

/* [] END OF FILE */
