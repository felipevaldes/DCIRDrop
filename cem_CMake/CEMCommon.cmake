
IF( UNIX )
    # Intel MKL:
    SET( MKL_INTEL ${MKL_LIB_DIR}/libmkl_intel_lp64.a )

ELSEIF( WIN32 )
    # Intel MKL:
    SET( MKL_INTEL ${MKL_LIB_DIR}/mkl_intel_lp64.lib )

ENDIF( )


#Link Libraries
IF( UNIX )
    SET(    LIBRARIES_TO_LINK
            ${LIBRARIES}
            -Wl,--start-group
            pthread
            ${MKL_INTEL}
            ${MKL_LIB_DIR}/libmkl_sequential.a
            ${MKL_LIB_DIR}/libmkl_core.a
            dl
            -Wl,--end-group
        )

    IF( GUI_NAME )

    ENDIF( GUI_NAME )

    IF( CONSOLE_NAME )
        ADD_EXECUTABLE( ${CONSOLE_NAME} ${CONSOLE_FILES} )
        SET_PROPERTY( TARGET ${CONSOLE_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION ${USE_IPO} )
        TARGET_LINK_LIBRARIES( ${CONSOLE_NAME} ${LIBRARIES_TO_LINK} )
    ENDIF( CONSOLE_NAME )

ELSEIF( WIN32 )

ENDIF( )







#EOF
