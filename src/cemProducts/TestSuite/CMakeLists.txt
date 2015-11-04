cmake_minimum_required(VERSION 2.8)

# External Variables:
SET( EXTERNAL_LIBS_DIR )

# Project Name:
set( BIN_NAME TestSuite )
project( ${BIN_NAME} )

# Source Files:
set( GUI_NAME ${BIN_NAME} )
set(	GUI_FILES
	TestSuite.cpp
   )

set( CONSOLE_NAME ${BIN_NAME}Console )
set(	CONSOLE_FILES
	TestSuite.cpp
   )

include( ${cem_ROOT}/cem_CMake/CEM.cmake )

aux_source_directory(TestCEMSpace   CONSOLE_FILES)
aux_source_directory(TestCEMMesh   CONSOLE_FILES)
aux_source_directory(TestCEMMath   CONSOLE_FILES)

# cemLibraries to be used:
set( 	LIBRARIES
        ${GTEST_DIR}/libgtest.a
        pthread
        cemCommon
        cemCore
        cemMesh
        cemMath
   )

ADD_EXECUTABLE( ${CONSOLE_NAME} ${CONSOLE_FILES} )
SET_PROPERTY( TARGET ${CONSOLE_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION ${USE_IPO} )
TARGET_LINK_LIBRARIES( ${CONSOLE_NAME} ${LIBRARIES} )

#EOF
