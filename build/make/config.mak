#====================================================================================================
#
#    @file        config.mak
#    @version     0.8.1
#
#    @brief       Integration Framework - Build configuration file
#    @details     This file contains specific macro's for make system
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
# Setup default paths and settings if local_config.mak not defined
################################################################################

################################################################################
# Disable error logging by default
################################################################################
ifeq ($(strip $(BUILD_LOG)),)
BUILD_LOG = None
endif

################################################################################
# Setup development directory
################################################################################
DEV_DIR := ../$(ROOT_DIR)

################################################################################
# Path to the root directory of development structure
################################################################################
BUILD_DIR := $(DEV_DIR)/build

################################################################################
# Setup internal directories
################################################################################
MAKE_DEV_DIR := $(BUILD_DIR)/make
LINKCMD_DEV_DIR := $(BUILD_DIR)/linkfiles
GENERATE_DIR      := $(TRESOS_WORKSPACE_DIR)

################################################################################
# Setup startup and services directories
################################################################################
DEV_STARTUP_SRC   :=  $(DEV_DIR)/src/startup
DEV_STARTUP_INC   :=  $(DEV_DIR)/include/startup

DEV_SERVICES_SRC  :=  $(DEV_DIR)/src/services
DEV_SERVICES_INC  :=  $(DEV_DIR)/include/services

#$(shell echo config file make dir $(abspath $(MAKE_DEV_DIR))  1>&2)
#$(shell echo config file dev dir $(abspath $(DEV_DIR)) 1>&2)
#$(shell echo config file startup dir $(abspath $(DEV_STARTUP_SRC))  1>&2)


include $(GENERATE_DIR)/specific_config.mak
################################################################################
# Setup default paths and settings if local_config.mak not defined
################################################################################

################################################################################
# OS Configuration
################################################################################
ifeq ($(ASR_OS_FLAG), AUTOSAR_OS_USED)
    # Source paths
    OS_DIR      := $(SSC_ROOT)/ssc
	#_OS_SG_PATH := bin\generator
    OS_SRC_PATH := $(OS_DIR)/src
    OS_INC_PATH := $(OS_DIR)/inc

	# SysGen tool path
    OS_GEN_PATH := $(OS_TRESOS_WORKSPACE_DIR)

    HWSPEC_SRC          := $(DEV_STARTUP_SRC)/hwspec
    HWSPEC_INC          := $(DEV_STARTUP_INC)/hwspec
    OTHER_INCLUDES  := $(SSC_ROOT)/ssc/other_includes
endif



################################################################################
# Disable error logging by default
################################################################################
ifeq ($(strip $(BUILD_LOG)),)
BUILD_LOG = None
endif

################################################################################
# Compiler used (default is GHS)
################################################################################
ifeq ($(TOOLCHAIN),)
# GHS used
TOOLCHAIN := gcc
endif

################################################################################
# Module version information (this numbering is module vendor specific, and it
# is recommended to follow these rules: update SW_VERSION_MAJOR in case of major
# change of module, update SW_VERSION_MINOR in case of minor change of module,
# update SW_VERSION_PATCH in case of bug-fix of module
################################################################################
SW_VERSION_MAJOR = 0
SW_VERSION_MINOR = 8
SW_VERSION_PATCH = 1


################################################################################
# AUTOSAR package name (i.e. tresos plugin name: TS_T11D3M2I0R0, etc.)
# - use the "M" section for coding major and minor version number
# - use "I" section for coding the patch number, this can contain 1 or more digits.
# - major version number will be left out, if it is "0", in this case the "M" section contains 1 digit only, otherwise it contains 2 digits
################################################################################
ifeq ($(SW_VERSION_MAJOR),0)
    AR_PKG_NAME = TS_T$(TRESOS_TARGET_ID)D$(TRESOS_DERIVATIVE_ID)M$(SW_VERSION_MINOR)I$(SW_VERSION_PATCH)R0
else
    AR_PKG_NAME = TS_T$(TRESOS_TARGET_ID)D$(TRESOS_DERIVATIVE_ID)M$(SW_VERSION_MAJOR)$(SW_VERSION_MINOR)I$(SW_VERSION_PATCH)R0
endif


################################################################################
# MCU family name (S12X, MPC etc.)
################################################################################
MCU_FAMILY = CORTEXM

BUILD_SOURCE=Plugin
TOOLCHAIN_VERSION=OFF


