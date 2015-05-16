#####################################################
# File:     CMakeLists.txt 
# Author:   Felipe Valdes
# Date:     May/2015
#####################################################
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET( LIB_TYPE "SHARED" CACHE STRING "Static or Shared libraries generated [STATIC|SHARED]" )

# External variables
SET( CEM_ROOT ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "PWD" )
SET( LIB_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/${LIB_TYPE}")
SET( BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/${LIB_TYPE}")




# Project Name: nSys
set( BIN_NAME cemDCIRDrop )
project( ${BIN_NAME} )

enable_testing()


add_subdirectory( src/cemCommon )


