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
FINAL_IMAGE=${DISTDIR}/Mavlink_minimal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Mavlink_minimal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../Board.X/Board.c ../Serial.X/SerialM32.c ../Radio_serial.X/Radio_serial.c ../System_timer.X/System_timer.c main.c ../NEO_M8N.X/NEO_M8N.c ../RC_RX.X/RC_RX.c ../ICM-20948.X/ICM_20948.c ../AS5047D.X/AS5047D.c ../RC_servo.X/RC_servo.c ../RC_ESC.X/RC_ESC.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/36105697/Board.o ${OBJECTDIR}/_ext/875531885/SerialM32.o ${OBJECTDIR}/_ext/1801597199/Radio_serial.o ${OBJECTDIR}/_ext/698669614/System_timer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/579527223/NEO_M8N.o ${OBJECTDIR}/_ext/88768175/RC_RX.o ${OBJECTDIR}/_ext/994540416/ICM_20948.o ${OBJECTDIR}/_ext/1737817073/AS5047D.o ${OBJECTDIR}/_ext/1548322204/RC_servo.o ${OBJECTDIR}/_ext/1555289632/RC_ESC.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/36105697/Board.o.d ${OBJECTDIR}/_ext/875531885/SerialM32.o.d ${OBJECTDIR}/_ext/1801597199/Radio_serial.o.d ${OBJECTDIR}/_ext/698669614/System_timer.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/_ext/579527223/NEO_M8N.o.d ${OBJECTDIR}/_ext/88768175/RC_RX.o.d ${OBJECTDIR}/_ext/994540416/ICM_20948.o.d ${OBJECTDIR}/_ext/1737817073/AS5047D.o.d ${OBJECTDIR}/_ext/1548322204/RC_servo.o.d ${OBJECTDIR}/_ext/1555289632/RC_ESC.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/36105697/Board.o ${OBJECTDIR}/_ext/875531885/SerialM32.o ${OBJECTDIR}/_ext/1801597199/Radio_serial.o ${OBJECTDIR}/_ext/698669614/System_timer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/579527223/NEO_M8N.o ${OBJECTDIR}/_ext/88768175/RC_RX.o ${OBJECTDIR}/_ext/994540416/ICM_20948.o ${OBJECTDIR}/_ext/1737817073/AS5047D.o ${OBJECTDIR}/_ext/1548322204/RC_servo.o ${OBJECTDIR}/_ext/1555289632/RC_ESC.o

# Source Files
SOURCEFILES=../Board.X/Board.c ../Serial.X/SerialM32.c ../Radio_serial.X/Radio_serial.c ../System_timer.X/System_timer.c main.c ../NEO_M8N.X/NEO_M8N.c ../RC_RX.X/RC_RX.c ../ICM-20948.X/ICM_20948.c ../AS5047D.X/AS5047D.c ../RC_servo.X/RC_servo.c ../RC_ESC.X/RC_ESC.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Mavlink_minimal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/36105697/Board.o: ../Board.X/Board.c  .generated_files/flags/default/91d88dc2ec191dd481e22a7d82f16b1043dc8654 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/36105697" 
	@${RM} ${OBJECTDIR}/_ext/36105697/Board.o.d 
	@${RM} ${OBJECTDIR}/_ext/36105697/Board.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/36105697/Board.o.d" -o ${OBJECTDIR}/_ext/36105697/Board.o ../Board.X/Board.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/875531885/SerialM32.o: ../Serial.X/SerialM32.c  .generated_files/flags/default/41aa3476f8793ed11760f18f1bd601a7e3345045 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/875531885" 
	@${RM} ${OBJECTDIR}/_ext/875531885/SerialM32.o.d 
	@${RM} ${OBJECTDIR}/_ext/875531885/SerialM32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/875531885/SerialM32.o.d" -o ${OBJECTDIR}/_ext/875531885/SerialM32.o ../Serial.X/SerialM32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1801597199/Radio_serial.o: ../Radio_serial.X/Radio_serial.c  .generated_files/flags/default/bbda112bb1ff4ae4995a0ac66912de4ff8f2eccc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1801597199" 
	@${RM} ${OBJECTDIR}/_ext/1801597199/Radio_serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1801597199/Radio_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1801597199/Radio_serial.o.d" -o ${OBJECTDIR}/_ext/1801597199/Radio_serial.o ../Radio_serial.X/Radio_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/698669614/System_timer.o: ../System_timer.X/System_timer.c  .generated_files/flags/default/39ae6cef964ec27c74a1b49121bb91e55890b3e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/698669614" 
	@${RM} ${OBJECTDIR}/_ext/698669614/System_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/698669614/System_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/698669614/System_timer.o.d" -o ${OBJECTDIR}/_ext/698669614/System_timer.o ../System_timer.X/System_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/fabc5e4426fa88ce94c7126a221eafa589cb030a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/579527223/NEO_M8N.o: ../NEO_M8N.X/NEO_M8N.c  .generated_files/flags/default/b6f5489ce0997fdb5381bbbb0699d7bfc7ca8011 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/579527223" 
	@${RM} ${OBJECTDIR}/_ext/579527223/NEO_M8N.o.d 
	@${RM} ${OBJECTDIR}/_ext/579527223/NEO_M8N.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/579527223/NEO_M8N.o.d" -o ${OBJECTDIR}/_ext/579527223/NEO_M8N.o ../NEO_M8N.X/NEO_M8N.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/88768175/RC_RX.o: ../RC_RX.X/RC_RX.c  .generated_files/flags/default/a1aba3b1af61962e6cfe8efcf9bbfbee5f555be3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/88768175" 
	@${RM} ${OBJECTDIR}/_ext/88768175/RC_RX.o.d 
	@${RM} ${OBJECTDIR}/_ext/88768175/RC_RX.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/88768175/RC_RX.o.d" -o ${OBJECTDIR}/_ext/88768175/RC_RX.o ../RC_RX.X/RC_RX.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/994540416/ICM_20948.o: ../ICM-20948.X/ICM_20948.c  .generated_files/flags/default/4be7e363b496715bdf1066efa7a2c12c1155f0f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/994540416" 
	@${RM} ${OBJECTDIR}/_ext/994540416/ICM_20948.o.d 
	@${RM} ${OBJECTDIR}/_ext/994540416/ICM_20948.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/994540416/ICM_20948.o.d" -o ${OBJECTDIR}/_ext/994540416/ICM_20948.o ../ICM-20948.X/ICM_20948.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1737817073/AS5047D.o: ../AS5047D.X/AS5047D.c  .generated_files/flags/default/34c09b037afb5b84b805df8381f79ef8663fdd8b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1737817073" 
	@${RM} ${OBJECTDIR}/_ext/1737817073/AS5047D.o.d 
	@${RM} ${OBJECTDIR}/_ext/1737817073/AS5047D.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1737817073/AS5047D.o.d" -o ${OBJECTDIR}/_ext/1737817073/AS5047D.o ../AS5047D.X/AS5047D.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1548322204/RC_servo.o: ../RC_servo.X/RC_servo.c  .generated_files/flags/default/246661b76adb9a3d943e942bdf520f9a1310e9d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1548322204" 
	@${RM} ${OBJECTDIR}/_ext/1548322204/RC_servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1548322204/RC_servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1548322204/RC_servo.o.d" -o ${OBJECTDIR}/_ext/1548322204/RC_servo.o ../RC_servo.X/RC_servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1555289632/RC_ESC.o: ../RC_ESC.X/RC_ESC.c  .generated_files/flags/default/fbd9534c2fb5771d0f45b08178aba3b608105a97 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1555289632" 
	@${RM} ${OBJECTDIR}/_ext/1555289632/RC_ESC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1555289632/RC_ESC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1555289632/RC_ESC.o.d" -o ${OBJECTDIR}/_ext/1555289632/RC_ESC.o ../RC_ESC.X/RC_ESC.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/36105697/Board.o: ../Board.X/Board.c  .generated_files/flags/default/97a1551d13ce65eeae66ce9e6fbfeab769e9cfc4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/36105697" 
	@${RM} ${OBJECTDIR}/_ext/36105697/Board.o.d 
	@${RM} ${OBJECTDIR}/_ext/36105697/Board.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/36105697/Board.o.d" -o ${OBJECTDIR}/_ext/36105697/Board.o ../Board.X/Board.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/875531885/SerialM32.o: ../Serial.X/SerialM32.c  .generated_files/flags/default/d1d5406e1d58fb3b99c792e393fb5ff99063a639 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/875531885" 
	@${RM} ${OBJECTDIR}/_ext/875531885/SerialM32.o.d 
	@${RM} ${OBJECTDIR}/_ext/875531885/SerialM32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/875531885/SerialM32.o.d" -o ${OBJECTDIR}/_ext/875531885/SerialM32.o ../Serial.X/SerialM32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1801597199/Radio_serial.o: ../Radio_serial.X/Radio_serial.c  .generated_files/flags/default/bace8ff0c09ff04290d1e5c9c634d6fc9b7ae64f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1801597199" 
	@${RM} ${OBJECTDIR}/_ext/1801597199/Radio_serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1801597199/Radio_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1801597199/Radio_serial.o.d" -o ${OBJECTDIR}/_ext/1801597199/Radio_serial.o ../Radio_serial.X/Radio_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/698669614/System_timer.o: ../System_timer.X/System_timer.c  .generated_files/flags/default/98493c51490426f63e1bf21da70fa27bdcd759e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/698669614" 
	@${RM} ${OBJECTDIR}/_ext/698669614/System_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/698669614/System_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/698669614/System_timer.o.d" -o ${OBJECTDIR}/_ext/698669614/System_timer.o ../System_timer.X/System_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/852d14f377dc3a854768579b15970b59fb4615d6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/579527223/NEO_M8N.o: ../NEO_M8N.X/NEO_M8N.c  .generated_files/flags/default/8fa60591e4e12f970d5506ec47f5d94316ee80ad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/579527223" 
	@${RM} ${OBJECTDIR}/_ext/579527223/NEO_M8N.o.d 
	@${RM} ${OBJECTDIR}/_ext/579527223/NEO_M8N.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/579527223/NEO_M8N.o.d" -o ${OBJECTDIR}/_ext/579527223/NEO_M8N.o ../NEO_M8N.X/NEO_M8N.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/88768175/RC_RX.o: ../RC_RX.X/RC_RX.c  .generated_files/flags/default/1c2fcf46df958658601537788b1c7f315dcfe1bf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/88768175" 
	@${RM} ${OBJECTDIR}/_ext/88768175/RC_RX.o.d 
	@${RM} ${OBJECTDIR}/_ext/88768175/RC_RX.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/88768175/RC_RX.o.d" -o ${OBJECTDIR}/_ext/88768175/RC_RX.o ../RC_RX.X/RC_RX.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/994540416/ICM_20948.o: ../ICM-20948.X/ICM_20948.c  .generated_files/flags/default/98047c666878e8885750cfc5583422a589168c9a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/994540416" 
	@${RM} ${OBJECTDIR}/_ext/994540416/ICM_20948.o.d 
	@${RM} ${OBJECTDIR}/_ext/994540416/ICM_20948.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/994540416/ICM_20948.o.d" -o ${OBJECTDIR}/_ext/994540416/ICM_20948.o ../ICM-20948.X/ICM_20948.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1737817073/AS5047D.o: ../AS5047D.X/AS5047D.c  .generated_files/flags/default/7f32d8668d5a4d2d5983db1c1c5005bf4a99a70 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1737817073" 
	@${RM} ${OBJECTDIR}/_ext/1737817073/AS5047D.o.d 
	@${RM} ${OBJECTDIR}/_ext/1737817073/AS5047D.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1737817073/AS5047D.o.d" -o ${OBJECTDIR}/_ext/1737817073/AS5047D.o ../AS5047D.X/AS5047D.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1548322204/RC_servo.o: ../RC_servo.X/RC_servo.c  .generated_files/flags/default/43deb7670ccc1a207d7df3b34653949c25c6a648 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1548322204" 
	@${RM} ${OBJECTDIR}/_ext/1548322204/RC_servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1548322204/RC_servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1548322204/RC_servo.o.d" -o ${OBJECTDIR}/_ext/1548322204/RC_servo.o ../RC_servo.X/RC_servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1555289632/RC_ESC.o: ../RC_ESC.X/RC_ESC.c  .generated_files/flags/default/e4c6668846db660bc24499c81ddf327b4918859b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1555289632" 
	@${RM} ${OBJECTDIR}/_ext/1555289632/RC_ESC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1555289632/RC_ESC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../Board.X" -I"../Radio_serial.X" -I"../../modules/c_library_v2" -I"../../modules/c_library_v2/common" -I"../System_timer.X" -I"../Serial.X" -I"../NEO_M8N.X" -I"../RC_RX.X" -I"../ICM-20948.X" -I"../AS5047D.X" -I"../RC_servo.X" -I"../RC_ESC.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1555289632/RC_ESC.o.d" -o ${OBJECTDIR}/_ext/1555289632/RC_ESC.o ../RC_ESC.X/RC_ESC.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Mavlink_minimal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Mavlink_minimal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Mavlink_minimal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Mavlink_minimal.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}/xc32-bin2hex ${DISTDIR}/Mavlink_minimal.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
