::====================================================================================================
::
::    @file                launch.bat
::    @version             0.8.1
::
::    @brief               Integration Framework - internal build launcher.
::    @details             Launches the build of the sample application
::
::    Platform      :      CORTEXM
::    Build Version :      S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
::
::   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
::       Copyright 2017 - 2018 NXP
::       All Rights Reserved.
::
::    This file contains sample code only. It is not part of the production code deliverables.
::
::====================================================================================================
::

@echo off

::You have to uncomment and set the following variables if they are not already set
:: uncomment line below if you do not set TRESOS_DIR over environment
::TRESOS
::SET TRESOS_DIR=C:/tools/Tresos_25_0_0
SET TRESOS_DIR=C:/EB/tresos
::MAKE
SET MAKE_DIR=C:/GnuWin32
::SET MAKE_DIR=C:/cygwin64
::SET MAKE_DIR=C:/NXP/S32DS.2018.R1/utils/msys32/usr
::GHS
::SET GHS_DIR=C:/ghs/comp_201854
::SET GHS_DIR=C:/NXP/S32DS.2018.R1/Cross_Tools/gcc-6.3-arm32-eabi
::IAR
::SET IAR_DIR=C:/Tools/IAR/ARM_7.40.7/arm
::GCC
::SET LINARO_DIR=C:/NXP/S32DS.2018.R1/Cross_Tools/gcc-6.3-arm32-eabi
SET LINARO_DIR=C:/NXP/S32DS.2018.R1/Cross_Tools/gcc-6.3-arm32-eabi
::IAR
::SET IAR_DIR=C:/_ProjectTools/IAR/EmbeddedWorkbench75/arm
::Path to the plugins folder
SET PLUGINS_DIR=C:/NXP/AUTOSAR/S32K2XX_MCAL4_3_EAR_0_8_1/eclipse/plugins
::SSC             
::SET SSC_ROOT=C:/NXP/AUTOSAR/S32K_AUTOSAR_OS_4_0_93_BETA_0_9_0

::CORE             
::SET CORE=m7
::SSC             
::SET TRESOS_WORKSPACE_DIR=C:/NXP/AUTOSAR/S32K2XX_MCAL4_3_EAR_0_8_1/S32K2XX_MCAL4_3_EAR_0_8_1_Sample_Application/Tresos/Workspace/lightning_s32K2XX_4.3_EAR0.8.1/output/generated/
SET TRESOS_WORKSPACE_DIR=C:/EB/tresos/workspace/lightning_s32K2XX_4.3_EAR0.8.1/output/generated
                               
if not defined TRESOS_DIR GOTO missing_path_names_TRESOS_DIR
if not exist %TRESOS_DIR% GOTO missing_path_names_TRESOS_DIR

cmd /c "make.bat %1 %2 %3 %4 %5 %6"

GOTO end

:: The variable TRESOS_DIR was not specified
:missing_path_names_TRESOS_DIR
ECHO.
ECHO    The variable TRESOS_DIR was not set correctly.
ECHO    Please specify this variable manually, by editing
ECHO    the batch file 'launch.bat'.
ECHO.
pause
GOTO end

:end