#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/cpps/BinaryHeap.o \
	${OBJECTDIR}/cpps/BinaryHeapCell.o \
	${OBJECTDIR}/cpps/Boton.o \
	${OBJECTDIR}/cpps/Camino.o \
	${OBJECTDIR}/cpps/Celda.o \
	${OBJECTDIR}/cpps/Efecto.o \
	${OBJECTDIR}/cpps/Enemigo.o \
	${OBJECTDIR}/cpps/FactoriaEnemigo.o \
	${OBJECTDIR}/cpps/Game.o \
	${OBJECTDIR}/cpps/GameState.o \
	${OBJECTDIR}/cpps/Interpolacion.o \
	${OBJECTDIR}/cpps/Mapa.o \
	${OBJECTDIR}/cpps/Nexo.o \
	${OBJECTDIR}/cpps/Nivel.o \
	${OBJECTDIR}/cpps/ResourceManager.o \
	${OBJECTDIR}/cpps/SFML.o \
	${OBJECTDIR}/cpps/State.o \
	${OBJECTDIR}/cpps/State_ChooseStage.o \
	${OBJECTDIR}/cpps/State_Game.o \
	${OBJECTDIR}/cpps/State_Menu.o \
	${OBJECTDIR}/cpps/Torreta.o \
	${OBJECTDIR}/cpps/config.o \
	${OBJECTDIR}/cpps/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practica0.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practica0.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practica0 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/cpps/BinaryHeap.o: cpps/BinaryHeap.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/BinaryHeap.o cpps/BinaryHeap.cpp

${OBJECTDIR}/cpps/BinaryHeapCell.o: cpps/BinaryHeapCell.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/BinaryHeapCell.o cpps/BinaryHeapCell.cpp

${OBJECTDIR}/cpps/Boton.o: cpps/Boton.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Boton.o cpps/Boton.cpp

${OBJECTDIR}/cpps/Camino.o: cpps/Camino.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Camino.o cpps/Camino.cpp

${OBJECTDIR}/cpps/Celda.o: cpps/Celda.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Celda.o cpps/Celda.cpp

${OBJECTDIR}/cpps/Efecto.o: cpps/Efecto.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Efecto.o cpps/Efecto.cpp

${OBJECTDIR}/cpps/Enemigo.o: cpps/Enemigo.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Enemigo.o cpps/Enemigo.cpp

${OBJECTDIR}/cpps/FactoriaEnemigo.o: cpps/FactoriaEnemigo.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/FactoriaEnemigo.o cpps/FactoriaEnemigo.cpp

${OBJECTDIR}/cpps/Game.o: cpps/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Game.o cpps/Game.cpp

${OBJECTDIR}/cpps/GameState.o: cpps/GameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/GameState.o cpps/GameState.cpp

${OBJECTDIR}/cpps/Interpolacion.o: cpps/Interpolacion.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Interpolacion.o cpps/Interpolacion.cpp

${OBJECTDIR}/cpps/Mapa.o: cpps/Mapa.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Mapa.o cpps/Mapa.cpp

${OBJECTDIR}/cpps/Nexo.o: cpps/Nexo.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Nexo.o cpps/Nexo.cpp

${OBJECTDIR}/cpps/Nivel.o: cpps/Nivel.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Nivel.o cpps/Nivel.cpp

${OBJECTDIR}/cpps/ResourceManager.o: cpps/ResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/ResourceManager.o cpps/ResourceManager.cpp

${OBJECTDIR}/cpps/SFML.o: cpps/SFML.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/SFML.o cpps/SFML.cpp

${OBJECTDIR}/cpps/State.o: cpps/State.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/State.o cpps/State.cpp

${OBJECTDIR}/cpps/State_ChooseStage.o: cpps/State_ChooseStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/State_ChooseStage.o cpps/State_ChooseStage.cpp

${OBJECTDIR}/cpps/State_Game.o: cpps/State_Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/State_Game.o cpps/State_Game.cpp

${OBJECTDIR}/cpps/State_Menu.o: cpps/State_Menu.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/State_Menu.o cpps/State_Menu.cpp

${OBJECTDIR}/cpps/Torreta.o: cpps/Torreta.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/Torreta.o cpps/Torreta.cpp

${OBJECTDIR}/cpps/config.o: cpps/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/config.o cpps/config.cpp

${OBJECTDIR}/cpps/main.o: cpps/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/cpps
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpps/main.o cpps/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practica0.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
