#====================================================================================================
#
#    @file        specific_config.mak
#    @version     0.8.1
#
#    @brief       Integration Framework - Specific tools and make commands file
#    @details     This file contains specific command for make system ('delete' file command)
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
[!NOCODE!]
[!CODE!]
################################################################################
# Tresos target ID (see the Encoding of Architecture and Derivative document for details)
# Target    Manufacturer    Architecture ID ("T")
#   PA      Freescale       2
################################################################################
TRESOS_TARGET_ID=40

################################################################################
# Tresos derivative ID (see the Encoding of Architecture and Derivative document for details)
#   Derivative ID ("D")
#       13          14          11           15          17
#    XPC560XB    XPC563XM    XPC560XP     XPC560XS     XPC56XXL
#    (Bolero)    (Monaco)    (Pictus)    (Spectrum)   (Leopard)
################################################################################
TRESOS_DERIVATIVE_ID=17
[!ENDCODE!]
[!SELECT "CommonPublishedInformation"!]
[!CODE!]
################################################################################
# Release type
################################################################################
[!ENDCODE!]
MCAL_MODULE_LIST :=  [!//
[!IF "SwMajorVersion  >= '1'"!]
   [!CODE!] 
SW_VERSION_SUFFIX = RTM[!//
   [!ENDCODE!]
[!ELSE!] 
    [!IF "SwMinorVersion    >= '9'"!]
        [!CODE!] 
SW_VERSION_SUFFIX = BETA[!//
        [!ENDCODE!] 
    [!ELSE!]
        [!CODE!] 
SW_VERSION_SUFFIX = EAR[!//
        [!ENDCODE!]     
   [!ENDIF!]
[!ENDIF!]
[!ENDSELECT!]
[!CODE!]
################################################################################
# Platform, derivative, package
################################################################################
ifeq ($(DERIVATIVE),)
DERIVATIVE := S32K2XX
endif
PLATFORM := S32K2XX

$(shell echo Running for $(DERIVATIVE) derivative, on $(PLATFORM) platform 1>&2)

################################################################################
# MCU derivative name (s12xep100, 5516 etc.) Used in pathname to product specific files.
################################################################################
MCU_DERIVATIVE = S32K2XX

################################################################################
# AUTOSAR OF FLAG
################################################################################
ASR_OS_FLAG = [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/UseAutosarOS) = 'true'"!] AUTOSAR_OS_USED[!ELSE!] AUTOSAR_OS_NOT_USED [!ENDIF!]

USER_CODE_FALG =  [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/EnableUserCode) = 'true'"!] USER_CODE_USED[!ELSE!] USER_CODE_NOT_USED [!ENDIF!]
[!ENDCODE!]
[!ENDNOCODE!]
