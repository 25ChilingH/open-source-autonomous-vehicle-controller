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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Garmin_LIDAR_V3HP.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Garmin_LIDAR_V3HP.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Board.X/Board.c ../Serial.X/SerialM32.c ../System_timer.X/System_timer.c Garmin_v3hp.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/36105697/Board.o ${OBJECTDIR}/_ext/875531885/SerialM32.o ${OBJECTDIR}/_ext/698669614/System_timer.o ${OBJECTDIR}/Garmin_v3hp.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/36105697/Board.o.d ${OBJECTDIR}/_ext/875531885/SerialM32.o.d ${OBJECTDIR}/_ext/698669614/System_timer.o.d ${OBJECTDIR}/Garmin_v3hp.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/36105697/Board.o ${OBJECTDIR}/_ext/875531885/SerialM32.o ${OBJECTDIR}/_ext/698669614/System_timer.o ${OBJECTDIR}/Garmin_v3hp.o

# Source Files
SOURCEFILES=../Board.X/Board.c ../Serial.X/SerialM32.c ../System_timer.X/System_timer.c Garmin_v3hp.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Garmin_LIDAR_V3HP.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/36105697/Board.o: ../Board.X/Board.c  .generated_files/flags/default/bccab5db348c2babe55a475566b187fbe379dd1b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/36105697" 
	@${RM} ${OBJECTDIR}/_ext/36105697/Board.o.d 
	@${RM} ${OBJECTDIR}/_ext/36105697/Board.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DLIDARV3HP_TESTING -I"../System_timer.X" -I"../Board.X" -I"../Serial.X" -MP -MMD -MF "${OBJECTDIR}/_ext/36105697/Board.o.d" -o ${OBJECTDIR}/_ext/36105697/Board.o ../Board.X/Board.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/875531885/SerialM32.o: ../Serial.X/SerialM32.c  .generated_files/flags/default/c52b28d44808e1edda8e37734046a27bef74b9d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/875531885" 
	@${RM} ${OBJECTDIR}/_ext/875531885/SerialM32.o.d 
	@${RM} ${OBJECTDIR}/_ext/875531885/SerialM32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DLIDARV3HP_TESTING -I"../System_timer.X" -I"../Board.X" -I"../Serial.X" -MP -MMD -MF "${OBJECTDIR}/_ext/875531885/SerialM32.o.d" -o ${OBJECTDIR}/_ext/875531885/SerialM32.o ../Serial.X/SerialM32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/698669614/System_timer.o: ../System_timer.X/System_timer.c  .generated_files/flags/default/403108bfcd362d1fa09503568bb6a1214411ce5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/698669614" 
	@${RM} ${OBJECTDIR}/_ext/698669614/System_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/698669614/System_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DLIDARV3HP_TESTING -I"../System_timer.X" -I"../Board.X" -I"../Serial.X" -MP -MMD -MF "${OBJECTDIR}/_ext/698669614/System_timer.o.d" -o ${OBJECTDIR}/_ext/698669614/System_timer.o ../System_timer.X/System_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Garmin_v3hp.o: Garmin_v3hp.c  .generated_files/flags/default/7e7683e3b181fcdaba23ffa281b736fa43943e71 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Garmin_v3hp.o.d 
	@${RM} ${OBJECTDIR}/Garmin_v3hp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DLIDARV3HP_TESTING -I"../System_timer.X" -I"../Board.X" -I"../Serial.X" -MP -MMD -MF "${OBJECTDIR}/Garmin_v3hp.o.d" -o ${OBJECTDIR}/Garmin_v3hp.o Garmin_v3hp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/36105697/Board.o: ../Board.X/Board.c  .generated_files/flags/default/767224ffaf9a0e58003ed5bd7e48230fca07f206 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/36105697" 
	@${RM} ${OBJECTDIR}/_ext/36105697/Board.o.d 
	@${RM} ${OBJECTDIR}/_ext/36105697/Board.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DLIDARV3HP_TESTING -I"../System_timer.X" -I"../Board.X" -I"../Serial.X" -MP -MMD -MF "${OBJECTDIR}/_ext/36105697/Board.o.d" -o ${OBJECTDIR}/_ext/36105697/Board.o ../Board.X/Board.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/875531885/SerialM32.o: ../Serial.X/SerialM32.c  .generated_files/flags/default/e26a406295782afd7f3ec43fbcbc681858f6ba0a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/875531885" 
	@${RM} ${OBJECTDIR}/_ext/875531885/SerialM32.o.d 
	@${RM} ${OBJECTDIR}/_ext/875531885/SerialM32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DLIDARV3HP_TESTING -I"../System_timer.X" -I"../Board.X" -I"../Serial.X" -MP -MMD -MF "${OBJECTDIR}/_ext/875531885/SerialM32.o.d" -o ${OBJECTDIR}/_ext/875531885/SerialM32.o ../Serial.X/SerialM32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/698669614/System_timer.o: ../System_timer.X/System_timer.c  .generated_files/flags/default/da7da29d91f9b50a0a5dd432da9ecb6da20fa57a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/698669614" 
	@${RM} ${OBJECTDIR}/_ext/698669614/System_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/698669614/System_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DLIDARV3HP_TESTING -I"../System_timer.X" -I"../Board.X" -I"../Serial.X" -MP -MMD -MF "${OBJECTDIR}/_ext/698669614/System_timer.o.d" -o ${OBJECTDIR}/_ext/698669614/System_timer.o ../System_timer.X/System_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Garmin_v3hp.o: Garmin_v3hp.c  .generated_files/flags/default/b6704feeda5f85113d4eeb47d4ebe51c6b420dd4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Garmin_v3hp.o.d 
	@${RM} ${OBJECTDIR}/Garmin_v3hp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DLIDARV3HP_TESTING -I"../System_timer.X" -I"../Board.X" -I"../Serial.X" -MP -MMD -MF "${OBJECTDIR}/Garmin_v3hp.o.d" -o ${OBJECTDIR}/Garmin_v3hp.o Garmin_v3hp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Garmin_LIDAR_V3HP.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Garmin_LIDAR_V3HP.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Garmin_LIDAR_V3HP.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Garmin_LIDAR_V3HP.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}/xc32-bin2hex ${DISTDIR}/Garmin_LIDAR_V3HP.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
