/**
 *******************************************************************************
 * @file    core_clint.c
 * @author  Milandr Application Team
 * @version V0.1
 * @date    11/12/2023
 * @brief   This file contains all RISC-V machine timer firmware functions.
 *******************************************************************************
 * <br><br>
 *
 * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
 * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT {YYYY} Milandr</center></h2>
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "core_clint.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(CLINT_PRESENT)

/** @addtogroup CORE_CLINT Core CLINT
 * @{
 */

/** @defgroup CLINT_Exported_Functions CLINT Exported Functions
 * @{
 */

#if (HARTS_AMOUNT == 1)

/**
 * @brief  Set the machine interrupt request.
 * @param  IRQStatus: @ref ITStatus - set or reset interrupt request.
 * @return None.
 */
void CLINT_SetSoftwareMachineIRQ(ITStatus IRQStatus)
{
    /* Check the parameters. */
    assert_param(IS_BIT_STATUS(IRQStatus));

    *(volatile uint32_t*)(MSIP_BASE(0)) = (uint32_t)IRQStatus;
}

/**
 * @brief  Set the machine interrupt request.
 * @param  None.
 * @return @ref IRQStatus: current interrupt request status.
 */
ITStatus CLINT_GetSoftwareMachineIRQ(void)
{
    return (ITStatus)(*(volatile uint32_t*)(MSIP_BASE(0)));
}

/**
 * @brief  Set a machine timer compare value.
 * @param  MTIMECMPValue: A new machine timer compare value.
 * @return None.
 */
void CLINT_MTIMER_SetCompareTime(uint64_t MTIMECMPValue)
{
#if (__riscv_xlen == 64)
    /* Single bus access. */
    volatile uint32_t* MTimeCmp = (volatile uint64_t*)(MTIMECMP_BASE(0));
    *MTimeCmp                   = MTIMECMPValue;
#else
    /* Set a new compare value with 2 writes of 32-bit words. */
    volatile uint32_t* MTimeCmpLow  = (volatile uint32_t*)(MTIMECMP_BASE(0));
    volatile uint32_t* MTimeCmpHigh = (volatile uint32_t*)(MTIMECMP_BASE(0) + 4);
    /* First set an unachievable value for mtimecmp_hi to prevent spurious interrupts. */
    *MTimeCmpHigh = 0xFFFFFFFF;
    /* Set mtimecmp_lo. */
    *MTimeCmpLow = (uint32_t)(MTIMECMPValue & 0x0FFFFFFFFUL);
    /* Set correct mtimecmp_hi. */
    *MTimeCmpHigh = (uint32_t)(MTIMECMPValue >> 32);
#endif
}

/**
 * @brief  Get machine timer compare value.
 * @param  None.
 * @return Machine timer compare value.
 */
uint64_t CLINT_MTIMER_GetCompareTime(void)
{
    return *(volatile uint64_t*)(MTIMECMP_BASE(0));
}

#else

/**
 * @brief  Set the machine interrupt request.
 * @param  IRQStatus: @ref ITStatus - set or reset interrupt request.
 * @param  HartID: Hard ID number.
 * @return None.
 */
void CLINT_SetSoftwareMachineIRQ(ITStatus IRQStatus, uint32_t HartID)
{
    /* Check the parameters. */
    assert_param(IS_BIT_STATUS(IRQStatus));
    assert_param(IS_HART_ID(HartID));

    *(volatile uint32_t*)(MSIP_BASE(HartID)) = (uint32_t)IRQStatus;
}

/**
 * @brief  Set the machine interrupt request.
 * @param  HartID: Hard ID number.
 * @return @ref IRQStatus: Current interrupt request status.
 */
ITStatus CLINT_GetSoftwareMachineIRQ(uint32_t HartID)
{
    /* Check the parameters. */
    assert_param(IS_HART_ID(HartID));

    return (ITStatus)(*(volatile uint32_t*)(MSIP_BASE(HartID)));
}

/**
 * @brief  Set a machine timer compare value.
 * @param  MTIMECMPValue: A new machine timer compare value.
 * @param  HartID: Hard ID number.
 * @return None.
 */
void CLINT_MTIMER_SetCompareTime(uint64_t MTIMECMPValue, uint32_t HartID)
{
    /* Check the parameters. */
    assert_param(IS_HART_ID(HartID));

#if (__riscv_xlen == 64)
    /* Single bus access. */
    volatile uint32_t* MTimeCmp = (volatile uint64_t*)(MTIMECMP_BASE(HartID));
    *MTimeCmp                   = MTIMECMPValue;
#else
    /* Set a new compare value with 2 writes of 32-bit words. */
    volatile uint32_t* MTimeCmpLow  = (volatile uint32_t*)(MTIMECMP_BASE(HartID));
    volatile uint32_t* MTimeCmpHigh = (volatile uint32_t*)(MTIMECMP_BASE(HartID) + 4);
    /* First set an unachievable value for mtimecmp_hi to prevent spurious interrupts. */
    *MTimeCmpHigh = 0xFFFFFFFF;
    /* Set mtimecmp_lo. */
    *MTimeCmpLow = (uint32_t)(MTIMECMPValue & 0x0FFFFFFFFUL);
    /* Set correct mtimecmp_hi. */
    *MTimeCmpHigh = (uint32_t)(MTIMECMPValue >> 32);
#endif
}

/**
 * @brief  Get machine timer compare value.
 * @param  HartID: Hard ID number.
 * @return Machine timer compare value.
 */
uint64_t CLINT_MTIMER_GetCompareTime(uint32_t HartID)
{
    /* Check the parameters. */
    assert_param(IS_HART_ID(HartID));

    return *(volatile uint64_t*)(MTIMECMP_BASE(HartID));
}

#endif

/**
 * @brief  Set a machine timer value.
 * @param  MTIMEValue: A new machine timer value.
 * @return None.
 */
void CLINT_MTIMER_SetTime(uint64_t MTIMEValue)
{
#if (__riscv_xlen == 64)
    /* Single bus access. */
    volatile uint64_t* MTime = (volatile uint64_t*)(MTIME_BASE);
    *MTime                   = MTIMEValue;
#else
    /* Set a new value with 2 writes of 32-bit words. */
    volatile uint32_t* MTimeLow  = (volatile uint32_t*)(MTIME_BASE);
    volatile uint32_t* MTimeHigh = (volatile uint32_t*)(MTIME_BASE + 4);

    *MTimeLow = 0x00000000;
    /* Set mtime_hi. */
    *MTimeHigh = (uint32_t)(MTIMEValue >> 32);
    /* Set mtime_lo. */
    *MTimeLow = (uint32_t)(MTIMEValue & 0x0FFFFFFFFUL);
#endif
}

/**
 * @brief  Get a machine timer value.
 * @param  None.
 * @return A machine timer value.
 */
uint64_t CLINT_MTIMER_GetTime(void)
{
#if (__riscv_xlen == 64)
    /* Directly read 64-bit value. */
    volatile uint64_t* MTime = (volatile uint64_t*)(MTIME_BASE);
    return *MTime;
#else
    volatile uint32_t* MTimeLow  = (volatile uint32_t*)(MTIME_BASE);
    volatile uint32_t* MTimeHigh = (volatile uint32_t*)(MTIME_BASE + 4);
    uint32_t           MTimeHighValue;
    uint32_t           MTimeLowValue;

    /* Safe read of a timer value. */
    do {
        MTimeHighValue = *MTimeHigh;
        MTimeLowValue  = *MTimeLow;
    } while (MTimeHighValue != *MTimeHigh);

    return (uint64_t)((((uint64_t)MTimeHighValue) << 32) | MTimeLowValue);
#endif
}

/** @} */ /* End of the group CLINT_Exported_Functions */

/** @} */ /* End of the group CORE_CLINT */

#endif

/** @} */ /* End of the group CORE_SUPPORT */

/*********************** (C) COPYRIGHT {YYYY} Milandr ****************************
 *
 * END OF FILE core_clint.c */
