ADD_DEFINITIONS( -DUSE_CMAKE )
IF( UNIX )
    INCLUDE (${CEM_ROOT}/cem_CMake/Linux.cmake)
ELSEIF( WIN32 )
    INCLUDE (${CEM_ROOT}/cem_CMake/Windows.cmake)
ENDIF( )
