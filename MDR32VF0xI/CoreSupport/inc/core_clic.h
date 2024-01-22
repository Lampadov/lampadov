/**
 ******************************************************************************
 * @file    core_clic.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    15/12/2023
 * @brief   RISC-V CLIC Access Layer Header File.
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
#ifndef CORE_CLIC
#define CORE_CLIC

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "core_types.h"
#include "core_compiler.h"
#include "core_config.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(CLIC_PRESENT) && (CLIC_PRESENT == 1U)

/** @addtogroup CORE_CLIC CLIC
 * @{
 */

/** @defgroup CORE_CLIC_Configuration CLIC Configuration
 * @{
 */

#ifndef CLIC_NUM_INTERRUPTS
#define CLIC_NUM_INTERRUPTS 32U
#warning "CLIC_NUM_INTERRUPTS not defined in device header file; using default value: 32."
#endif

#ifndef CLIC_INTxCTL_BITS
#define CLIC_INTxCTL_BITS 4U
#warning "CLIC_INTxCTL_BITS not defined in device header file; using default value: 4."
#endif

#ifndef CLIC_xTVEC_ALIGN
#define CLIC_xTVEC_ALIGN 6U
#warning "CLIC_xTVEC_ALIGN not defined in device header file; using default value: 6."
#endif

#ifndef CLIC_PRIVILEGE_MODES
#define CLIC_PRIVILEGE_MODES 1U
#warning "CLIC_PRIVILEGE_MODES not defined in device header file; using default value: 1."
#endif

/** @} */ /* End of group CORE_CLIC_Configuration */

/** @defgroup CORE_CLIC_Exported_Defines CLIC Exported Defines
 * @{
 */

#define CLIC_VECTOR_MASK             ((0xFFFFFFFFUL >> CLIC_xTVEC_ALIGN) << CLIC_xTVEC_ALIGN)
#define CLIC_VECTOR_ALIGN            (1U << CLIC_xTVEC_ALIGN)

#define IS_CLIC_xTVEC_ALIGNED(xTVEC) (((uint32_t)(xTVEC) & ~CLIC_VECTOR_MASK) == 0)
#define IS_CLIC_xTVT_ALIGNED(xTVT)      (((uint32_t)(xTVT) & ~CLIC_VECTOR_MASK)) == 0)
#define __TRAP_HANDLER_ALIGNED __attribute__((aligned(CLIC_VECTOR_ALIGN)))
#define __VECTOR_TABLE_ALIGNED __attribute__((aligned(CLIC_VECTOR_ALIGN)))

/** @} */ /* End of group CORE_CLIC_Exported_Defines */

/** @defgroup CORE_CLIC_CSR CLIC CSR
 * @{
 */

#define CSR_MTVT         (0x307UL)
#define CSR_MCLICBASE    (0x308UL)
#define CSR_MNXTI        (0x345UL)
#define CSR_MINTSTATUS   (0x346UL)
#define CSR_MINTTHRESH   (0x347UL)
#define CSR_MSCRATCHCSW  (0x348UL)
#define CSR_MSCRATCHCSWL (0x349UL)

#if (CLIC_PRIVILEGE_MODES == 3)
#define CSR_STVT         (0x107UL)
#define CSR_SNXTI        (0x145UL)
#define CSR_SINTSTATUS   (0x146UL)
#define CSR_SINTTHRESH   (0x147UL)
#define CSR_SSCRATCHCSW  (0x148UL)
#define CSR_SSCRATCHCSWL (0x149UL)
#endif /* CLIC_PRIVILEGE_MODES */

#if (CLIC_PRIVILEGE_MODES >= 2)
#define CSR_UTVT         (0x007UL)
#define CSR_UNXTI        (0x045UL)
#define CSR_UINTSTATUS   (0x046UL)
#define CSR_UINTTHRESH   (0x047UL)
#define CSR_USCRATCHCSW  (0x048UL)
#define CSR_USCRATCHCSWL (0x049UL)
#endif /* CLIC_PRIVILEGE_MODES */

/** @defgroup CORE_CLIC_CSR_XINTSTATUS CLIC CSR XINTSTATUS
 * @{
 */

#define CSR_XINTSTATUS_UIL_Pos 0
#define CSR_XINTSTATUS_UIL_Msk (0xFFUL << CSR_XINTSTATUS_UIL_Pos)

#define CSR_XINTSTATUS_SIL_Pos 8
#define CSR_XINTSTATUS_SIL_Msk (0xFFUL << CSR_XINTSTATUS_SIL_Pos)

#define CSR_XINTSTATUS_MIL_Pos 24
#define CSR_XINTSTATUS_MIL_Msk (0xFFUL << CSR_XINTSTATUS_MIL_Pos)

/** @} */ /* End of group CORE_CLIC_CSR_XINTSTATUS */

/** @defgroup CORE_CLIC_CSR_XINTTHRESH CLIC CSR XINTTHRESH
 * @{
 */

#define CSR_XINTTHRESH_TH_Pos 0
#define CSR_XINTTHRESH_TH_Msk (0xFFUL << CSR_XINTTHRESH_TH_Pos)

/** @} */ /* End of group CORE_CLIC_CSR_XINTTHRESH */

/** @defgroup CORE_CLIC_CSR_MCAUSE CLIC CSR MCAUSE
 * @{
 */

#define CSR_MCAUSE_EXCCODE_Pos   0
#define CSR_MCAUSE_EXCCODE_Msk   (0xFFFUL << CSR_MCAUSE_EXCCODE_Pos)

#define CSR_MCAUSE_MPIL_Pos      16
#define CSR_MCAUSE_MPIL_Msk      (0xFFUL << CSR_MCAUSE_MPIL_Pos)

#define CSR_MCAUSE_MPIE_Pos      27
#define CSR_MCAUSE_MPIE_Msk      (0x1UL << CSR_MCAUSE_MPIE_Pos)
#define CSR_MCAUSE_MPIE          CSR_MCAUSE_MPIE_Msk

#define CSR_MCAUSE_MPP_Pos       28
#define CSR_MCAUSE_MPP_Msk       (0x3UL << CSR_MCAUSE_MPP_Pos)

#define CSR_MCAUSE_MINHV_Pos     30
#define CSR_MCAUSE_MINHV_Msk     (0x1UL << CSR_MCAUSE_MINHV_Pos)
#define CSR_MCAUSE_MINHV         CSR_MCAUSE_MINHV_Msk

#define CSR_MCAUSE_INTERRUPT_Pos 31
#define CSR_MCAUSE_INTERRUPT_Msk (0x1UL << CSR_MCAUSE_INTERRUPT_Pos)
#define CSR_MCAUSE_INTERRUPT     CSR_MCAUSE_INTERRUPT_Msk

/** @} */ /* End of group CORE_CLIC_CSR_MCAUSE */

#if (CLIC_PRIVILEGE_MODES == 3)

/** @defgroup CORE_CLIC_CSR_SCAUSE CLIC CSR SCAUSE
 * @{
 */

#define CSR_SCAUSE_EXCCODE_Pos   0
#define CSR_SCAUSE_EXCCODE_Msk   (0xFFFUL << CSR_SCAUSE_EXCCODE_Pos)

#define CSR_SCAUSE_SPIL_Pos      16
#define CSR_SCAUSE_SPIL_Msk      (0xFFUL << CSR_SCAUSE_SPIL_Pos)

#define CSR_SCAUSE_SPIE_Pos      27
#define CSR_SCAUSE_SPIE_Msk      (0x1UL << CSR_SCAUSE_SPIE_Pos)
#define CSR_SCAUSE_SPIE          CSR_SCAUSE_SPIE_Msk

#define CSR_SCAUSE_SPP_Pos       28
#define CSR_SCAUSE_SPP_Msk       (0x1UL << CSR_SCAUSE_SPP_Pos)
#define CSR_SCAUSE_SPP           CSR_SCAUSE_SPP_Msk

#define CSR_SCAUSE_SINHV_Pos     30
#define CSR_SCAUSE_SINHV_Msk     (0x1UL << CSR_SCAUSE_SINHV_Pos)
#define CSR_SCAUSE_SINHV         CSR_SCAUSE_SINHV_Msk

#define CSR_SCAUSE_INTERRUPT_Pos 31
#define CSR_SCAUSE_INTERRUPT_Msk (0x1UL << CSR_SCAUSE_INTERRUPT_Pos)
#define CSR_SCAUSE_INTERRUPT     CSR_SCAUSE_INTERRUPT_Msk

/** @} */ /* End of group CORE_CLIC_CSR_SCAUSE */

#endif /* CLIC_PRIVILEGE_MODES */

#if (CLIC_PRIVILEGE_MODES >= 2)

/** @defgroup CORE_CLIC_CSR_UCAUSE CLIC CSR UCAUSE
 * @{
 */

#define CSR_UCAUSE_EXCCODE_Pos   0
#define CSR_UCAUSE_EXCCODE_Msk   (0xFFFUL << CSR_UCAUSE_EXCCODE_Pos)

#define CSR_UCAUSE_UPIL_Pos      16
#define CSR_UCAUSE_UPIL_Msk      (0xFFUL << CSR_UCAUSE_UPIL_Pos)

#define CSR_UCAUSE_UPIE_Pos      27
#define CSR_UCAUSE_UPIE_Msk      (0x1UL << CSR_UCAUSE_UPIE_Pos)
#define CSR_UCAUSE_UPIE          CSR_UCAUSE_UPIE_Msk

#define CSR_UCAUSE_UINHV_Pos     30
#define CSR_UCAUSE_UINHV_Msk     (0x1UL << CSR_UCAUSE_UINHV_Pos)
#define CSR_UCAUSE_UINHV         CSR_UCAUSE_UINHV_Msk

#define CSR_UCAUSE_INTERRUPT_Pos 31
#define CSR_UCAUSE_INTERRUPT_Msk (0x1UL << CSR_UCAUSE_INTERRUPT_Pos)
#define CSR_UCAUSE_INTERRUPT     CSR_UCAUSE_INTERRUPT_Msk

/** @} */ /* End of group CORE_CLIC_CSR_UCAUSE */

#endif /* CLIC_PRIVILEGE_MODES */

/** @defgroup CORE_CLIC_CSR_xTVEC CLIC CSR xTVEC
 * @{
 */

#define CSR_xTVEC_MODE_Pos          0
#define CSR_xTVEC_MODE_Msk          (0x3UL << CSR_xTVEC_MODE_Pos)
#define CSR_xTVEC_MODE_NON_VECTORED (0x0UL << CSR_xTVEC_MODE_Pos)
#define CSR_xTVEC_MODE_VECTORED     (0x1UL << CSR_xTVEC_MODE_Pos)
#define CSR_xTVEC_MODE_CLIC         (0x3UL << CSR_xTVEC_MODE_Pos)

#define CSR_xTVEC_NBASE_Pos         CLIC_xTVEC_ALIGN
#define CSR_xTVEC_NBASE_Msk         CLIC_VECTOR_MASK

/** @} */ /* End of group CORE_CLIC_CSR_xTVEC */

/** @defgroup CORE_CLIC_CSR_xTVT CLIC CSR xTVT
 * @{
 */

#define CSR_xTVT_TBASE_Pos CLIC_xTVEC_ALIGN
#define CSR_xTVT_TBASE_Msk CLIC_VECTOR_MASK

/** @} */ /* End of group CORE_CLIC_CSR_xTVT */

/** @} */ /* End of group CORE_CLIC_CSR */

/** @addtogroup CORE_CLIC_Registers_Abstraction_Layer CLIC Register Abstraction Layer
 * @{
 */

/**
 * @brief CLIC interrupt register structure.
 */
typedef struct {
    __IO uint8_t IP;   /*!<CLIC Interrupt IP Register */
    __IO uint8_t IE;   /*!<CLIC Interrupt IE Register */
    __IO uint8_t ATTR; /*!<CLIC Interrupt ATTR Register */
    __IO uint8_t CTL;  /*!<CLIC Interrupt CTL Register */
} CLIC_INT_TypeDef;

/**
 * @brief CLIC control structure.
 */
typedef struct {
    __IO uint8_t          CFG;                      /*!<CLIC Сonfiguration Register */
    __I uint8_t           RESERVED0[3];             /*!<Reserved */
    __I uint32_t          INFO;                     /*!<CLIC Information Register */
    __I uint32_t          RESERVED1[14];            /*!<Reserved */
    __I uint32_t          INTTRIG[32];              /*!<CLIC Interrupt Trigger Register */
    __I uint32_t          RESERVED2[976];           /*!<Reserved */
    __IO CLIC_INT_TypeDef INT[CLIC_NUM_INTERRUPTS]; /*!<CLIC Interrupt Register Set */
} CLIC_TypeDef;

/** @defgroup CORE_CLIC_Declaration CLIC Declaration
 * @{
 */

#define CLIC ((CLIC_TypeDef*)CLIC_BASE)

/** @} */ /* End of group CORE_CLIC_Declaration */

/** @defgroup CORE_CLIC_CFG CLIC CFG
 * @{
 */

#define CLIC_CFG_NVBITS_Pos 0
#define CLIC_CFG_NVBITS_Msk (0x1UL << CLIC_CFG_NVBITS_Pos)
#define CLIC_CFG_NVBITS     CLIC_CFG_NVBITS_Msk

#define CLIC_CFG_NLBITS_Pos 1
#define CLIC_CFG_NLBITS_Msk (0xFUL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_0   (0x0UL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_1   (0x1UL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_2   (0x2UL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_3   (0x3UL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_4   (0x4UL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_5   (0x5UL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_6   (0x6UL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_7   (0x7UL << CLIC_CFG_NLBITS_Pos)
#define CLIC_CFG_NLBITS_8   (0x8UL << CLIC_CFG_NLBITS_Pos)

#define CLIC_CFG_NMBITS_Pos 5
#define CLIC_CFG_NMBITS_Msk (0x3UL << CLIC_CFG_NMBITS_Pos)
#define CLIC_CFG_NMBITS_0   (0x0UL << CLIC_CFG_NMBITS_Pos)
#define CLIC_CFG_NMBITS_1   (0x1UL << CLIC_CFG_NMBITS_Pos)
#define CLIC_CFG_NMBITS_2   (0x2UL << CLIC_CFG_NMBITS_Pos)

/** @} */ /* End of group CORE_CLIC_CFG */

/** @defgroup CORE_CLIC_INFO CLIC INFO
 * @{
 */

#define CLIC_INFO_NUM_INTERRUPT_Pos  0
#define CLIC_INFO_NUM_INTERRUPT_Msk  (0x1FFFUL << CLIC_INFO_NUM_INTERRUPT_Pos)

#define CLIC_INFO_IMPL_VERSION_Pos   13
#define CLIC_INFO_IMPL_VERSION_Msk   (0xFUL << CLIC_INFO_IMPL_VERSION_Pos)

#define CLIC_INFO_ARCH_VERSION_Pos   17
#define CLIC_INFO_ARCH_VERSION_Msk   (0xFUL << CLIC_INFO_ARCH_VERSION_Pos)

#define CLIC_INFO_CLICINTCTLBITS_Pos 21
#define CLIC_INFO_CLICINTCTLBITS_Msk (0xFUL << CLIC_INFO_CLICINTCTLBITS_Pos)

#define CLIC_INFO_NUM_TRIGGER_Pos    25
#define CLIC_INFO_NUM_TRIGGER_Msk    (0x3FUL << CLIC_INFO_NUM_TRIGGER_Pos)

/** @} */ /* End of group CORE_CLIC_INFO */

/** @defgroup CORE_CLIC_INTTRIGx CLIC INTTRIGx
 * @{
 */

#define CLIC_INTTRIGx_INTERRUPT_NUMBER_Pos 0
#define CLIC_INTTRIGx_INTERRUPT_NUMBER_Msk (0x1FFFUL << CLIC_INTTRIGx_INTERRUPT_NUMBER_Pos)

#define CLIC_INTTRIGx_ENABLE_Pos           31
#define CLIC_INTTRIGx_ENABLE_Msk           (0x1UL << CLIC_INTTRIGx_ENABLE_Pos)

/** @} */ /* End of group CORE_CLIC_INTTRIGx */

/** @defgroup CORE_CLIC_INTxIP CLIC INTxIP
 * @{
 */

#define CLIC_INTxIP_IP_Pos 0
#define CLIC_INTxIP_IP_Msk (0x1UL << CLIC_INTxIP_IP_Pos)

/** @} */ /* End of group CORE_CLIC_INTxIP */

/** @defgroup CORE_CLIC_INTxIE CLIC INTxIE
 * @{
 */

#define CLIC_INTxIE_IE_Pos 0
#define CLIC_INTxIE_IE_Msk (0x1UL << CLIC_INTxIE_IE_Pos)

/** @} */ /* End of group CORE_CLIC_INTxIE */

/** @defgroup CORE_CLIC_INTxATTR CLIC INTxATTR
 * @{
 */

#define CLIC_INTxATTR_SHV_Pos           0
#define CLIC_INTxATTR_SHV_Msk           (0x1UL << CLIC_INTxATTR_SHV_Pos)
#define CLIC_INTxATTR_SHV               CLIC_INTxATTR_SHV_Msk

#define CLIC_INTxATTR_TRIG_Pos          1
#define CLIC_INTxATTR_TRIG_Msk          (0x3UL << CLIC_INTxATTR_TRIG_Pos)
#define CLIC_INTxATTR_TRIG_LEVEL_HIGH   (0x0UL << CLIC_INTxATTR_TRIG_Pos)
#define CLIC_INTxATTR_TRIG_EDGE_RISING  (0x1UL << CLIC_INTxATTR_TRIG_Pos)
#define CLIC_INTxATTR_TRIG_LEVEL_LOW    (0x2UL << CLIC_INTxATTR_TRIG_Pos)
#define CLIC_INTxATTR_TRIG_EDGE_FALLING (0x3UL << CLIC_INTxATTR_TRIG_Pos)

#define CLIC_INTxATTR_MODE_Pos          6
#define CLIC_INTxATTR_MODE_Msk          (0x3UL << CLIC_INTxATTR_MODE_Pos)
#define CLIC_INTxATTR_MODE_U            (0x0UL << CLIC_INTxATTR_MODE_Pos)
#define CLIC_INTxATTR_MODE_S            (0x1UL << CLIC_INTxATTR_MODE_Pos)
#define CLIC_INTxATTR_MODE_M            (0x3UL << CLIC_INTxATTR_MODE_Pos)

/** @} */ /* End of group CORE_CLIC_INTxATTR */

/** @defgroup CORE_CLIC_INTxCTL CLIC INTxCTL
 * @{
 */

#define CLIC_INTxCTL_LEVEL_PRIORITY_Pos 0
#define CLIC_INTxCTL_LEVEL_PRIORITY_Msk (0xFFUL << CLIC_INTxCTL_LEVEL_PRIORITY_Pos)

/** @} */ /* End of group CORE_CLIC_INTxCTL */

/** @} */ /* End of group CORE_CLIC_Registers_Abstraction_Layer */

/** @addtogroup CORE_CLIC_Hardware_Abstraction_Layer CLIC Hardware Abstraction Layer
 * @{
 */

/** @defgroup CORE_CLIC_Exported_Types CLIC Exported Types
 * @{
 */

/**
 * @brief CLIC maximum number of interrupt levels.
 */
typedef enum {
#if (CLIC_INTxCTL_BITS >= 0)
    CLIC_MAX_LEVELS_1 = CLIC_CFG_NLBITS_0, /*!< 1 interrupt level available. */
#endif
#if (CLIC_INTxCTL_BITS >= 1)
    CLIC_MAX_LEVELS_2 = CLIC_CFG_NLBITS_1, /*!< 2 interrupt levels available. */
#endif
#if (CLIC_INTxCTL_BITS >= 2)
    CLIC_MAX_LEVELS_4 = CLIC_CFG_NLBITS_2, /*!< 4 interrupt levels available. */
#endif
#if (CLIC_INTxCTL_BITS >= 3)
    CLIC_MAX_LEVELS_8 = CLIC_CFG_NLBITS_3, /*!< 8 interrupt levels available. */
#endif
#if (CLIC_INTxCTL_BITS >= 4)
    CLIC_MAX_LEVELS_16 = CLIC_CFG_NLBITS_4, /*!< 16 interrupt levels available. */
#endif
#if (CLIC_INTxCTL_BITS >= 5)
    CLIC_MAX_LEVELS_32 = CLIC_CFG_NLBITS_5, /*!< 32 interrupt levels available. */
#endif
#if (CLIC_INTxCTL_BITS >= 6)
    CLIC_MAX_LEVELS_64 = CLIC_CFG_NLBITS_6, /*!< 64 interrupt levels available. */
#endif
#if (CLIC_INTxCTL_BITS >= 7)
    CLIC_MAX_LEVELS_128 = CLIC_CFG_NLBITS_7, /*!< 128 interrupt levels available. */
#endif
#if (CLIC_INTxCTL_BITS >= 8)
    CLIC_MAX_LEVELS_256 = CLIC_CFG_NLBITS_8 /*!< 256 interrupt levels available. */
#endif
} CLIC_MaxLevels_TypeDef;

#if (CLIC_INTxCTL_BITS == 0)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) ((MAX_LEVELS) == CLIC_MAX_LEVELS_1)
#elif (CLIC_INTxCTL_BITS == 1)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) (((MAX_LEVELS) == CLIC_MAX_LEVELS_1) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_2))
#elif (CLIC_INTxCTL_BITS == 2)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) (((MAX_LEVELS) == CLIC_MAX_LEVELS_1) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_2) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_4))
#elif (CLIC_INTxCTL_BITS == 3)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) (((MAX_LEVELS) == CLIC_MAX_LEVELS_1) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_2) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_4) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_8))
#elif (CLIC_INTxCTL_BITS == 4)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) (((MAX_LEVELS) == CLIC_MAX_LEVELS_1) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_2) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_4) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_8) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_16))
#elif (CLIC_INTxCTL_BITS == 5)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) (((MAX_LEVELS) == CLIC_MAX_LEVELS_1) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_2) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_4) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_8) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_16) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_32))
#elif (CLIC_INTxCTL_BITS == 6)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) (((MAX_LEVELS) == CLIC_MAX_LEVELS_1) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_2) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_4) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_8) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_16) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_32) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_64))
#elif (CLIC_INTxCTL_BITS == 7)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) (((MAX_LEVELS) == CLIC_MAX_LEVELS_1) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_2) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_4) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_8) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_16) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_32) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_64) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_128))
#elif (CLIC_INTxCTL_BITS == 8)
#define IS_CLIC_MAX_LEVELS(MAX_LEVELS) (((MAX_LEVELS) == CLIC_MAX_LEVELS_1) ||   \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_2) ||   \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_4) ||   \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_8) ||   \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_16) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_32) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_64) ||  \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_128) || \
                                        ((MAX_LEVELS) == CLIC_MAX_LEVELS_256))
#endif

/**
 * @brief CLIC privilege levels for interrupts.
 */
typedef enum {
    CLIC_PRIVILEGE_LEVEL_M = CLIC_CFG_NMBITS_0, /*!< M-mode is available for interrupts. */
#if (CLIC_PRIVILEGE_MODES == 2)
    CLIC_PRIVILEGE_LEVEL_MU = CLIC_CFG_NMBITS_1 /*!< M-mode and U-mode are available for interrupts. */
#elif (CLIC_PRIVILEGE_MODES == 3)
    CLIC_PRIVILEGE_LEVEL_MS  = CLIC_CFG_NMBITS_1, /*!< M-mode and S-mode are available for interrupts. */
    CLIC_PRIVILEGE_LEVEL_MSU = CLIC_CFG_NMBITS_2  /*!< M-mode, S-mode and U-mode are available for interrupts. */
#endif
} CLIC_PrivilegeLevel_TypeDef;

#if (CLIC_PRIVILEGE_MODES == 3)
#define IS_CLIC_PRIVILEGE_LEVEL(PRIVILEGE) (((PRIVILEGE) == CLIC_PRIVILEGE_LEVEL_M) ||  \
                                            ((PRIVILEGE) == CLIC_PRIVILEGE_LEVEL_MS) || \
                                            ((PRIVILEGE) == CLIC_PRIVILEGE_LEVEL_MSU))
#elif (CLIC_PRIVILEGE_MODES == 2)
#define IS_CLIC_PRIVILEGE_LEVEL(PRIVILEGE) (((PRIVILEGE) == CLIC_PRIVILEGE_LEVEL_M) || \
                                            ((PRIVILEGE) == CLIC_PRIVILEGE_LEVEL_MU))
#else
#define IS_CLIC_PRIVILEGE_LEVEL(PRIVILEGE) ((PRIVILEGE) == CLIC_PRIVILEGE_LEVEL_M)
#endif

/**
 * @brief CLIC trigger type and polarity for interrupt.
 */
typedef enum {
    CLIC_TRIGGER_IRQ_LEVEL_HIGH   = CLIC_INTxATTR_TRIG_LEVEL_HIGH,  /*!< Select a high trigger level. */
    CLIC_TRIGGER_IRQ_LEVEL_LOW    = CLIC_INTxATTR_TRIG_LEVEL_LOW,   /*!< Select a low trigger level. */
    CLIC_TRIGGER_IRQ_EDGE_RISING  = CLIC_INTxATTR_TRIG_EDGE_RISING, /*!< Select a rising edge triggering. */
    CLIC_TRIGGER_IRQ_EDGE_FALLING = CLIC_INTxATTR_TRIG_EDGE_FALLING /*!< Select a falling edge triggering. */
} CLIC_TriggerIRQ_TypeDef;

#define IS_CLIC_TRIGGER_IRQ(TRIGGER_IRQ) (((TRIGGER_IRQ) == CLIC_TRIGGER_IRQ_LEVEL_HIGH) ||  \
                                          ((TRIGGER_IRQ) == CLIC_TRIGGER_IRQ_LEVEL_LOW) ||   \
                                          ((TRIGGER_IRQ) == CLIC_TRIGGER_IRQ_EDGE_RISING) || \
                                          ((TRIGGER_IRQ) == CLIC_TRIGGER_IRQ_EDGE_FALLING))

/**
 * @brief CLIC interrupt privilege modes.
 */
typedef enum {
    CLIC_PRIVILEGE_MODE_IRQ_M = CLIC_INTxATTR_MODE_M, /*!< Select a M-mode for interrupt. */
#if (CLIC_PRIVILEGE_MODES == 2)
    CLIC_PRIVILEGE_MODE_IRQ_U = CLIC_INTxATTR_MODE_U /*!< Select a U-mode for interrupt. */
#elif (CLIC_PRIVILEGE_MODES == 3)
    CLIC_PRIVILEGE_MODE_IRQ_S = CLIC_INTxATTR_MODE_S, /*!< Select a S-mode for interrupt. */
    CLIC_PRIVILEGE_MODE_IRQ_U = CLIC_INTxATTR_MODE_U  /*!< Select a U-mode for interrupt. */
#endif
} CLIC_PrivilegeModeIRQ_TypeDef;

#if (CLIC_PRIVILEGE_MODES == 3)
#define IS_CLIC_PRIVILEGE_MODE_IRQ(PRIVILEGE) (((PRIVILEGE) == CLIC_PRIVILEGE_MODE_IRQ_M) || \
                                               ((PRIVILEGE) == CLIC_PRIVILEGE_MODE_IRQ_S) || \
                                               ((PRIVILEGE) == CLIC_PRIVILEGE_MODE_IRQ_U))
#elif (CLIC_PRIVILEGE_MODES == 2)
#define IS_CLIC_PRIVILEGE_MODE_IRQ(PRIVILEGE) (((PRIVILEGE) == CLIC_PRIVILEGE_MODE_IRQ_M) || \
                                               ((PRIVILEGE) == CLIC_PRIVILEGE_MODE_IRQ_U))
#else
#define IS_CLIC_PRIVILEGE_MODE_IRQ(PRIVILEGE) ((PRIVILEGE) == CLIC_PRIVILEGE_MODE_IRQ_M)
#endif

/**
 * @brief CLIC configuration.
 */
typedef struct
{
    CLIC_PrivilegeLevel_TypeDef CLIC_PrivilegeLevel;        /*!< Privilege levels for interrupts. */
    FunctionalState             CLIC_Vectoring;             /*!< Vectoring mode. */
    uint8_t                     CLIC_LevelPriotityBits;     /*!< Number of hardware bits is actually implemented in INTxCTL registers. */
    uint8_t                     CLIC_MaxLevels;             /*!< Maximum number of interrupt levels. */
    uint8_t                     CLIC_MaxPriorities;         /*!< Maximum number of interrupt priorities. */
    uint8_t                     CLIC_Triggers;              /*!< Number of maximum interrupt triggers supported. */
    uint16_t                    CLIC_Interrupts;            /*!< Number of maximum interrupt inputs supported. */
    uint8_t                     CLIC_ImplementationVersion; /*!< Implementation version. */
    uint8_t                     CLIC_ArchitectureVersion;   /*!< Architecture version. */
} CLIC_Config_TypeDef;

/**
 * @brief CLIC init structure definition.
 */
typedef struct
{
    CLIC_PrivilegeLevel_TypeDef CLIC_PrivilegeLevel; /*!< Specify the privilege levels for interrupts.
                                                          This parameter can be a value of @ref CLIC_PrivilegeLevel_TypeDef. */
    CLIC_MaxLevels_TypeDef CLIC_MaxLevels;           /*!< Specify the maximum number of interrupt levels.
                                                          This parameter can be a value of @ref CLIC_MaxLevels_TypeDef. */
} CLIC_InitTypeDef;

/**
 * @brief CLIC IRQ init structure definition.
 */
typedef struct
{
    FunctionalState CLIC_EnableIRQ;                      /*!< Enable or disable interrupt.
                                                              This parameter can be a value of @ref FunctionalState. */
    FunctionalState CLIC_VectoringIRQ;                   /*!< Enable or disable interrupt vectoring.
                                                              This parameter can be a value of @ref FunctionalState. */
    CLIC_TriggerIRQ_TypeDef CLIC_TriggerIRQ;             /*!< Specify the trigger type and polarity for interrupt.
                                                              This parameter can be a value of @ref CLIC_TriggerIRQ_TypeDef. */
    CLIC_PrivilegeModeIRQ_TypeDef CLIC_PrivilegeModeIRQ; /*!< Specify the interrupt privilege mode.
                                                              This parameter can be a value of @ref CLIC_PrivilegeModeIRQ_TypeDef depending on CLIC_Privilege. */
    uint8_t CLIC_LevelIRQ;                               /*!< Specify the interrupt level.
                                                              This parameter can be a number from 0x00 to CLIC_MaxLevels. */
    uint8_t CLIC_PriorityIRQ;                            /*!< Specify the interrupt priority.
                                                              This parameter can be a number from 0x00 to CLIC_MaxPriorities. */
} CLIC_IRQ_InitTypeDef;

/** @} */ /* End of group CORE_CLIC_Exported_Types */

/** @addtogroup CORE_CLIC_Exported_Functions CLIC Exported Functions
 * @{
 */

void CLIC_Init(const CLIC_InitTypeDef* CLIC_InitStruct);
void CLIC_StructInit(CLIC_InitTypeDef* CLIC_InitStruct);
void CLIC_GetConfig(CLIC_Config_TypeDef* CLIC_ConfigStruct);

void CLIC_InitIRQ(IRQn_TypeDef IRQn, const CLIC_IRQ_InitTypeDef* CLIC_InitStructIRQ);
void CLIC_InitAllIRQ(const CLIC_IRQ_InitTypeDef* CLIC_InitStructIRQ);
void CLIC_StructInitIRQ(CLIC_IRQ_InitTypeDef* CLIC_InitStructIRQ);

void       CLIC_EnableIRQ(IRQn_TypeDef IRQn);
void       CLIC_DisableIRQ(IRQn_TypeDef IRQn);
FlagStatus CLIC_GetEnableIRQ(IRQn_TypeDef IRQn);

void       CLIC_SetPendingIRQ(IRQn_TypeDef IRQn);
void       CLIC_ClearPendingIRQ(IRQn_TypeDef IRQn);
FlagStatus CLIC_GetPendingIRQ(IRQn_TypeDef IRQn);

void    CLIC_SetLevelIRQ(IRQn_TypeDef IRQn, uint8_t Level);
uint8_t CLIC_GetLevelIRQ(IRQn_TypeDef IRQn);

void    CLIC_SetPriorityIRQ(IRQn_TypeDef IRQn, uint8_t Priority);
uint8_t CLIC_GetPriorityIRQ(IRQn_TypeDef IRQn);

void                CLIC_SetVectorTable(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode, IRQHandler_TypeDef* VectorTable);
IRQHandler_TypeDef* CLIC_GetVectorTable(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode);

void               CLIC_SetTrapVector(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode, IRQHandler_TypeDef TrapVector);
IRQHandler_TypeDef CLIC_GetTrapVector(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode);

uint8_t CLIC_GetLevelActiveIRQ(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode);

void    CLIC_SetThresholdLevelIRQ(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode, uint8_t Level);
uint8_t CLIC_GetThresholdLevelIRQ(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode);

/** @} */ /* End of the group CORE_CLIC_Exported_Functions */

/** @} */ /* End of group CORE_CLIC_Hardware_Abstraction_Layer */

/** @} */ /* End of the group CORE_CLIC */

#endif /* CLIC_PRESENT */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_CLIC */

/*********************** (C) COPYRIGHT {YYYY} Milandr ****************************
 *
 * END OF FILE core_clic.h */
