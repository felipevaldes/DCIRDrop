#ifndef TESTCEMMATH_H
#define TESTCEMMATH_H

#include "gtest/gtest.h"
#include "cemTypes.h"
#include "MKL/BlasLevel1.h"
#include "Matrix/DenseMatrix.h"


//************************************************************************************************//
// This is an example on how to use Fixtures in GoogleTest
//************************************************************************************************//

//using namespace cem_def;

//namespace cem_math{

//class MKL_BLAS_Level1_Test : public ::testing::Test
//{
//protected:
//    static void SetUpTestCase()
//    {
//        N_ = 300;
//        vector_x_ = new cemDOUBLE[N_];
//        vector_y_ = new cemDOUBLE[N_];
//        vector_x_plus_y_ = new cemDOUBLE[N_];
//    }

//    static void TearDownTestCase()
//    {
//        CLEAN_ARRAY(vector_x_);
//        CLEAN_ARRAY(vector_y_);
//        CLEAN_ARRAY(vector_x_plus_y_);
//    }

//    static cemINT N_;
//    static cemDOUBLE* vector_x_;
//    static cemDOUBLE* vector_y_;
//    static cemDOUBLE* vector_x_plus_y_;
//};

//cemINT MKL_BLAS_Level1_Test::N_;
//cemDOUBLE* MKL_BLAS_Level1_Test::vector_x_;
//cemDOUBLE* MKL_BLAS_Level1_Test::vector_y_;
//cemDOUBLE* MKL_BLAS_Level1_Test::vector_x_plus_y_;

//}

//************************************************************************************************//
// End of Example
//************************************************************************************************//


#endif // TESTCEMMATH_H

