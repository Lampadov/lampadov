/**
 ******************************************************************************
 * @file    core_clint.h
 * @author  Milandr Application Team
 * @version V0.1
 * @date    08/12/2023
 * @brief   This file contains all the functions prototypes for RISC-V CLINT interruptor.
 ******************************************************************************
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
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CORE_CLINT
#define CORE_CLINT

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "core_types.h"
#include "core_config.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined (CLINT_PRESENT) && (CLINT_PRESENT == 1U)

/** @addtogroup CORE_CLINT Core CLINT
 * @{
 */

/** @addtogroup CORE_CLIC_Exported_Defines CLIC Exported Defines
 * @{
 */

/** @} */ /* End of group CORE_CLIC_Exported_Defines */

/** @defgroup CLINT_Exported_Functions CLINT Exported Functions
 * @{
 */

#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)

void     CLINT_SetSoftwareMachineIRQ(ITStatus IRQStatus);
ITStatus CLINT_GetSoftwareMachineIRQ(void);

void     CLINT_MTIMER_SetCompareTime(uint64_t MTIMECMPValue);
uint64_t CLINT_MTIMER_GetCompareTime(void);

#else

void     CLINT_SetSoftwareMachineIRQ(ITStatus IRQStatus, uint32_t HartID);
ITStatus CLINT_GetSoftwareMachineIRQ(uint32_t HartID);

void     CLINT_MTIMER_SetCompareTime(uint64_t MTIMECMPValue, uint32_t HartID);
uint64_t CLINT_MTIMER_GetCompareTime(uint32_t HartID);

#endif

void     CLINT_MTIMER_SetTime(uint64_t MTIMEValue);
uint64_t CLINT_MTIMER_GetTime(void);

/** @} */ /* End of the group CLINT_Exported_Functions */

/** @} */ /* End of the group CORE_CLINT */

#endif

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_CLINT */

/*********************** (C) COPYRIGHT {YYYY} Milandr ****************************
 *
 * END OF FILE core_clint.h */
