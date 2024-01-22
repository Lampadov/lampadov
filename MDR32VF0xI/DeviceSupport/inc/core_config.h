/**
 ******************************************************************************
 * @file    core_config.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    14/12/2023
 * @brief   Core Peripheral Access Layer Configuration File for MDR32VF0xI.
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
#ifndef CORE_CONFIG_H
#define CORE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_types.h"
#include "system_MDR32VF0xI_config.h"

/** @addtogroup DEVICE_SUPPORT Device Support
 * @{
 */

/** @addtogroup MDR32VF0xI_DEVICE MDR32VF0xI
 * @{
 */

/** @addtogroup MDR32VF0xI_CORE_Configuration MDR32VF0xI Core Configuration
 * @{
 */

/** @defgroup MDR32VF0xI_CORE_Interrupts_Definitions MDR32VF0xI Core Interrupts Definitions
 * @{
 */

#if defined(USE_MDR32F02)
/**
 * @brief MDR32F02 Peripheral interrupt number definition.
 *        int_globalX, where X - enumerated number of the interrupt.
 */
typedef enum {
    DMA_IRQn         = 0,  /*!< DMA_ERR, DMA_DONE Interrupt */
    UART1_IRQn       = 1,  /*!< UART1 Interrupt */
    UART2_IRQn       = 2,  /*!< UART2 Interrupt */
    SSP1_IRQn        = 3,  /*!< SSP1 Interrupt */
    POWER_IRQn       = 4,  /*!< POWER Detector Interrupt */
    WWDG_IRQn        = 5,  /*!< WWDG Interrupt */
    TIMER1_IRQn      = 6,  /*!< TIMER1 STATUS, IE Interrupt */
    TIMER2_IRQn      = 7,  /*!< TIMER2 STATUS, IE Interrupt */
    ADC_IRQn         = 8,  /*!< ADC EOCIF_1, AWOIF_1, EOCIF_2, AWOIF_2 Interrupt */
    I2C_IRQn         = 9,  /*!< I2C Interrupt */
    BKP_IRQn         = 10, /*!< BKP and RTC Interrupt */
    EXT_INT1_IRQn    = 11, /*!< EXT_INT1 Interrupt */
    EXT_INT2_IRQn    = 12, /*!< EXT_INT2 Interrupt */
    EXT_INT3_IRQn    = 13, /*!< EXT_INT3 Interrupt */
    ADCUI_F03_IRQn   = 14, /*!< ADCUI Channels 0, 3 Interrupt */
    ADCUI_F1_IRQn    = 15, /*!< ADCUI Channel 1 Interrupt */
    ADCUI_F2_IRQn    = 16, /*!< ADCUI Channel 2 Interrupt */
    L_BLOCK_IRQn     = 17, /*!< L_BLOCK Interrupt */
    SENSORS_IRQn     = 19, /*!< SENSORS Interrupt */
    CLK_MEASURE_IRQn = 20, /*!< CLK_MEASURE Interrupt */
    RANDOM_IRQn      = 21, /*!< RANDOM Interrupt */
    USART_IRQn       = 22, /*!< UART ISO7816 (USART) Interface Interrupt */
    UART3_IRQn       = 23, /*!< UART3 Interrupt */
    SSP2_IRQn        = 24, /*!< SSP2 Interrupt */
    SSP3_IRQn        = 25, /*!< SSP3 Interrupt */
    TIMER3_IRQn      = 26, /*!< TIMER3 STATUS, IE Interrupt */
    TIMER4_IRQn      = 27, /*!< TIMER4 STATUS, IE Interrupt */
    UART4_IRQn       = 28, /*!< UART4 Interrupt */
    OTP_IRQn         = 29  /*!< OTP CRC Corrupt Interrupt */
} IRQn_TypeDef;

#define IS_IRQ(IRQ) (((IRQ) == DMA_IRQn) ||         \
                     ((IRQ) == UART1_IRQn) ||       \
                     ((IRQ) == UART2_IRQn) ||       \
                     ((IRQ) == SSP1_IRQn) ||        \
                     ((IRQ) == POWER_IRQn) ||       \
                     ((IRQ) == WWDG_IRQn) ||        \
                     ((IRQ) == TIMER1_IRQn) ||      \
                     ((IRQ) == TIMER2_IRQn) ||      \
                     ((IRQ) == ADC_IRQn) ||         \
                     ((IRQ) == I2C_IRQn) ||         \
                     ((IRQ) == BKP_IRQn) ||         \
                     ((IRQ) == EXT_INT1_IRQn) ||    \
                     ((IRQ) == EXT_INT2_IRQn) ||    \
                     ((IRQ) == EXT_INT3_IRQn) ||    \
                     ((IRQ) == ADCUI_F03_IRQn) ||   \
                     ((IRQ) == ADCUI_F1_IRQn) ||    \
                     ((IRQ) == ADCUI_F2_IRQn) ||    \
                     ((IRQ) == L_BLOCK_IRQn) ||     \
                     ((IRQ) == SENSORS_IRQn) ||     \
                     ((IRQ) == CLK_MEASURE_IRQn) || \
                     ((IRQ) == RANDOM_IRQn) ||      \
                     ((IRQ) == USART_IRQn) ||       \
                     ((IRQ) == UART3_IRQn) ||       \
                     ((IRQ) == SSP2_IRQn) ||        \
                     ((IRQ) == SSP3_IRQn) ||        \
                     ((IRQ) == TIMER3_IRQn) ||      \
                     ((IRQ) == TIMER4_IRQn) ||      \
                     ((IRQ) == UART4_IRQn) ||       \
                     ((IRQ) == OTP_IRQn))

#elif defined(USE_MDR1206)
/**
 * @brief MDR1206 Peripheral interrupt number definition.
 *        int_globalX, where X - enumerated number of the interrupt.
 */
typedef enum {
    USIP_IRQn      = 0,  /*!< User Software Interrupt */
    MSIP_IRQn      = 3,  /*!< Machine Software Interrupt */
    UTIP_IRQn      = 4,  /*!< User Timer Interrupt */
    MTIP_IRQn      = 7,  /*!< Machine Timer Interrupt */
    CSIP_IRQn      = 12, /*!< CLIC Software Interrupt */
    DMA_IRQn       = 16, /*!< DMA_ERR, DMA_DONE Interrupt */
    UART1_IRQn     = 17, /*!< UART1 Interrupt */
    UART2_IRQn     = 18, /*!< UART2 Interrupt */
    SSP1_IRQn      = 19, /*!< SSP1 Interrupt */
    POWER_IRQn     = 20, /*!< POWER Detector Interrupt */
    WWDG_IRQn      = 21, /*!< WWDG Interrupt */
    TIMER1_IRQn    = 22, /*!< TIMER1 STATUS, IE Interrupt */
    TIMER2_IRQn    = 23, /*!< TIMER2 STATUS, IE Interrupt */
    ADC_IRQn       = 24, /*!< ADC EOCIF_1, AWOIF_1, EOCIF_2, AWOIF_2 Interrupt */
    I2C_IRQn       = 25, /*!< I2C Interrupt */
    BKP_IRQn       = 26, /*!< BKP and RTC Interrupt */
    EXT_INT1_IRQn  = 27, /*!< EXT_INT1 Interrupt */
    EXT_INT2_IRQn  = 28, /*!< EXT_INT2 Interrupt */
    EXT_INT3_IRQn  = 29, /*!< EXT_INT3 Interrupt */
    ADCUI_F03_IRQn = 30, /*!< ADCUI Channels 0, 3 Interrupt */
    ADCUI_F1_IRQn  = 31, /*!< ADCUI Channel 1 Interrupt */
    ADCUI_F2_IRQn  = 32, /*!< ADCUI Channel 2 Interrupt */
    RANDOM_IRQn    = 37, /*!< RANDOM Interrupt */
    USART_IRQn     = 38, /*!< UART ISO7816 (USART) Interrupt */
    UART3_IRQn     = 39, /*!< UART3 Interrupt */
    SSP2_IRQn      = 40, /*!< SSP2 Interrupt */
    SSP3_IRQn      = 41, /*!< SSP3 Interrupt */
    TIMER3_IRQn    = 42, /*!< TIMER3 STATUS, IE Interrupt */
    TIMER4_IRQn    = 43, /*!< TIMER4 STATUS, IE Interrupt */
    UART4_IRQn     = 44, /*!< UART4 Interrupt */
} IRQn_TypeDef;

#define IS_IRQ(IRQ) (((IRQ) == USIP_IRQn) ||      \
                     ((IRQ) == MSIP_IRQn) ||      \
                     ((IRQ) == UTIP_IRQn) ||      \
                     ((IRQ) == MTIP_IRQn) ||      \
                     ((IRQ) == CSIP_IRQn) ||      \
                     ((IRQ) == DMA_IRQn) ||       \
                     ((IRQ) == UART1_IRQn) ||     \
                     ((IRQ) == UART2_IRQn) ||     \
                     ((IRQ) == SSP1_IRQn) ||      \
                     ((IRQ) == POWER_IRQn) ||     \
                     ((IRQ) == WWDG_IRQn) ||      \
                     ((IRQ) == TIMER1_IRQn) ||    \
                     ((IRQ) == TIMER2_IRQn) ||    \
                     ((IRQ) == ADC_IRQn) ||       \
                     ((IRQ) == I2C_IRQn) ||       \
                     ((IRQ) == BKP_IRQn) ||       \
                     ((IRQ) == EXT_INT1_IRQn) ||  \
                     ((IRQ) == EXT_INT2_IRQn) ||  \
                     ((IRQ) == EXT_INT3_IRQn) ||  \
                     ((IRQ) == ADCUI_F03_IRQn) || \
                     ((IRQ) == ADCUI_F1_IRQn) ||  \
                     ((IRQ) == ADCUI_F2_IRQn) ||  \
                     ((IRQ) == RANDOM_IRQn) ||    \
                     ((IRQ) == USART_IRQn) ||     \
                     ((IRQ) == UART3_IRQn) ||     \
                     ((IRQ) == SSP2_IRQn) ||      \
                     ((IRQ) == SSP3_IRQn) ||      \
                     ((IRQ) == TIMER3_IRQn) ||    \
                     ((IRQ) == TIMER4_IRQn) ||    \
                     ((IRQ) == UART4_IRQn))

#endif

/** @} */ /* End of group MDR32VF0xI_Interrupts_Definitions */

/** @addtogroup CMSIS_CONFIGURATION Configuration of CMSIS
 * @{
 */
/* Configuration of the Processor and Core Peripherals */
#define HARTS_AMOUNT         1U
#define FPU_PRESENT          0U /*!< FPU present or not. */

#define CORE_PRIVILEGE_LEVEL (CORE_PRIVILEGE_MODE_MACHINE | \
                              CORE_PRIVILEGE_MODE_USER) /*!< Core privilege levels. */

#define CLINT_PRESENT         1U /*!< CLINT present or not. */
#define CLINT_BASE            0x02000000
#define MSIP_BASE(hartid)     (CLINT_BASE + (hartid * 4))
#define MTIMECMP_BASE(hartid) (CLINT_BASE + 0x4000 + (hartid * 4 * 2))
#define MTIME_BASE            (CLINT_BASE + 0xBFF8)

#if defined(USE_MDR32F02)
#define PLIC_PRESENT         1U                            /*!< PLIC present or not. */
#define PLIC_NUM_INTERRUPTS  32U                           /*!< PLIC number of interrupts. */
#define PLIC_PRIVILEGE_LEVEL (CORE_PRIVILEGE_MODE_MACHINE) /*!< PLIC number privilege modes. */
#define PLIC_BASE            0x0C000000UL                  /*!< PLIC base address. */
#endif

#if defined(USE_MDR1206)
#define CLIC_PRESENT         1U           /*!< CLIC present or not. */
#define CLIC_NUM_INTERRUPTS  48U          /*!< CLIC number of interrupts. */
#define CLIC_INTxCTL_BITS    4U           /*!< CLIC number of bits implemented in INTxCTL register. */
#define CLIC_xTVEC_ALIGN     6U           /*!< CLIC trap vector base address alignment in xTVEC. */
#define CLIC_PRIVILEGE_MODES 2U           /*!< CLIC number privilege modes: 1=M, 2=M/U, 3=M/S/U. */
#define CLIC_BASE            0x0D000000UL /*!< CLIC base address. */
#endif

#if defined(USE_MDR1206)
#define CORE_EXTENSION_XGOST 1U /*!< xGost Extension present or not. */
#endif

/** @} */ /* End of group CMSIS_CONFIGURATION */

/** @addtogroup MDR32VF0xI_CORE_Assert_Parameters MDR32VF0xI Core Assert Parameters
 * @{
 */

#ifndef USE_ASSERT_INFO
#define assert_param(expr) ((void)0U)
#warning "USE_ASSERT_INFO not defined! Using default assert_param(expr)."
#endif

/** @} */ /* End of group MDR32VF0xI_CORE_Assert_Parameters */

#if defined(USE_MDR32F02) || defined(USE_MDR1206)
#include "core_bm310s.h"
#endif

/** @} */ /* End of the group MDR32VF0xI_CORE_Configuration */

/** @} */ /* End of the group MDR32VF0xI_DEVICE */

/** @} */ /* End of the group DEVICE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* CORE_CONFIG_H */

/*********************** (C) COPYRIGHT {YYYY} Milandr ****************************
 *
 * END OF FILE core_config.h */
