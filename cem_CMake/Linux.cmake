# External Variables:
SET ( CEM_ROOT )
SET( EXTERNAL_LIBS_DIR )


INCLUDE_DIRECTORIES( ${EXTERNAL_LIBS_DIR}/gtest-1.7.0/include )
SET( GTEST_DIR ${EXTERNAL_LIBS_DIR}/gtest-1.7.0/lib )

INCLUDE_DIRECTORIES( /opt/intel/mkl/include )
SET( MKL_LIB_DIR /opt/intel/mkl/lib/intel64 )


#EOF
