/**
 *******************************************************************************
 * @file    link_FLASH.ld
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    09/11/2023
 * @brief   Linker script file for MDR1206.
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

/* It defines following symbols, which code can use without definition:
 *   __data_load_start
 *   __data_start
 *   __sdata_start
 *   __data_end
 *   __bss_start
 *   __bss_end
 *   __global_pointer$
 *   __end
 *   __ahbram_data_load_start
 *   __ahbram_data_start
 *   __ahbram_data_end
 *   __ahbram_bss_start
 *   __ahbram_bss_end
 *   __text_load_start
 *   __text_start
 *   __text_end
 *   __ramfunc_load_start
 *   __ramfunc_start
 *   __ramfunc_end
 *   __stack_top
 *   __stack_size
 *   __stack_limit
 *   __heap_top
 *   __heap_min_size
 *   __heap_size
 *   __heap_limit
 */

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

/* __stack_size - total stack size */
__stack_size    = 0x1000;
/* __heap_min_size - minimum heap size, used to check if space can be allocated. The total heap size (__heap_size) takes up all space from end of the .bss to beginning of .stack */
__heap_min_size = 0x1000;

/* Specify the memory areas */
MEMORY
{
    BOOT      (rx)      : ORIGIN = 0x00020000, LENGTH = 15K
    FLASH     (rx)      : ORIGIN = 0x10000000, LENGTH = 256K
    RAM_TCMA  (xrw)     : ORIGIN = 0x80000000, LENGTH = 64K
    RAM_TCMB  (xrw)     : ORIGIN = 0x80010000, LENGTH = 32K
    RAM_AHB   (xrw)     : ORIGIN = 0x20000000, LENGTH = 16K
}

/* Description of regions:
- REGION_LOAD       - region where the program is stored
- REGION_TEXT       - region where the code is located
- REGION_DATA       - region where initialized and uninitialized data, stack and heap are located
- REGION_RAMFUNC    - the region of RAM TCM where the code is stored */

/* ----------------------- */
/* LOAD AND RUN FROM FLASH */
/* ----------------------- */

REGION_ALIAS("REGION_LOAD",       FLASH);
REGION_ALIAS("REGION_TEXT",       FLASH);
REGION_ALIAS("REGION_DATA",       RAM_TCMA);
REGION_ALIAS("REGION_RAMFUNC",    RAM_TCMB);


/* ------------------------- */
/* LOAD AND RUN FROM RAM TCM */
/* ------------------------- */
/*
REGION_ALIAS("REGION_LOAD",       RAM_TCMA);
REGION_ALIAS("REGION_TEXT",       RAM_TCMA);
REGION_ALIAS("REGION_DATA",       RAM_TCMA);
REGION_ALIAS("REGION_RAMFUNC",    RAM_TCMB);
*/

/* ------------------------- */
/* LOAD AND RUN FROM RAM AHB */
/* ------------------------- */
/*
REGION_ALIAS("REGION_LOAD",       RAM_AHB);
REGION_ALIAS("REGION_TEXT",       RAM_AHB);
REGION_ALIAS("REGION_DATA",       RAM_TCMA);
REGION_ALIAS("REGION_RAMFUNC",    RAM_TCMB);
*/

/* ------------------------------------------ */
/* LOAD FROM FLASH TO RAM TCM, RUN IN RAM TCM */
/* ------------------------------------------ */
/*
REGION_ALIAS("REGION_LOAD",       FLASH);
REGION_ALIAS("REGION_TEXT",       RAM_TCMA);
REGION_ALIAS("REGION_DATA",       RAM_TCMA);
REGION_ALIAS("REGION_RAMFUNC",    RAM_TCMB);
*/

/* ------------------------------------------ */
/* LOAD FROM FLASH TO RAM AHB, RUN IN RAM AHB */
/* ------------------------------------------ */
/*
REGION_ALIAS("REGION_LOAD",       FLASH);
REGION_ALIAS("REGION_TEXT",       RAM_AHB);
REGION_ALIAS("REGION_DATA",       RAM_TCMA);
REGION_ALIAS("REGION_RAMFUNC",    RAM_TCMB);
*/

/* Define output sections */
/* ">vma_region" - VMA (virtual memory address),
   "AT>lma_region" - LMA (load memory address) */

SECTIONS
{
  .boot :
    {
        *(.boot)
        KEEP(*(.boot));
        //. = ALIGN(4);
        //__boot_end = .;
    } >BOOT AT>BOOT

    /* The startup code goes first into REGION_LOAD */
    .text.init :
    {
        *(.text.init)
        . = ALIGN(4);
    } >REGION_LOAD

    /* Alignment of the following section .text */
    .lalign :
    {
        . = ALIGN(4);
    } >REGION_LOAD

    /* The program code and other data goes into REGION_TEXT, load from REGION_LOAD */
    __text_load_start = LOADADDR(.text);
    .text :
    {
        . = ALIGN(4);
        __text_start = .;
        *(.text*)
        . = ALIGN(4);
        __text_end = .;
    } >REGION_TEXT AT>REGION_LOAD

    /* Alignment of the following section */
    .ralign :
    {
        . = ALIGN(4);
    } >REGION_DATA AT>REGION_LOAD

    /* Read-only data goes into REGION_LOAD */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata*)
        *(.srodata*)
    } >REGION_LOAD AT>REGION_LOAD

    /* Alignment of the following section .data */
    .dalign :
    {
        . = ALIGN(4);
    } >REGION_DATA AT>REGION_LOAD

    /* Initialized data sections goes into REGION_DATA, load from REGION_LOAD */
    __data_load_start = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        __data_start = .;
        *(.data*)
        . = ALIGN(8);
        __sdata_start = .;
        *(.sdata*)
    } >REGION_DATA AT>REGION_LOAD

    . = ALIGN(4);
    __data_end = .;

    /* Uninitialized data section goes into REGION_DATA*/
    .bss :
    {
        . = ALIGN(8);
        __bss_start = .; 
        *(.sbss*)
        *(.scommon)
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        __bss_end = .;
        /* The linker uses the __global_pointer$ symbol definition to compare the memory addresses and,
           if within range, it replaces absolute/pc-relative addressing with gp-relative addressing,
           which makes the code more efficient. */
        __global_pointer$ = MIN(__sdata_start + 0x800, MAX(__data_start + 0x800, __bss_end - 0x800));
    } >REGION_DATA AT>REGION_DATA

    . = ALIGN(8);
    __end = .;

    /* Alignment of the following section .ahbram */
    .aalign :
    {
        . = ALIGN(4);
    } >REGION_LOAD

    /* RAM_AHB section */
    /* Initialized ahbram_data section goes into RAM_AHB, load from REGION_LOAD */
    __ahbram_data_load_start = LOADADDR(.ahbram_data);
    .ahbram_data :
    {
        . = ALIGN(4);
        __ahbram_data_start = .;
        *(.ahbram_data)
        . = ALIGN(4);
        __ahbram_data_end = .;
    } >RAM_AHB AT>REGION_LOAD

    .ahbram_bss :
    {
        . = ALIGN(4);
        __ahbram_bss_start = .;
        *(.ahbram_bss)
        . = ALIGN(4);
        __ahbram_bss_end = .;
    } >RAM_AHB AT>RAM_AHB

    /* Alignment of the following section .ramfunc */
    .ralign :
    {
        . = ALIGN(4);
    } >REGION_LOAD

    /* RAM functions goes into REGION_RAMFUNC, loaded from REGION_LOAD */
    __ramfunc_load_start = LOADADDR(.ramfunc);
    .ramfunc :
    {
        . = ALIGN(4);
        __ramfunc_start = .;
        *(.ramfunc*)
    } >REGION_RAMFUNC AT>REGION_LOAD

    . = ALIGN(4);   
    __ramfunc_end = .;

      /* Stack and Heap symbol definitions */
      __stack_top = ORIGIN(REGION_DATA) + LENGTH(REGION_DATA);
      __stack_limit = __stack_top - __stack_size;
      __heap_top = __end;
      __heap_size = __stack_limit - __heap_top;
      __heap_limit = __heap_top + __heap_size;

    /* Check allocation for heap of size __heap_min_size */
    ASSERT(__heap_size >= __heap_min_size, "Unable to allocate __heap_min_size for heap!")

    /* .heap section doesn't contains any symbols. 
     It is only used for linker to calculate size of heap sections, and assign values to heap symbols */
    .heap __heap_top :
    {
        . += __heap_size;
    } >REGION_DATA

    /* .stack section doesn't contains any symbols. 
     It is only used for linker to calculate size of stack sections, and assign values to stack symbols */
    .stack __stack_limit :
    {
        . += __stack_size;
    } >REGION_DATA
}