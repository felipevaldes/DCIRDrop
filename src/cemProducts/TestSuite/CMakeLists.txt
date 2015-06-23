cmake_minimum_required(VERSION 2.8)

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

# cemLibraries to be used:
SET( 	LIBRARIES
        cemCommon
#	cemCore
#	cemMath
   )

ADD_EXECUTABLE( ${CONSOLE_NAME} ${CONSOLE_FILES} )
SET_PROPERTY( TARGET ${CONSOLE_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION ${USE_IPO} )
TARGET_LINK_LIBRARIES( ${CONSOLE_NAME} ${LIBRARIES} )

#EOF
