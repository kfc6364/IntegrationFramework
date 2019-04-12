/*==================================================================================================

   @file        autosar_intram.ld
   @version     0.8.1

   @brief       GHS Linker Command File for RAM for S32K2XX
   @details     GHS Linker Command File for RAM for S32K2XX
                This file contains sample code only. It is not part of the production code deliverables
====================================================================================================    
   Project      : AUTOSAR 4.3 MCAL
   Platform     : CORTEXM
   Peripheral   : Pit
   Dependencies : none
   
   Autosar Version       : 4.3.1
   Autosar Revision      : ASR_REL_4_3_REV_0001
   Autosar Conf. Variant : 
   Software Version      : 0.8.1
   Build Version         : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420

   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
   All Rights Reserved.

====================================================================================================

Note: This linker command file to be used with S32K2XX device only.
==================================================================================================*/

MEMORY 
{
    /* S32K2XX - 2000_0000	2003_FFFF	256KB PRAM0 */
    /* S32K2XX - 2004_0000	2007_FFFF	256KB PRAM1 */
    /* S32K2XX - 2008_0000	200B_FFFF	256KB PRAM1 */
    int_sram             : org = 0x20000000, len = 0xBEF00    /* 252K - 0x60 - 0x90 - 0x100 */
    int_results          : org = 0x200BEF00, len = 0x100      /* Update also TEST_BASE_ADDR if this address is changed. */
    ram_rsvd2            : org = .,          len = 0
    hse_loop_sec         : org = 0x200BF000, len = 0x10       /* A reserved ram in which the hse core can loop */
}


SECTIONS
{
    .intc_vector                                    : > int_sram
    .startup                                        : > . /* Reset code*/
    .systeminit                                     : > . /* SystemInit */
    .text.startup                                   : > .
    .text                                           : > .
    .acfls_code_rom                        ALIGN(4) : > .
    .aceep_code_rom                        ALIGN(4) : > .
    .acmcu_code_rom                        ALIGN(4) : > .
    .mcal_text                                      : > .
    .ramcode                                    ABS : > .
    .acfls_code_ram                        ALIGN(4) : > .
    .aceep_code_ram                        ALIGN(4) : > .
    .acfls_code_ram_end                             : > .
    .aceep_code_ram_end                             : > .
    
    .rodata                                         : > .
    .mcal_const_cfg                                 : > .
    .mcal_const                                     : > .
    
    .data                                 ALIGN(16) : > .
    .mcal_data                                      : > .
    .mcal_data_no_cacheable                         : > .
    
    .bss                                  ALIGN(16) : > .
    .sbss                                           : > .
    .mcal_bss                                       : > .
    .mcal_bss_no_cacheable                          : > .
     
    .stack_main  ALIGN(16)                          : > .
    
    _Stack_end    = ADDR(.stack_main);
    _Stack_start  = ADDR(.stack_main)+sizeof(.stack_main); 
 
    BOOT_APP_CORE       = ADDR(.intc_vector);
    HSE_LOOP_ADDR       = ADDR(hse_loop_sec);
 
    INT_SRAM_START      = ADDR(int_sram);
    /*INT_SRAM_SIZE       = (ADDR(ram_rsvd2) - ADDR(int_sram))/64; */                    // Init 64 bytes at a time
    INT_SRAM_END        = ADDR(ram_rsvd2);
    
    BSS_SRAM_START      = ADDR(.bss);
    BSS_SRAM_SIZE       = SIZEOF(.bss)+SIZEOF(.sbss)+SIZEOF(.mcal_bss)+SIZEOF(.mcal_bss_no_cacheable);
    BSS_SRAM_END        = BSS_SRAM_START+BSS_SRAM_SIZE;    

    /* Fls module access code support */    
    Fls_ACEraseRomStart         = ADDR(.acfls_code_rom);
    Fls_ACEraseRomEnd           = ADDR(.acfls_code_rom) + SIZEOF(.acfls_code_rom);
    Fls_ACEraseSize             = (SIZEOF(.acfls_code_rom)+3) / 4; /* Copy 4 bytes at a time*/

    Fls_ACWriteRomStart         = ADDR(.acfls_code_rom);
    Fls_ACWriteRomEnd           = ADDR(.acfls_code_rom) + SIZEOF(.acfls_code_rom);
    Fls_ACWriteSize             = (SIZEOF(.acfls_code_rom)+3) / 4; /* Copy 4 bytes at a time*/
    
    _ERASE_FUNC_ADDRESS_        = ADDR(.acfls_code_ram);
    _WRITE_FUNC_ADDRESS_        = ADDR(.acfls_code_ram);
  
    /* Eep module access code support */    
    Eep_ACWriteRomStart         = ADDR(.aceep_code_rom);
    Eep_ACWriteRomEnd           = ADDR(.aceep_code_rom) + SIZEOF(.aceep_code_rom);
    Eep_ACWriteSize             = (SIZEOF(.aceep_code_rom)+3) / 4; /* Copy 4 bytes at a time*/
    
    _WRITE_FUNC_ADDRESS_EEP_    = ADDR(.aceep_code_ram);
}
