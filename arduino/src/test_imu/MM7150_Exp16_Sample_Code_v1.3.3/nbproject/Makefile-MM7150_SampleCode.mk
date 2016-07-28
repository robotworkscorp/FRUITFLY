#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-MM7150_SampleCode.mk)" "nbproject/Makefile-local-MM7150_SampleCode.mk"
include nbproject/Makefile-local-MM7150_SampleCode.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=MM7150_SampleCode
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MM7150_Exp16_Sample_Code_v1.3.3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MM7150_Exp16_Sample_Code_v1.3.3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=source/src/i2cIO.c source/src/interrupts.c source/src/lcd.c source/src/main.c source/src/sf.c source/src/system.c source/src/vregs.c source/src/err.c source/src/flashupdate.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/source/src/i2cIO.o ${OBJECTDIR}/source/src/interrupts.o ${OBJECTDIR}/source/src/lcd.o ${OBJECTDIR}/source/src/main.o ${OBJECTDIR}/source/src/sf.o ${OBJECTDIR}/source/src/system.o ${OBJECTDIR}/source/src/vregs.o ${OBJECTDIR}/source/src/err.o ${OBJECTDIR}/source/src/flashupdate.o
POSSIBLE_DEPFILES=${OBJECTDIR}/source/src/i2cIO.o.d ${OBJECTDIR}/source/src/interrupts.o.d ${OBJECTDIR}/source/src/lcd.o.d ${OBJECTDIR}/source/src/main.o.d ${OBJECTDIR}/source/src/sf.o.d ${OBJECTDIR}/source/src/system.o.d ${OBJECTDIR}/source/src/vregs.o.d ${OBJECTDIR}/source/src/err.o.d ${OBJECTDIR}/source/src/flashupdate.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/source/src/i2cIO.o ${OBJECTDIR}/source/src/interrupts.o ${OBJECTDIR}/source/src/lcd.o ${OBJECTDIR}/source/src/main.o ${OBJECTDIR}/source/src/sf.o ${OBJECTDIR}/source/src/system.o ${OBJECTDIR}/source/src/vregs.o ${OBJECTDIR}/source/src/err.o ${OBJECTDIR}/source/src/flashupdate.o

# Source Files
SOURCEFILES=source/src/i2cIO.c source/src/interrupts.c source/src/lcd.c source/src/main.c source/src/sf.c source/src/system.c source/src/vregs.c source/src/err.c source/src/flashupdate.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-MM7150_SampleCode.mk dist/${CND_CONF}/${IMAGE_TYPE}/MM7150_Exp16_Sample_Code_v1.3.3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GA010
MP_LINKER_FILE_OPTION=,--script="p24FJ128GA010.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/source/src/i2cIO.o: source/src/i2cIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/i2cIO.o.d 
	@${RM} ${OBJECTDIR}/source/src/i2cIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/i2cIO.c  -o ${OBJECTDIR}/source/src/i2cIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/i2cIO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/i2cIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/interrupts.o: source/src/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/interrupts.o.d 
	@${RM} ${OBJECTDIR}/source/src/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/interrupts.c  -o ${OBJECTDIR}/source/src/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/interrupts.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/lcd.o: source/src/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/lcd.o.d 
	@${RM} ${OBJECTDIR}/source/src/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/lcd.c  -o ${OBJECTDIR}/source/src/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/main.o: source/src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/main.o.d 
	@${RM} ${OBJECTDIR}/source/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/main.c  -o ${OBJECTDIR}/source/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/sf.o: source/src/sf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/sf.o.d 
	@${RM} ${OBJECTDIR}/source/src/sf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/sf.c  -o ${OBJECTDIR}/source/src/sf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/sf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/sf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/system.o: source/src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/system.o.d 
	@${RM} ${OBJECTDIR}/source/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/system.c  -o ${OBJECTDIR}/source/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/vregs.o: source/src/vregs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/vregs.o.d 
	@${RM} ${OBJECTDIR}/source/src/vregs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/vregs.c  -o ${OBJECTDIR}/source/src/vregs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/vregs.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/vregs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/err.o: source/src/err.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/err.o.d 
	@${RM} ${OBJECTDIR}/source/src/err.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/err.c  -o ${OBJECTDIR}/source/src/err.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/err.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/err.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/flashupdate.o: source/src/flashupdate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/flashupdate.o.d 
	@${RM} ${OBJECTDIR}/source/src/flashupdate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/flashupdate.c  -o ${OBJECTDIR}/source/src/flashupdate.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/flashupdate.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/flashupdate.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/source/src/i2cIO.o: source/src/i2cIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/i2cIO.o.d 
	@${RM} ${OBJECTDIR}/source/src/i2cIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/i2cIO.c  -o ${OBJECTDIR}/source/src/i2cIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/i2cIO.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/i2cIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/interrupts.o: source/src/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/interrupts.o.d 
	@${RM} ${OBJECTDIR}/source/src/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/interrupts.c  -o ${OBJECTDIR}/source/src/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/interrupts.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/lcd.o: source/src/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/lcd.o.d 
	@${RM} ${OBJECTDIR}/source/src/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/lcd.c  -o ${OBJECTDIR}/source/src/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/lcd.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/main.o: source/src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/main.o.d 
	@${RM} ${OBJECTDIR}/source/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/main.c  -o ${OBJECTDIR}/source/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/main.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/sf.o: source/src/sf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/sf.o.d 
	@${RM} ${OBJECTDIR}/source/src/sf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/sf.c  -o ${OBJECTDIR}/source/src/sf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/sf.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/sf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/system.o: source/src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/system.o.d 
	@${RM} ${OBJECTDIR}/source/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/system.c  -o ${OBJECTDIR}/source/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/system.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/vregs.o: source/src/vregs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/vregs.o.d 
	@${RM} ${OBJECTDIR}/source/src/vregs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/vregs.c  -o ${OBJECTDIR}/source/src/vregs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/vregs.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/vregs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/err.o: source/src/err.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/err.o.d 
	@${RM} ${OBJECTDIR}/source/src/err.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/err.c  -o ${OBJECTDIR}/source/src/err.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/err.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/err.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/source/src/flashupdate.o: source/src/flashupdate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source/src" 
	@${RM} ${OBJECTDIR}/source/src/flashupdate.o.d 
	@${RM} ${OBJECTDIR}/source/src/flashupdate.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/src/flashupdate.c  -o ${OBJECTDIR}/source/src/flashupdate.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/source/src/flashupdate.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/source/src/flashupdate.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MM7150_Exp16_Sample_Code_v1.3.3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p24FJ128GA010.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MM7150_Exp16_Sample_Code_v1.3.3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MM7150_Exp16_Sample_Code_v1.3.3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p24FJ128GA010.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MM7150_Exp16_Sample_Code_v1.3.3.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MM7150_Exp16_Sample_Code_v1.3.3.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/MM7150_SampleCode
	${RM} -r dist/MM7150_SampleCode

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
