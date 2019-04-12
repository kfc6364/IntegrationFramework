#====================================================================================================
#
#    @file        compiler_options.mak
#    @version     0.8.1
#
#    @brief       Integration Framework - Make file used for storing compile and link options
#    @details     This file contains compiler specific options for building the system 
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
PROD_PAT_MCAL = $(TRESOS_DIR)  $(GENERATE_DIR)
PROD_PAT_OS   = $(SSC_ROOT)  $(OS_TRESOS_WORKSPACE_DIR)
PRJFLAG :=-D$(DERIVATIVE)



SUBDERIVATIVE_NAME=-DDERIVATIVE_$(DERIVATIVE)

OBJ_FILE_SUFFIX = o
LIB_FILE_SUFFIX = lib

.SUFFIXES:            # Delete the default suffixes
.SUFFIXES: .c .h .$(OBJ_FILE_SUFFIX) .$(LIB_FILE_SUFFIX)

cpopt      += $(addprefix -I, $(INCLUDE_DIRS)) 
cpopt      += -DSCHM_USE_MACROS

MAPFILE = $(call winpath, $(OUT_DIR)/$(SAMPLE_APP_NAME).map)
EXE_EXT := elf

ifeq ($(ASR_OS_FLAG), AUTOSAR_OS_USED)
        PREPROCESSOR_DEFINES += osclassname apptypesh oscfgname ospropname
        osclassname_KEY      := __CLASS_SC1
        osclassname_VALUE    := 1
        apptypesh_KEY        := APPTYPESH
        apptypesh_VALUE      := "\".\\..\\..\\..\\common\\memory.h\""
        oscfgname_KEY        := OSCFGH
        oscfgname_VALUE      := "<$(projname)_cfg.h>"
        ospropname_KEY       := OSPROPH
        ospropname_VALUE     :="\"$(call remove_slashes,$(OS_PROPHEADER))\""

        #ifeq ($(CC_I),)
        #CC_I := -I
        #endif

        #ifeq ($(CC_D),)
        #CC_D := -D
        #endif

        $(foreach bsw,$(modulelist),\
        $(eval bsw_name=$(call remove_slashes,$($(bsw)_dir)))\
        $(eval $(bsw)_cfg_dir?=cfgno)\
        $(eval PREPROCESSOR_DEFINES += $(bsw) $(bsw_name) $(bsw)_name_string $(bsw)_cfg_id)\
        $(eval $(bsw)_KEY=$(bsw)_integrated)\
        $(eval $(bsw)_VALUE=1)\
        $(eval $(bsw)_name_string_KEY=$(bsw)_name_string)\
        $(eval $(bsw)_name_string_VALUE=$(bsw_name)_string)\
        $(eval $(bsw)_cfg_id_KEY=$(bsw)_cfg_id)\
        $(eval $(bsw)_cfg_id_VALUE=$(call remove_slashes,$($(bsw)_cfg_dir)_id))\
        $(eval $(bsw_name)_KEY=$(bsw_name))\
        $(eval $(bsw_name)_VALUE=1))
endif


ifeq ($(TOOLCHAIN),ghs)
#\/----------------------------------------------------- GREEN HILLS START -----------------------------------------------------\/
    CC             := $(call winpath, $(TOOLCHAIN_DIR)/ccthumb.exe)
    LD             := $(call winpath, $(TOOLCHAIN_DIR)/elxr.exe)
    AS             := $(call winpath, $(TOOLCHAIN_DIR)/ccthumb.exe)

# Compiler paths
    cbin        := $(TOOLCHAIN_DIR)
    cinc        := $(TOOLCHAIN_DIR)/include/arm
    clibinc     := .
    ceabinc     := .
    ceablib     := .

	clib        := $(call winpath, $(TOOLCHAIN_DIR)/lib/thumb2)

# Common Compilers options
    ccopt   :=      $(CCOPT) \
                    -cpu=cortexm7 \
                    $(MISRA) \
                    $(PRJFLAG) \
                    -DGHS \
                   -DAUTOSAR_OS_NOT_USED \
                   $(SUBDERIVATIVE_NAME) \
                   -DEU_DISABLE_ANSILIB_CALLS \
                   -c \
                   -Osize \
                   -Wall\
                   -ansi \
                   -G \
                   -preprocess_assembly_files \
                   --no_exceptions \
                   -dual_debug \
                   --prototype_errors \
                   -Wundef \
                   -noslashcomment \
                   -Wimplicit-int \
                   -Wshadow \
                   -Wtrigraphs \
                   -nostartfile \
                   --no_commons \
                   --incorrect_pragma_warnings \
                   -keeptempfiles \
                   -list \
                   --short_enum \
                   --ghstd=last

# Common Preprocessor options
    cpopt  :=  -I$(cinc) \
               -I$(clib) \
               -I$(clibinc) \
               -I$(ceabinc)


# Common Assembler options
    asopt    :=     $(ASOPT) \
                    -cpu=cortexm7 \
                    -c \
                    -preprocess_assembly_files \
                    -asm=-list


    ldopt   :=      -Mn -delete \
                    -v \
                    -ignore_debug_references \
                    -map \
                    -keepmap \
                    -L$(clib) \
                    -lstartup \
                    -lsys \
                    -larch \
                    -lansi \
                    -lutf8_s32


#OS specific compiler options
    ifeq ($(ASR_OS_FLAG), AUTOSAR_OS_USED)
        proc   :=   -cpu=cortexm4f \
        
        # Compilers' options specific to OS
        ccopt     :=   $(ccopt) \
                       $(proc) \
                       -DOSDISABLE_AUTOSAR_VERSION_CHECK \
                       -fhard \
                       -fpu=vfpv4_d16

        # Preprocessor options specific to OS
        cpopt       +=  -I$(OTHER_INCLUDES) \
                        -I$(SAMPLE_INCLUDES)

        # Assembler options specific to OS
        asopt       +=  -asm=-list \
                        $(proc) \
                        -D__STACK_SIZE=0x800 \
                        -fhard \
                        -fpu=vfpv4_d16

        cpopt       += $(foreach define,$(PREPROCESSOR_DEFINES), -D$($(define)_KEY)=$($(define)_VALUE))

    else
        #processor selection for non OS components
        ifeq ($(DERIVATIVE),S32K118)
            proc   :=  -cpu=cortexm0plus
        else
            proc   :=  -cpu=cortexm4
        endif           

        # Compilers' options specific to Drivers
         ccopt    := $(ccopt) \
                     $(proc) \
                     $(MODEFLAG)
    
         # Compilers' options specific to Drivers
         asopt    := $(asopt) \
                     $(proc) \ 
                     $(MODEFLAG)        
    endif


#/\----------------------------------------------------- GREEN HILLS END -----------------------------------------------------/\

endif
# $(compiler) == ghs


ifeq ($(TOOLCHAIN),iar)
#\/----------------------------------------------------- IAR START -----------------------------------------------------\/
ifeq ($(DERIVATIVE),S32K118)
    clib        := $(call winpath, $(TOOLCHAIN_DIR)/lib/thumb)  
else
    clib        := $(call winpath, $(TOOLCHAIN_DIR)/lib/thumb2)
endif 


CC             := $(call winpath, $(TOOLCHAIN_DIR)/bin/iccarm.exe)
LD             := $(call winpath, $(TOOLCHAIN_DIR)/bin/ilinkarm.exe)
AS             := $(call winpath, $(TOOLCHAIN_DIR)/bin/iasmarm.exe)


# Compiler paths
cbin        := $(TOOLCHAIN_DIR)/bin
cinc        := $(TOOLCHAIN_DIR)/arm/inc/c
clibinc     := $(TOOLCHAIN_DIR)/arm/lib
ceabinc     := .
ceablib     := .

#processor selection for non OS components
ifeq ($(DERIVATIVE),S32K118)
    proc :=   Cortex-M0+
else
    proc :=   Cortex-M4
endif   

# Compilers' options
ccopt       := $(PRJFLAG) \
               -DOSIARARM \
               -DIAR \
               --cpu_mode=thumb \
               --endian=little \
               $(SUBDERIVATIVE_NAME) \
               -D$(ASR_OS_FLAG) \
               --debug \
               --no_clustering \
               --no_mem_idioms \
               --no_explicit_zero_opt \
               -e \
               --no_system_include \
               -c \
               --diag_suppress=Pa050 \
               --no_wrap_diagnostics

asopt       := --cpu_mode thumb \
               -g


ldopt       :=  --entry _start \
                --enable_stack_usage \
                --skip_dynamic_initialization \
                 --no_wrap_diagnostics \
                 -L $(ceablib)
                 

# Preprocessor options
cpopt      :=  -DEU_DISABLE_ANSILIB_CALLS \
               -I$(cinc) \
               -I$(clib) \
               -I$(clibinc) \
               -I$(ceabinc)


               
    #OS specific compiler options
    ifeq ($(ASR_OS_FLAG), AUTOSAR_OS_USED)
        
        # Compilers' options specific to OS
        ccopt     :=   $(ccopt) \
                       --cpu=$(proc) \
                       -DOSDISABLE_AUTOSAR_VERSION_CHECK \
                       -Ohs \
                       --fpu=VFPv4_sp
                
                       
        # Preprocessor options specific to OS
        cpopt       :=  $(cpopt) \
                        -D__STACK_SIZE=0x800 \
                        -I$(OTHER_INCLUDES) \
                        -I$(SAMPLE_INCLUDES)

        # Assembler options specific to OS
        asopt       += --cpu $(proc) \
                        --fpu VFPv4_sp
        
        cpopt       += $(foreach define,$(PREPROCESSOR_DEFINES), -D$($(define)_KEY)=$($(define)_VALUE))

    else    

        # Compilers' options specific to Drivers
         ccopt    := $(ccopt) \
                     --cpu=$(proc) \
                     $(MODEFLAG)

         # Compilers' options specific to Drivers
         asopt    := $(asopt) \
                     --cpu $(proc) \
                     $(MODEFLAG)
    endif
 
    $(shell echo Include path $(cpopt) 1>&2)
#/\----------------------------------------------------- IAR END -----------------------------------------------------/\

endif
# $(compiler) == iar


ifeq ($(TOOLCHAIN),gcc)
#\/----------------------------------------------------- GCC START -----------------------------------------------------\/

CC             := $(call winpath, $(TOOLCHAIN_DIR)/bin/arm-none-eabi-gcc.exe)
LD             := $(call winpath, $(TOOLCHAIN_DIR)/bin/arm-none-eabi-ld.exe)
AS             := $(call winpath, $(TOOLCHAIN_DIR)/bin/arm-none-eabi-gcc.exe)

clib           := $(call winpath, $(TOOLCHAIN_DIR)/arm-none-eabi/newlib/lib/thumb)

# Compiler paths
cbin       := $(TOOLCHAIN_DIR)
cinc       := $(TOOLCHAIN_DIR)/arm-none-eabi/include
clibinc    := .
ceabinc    := .
ceablib    := .

#clib       := $(call winpath, $(TOOLCHAIN_DIR)/arm-none-eabi/newlib/lib/thumb/v7-m)

# Common Compilers options 
ccopt      :=       $(CCOPT) \
                    $(MISRA) \
                    $(PRJFLAG) \
                    -DGCC \
                    -DAUTOSAR_OS_NOT_USED \
                    $(SUBDERIVATIVE_NAME) \
                    -DEU_DISABLE_ANSILIB_CALLS \
                    -c \
                    -Os \
                    -ggdb3 \
                    -mlittle-endian \
                    -mthumb \
                    -fomit-frame-pointer \
                    -msoft-float \
                    -mcpu=cortex-m7 \
                    -fno-common \
                    -Wall \
                    -Wextra \
                    -Wstrict-prototypes \
                    -Wno-sign-compare \
                    -fstack-usage \
                    -fdump-ipa-all \
                    -Werror=implicit-function-declaration

# Common Preprocessor options				
cpopt  :=    -I$(cinc) \
             -I$(clib) \
             -I$(clibinc) \
             -I$(ceabinc)

# Common Assembler options
asopt  :=    $(ASOPT_CORE) \
             -c \
             -mthumb \
             -mcpu=cortex-m7 \
             -x assembler-with-cpp

ldopt  := 
               
#OS specific compiler options           
ifeq ($(ASR_OS_FLAG), AUTOSAR_OS_USED)
        proc :=   -mcpu=cortex-m4
    
        # Compilers' options
        ccopt  :=   $(ccopt) \
                    $(proc) \
                    -DOSDISABLE_AUTOSAR_VERSION_CHECK \
                    -O1 \
                    -msoft-float \
                    -mfloat-abi=softfp \
                    -mfpu=fpv4-sp-d16

        asopt  :=   $(asopt) \
                    $(proc) \
                    -D__STACK_SIZE=0x800 \
                    -mfloat-abi=softfp  \
                    -mfpu=fpv4-sp-d16
                    
        ldopt  :=   $(ldopt) \
                    -msoft-float \
                    $(proc)
else  

#        ifeq ($(DERIVATIVE),S32K118)
#            proc :=   -mcpu=cortex-m0    
#        else
#            proc :=   -mcpu=cortex-m4    
#        endif
    
        ccopt   :=  $(ccopt) \
                    $(proc) \
                    -Os \
                    $(MODEFLAG) \
                    #-msoft-float \
                    -mfloat-abi=soft \
                    -fdump-ipa-all \
                    -fstack-usage \
                    -lc

         asopt  :=  $(asopt) \
                    $(proc) \
                    $(MODEFLAG)
                     
                     
         ldopt  :=  $(ldopt) \
                    $(proc) \
                    #-msoft-float \
                    -u _printf_float \
                    -u _scanf_float

endif


#/\----------------------------------------------------- GCC END -----------------------------------------------------/\

endif
# $(compiler) == gcc
