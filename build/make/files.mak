#====================================================================================================
#
#    @file        files.mak
#    @version     0.8.1
#
#    @brief       Integration Framework - files to be build for the current application.
#    @details     List of files to be built for the Leds Sample Application.
#
#    Platform        : CORTEXM
#    Build Version   : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
#
#   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
#       Copyright 2017 - 2018 NXP
#       All Rights Reserved.
#
#    This file contains sample code only. It is not part of the production code deliverables.
#
#====================================================================================================
#

################################################################################
# List of all source directories (test, dependency, and generated .c files)
################################################################################
# specify modules which will be compiled and linked
MODULES_MAK_FILE := $(GENERATE_DIR)/Modules.mak

# Including local configuration file
-include  $(MODULES_MAK_FILE)


# paths for building installed plugins
SRC_DIRS    +=  $(GENERATE_DIR)/src \
                $(foreach mod,$(MCAL_MODULE_LIST),$(PLUGINS_DIR)/$(mod)_$(AR_PKG_NAME)/src) \
                $(foreach swc_comp,$(APP_SWC_LIST),$(PLUGINS_DIR)/$(SAMPLE_APP_NAME)_$(AR_PKG_NAME)/src/swc/$(swc_comp)) \
                $(foreach bsw_comp,$(APP_BSW_LIST),$(PLUGINS_DIR)/$(SAMPLE_APP_NAME)_$(AR_PKG_NAME)/src/bsw/$(bsw_comp))

################################################################################
# List of all include directories (test, dependency, and generated .h files)
################################################################################
#
INCLUDE_DIRS+=      $(GENERATE_DIR)/include \
                    $(foreach mod,$(MCAL_MODULE_LIST),$(PLUGINS_DIR)/$(mod)_$(AR_PKG_NAME)/include) \
                    $(foreach swc_comp,$(APP_SWC_LIST),$(PLUGINS_DIR)/$(SAMPLE_APP_NAME)_$(AR_PKG_NAME)/include/swc/$(swc_comp)) \
                    $(foreach bsw_comp,$(APP_BSW_LIST),$(PLUGINS_DIR)/$(SAMPLE_APP_NAME)_$(AR_PKG_NAME)/include/bsw/$(bsw_comp))

                    
ifneq ($(ANFC_CONFIG_DIR),)
ifneq ($(ANFC_CONFIG_DIR),$(TRESOS_WORKSPACE_DIR))
INCLUDE_DIRS+=$(ANFC_CONFIG_DIR)/include
SRC_DIRS+=$(ANFC_CONFIG_DIR)/src
endif
endif
################################################################################
# Additional test specific C compiler options
################################################################################
CCOPT           +=

################################################################################
# Additional test specific linker options
################################################################################
LDOPT           +=

################################################################################
# Custom libraries
################################################################################
LIBS            +=

################################################################################
# Path to the linker definition file
################################################################################
ifeq ($(ASR_OS_FLAG), AUTOSAR_OS_USED)
    LINKER_DEFS_GHS_FLASH     :=    $(LINKCMD_DEV_DIR)/autosar_flash_os.ld
    LINKER_DEFS_LINARO_FLASH  :=    $(LINKCMD_DEV_DIR)/autosar_flash_os.gld
    LINKER_DEFS_IAR_FLASH     :=    $(LINKCMD_DEV_DIR)/autosar_flash_os.icf
else
    LINKER_DEFS_GHS_FLASH     :=    $(LINKCMD_DEV_DIR)/autosar_flash.ld
    LINKER_DEFS_GHS_RAM       :=    $(LINKCMD_DEV_DIR)/autosar_intram.ld
    LINKER_DEFS_LINARO_FLASH  :=    $(LINKCMD_DEV_DIR)/autosar_flash.gld
    LINKER_DEFS_LINARO_RAM    :=    $(LINKCMD_DEV_DIR)/autosar_intram.gld
    LINKER_DEFS_IAR_FLASH     :=    $(LINKCMD_DEV_DIR)/autosar_flash.icf
    LINKER_DEFS_IAR_RAM       :=    $(LINKCMD_DEV_DIR)/autosar_intram.icf
endif
  
ifeq ($(TOOLCHAIN),ghs)
    LINKER_DEFS      :=    $(LINKER_DEFS_GHS_FLASH)
else
    ifeq ($(TOOLCHAIN),gcc)
        LINKER_DEFS      :=    $(LINKER_DEFS_LINARO_FLASH)
    else
        LINKER_DEFS      :=    $(LINKER_DEFS_IAR_FLASH)    
    endif
endif

################################################################################
# Add Platform specific statup and vector files
################################################################################

SRC_FILES       +=  $(DEV_DIR)/src/main.c

INCLUDE_DIRS        +=  $(DEV_STARTUP_INC)                    

#include services source files and header folders to build system
SRC_FILES += $(DEV_SERVICES_SRC)/string/StringLib.c
INCLUDE_DIRS    +=  $(DEV_SERVICES_INC)/string

ifeq ($(ASR_OS_FLAG), AUTOSAR_OS_USED)
    CC_FILES_TO_BUILD += $(wildcard $(OS_SRC_PATH)/*.c)
    INCLUDE_DIRS    +=  $(OS_INC_PATH)
    INCLUDE_DIRS    +=  $(HWSPEC_INC)
    INCLUDE_DIRS    +=  $(OS_GEN_PATH)

    CC_FILES_TO_BUILD += $(wildcard $(OS_SRC_PATH)/*.c)
    CC_FILES_TO_BUILD += $(HWSPEC_SRC)/SystemInit.c

#$(shell echo config file startup dir $(abspath $(HWSPEC_INC))  1>&2)
    CC_FILES_FOR_COMPILER := $(wildcard $(HWSPEC_SRC)/$(ACTIVE_TOOL)/*.c)

    ASM_FILES_FOR_COMPILER := $(wildcard $(HWSPEC_SRC)/$(ACTIVE_TOOL)/*.s)
    ASM_FILES_FOR_COMPILER += $(wildcard $(HWSPEC_SRC)/$(ACTIVE_TOOL)/*.asm)

    CC_FILES_TO_BUILD  += $(CC_FILES_FOR_COMPILER)
    CC_FILES_TO_BUILD  += $(wildcard $(OS_GEN_PATH)/*.c)
    
    OS_PROPHEADER   := $(OS_GEN_PATH)/osprop.h
    
    ifeq ($(TOOLCHAIN_DIR),iararm)
    ASM_FILES_FOR_COMPILER += $(wildcard $(OS_SRC_PATH)/*.s)
    endif    
    
    ASM_FILES_TO_BUILD += $(ASM_FILES_FOR_COMPILER)    
    
    
    SRC_DIRS  += $(dir $(CC_FILES_TO_BUILD))    
    SRC_FILES += $(CC_FILES_TO_BUILD) 
    SRC_FILES += $(ASM_FILES_TO_BUILD)

else
    SRC_STARTUP_FILES   +=  $(DEV_STARTUP_SRC)/sys_init.c
                  
$(shell echo CORE  is $(CORE) 1>&2)
ifeq ($(CORE_SET),m7)                    
    SRC_STARTUP_FILES   +=  $(DEV_STARTUP_SRC)/nvic.c
endif 

ifeq ($(CORE_SET),a53)                    
    SRC_STARTUP_FILES   +=  $(DEV_STARTUP_SRC)/gic400.c
endif 

ifeq ($(CORE_SET),r52)                    
    SRC_STARTUP_FILES   +=  $(DEV_STARTUP_SRC)/gic400.c
endif 

ifeq ($(CORE_SET),m7)                    
    ifeq ($(TOOLCHAIN),iar)
       SRC_STARTUP_FILES   += $(DEV_STARTUP_SRC)/m7/exceptions_iar.c    
    else
        SRC_STARTUP_FILES    += $(DEV_STARTUP_SRC)/m7/exceptions.c
    endif                    
            
    ifeq ($(TOOLCHAIN),iar)
        SRC_STARTUP_FILES       += $(DEV_STARTUP_SRC)/m7/Startup_iar.s
    else
        SRC_STARTUP_FILES       += $(DEV_STARTUP_SRC)/m7/Startup.s
    endif                    

    ifeq ($(TOOLCHAIN),iar)
          SRC_STARTUP_FILES       += $(DEV_STARTUP_SRC)/m7/Vector_core_iar.s
    else
          SRC_STARTUP_FILES       += $(DEV_STARTUP_SRC)/m7/Vector_core.s
    endif
endif    

ifeq ($(CORE_SET),r52)                    
   
    SRC_STARTUP_FILES   +=  $(DEV_STARTUP_SRC)/r52/Exception_Handlers.c    
                       
            
    ifeq ($(TOOLCHAIN),gcc)
        SRC_STARTUP_FILES       += $(DEV_STARTUP_SRC)/r52/Startup_gcc.s
    else
        SRC_STARTUP_FILES       += $(DEV_STARTUP_SRC)/r52/Startup.s
    endif                    

    ifeq ($(TOOLCHAIN),gcc)
          SRC_STATUP_FILES       += $(DEV_STARTUP_SRC)/r52/Vector_gcc.s
    else
          SRC_STARTUP_FILES      += $(DEV_STARTUP_SRC)/r52/Vector_ghs.s
    endif
endif    

INCLUDE_DIRS    +=  $(SRC_STATUP_FILES)/include/

    SRC_FILES +=  $(SRC_STARTUP_FILES)	

ifeq ($(TOOLCHAIN),iar)
    INCLUDE_DIRS    +=  $(TOOLCHAIN_DIR)/inc/c/
endif



ifeq ($(USER_CODE_FALG), USER_CODE_USED)
#      $(shell echo added to include headers $(USER_CODE_DIR) 1>&2)
      INCLUDE_DIRS  += $(USER_CODE_DIR)
      SRC_FILES += $(foreach DIR, $(USER_CODE_DIR), $(wildcard $(DIR)/*.c))
endif
endif
