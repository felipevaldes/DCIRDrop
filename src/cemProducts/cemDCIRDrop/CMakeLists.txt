cmake_minimum_required(VERSION 2.8)

# External Variables:
SET ( CEM_ROOT )
SET( EXTERNAL_LIBS_DIR )

INCLUDE( ${CEM_ROOT}/cem_CMake/CEM.cmake )


# Project Name:
SET( BIN_NAME cemDCIRDrop )
PROJECT( ${BIN_NAME} )

# Source Files:
SET( GUI_NAME ${BIN_NAME} )
SET(	GUI_FILES
	main.cpp
   )

SET( CONSOLE_NAME ${BIN_NAME}Console )
SET(	CONSOLE_FILES
	main.cpp
   )

# cemLibraries to be used:
SET( 	LIBRARIES
        cemCommon
        cemCore
        cemMesh
        cemMath
   )

INCLUDE( ${CEM_ROOT}/cem_CMake/CEMCommon.cmake )

#EOF
