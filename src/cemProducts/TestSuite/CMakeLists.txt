cmake_minimum_required(VERSION 2.8)

# External Variables:
SET ( CEM_ROOT )
SET( EXTERNAL_LIBS_DIR )

INCLUDE( ${CEM_ROOT}/cem_CMake/CEM.cmake )


# Project Name:
SET( BIN_NAME TestSuite )
PROJECT( ${BIN_NAME} )

# Source Files:
SET( GUI_NAME ${BIN_NAME} )
SET(	GUI_FILES
	TestSuite.cpp
   )

SET( CONSOLE_NAME ${BIN_NAME}Console )
SET(	CONSOLE_FILES
	TestSuite.cpp
   )

AUX_SOURCE_DIRECTORY(.              CONSOLE_FILES)
AUX_SOURCE_DIRECTORY(TestCEMSpace   CONSOLE_FILES)
AUX_SOURCE_DIRECTORY(TestCEMMesh   CONSOLE_FILES)
AUX_SOURCE_DIRECTORY(TestCEMMath   CONSOLE_FILES)
AUX_SOURCE_DIRECTORY(TestIntegration   CONSOLE_FILES)
AUX_SOURCE_DIRECTORY(TestBasisFunctions   CONSOLE_FILES)

# cemLibraries to be used:
SET( 	LIBRARIES
        ${GTEST_DIR}/libgtest.a
        cemCommon
        cemCore
        cemMesh
        cemMath
   )

INCLUDE( ${CEM_ROOT}/cem_CMake/CEMCommon.cmake )

#EOF
