#====================================================================================================
#
#    @file        Makefile
#    @version     0.8.1
#
#    @brief       Integration Framework - Internal build application Makefile.
#    @details     File used to build the the framework application.
#
#===================================================================================================
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
# Command separator
################################################################################
#
	# running on windows command prompt
	COMMAND_SEPARATOR = &&
	COMMAND_INTERPRETER = cmd

################################################################################
# Path to the root directory of the project
################################################################################
ifeq ($(ROOT_DIR),)
ROOT_DIR :=  .
endif

#
################################################################################
# Load and check the configuration
################################################################################
CFG_MAK_FILE := $(ROOT_DIR)/make/config.mak
#
#
# Including local configuration file
#
-include $(CFG_MAK_FILE)

# Check the dev dir


$(shell echo makefile root  dir  $(abspath $(ROOT_DIR))  1>&2)
#
# Including cygwin environment tools (absolute paths)
#
-include := $(MAKE_DEV_DIR)/tools.mak


# Check the dev dir
ifeq ($(strip $(DEV_DIR)),)
$(error Development directory path (DEV_DIR) is empty)
endif


#current_dir = $(shell pwd)


# Check the Build dir
ifeq ($(strip $(BUILD_DIR)),)
$(error Build directory path (BUILD_DIR) is empty)
endif

# Check the AUTOSAR package name
ifeq ($(strip $(AR_PKG_NAME)),)
$(error AUTOSAR package name (AR_PKG_NAME) is empty)
endif

# Check the device name
ifeq ($(strip $(DERIVATIVE)),)
$(error Device name (DERIVATIVE) is empty)
endif

# Check the platform name
ifeq ($(strip $(PLATFORM)),)
$(error Device name (PLATFORM) is empty)
endif

# Check the toolchain name
ifeq ($(strip $(TOOLCHAIN)),)
$(error Toolchain name (TOOLCHAIN) is empty)
endif


ifeq ($(TOOLCHAIN),ghs)
    ifeq ($(GHS_DIR),)
    $(error Toolchain name GHS_DIR is empty)
    endif
    TOOLCHAIN_DIR := $(GHS_DIR)
    ACTIVE_TOOL := ghsarm
endif

ifeq ($(TOOLCHAIN),iar)
    ifeq ($(IAR_DIR),)
    $(error Toolchain name IAR_DIR is empty)
    endif
    TOOLCHAIN_DIR := $(IAR_DIR)
    ACTIVE_TOOL := iararm
endif
	
ifeq ($(TOOLCHAIN),gcc)
    ifeq ($(LINARO_DIR),)
    $(error Toolchain name GCC_DIR is empty)
    endif
    TOOLCHAIN_DIR := $(LINARO_DIR)
    ACTIVE_TOOL := gccarm
endif

# Check the Toolchain dir
ifeq ($(strip $(TOOLCHAIN_DIR)),)
$(error TOOLCHAIN directory path $(TOOLCHAIN_DIR) is empty)
endif
#
# Check the dev dir
ifeq ($(strip $(GENERATE_CMD)),)
GENERATE_CMD = generate
endif

# Check log file
ifeq ($(strip $(BUILD_LOG)),)
BUILD_LOG = build.log
$(shell echo Using default BUILD_LOG: $(BUILD_LOG). Other options - file_name or None 1>&2)
endif

ifneq ($(strip $(BUILD_LOG)),None)
CAPTURE_OUTPUT = 2>&1 | $(TEE) -a $(OUT_DIR)/$(BUILD_LOG); \
if test ! "$${PIPESTATUS[0]}" -eq 0 ; then  \
 $(ECHO) ERROR: Build of $(SAMPLE_APP_NAME) has failed >>$(OUT_DIR)/$(BUILD_LOG); \
 $(DO_BEFORE_BUILD_FAIL) \
 exit 1; fi;
else
CAPTURE_OUTPUT :=
endif

# Flags used for M4 and compiler to define macros from CMD line
ifeq ($(MODE),)
#enable supervisor mode
USED_RUNMODE = SUPR
DEFINE_FLAG_SPECIFIC := -DMCAL_ENABLE_SUPERVISOR_MODE
endif

ifeq ($(MODE),USER)
    USED_RUNMODE =  USER
    DEFINE_FLAG_SPECIFIC:= -DMCAL_ENABLE_USER_MODE_SUPPORT
     $(shell echo Using runmode USER 1>&2)
else
    USED_RUNMODE =  SUPR 
    DEFINE_FLAG_SPECIFIC := -DMCAL_ENABLE_SUPERVISOR_MODE
    $(shell echo Using runmode SUPERVISOR 1>&2)
endif

# Flags used for M4 and compiler to define macros from CMD line
ifeq ($(CORE),)
CORE_SET=m7
else
CORE_SET:=$(CORE)
endif

$(shell echo building for core $(CORE_SET) 1>&2)

################################################################################
# Path conversion utilities
################################################################################
winpath = $(patsubst /cygdrive/$(word 2,$(subst /, , $(1)))%,$(word 2,$(subst /, ,$(1))):%,$(1))
cygpath = $(if $(findstring :,$(1)),/cygdrive/$(subst :,,$(1)),$(1))
cmdpath = $(subst /,\,$(1))

AR_PKG_REG_EXP		:= "TS_T[0-9]\{1,2\}D[0-9]\{1,2\}M[0-9]\{1,2\}I[0-9]\{1,2\}R[0-9]\{1,2\}"


ifeq ($(PLUGINS_DIR),)
	PLUGINS_DIR		:= $(TRESOS_DIR)/plugins
endif

################################################################################
# Builder specific options defined in the included make
#
#	CC; LD; AS ... 			generators
#	CCOPT; LDOPT; ASOPT		their options
#	LIBS; INCLUDE_DIRS; SRC_FILES	system libs, inlude dirs, and sourceinclude files
#
#	EXE_EXT				test file extentions
#	COMPILE_C_FILE			macro called for "C -> OBJ" rule
#	COMPILE_S_FILE			macro called for "S -> OBJ" rule (could be blank)
#	LINK_O_FILES			macro called for "OBJ -> $(EXE_EXT)" rule
#
################################################################################
# Include the sample specification make file
include $(MAKE_DEV_DIR)/files.mak

#include general compiler options options
include  $(MAKE_DEV_DIR)/compiler_options.mak


################################################################################
# Add Non-OS Options
################################################################################


OUT_DIR			= $(BUILD_DIR)/bin


ifneq ($(strip $(BUILD_LOG)),None)
CAPTURE_OUTPUT = 2>&1 | $(TEE) -a $(OUT_DIR)/$(BUILD_LOG); \
if test ! "$${PIPESTATUS[0]}" -eq 0 ; then  \
 $(ECHO) ERROR: Build of $(SAMPLE_APP_NAME) has failed >>$(OUT_DIR)/$(BUILD_LOG); \
 $(DO_BEFORE_BUILD_FAIL) \
 exit 1; fi;
else
CAPTURE_OUTPUT :=
endif



# List of all source file names (.c files in SRC_DIRS directories and SRC_FILES)
SRC_FILES := $(foreach DIR,$(SRC_DIRS), $(wildcard $(call winpath, $(DIR))/*.c)) $(foreach FILE, $(SRC_FILES), $(call winpath, $(FILE)))
OUT_FILES     := $(foreach DIR,$(SRC_DIRS),$(notdir $(wildcard $(DIR)/*.c))) $(notdir $(SRC_FILES))
PARSE_FILES := $(OUT_FILES:.c=.par)
OUT_FILES := $(OUT_FILES:.c=.o)
OUT_FILES := $(OUT_FILES:.C=.o)
OUT_FILES := $(OUT_FILES:.s=.o)
OUT_FILES := $(OUT_FILES:.asm=.o)
OUT_FILES := $(sort $(OUT_FILES))

# Append directories of the SRC_FILES
SRC_DIRS += $(dir $(SRC_FILES))
#$(shell echo down $(SRC_DIRS) 1>&2)

# List of include files (must be in the cygwin path format since they are used in prerequisities)
INCLUDE_FILES := $(foreach DIR, $(INCLUDE_DIRS), $(wildcard $(DIR)/*.h))

# List of include directories (must be in the windows path format since it's passed to the compiler)
INCLUDE_DIRS := $(foreach DIR, $(INCLUDE_DIRS), $(call winpath, $(DIR)))
# print path to used linker script files

$(shell echo Linker command file = $(LINKER_DEFS) 1>&2)

OBJ_OUTPUT_PATH1 = $(BUILD_DIR)


#$(eval $(call targetcheck_rule))
#macros used for building the source files
COMPILE_C_FILE = $(CC) $(ccopt)  -DFILE_BASENAME=$(basename $(notdir $<)) -c $(call winpath, $<) $(addprefix -I, $(INCLUDE_DIRS)) -o $(call winpath, $(OUT_DIR)/$@)
COMPILE_S_FILE = $(AS) $(asopt)   $(call winpath, $<) -o $(call winpath, $(OUT_DIR)/$@)
# linking options

ifeq ($(TOOLCHAIN),ghs)
LINK_O_FILES = $(LD) $(ldopt) $(foreach LINKER_DEF, $(LINKER_DEFS), $(call winpath, $(LINKER_DEF))) $(addprefix $(call winpath, $(OUT_DIR)/), $(OUT_FILES)) $(call winpath, $(LIBS)) -o $(call winpath, $@)
endif
ifeq ($(TOOLCHAIN),gcc)
LINK_O_FILES = $(LD) $(ldopt) -Map=$(MAPFILE) -T $(foreach LINKER_DEF, $(LINKER_DEFS), $(call winpath, $(LINKER_DEF))) $(addprefix $(call winpath, $(OUT_DIR)/), $(OUT_FILES)) $(call winpath, $(LIBS)) -o $(call winpath, $@)
endif
ifeq ($(TOOLCHAIN),iar)
LINK_O_FILES = $(LD) $(ldopt) --map $(MAPFILE) --config $(foreach LINKER_DEF, $(LINKER_DEFS), $(call winpath, $(LINKER_DEF))) $(addprefix $(call winpath, $(OUT_DIR)/), $(OUT_FILES)) $(call winpath, $(LIBS)) -o $(call winpath, $@)
endif

#$(shell echo  compile options $(ccopt) 1>&2)
# Print a delimiter line after the make header log
#$(shell echo  include headers $(INCLUDE_DIRS) 1>&2)
$(shell echo --------------------------------------------------------------------------------- 1>&2)
################################################################################
# Build targets
################################################################################
.PHONY: build
build: $(OUT_DIR)/$(SAMPLE_APP_NAME).$(EXE_EXT)

vpath %.c $(addsuffix :, $(SRC_DIRS))
vpath %.C $(addsuffix :, $(SRC_DIRS))
vpath %.s $(addsuffix :, $(SRC_DIRS))
vpath %.asm $(addsuffix :, $(SRC_DIRS))
vpath %.o $(OUT_DIR)

$(OUT_DIR)/$(SAMPLE_APP_NAME).$(EXE_EXT): $(OUT_FILES) $(LIBS) $(LINKER_DEF)
	$(shell Linking 1>&2)  $(call LINK_O_FILES)  $(call CAPTURE_OUTPUT)

%.o : %.c $(INCLUDE_FILES)
	$(shell echo Building Source File 1>&2) $(call COMPILE_C_FILE)  $(call CAPTURE_OUTPUT)
	
%.o : %.C $(INCLUDE_FILES)
	$(shell echo Building Source Files 1>&2) $(call COMPILE_C_FILE)  $(call CAPTURE_OUTPUT)

%.o : %.asm
	$(shell echo Processing ASM File 1>&2) $(call COMPILE_S_FILE)  $(call CAPTURE_OUTPUT)
	
%.o : %.s
	$(shell echo Processing S File 1>&2) $(call COMPILE_S_FILE)  $(call CAPTURE_OUTPUT)	

	
################################################################################
# Type the list of available tests on specified directory
################################################################################
.PHONY: help
help:
		@$(ECHO);
		@$(ECHO) "Makefile for building the MCAL Sample Application"
		@$(ECHO) "        "
		@$(ECHO) "Available targets:"
		@$(ECHO) "    build - compiles and links the application"
		@$(ECHO) "    clean - cleans the folder structure of the files generated during build"
		@$(ECHO) "        "
		@$(ECHO) "Options:"
		@$(ECHO) "    TOOLCHAIN=toolchain_name  - selects the toolchain used for building the application"
		@$(ECHO) "           Possible values for toolchain_name:"
		@$(ECHO) "                 - ghs  - (default) - Builds with GreenHills Multi. Uses GHS_DIR environment variable."
		@$(ECHO) "                 - cw   - Builds with Freescale CodeWarrior for MPC. Uses CW_DIR environment variable."
		@$(ECHO) "                 - diab - Builds with Windriver DIAB. Uses DIAB_DIR environment variable."
		@$(ECHO) "        "
		@$(ECHO) "Example commands:"
		@$(ECHO) "        "
		@$(ECHO) "    make clean"
		@$(ECHO) "    make build"
		@$(ECHO) "    make TOOLCHAIN=diab clean build"
		@$(ECHO) "        "

#

################################################################################
# Makefile show flags
################################################################################
showflags:
	@$(ECHO) COMPILEROPTIONS = $(ccopt_drv) $(cpopt_drv) $(ccopt_os) $(cpopt_os)
	@$(ECHO) LINKEROPTIONS = $(ldopt)
	@$(ECHO) PREPROCESSOR_DEFINES = $(PREPROCESSOR_DEFINES)
	@$(ECHO) CC_FILES_TO_BUILD = $(CC_FILES_TO_BUILD)
	@$(ECHO) ASM_FILES_TO_BUILD = $(ASM_FILES_TO_BUILD)
	@$(ECHO) CC_INCLUDE_PATH = $(CC_INCLUDE_PATH)
	@$(ECHO) ALL_SRC_FILES = $(ALL_SRC_FILES)
	@$(ECHO) SRC_FILES = $(SRC_FILES)
	@$(ECHO) LINKER_CMD_OUTFILE = $(LINKER_CMD_OUTFILE)

################################################################################
# Makefile clean all obj including elf
################################################################################
.PHONY: clean
clean:
	@$(ECHO) Clean...
	#RM $(OUT_DIR)/*.*
	RM $(OUT_DIR)/*.elf
	#RM $(OUT_DIR)/*.a
	RM $(OUT_DIR)/*.o
	#RM $(OUT_DIR)/*.dba
	#RM $(OUT_DIR)/*.dbo
	#RM $(OUT_DIR)/*.dla
	#RM $(OUT_DIR)/*.dnm
	RM $(OUT_DIR)/*.map
	#RM $(OUT_DIR)/*.run
	#RM $(OUT_DIR)/*.lst
	#RM *.si
	#RM *.s
	#RM compiler_used.s
	#RM $(OUT_DIR)/*.d


################################################################################
# Makefile clean obj but keep elf
################################################################################
clean_keep_elf:
	@$(ECHO) Clean with keep elf ...
	$(RM) $(call cmdpath, $(OUT_DIR)/*.a)
	$(RM) $(call cmdpath, $(OUT_DIR)/*.o)
	$(RM) $(call cmdpath, $(OUT_DIR)/*.dba)
	$(RM) $(call cmdpath, $(OUT_DIR)/*.dbo)
	$(RM) $(call cmdpath, $(OUT_DIR)/*.dla)
	$(RM) $(call cmdpath, $(OUT_DIR)/*.dnm)
	$(RM) $(call cmdpath, $(OUT_DIR)/*.map)
	$(RM) $(call cmdpath, $(OUT_DIR)/*.run)
	$(RM) $(call cmdpath, $(OUT_DIR)/*.lst)
	$(RM) *.si
	$(RM) *.s
	$(RM) compiler_used.s
	$(RM) $(call cmdpath, $(OUT_DIR)/*.d)

#
################################################################################
# Makefile debug targets
################################################################################
print-%: ; $(error DEBUG Info: $* is $($*) ($(value $*)) (from $(origin $*)))

