/**
 *******************************************************************************
 * @file    core_clic.c
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    15/12/2023
 * @brief   RISC-V CLIC Access Layer Source File.
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
#include "core_clic.h"
#include "core_csr.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(CLIC_PRESENT) && (CLIC_PRESENT == 1U)

/** @addtogroup CORE_CLIC CLIC
 * @{
 */

/** @defgroup CORE_CLIC_Private_Functions_Declarations CLIC Private Functions Declarations
 * @{
 */

static uint32_t CLIC_GetConfigIRQ(const CLIC_IRQ_InitTypeDef* CLIC_InitStructIRQ);

/** @} */ /* End of the group CORE_CLIC_Private_Functions_Declarations */

/** @addtogroup CORE_CLIC_Exported_Functions CLIC Exported Functions
 * @{
 */

/**
 * @brief  Initialize the CLIC according to the specified
 *         parameters in the CLIC_InitStruct.
 * @param  CLIC_InitStruct: The pointer to the @ref CLIC_InitTypeDef structure
 *         that contains the configuration information for the CLIC.
 * @return None.
 */
void CLIC_Init(const CLIC_InitTypeDef* CLIC_InitStruct)
{
    uint8_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_CLIC_PRIVILEGE_LEVEL(CLIC_InitStruct->CLIC_PrivilegeLevel));
    assert_param(IS_CLIC_MAX_LEVELS(CLIC_InitStruct->CLIC_MaxLevels));

    TmpReg = (uint8_t)CLIC_InitStruct->CLIC_PrivilegeLevel |
             (uint8_t)CLIC_InitStruct->CLIC_MaxLevels;

    CLIC->CFG = TmpReg;
}

/**
 * @brief  Fill each CLIC_InitStruct member with its default value.
 * @param  CLIC_InitStruct: the pointer to the @ref CLIC_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void CLIC_StructInit(CLIC_InitTypeDef* CLIC_InitStruct)
{
    CLIC_InitStruct->CLIC_PrivilegeLevel = CLIC_PRIVILEGE_LEVEL_M;
#if (CLIC_INTxCTL_BITS == 0)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_1;
#elif (CLIC_INTxCTL_BITS == 1)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_2;
#elif (CLIC_INTxCTL_BITS == 2)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_2;
#elif (CLIC_INTxCTL_BITS == 3)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_4;
#elif (CLIC_INTxCTL_BITS == 4)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_4;
#elif (CLIC_INTxCTL_BITS == 5)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_8;
#elif (CLIC_INTxCTL_BITS == 6)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_8;
#elif (CLIC_INTxCTL_BITS == 7)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_16;
#elif (CLIC_INTxCTL_BITS == 8)
    CLIC_InitStruct->CLIC_MaxLevels = CLIC_MAX_LEVELS_16;
#endif
}

/**
 * @brief  Get CLIC configuration.
 * @param  CLIC_ConfigStruct: the pointer to the @ref CLIC_Config_TypeDef structure
 *         into which the configuration data will be written.
 * @return None.
 */
void CLIC_GetConfig(CLIC_Config_TypeDef* CLIC_ConfigStruct)
{
    uint32_t TmpInfo;
    uint8_t  TmpCfg, LevelBits, PriorityBits;

    TmpInfo                                       = CLIC->INFO;
    CLIC_ConfigStruct->CLIC_LevelPriotityBits     = (TmpInfo & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
    CLIC_ConfigStruct->CLIC_Interrupts            = (TmpInfo & CLIC_INFO_NUM_INTERRUPT_Msk) >> CLIC_INFO_NUM_INTERRUPT_Pos;
    CLIC_ConfigStruct->CLIC_Triggers              = (TmpInfo & CLIC_INFO_NUM_TRIGGER_Msk) >> CLIC_INFO_NUM_TRIGGER_Pos;
    CLIC_ConfigStruct->CLIC_ImplementationVersion = (TmpInfo & CLIC_INFO_IMPL_VERSION_Msk) >> CLIC_INFO_IMPL_VERSION_Pos;
    CLIC_ConfigStruct->CLIC_ArchitectureVersion   = (TmpInfo & CLIC_INFO_ARCH_VERSION_Msk) >> CLIC_INFO_ARCH_VERSION_Pos;

    TmpCfg    = CLIC->CFG;
    LevelBits = (TmpCfg & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    if (LevelBits < CLIC_INTxCTL_BITS) {
        PriorityBits = CLIC_INTxCTL_BITS - LevelBits;
    } else {
        LevelBits    = CLIC_INTxCTL_BITS;
        PriorityBits = 0;
    }
    CLIC_ConfigStruct->CLIC_PrivilegeLevel = (CLIC_PrivilegeLevel_TypeDef)(TmpCfg & CLIC_CFG_NMBITS_Msk);
    CLIC_ConfigStruct->CLIC_Vectoring      = (FunctionalState)((TmpCfg & CLIC_CFG_NVBITS) >> CLIC_CFG_NVBITS_Pos);
    CLIC_ConfigStruct->CLIC_MaxLevels      = (uint8_t)(1 << LevelBits);
    CLIC_ConfigStruct->CLIC_MaxPriorities  = (uint8_t)(1 << PriorityBits);
}

/**
 * @brief  Get the 32-bit value of the CLIC interrupt register according
 *         to the specified parameters in the CLIC_InitStructIRQ.
 * @param  CLIC_InitStructIRQ: The pointer to the @ref CLIC_IRQ_InitTypeDef structure
 *         that contains the configuration information for the CLIC interrupt.
 * @return The value of the CLIC interrupt register.
 */
static uint32_t CLIC_GetConfigIRQ(const CLIC_IRQ_InitTypeDef* CLIC_InitStructIRQ)
{
    uint32_t TmpInt, TmpIntCtl, TmpIntAttr, TmpIntIe;
    uint8_t  LevelBits, PriorityBits, PriorityMask;

    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(CLIC_InitStructIRQ->CLIC_EnableIRQ));
    assert_param(IS_FUNCTIONAL_STATE(CLIC_InitStructIRQ->CLIC_VectoringIRQ));
    assert_param(IS_CLIC_TRIGGER_IRQ(CLIC_InitStructIRQ->CLIC_TriggerIRQ));
    assert_param(IS_CLIC_PRIVILEGE_MODE_IRQ(CLIC_InitStructIRQ->CLIC_PrivilegeModeIRQ));

    LevelBits = (CLIC->CFG & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    TmpIntCtl = CLIC_InitStructIRQ->CLIC_LevelIRQ << (8 - LevelBits);
    if (LevelBits < CLIC_INTxCTL_BITS) {
        PriorityBits = (uint8_t)(CLIC_INTxCTL_BITS - LevelBits);
        PriorityMask = (uint8_t)(0xFFU >> (8 - PriorityBits)) << CLIC_INTxCTL_BITS;
        TmpIntCtl |= (CLIC_InitStructIRQ->CLIC_PriorityIRQ << CLIC_INTxCTL_BITS) & PriorityMask;
    }
    TmpIntAttr = (uint32_t)CLIC_InitStructIRQ->CLIC_VectoringIRQ |
                 (uint32_t)CLIC_InitStructIRQ->CLIC_TriggerIRQ |
                 (uint32_t)CLIC_InitStructIRQ->CLIC_PrivilegeModeIRQ;
    TmpIntIe = (uint32_t)CLIC_InitStructIRQ->CLIC_EnableIRQ;
    TmpInt   = (TmpIntIe << 8) | (TmpIntAttr << 16) | (TmpIntCtl << 24);

    return TmpInt;
}

/**
 * @brief  Initialize the CLIC interrupt according to the specified
 *         parameters in the CLIC_InitStructIRQ.
 * @param  IRQn: Device specific interrupt number.
 * @param  CLIC_InitStructIRQ: The pointer to the @ref CLIC_IRQ_InitTypeDef structure
 *         that contains the configuration information for the CLIC interrupt.
 * @return None.
 */
void CLIC_InitIRQ(IRQn_TypeDef IRQn, const CLIC_IRQ_InitTypeDef* CLIC_InitStructIRQ)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    TmpReg                              = CLIC_GetConfigIRQ(CLIC_InitStructIRQ);
    *((__IO uint32_t*)&CLIC->INT[IRQn]) = TmpReg;
}

/**
 * @brief  Initialize all CLIC interrupts according to the specified
 *         parameters in the CLIC_InitStructIRQ.
 * @param  CLIC_InitStructIRQ: The pointer to the @ref CLIC_IRQ_InitTypeDef structure
 *         that contains the configuration information for the CLIC interrupt.
 * @return None.
 */
void CLIC_InitAllIRQ(const CLIC_IRQ_InitTypeDef* CLIC_InitStructIRQ)
{
    __IO uint32_t* TmpPtr;
    uint32_t       TmpReg, TmpIRQ;

    TmpReg = CLIC_GetConfigIRQ(CLIC_InitStructIRQ);
    TmpPtr = (__IO uint32_t*)&CLIC->INT[0];

    for (TmpIRQ = 0; TmpIRQ < CLIC_NUM_INTERRUPTS; TmpIRQ++) {
        TmpPtr[TmpIRQ] = TmpReg;
    }
}

/**
 * @brief  Fill each CLIC_InitStructIRQ member with its default value.
 * @param  CLIC_InitStructIRQ: the pointer to the @ref CLIC_IRQ_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void CLIC_StructInitIRQ(CLIC_IRQ_InitTypeDef* CLIC_InitStructIRQ)
{
    CLIC_InitStructIRQ->CLIC_EnableIRQ        = DISABLE;
    CLIC_InitStructIRQ->CLIC_VectoringIRQ     = ENABLE;
    CLIC_InitStructIRQ->CLIC_TriggerIRQ       = CLIC_TRIGGER_IRQ_EDGE_RISING;
    CLIC_InitStructIRQ->CLIC_PrivilegeModeIRQ = CLIC_PRIVILEGE_MODE_IRQ_M;
    CLIC_InitStructIRQ->CLIC_LevelIRQ         = 1;
    CLIC_InitStructIRQ->CLIC_PriorityIRQ      = 1;
}

/**
 * @brief  Enable interrupt.
 * @param  IRQn: Device specific interrupt number.
 * @return None.
 */
void CLIC_EnableIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    CLIC->INT[IRQn].IE = 1;
}

/**
 * @brief  Disable interrupt.
 * @param  IRQn: Device specific interrupt number.
 * @return None.
 */
void CLIC_DisableIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    CLIC->INT[IRQn].IE = 0;
}

/**
 * @brief  Get the interrupt enable status.
 * @param  IRQn: Device specific interrupt number.
 * @return Interrupt enable status.
 */
FlagStatus CLIC_GetEnableIRQ(IRQn_TypeDef IRQn)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    if (CLIC->INT[IRQn].IE == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Set the interrupt pending bit.
 * @note   Used only when the interrupt is configured for edge-triggered mode.
 * @param  IRQn: Device specific interrupt number.
 * @return None.
 */
void CLIC_SetPendingIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    CLIC->INT[IRQn].IP = 1;
}

/**
 * @brief  Clear the interrupt pending bit.
 * @note   Used only when the interrupt is configured for edge-triggered mode.
 * @param  IRQn: Device specific interrupt number.
 * @return None.
 */
void CLIC_ClearPendingIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    CLIC->INT[IRQn].IP = 0;
}

/**
 * @brief  Get the interrupt pending bit.
 * @param  IRQn: Device specific interrupt number.
 * @return None.
 */
FlagStatus CLIC_GetPendingIRQ(IRQn_TypeDef IRQn)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    if (CLIC->INT[IRQn].IP == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Set interrupt level.
 * @param  IRQn: Device specific interrupt number.
 * @param  Level: Interrupt level to set.
 * @return None.
 */
void CLIC_SetLevelIRQ(IRQn_TypeDef IRQn, uint8_t Level)
{
    uint8_t TmpReg, LevelBits, LevelMask;

    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    LevelBits = (CLIC->CFG & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    LevelMask = 0xFFU << (8 - LevelBits);

    TmpReg = CLIC->INT[IRQn].CTL & ~LevelMask;
    TmpReg |= Level << (8 - LevelBits);
    CLIC->INT[IRQn].CTL = TmpReg;
}

/**
 * @brief  Get interrupt level.
 * @param  IRQn: Device specific interrupt number.
 * @return None.
 */
uint8_t CLIC_GetLevelIRQ(IRQn_TypeDef IRQn)
{
    uint8_t Level, LevelBits;

    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    LevelBits = (CLIC->CFG & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    Level     = CLIC->INT[IRQn].CTL >> (8 - LevelBits);

    return Level;
}

/**
 * @brief  Set interrupt priority.
 * @param  IRQn: Device specific interrupt number.
 * @param  Priority: Interrupt priority to set.
 * @return None.
 */
void CLIC_SetPriorityIRQ(IRQn_TypeDef IRQn, uint8_t Priority)
{
    uint8_t TmpReg, LevelBits, PriorityBits, PriorityMask;

    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    LevelBits = (CLIC->CFG & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    if (LevelBits < CLIC_INTxCTL_BITS) {
        PriorityBits = (uint8_t)(CLIC_INTxCTL_BITS - LevelBits);
        PriorityMask = (uint8_t)(0xFFU >> (8 - PriorityBits)) << CLIC_INTxCTL_BITS;
        TmpReg       = CLIC->INT[IRQn].CTL & ~PriorityMask;
        TmpReg |= (Priority << CLIC_INTxCTL_BITS) & PriorityMask;
        CLIC->INT[IRQn].CTL = TmpReg;
    }
}

/**
 * @brief  Get interrupt priority.
 * @param  IRQn: Device specific interrupt number.
 * @return None.
 */
uint8_t CLIC_GetPriorityIRQ(IRQn_TypeDef IRQn)
{
    uint8_t LevelBits, PriorityBits, Priority, PriorityMask;

    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    LevelBits = (CLIC->CFG & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    if (LevelBits < CLIC_INTxCTL_BITS) {
        PriorityBits = CLIC_INTxCTL_BITS - LevelBits;
        PriorityMask = 0xFFU >> (8 - PriorityBits);
        Priority     = (CLIC->INT[IRQn].CTL >> CLIC_INTxCTL_BITS) & PriorityMask;
    } else {
        Priority = 0;
    }

    return Priority;
}

/**
 * @brief  Set interrupt vector table.
 * @param  PrivilegeMode: @ref CLIC_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @param  VectorTable: @ref IRQHandler_TypeDef - pointer to the interrupt vector table.
 * @return None.
 */
void CLIC_SetVectorTable(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode, IRQHandler_TypeDef* VectorTable)
{
    /* Check the parameters. */
    assert_param(IS_CLIC_PRIVILEGE_MODE_IRQ(PrivilegeMode));
    assert_param(IS_CLIC_xTVT_ALIGNED(VectorTable));

    if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_M) {
        csr_write(CSR_MTVT, (uint32_t)VectorTable & CSR_xTVT_TBASE_Msk);
    }
#if (CLIC_PRIVILEGE_MODES >= 2)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_U) {
        csr_write(CSR_UTVT, (uint32_t)VectorTable & CSR_xTVT_TBASE_Msk);
    }
#endif
#if (CLIC_PRIVILEGE_MODES == 3)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_S) {
        csr_write(CSR_STVT, (uint32_t)VectorTable & CSR_xTVT_TBASE_Msk);
    }
#endif
}

/**
 * @brief  Get interrupt vector table.
 * @param  PrivilegeMode: @ref CLIC_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @return @ref IRQHandler_TypeDef - pointer to the interrupt vector table.
 */
IRQHandler_TypeDef* CLIC_GetVectorTable(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode)
{
    /* Check the parameters. */
    assert_param(IS_CLIC_PRIVILEGE_MODE_IRQ(PrivilegeMode));

    IRQHandler_TypeDef* VectorTable = (IRQHandler_TypeDef*)0;

    if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_M) {
        VectorTable = (IRQHandler_TypeDef*)(csr_read(CSR_MTVT) & CSR_xTVT_TBASE_Msk);
    }
#if (CLIC_PRIVILEGE_MODES >= 2)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_U) {
        VectorTable = (IRQHandler_TypeDef*)(csr_read(CSR_UTVT) & CSR_xTVT_TBASE_Msk);
    }
#endif
#if (CLIC_PRIVILEGE_MODES == 3)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_S) {
        VectorTable = (IRQHandler_TypeDef*)(csr_read(CSR_STVT) & CSR_xTVT_TBASE_Msk);
    }
#endif

    return VectorTable;
}

/**
 * @brief  Set trap vector.
 * @param  PrivilegeMode: @ref CLIC_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @param  TrapVector: @ref IRQHandler_TypeDef - trap vector.
 * @return None.
 */
void CLIC_SetTrapVector(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode, IRQHandler_TypeDef TrapVector)
{
    /* Check the parameters. */
    assert_param(IS_CLIC_PRIVILEGE_MODE_IRQ(PrivilegeMode));
    assert_param(IS_CLIC_xTVEC_ALIGNED(TrapVector));

    if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_M) {
        csr_clear_bits(CSR_MTVEC, CSR_xTVEC_NBASE_Msk);
        csr_set_bits(CSR_MTVEC, (uint32_t)TrapVector & CSR_xTVEC_NBASE_Msk);
    }
#if (CLIC_PRIVILEGE_MODES >= 2)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_U) {
        csr_clear_bits(CSR_UTVEC, CSR_xTVEC_NBASE_Msk);
        csr_set_bits(CSR_UTVEC, (uint32_t)TrapVector & CSR_xTVEC_NBASE_Msk);
    }
#endif
#if (CLIC_PRIVILEGE_MODES == 3)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_S) {
        csr_clear_bits(CSR_STVEC, CSR_xTVEC_NBASE_Msk);
        csr_set_bits(CSR_STVEC, (uint32_t)TrapVector & CSR_xTVEC_NBASE_Msk);
    }
#endif
}

/**
 * @brief  Get trap vector.
 * @param  PrivilegeMode: @ref CLIC_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @return @ref IRQHandler_TypeDef - trap vector.
 */
IRQHandler_TypeDef CLIC_GetTrapVector(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode)
{
    /* Check the parameters. */
    assert_param(IS_CLIC_PRIVILEGE_MODE_IRQ(PrivilegeMode));

    IRQHandler_TypeDef TrapVector = (IRQHandler_TypeDef)0;

    if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_M) {
        TrapVector = (IRQHandler_TypeDef)(csr_read(CSR_MTVEC) & CSR_xTVEC_NBASE_Msk);
    }
#if (CLIC_PRIVILEGE_MODES >= 2)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_U) {
        TrapVector = (IRQHandler_TypeDef)(csr_read(CSR_UTVEC) & CSR_xTVEC_NBASE_Msk);
    }
#endif
#if (CLIC_PRIVILEGE_MODES == 3)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_S) {
        TrapVector = (IRQHandler_TypeDef)(csr_read(CSR_STVEC) & CSR_xTVEC_NBASE_Msk);
    }
#endif

    return TrapVector;
}

/**
 * @brief  Get the active interrupt level.
 * @param  PrivilegeMode: @ref CLIC_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
uint8_t CLIC_GetLevelActiveIRQ(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode)
{
    uint8_t TmpReg = 0, LevelBits = 0, Level = 0;

    /* Check the parameters. */
    assert_param(IS_CLIC_PRIVILEGE_MODE_IRQ(PrivilegeMode));

    if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_M) {
        TmpReg = (uint8_t)(csr_read(CSR_MINTSTATUS) & CSR_XINTSTATUS_MIL_Msk) >> CSR_XINTSTATUS_MIL_Pos;
    }
#if (CLIC_PRIVILEGE_MODES >= 2)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_U) {
        TmpReg = (uint8_t)(csr_read(CSR_UINTSTATUS) & CSR_XINTSTATUS_UIL_Msk) >> CSR_XINTSTATUS_UIL_Pos;
    }
#endif
#if (CLIC_PRIVILEGE_MODES == 3)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_S) {
        TmpReg = (uint8_t)(csr_read(CSR_SINTSTATUS) & CSR_XINTSTATUS_UIL_Msk) >> CSR_XINTSTATUS_UIL_Pos;
    }
#endif

    LevelBits = (CLIC->CFG & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    Level     = TmpReg >> (8 - LevelBits);

    return Level;
}

/**
 * @brief  Set interrupt level threshold.
 * @param  PrivilegeMode: @ref CLIC_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @param  Level: Interrupt level threshold.
 * @return None.
 */
void CLIC_SetThresholdLevelIRQ(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode, uint8_t Level)
{
    uint8_t TmpReg, LevelBits;

    /* Check the parameters. */
    assert_param(IS_CLIC_PRIVILEGE_MODE_IRQ(PrivilegeMode));

    LevelBits = (CLIC->CFG & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    TmpReg    = Level << (8 - LevelBits);

    if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_M) {
        csr_write(CSR_MINTTHRESH, TmpReg);
    }
#if (CLIC_PRIVILEGE_MODES >= 2)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_U) {
        csr_write(CSR_UINTTHRESH, TmpReg);
    }
#endif
#if (CLIC_PRIVILEGE_MODES == 3)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_S) {
        csr_write(CSR_SINTTHRESH, TmpReg);
    }
#endif
}

/**
 * @brief  Get interrupt level threshold.
 * @param  PrivilegeMode: @ref CLIC_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @return Interrupt level threshold.
 */
uint8_t CLIC_GetThresholdLevelIRQ(CLIC_PrivilegeModeIRQ_TypeDef PrivilegeMode)
{
    uint8_t TmpReg = 0, LevelBits = 0, Level = 0;

    /* Check the parameters. */
    assert_param(IS_CLIC_PRIVILEGE_MODE_IRQ(PrivilegeMode));

    if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_M) {
        TmpReg = (uint8_t)(csr_read(CSR_MINTTHRESH) & CSR_XINTTHRESH_TH_Msk) >> CSR_XINTTHRESH_TH_Pos;
    }
#if (CLIC_PRIVILEGE_MODES >= 2)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_U) {
        TmpReg = (uint8_t)(csr_read(CSR_UINTTHRESH) & CSR_XINTTHRESH_TH_Msk) >> CSR_XINTTHRESH_TH_Pos;
    }
#endif
#if (CLIC_PRIVILEGE_MODES == 3)
    else if (PrivilegeMode == CLIC_PRIVILEGE_MODE_IRQ_S) {
        TmpReg = (uint8_t)(csr_read(CSR_SINTTHRESH) & CSR_XINTTHRESH_TH_Msk) >> CSR_XINTTHRESH_TH_Pos;
    }
#endif

    LevelBits = (CLIC->CFG & CLIC_CFG_NLBITS_Msk) >> CLIC_CFG_NLBITS_Pos;
    Level     = TmpReg >> (8 - LevelBits);

    return Level;
}

/** @} */ /* End of group CORE_CLIC_Exported_Functions */

/** @} */ /* End of group CORE_CLIC */

#endif /* CLIC_PRESENT */

/** @} */ /* End of group CORE_SUPPORT */

/*********************** (C) COPYRIGHT {YYYY} Milandr ****************************
 *
 * END OF FILE core_clic.c */
