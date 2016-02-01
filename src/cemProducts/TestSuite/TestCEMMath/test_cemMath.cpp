#include "test_cemMath.h"
#include "cemError.h"
#include "cemConsts.h"
#include "cemUtils.h"
#include <iostream>
#include <cstring>
#include <time.h>

using namespace cem_math;
using cemcommon::Exception;

//************************************************************************************************//
// Main Test Function:
//************************************************************************************************//
int RunTestCEMMath(int argc, char* argv[])
{
    std::cout << "Running cem_math Test" << std::endl;

    if (argc < 2)
        throw(Exception("INSUFFICIENT_INPUT_ARGUMENTS","Must specify test to run"));

    if (!strcmp(argv[1],"-MKL_BLAS_Level1"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "MKL_BLAS_Level1.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-DenseMatrix"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "DenseMatrix.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-BasicTest"))
    {
        return TestMathBasics();
    }
    return 1;
}

//************************************************************************************************//
// MKL_VectorPlusEqualVector:
//************************************************************************************************//
TEST(MKL_BLAS_Level1,VectorPlusEqualVectorD)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDOUBLE* x = new cemDOUBLE[N];
    cemDOUBLE* y = new cemDOUBLE[N];
    cemDOUBLE* x_plus_y = new cemDOUBLE[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i] = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        y[i] = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 20 + 1);
        x_plus_y[i] = x[i] + y[i];
    }

    MKL_VectorPlusEqualVector(N,y,x);

    for (cemINT i=0; i<N; ++i)
        ASSERT_DOUBLE_EQ(x_plus_y[i], y[i]);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
    CLEAN_ARRAY(x_plus_y);
}

TEST(MKL_BLAS_Level1,VectorPlusEqualVectorF)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFLOAT* x = new cemFLOAT[N];
    cemFLOAT* y = new cemFLOAT[N];
    cemFLOAT* x_plus_y = new cemFLOAT[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i] = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        y[i] = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 20 + 1);
        x_plus_y[i] = x[i] + y[i];
    }

    MKL_VectorPlusEqualVector(N,y,x);

    for (cemINT i=0; i<N; ++i)
        ASSERT_FLOAT_EQ(x_plus_y[i], y[i]);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
    CLEAN_ARRAY(x_plus_y);
}

TEST(MKL_BLAS_Level1,VectorPlusEqualVectorDC)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDCOMPLEX* x = new cemDCOMPLEX[N];
    cemDCOMPLEX* y = new cemDCOMPLEX[N];
    cemDCOMPLEX* x_plus_y = new cemDCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        y[i].real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 20 + 1);
        y[i].imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 20 + 1);
        x_plus_y[i] = x[i] + y[i];
    }

    MKL_VectorPlusEqualVector(N,y,x);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_DOUBLE_EQ(x_plus_y[i].real(), y[i].real());
        ASSERT_DOUBLE_EQ(x_plus_y[i].imag(), y[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
    CLEAN_ARRAY(x_plus_y);
}

TEST(MKL_BLAS_Level1,VectorPlusEqualVectorFC)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFCOMPLEX* x = new cemFCOMPLEX[N];
    cemFCOMPLEX* y = new cemFCOMPLEX[N];
    cemFCOMPLEX* x_plus_y = new cemFCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        y[i].real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 20 + 1);
        y[i].imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 20 + 1);
        x_plus_y[i] = x[i] + y[i];
    }

    MKL_VectorPlusEqualVector(N,y,x);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_FLOAT_EQ(x_plus_y[i].real(), y[i].real());
        ASSERT_FLOAT_EQ(x_plus_y[i].imag(), y[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
    CLEAN_ARRAY(x_plus_y);
}


//************************************************************************************************//
// MKL_VectorMinusEqualVector:
//************************************************************************************************//
TEST(MKL_BLAS_Level1,MKL_VectorMinusEqualVectorD)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDOUBLE* x = new cemDOUBLE[N];
    cemDOUBLE* y = new cemDOUBLE[N];
    cemDOUBLE* y_minus_x = new cemDOUBLE[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i] = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        y[i] = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 20 + 1);
        y_minus_x[i] = y[i] - x[i];
    }

    MKL_VectorMinusEqualVector(N,y,x);

    for (cemINT i=0; i<N; ++i)
        ASSERT_DOUBLE_EQ(y_minus_x[i], y[i]);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
    CLEAN_ARRAY(y_minus_x);
}

TEST(MKL_BLAS_Level1,MKL_VectorMinusEqualVectorF)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFLOAT* x = new cemFLOAT[N];
    cemFLOAT* y = new cemFLOAT[N];
    cemFLOAT* y_minus_x = new cemFLOAT[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i] = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        y[i] = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 20 + 1);
        y_minus_x[i] = y[i] - x[i];
    }

    MKL_VectorMinusEqualVector(N,y,x);

    for (cemINT i=0; i<N; ++i)
        ASSERT_FLOAT_EQ(y_minus_x[i], y[i]);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
    CLEAN_ARRAY(y_minus_x);
}

TEST(MKL_BLAS_Level1,MKL_VectorMinusEqualVectorDC)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDCOMPLEX* x = new cemDCOMPLEX[N];
    cemDCOMPLEX* y = new cemDCOMPLEX[N];
    cemDCOMPLEX* y_minus_x = new cemDCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        y[i].real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 20 + 1);
        y[i].imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 20 + 1);
        y_minus_x[i] = y[i] - x[i];
    }

    MKL_VectorMinusEqualVector(N,y,x);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_DOUBLE_EQ(y_minus_x[i].real(), y[i].real());
        ASSERT_DOUBLE_EQ(y_minus_x[i].imag(), y[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
    CLEAN_ARRAY(y_minus_x);
}

TEST(MKL_BLAS_Level1,MKL_VectorMinusEqualVectorFC)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFCOMPLEX* x = new cemFCOMPLEX[N];
    cemFCOMPLEX* y = new cemFCOMPLEX[N];
    cemFCOMPLEX* y_minus_x = new cemFCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        y[i].real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 20 + 1);
        y[i].imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 20 + 1);
        y_minus_x[i] = y[i] - x[i];
    }

    MKL_VectorMinusEqualVector(N,y,x);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_FLOAT_EQ(y_minus_x[i].real(), y[i].real());
        ASSERT_FLOAT_EQ(y_minus_x[i].imag(), y[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
    CLEAN_ARRAY(y_minus_x);
}


//************************************************************************************************//
// MKL_ScalarTimesEqualVector:
//************************************************************************************************//
TEST(MKL_BLAS_Level1,MKL_ScalarTimesEqualVectorD)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDOUBLE* x = new cemDOUBLE[N];
    cemDOUBLE* a_times_x = new cemDOUBLE[N];
    cemDOUBLE a = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);

    for (cemINT i=0; i<N; ++i)
    {
        x[i] = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        a_times_x[i] = a*x[i];
    }

    MKL_ScalarTimesEqualVector(N,x,a);

    for (cemINT i=0; i<N; ++i)
        ASSERT_DOUBLE_EQ(a_times_x[i], x[i]);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(a_times_x);
}

TEST(MKL_BLAS_Level1,MKL_ScalarTimesEqualVectorF)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFLOAT* x = new cemFLOAT[N];
    cemFLOAT* a_times_x = new cemFLOAT[N];
    cemFLOAT a = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);

    for (cemINT i=0; i<N; ++i)
    {
        x[i] = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        a_times_x[i] = a*x[i];
    }

    MKL_ScalarTimesEqualVector(N,x,a);

    for (cemINT i=0; i<N; ++i)
        ASSERT_FLOAT_EQ(a_times_x[i], x[i]);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(a_times_x);
}

TEST(MKL_BLAS_Level1,DISABLED_MKL_ScalarTimesEqualVectorDC)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDCOMPLEX* x = new cemDCOMPLEX[N];
    cemDCOMPLEX* a_times_x = new cemDCOMPLEX[N];
    cemDCOMPLEX a;
    a.real()= static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
    a.imag()= static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        a_times_x[i] = a*x[i];
    }

    MKL_ScalarTimesEqualVector(N,x,a);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_DOUBLE_EQ(a_times_x[i].real(), x[i].real());
        ASSERT_DOUBLE_EQ(a_times_x[i].imag(), x[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(a_times_x);
}

TEST(MKL_BLAS_Level1,DISABLED_MKL_ScalarTimesEqualVectorFC)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFCOMPLEX* x = new cemFCOMPLEX[N];
    cemFCOMPLEX* a_times_x = new cemFCOMPLEX[N];
    cemFCOMPLEX a;
    a.real()= static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
    a.imag()= static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        a_times_x[i] = a*x[i];
    }

    MKL_ScalarTimesEqualVector(N,x,a);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_FLOAT_EQ(a_times_x[i].real(), x[i].real());
        ASSERT_FLOAT_EQ(a_times_x[i].imag(), x[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(a_times_x);
}

TEST(MKL_BLAS_Level1,MKL_ScalarTimesEqualVectorDCD)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDCOMPLEX* x = new cemDCOMPLEX[N];
    cemDCOMPLEX* a_times_x = new cemDCOMPLEX[N];
    cemDOUBLE a = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        a_times_x[i] = a*x[i];
    }

    MKL_ScalarTimesEqualVector(N,x,a);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_DOUBLE_EQ(a_times_x[i].real(), x[i].real());
        ASSERT_DOUBLE_EQ(a_times_x[i].imag(), x[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(a_times_x);
}

TEST(MKL_BLAS_Level1,MKL_ScalarTimesEqualVectorFCF)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFCOMPLEX* x = new cemFCOMPLEX[N];
    cemFCOMPLEX* a_times_x = new cemFCOMPLEX[N];
    cemFLOAT a = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        a_times_x[i] = a*x[i];
    }

    MKL_ScalarTimesEqualVector(N,x,a);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_FLOAT_EQ(a_times_x[i].real(), x[i].real());
        ASSERT_FLOAT_EQ(a_times_x[i].imag(), x[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(a_times_x);
}


//************************************************************************************************//
// MKL_VectorCopy:
//************************************************************************************************//
TEST(MKL_BLAS_Level1,MKL_VectorCopyD)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDOUBLE* x = new cemDOUBLE[N];
    cemDOUBLE* x_copy = new cemDOUBLE[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i] = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
    }

    MKL_VectorCopy(N,x_copy,1,x,1);

    for (cemINT i=0; i<N; ++i)
        ASSERT_DOUBLE_EQ(x[i], x_copy[i]);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(x_copy);
}

TEST(MKL_BLAS_Level1,MKL_VectorCopyF)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFLOAT* x = new cemFLOAT[N];
    cemFLOAT* x_copy = new cemFLOAT[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i] = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
    }

    MKL_VectorCopy(N,x_copy,1,x,1);

    for (cemINT i=0; i<N; ++i)
        ASSERT_FLOAT_EQ(x[i], x_copy[i]);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(x_copy);
}

TEST(MKL_BLAS_Level1,MKL_VectorCopyDC)
{
    srand(time(NULL));
    cemINT N = 300;
    cemDCOMPLEX* x = new cemDCOMPLEX[N];
    cemDCOMPLEX* x_copy = new cemDCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
    }

    MKL_VectorCopy(N,x_copy,1,x,1);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_DOUBLE_EQ(x[i].real(), x_copy[i].real());
        ASSERT_DOUBLE_EQ(x[i].imag(), x_copy[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(x_copy);
}

TEST(MKL_BLAS_Level1,MKL_VectorCopyFC)
{
    srand(time(NULL));
    cemINT N = 300;
    cemFCOMPLEX* x = new cemFCOMPLEX[N];
    cemFCOMPLEX* x_copy = new cemFCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        x[i].real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        x[i].imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
    }

    MKL_VectorCopy(N,x_copy,1,x,1);

    for (cemINT i=0; i<N; ++i)
    {
        ASSERT_FLOAT_EQ(x[i].real(), x_copy[i].real());
        ASSERT_FLOAT_EQ(x[i].imag(), x_copy[i].imag());
    }

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(x_copy);
}


//************************************************************************************************//
// MKL_VectorDotProduct:
//************************************************************************************************//
TEST(MKL_BLAS_Level1,MKL_VectorDotProductD)
{
    cemINT N = 1000;
    cemDOUBLE* x = new cemDOUBLE[N];
    cemDOUBLE* y = new cemDOUBLE[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemDOUBLE a = static_cast<cemDOUBLE>(i)*cem_const::PI2/999.0;
        x[i] = cos(a);
        y[i] = sin(a);
    }

    cemDOUBLE result = MKL_VectorDotProduct(N,x,y);

    ASSERT_DOUBLE_EQ(7.045579397679802e-15, result);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
}

TEST(MKL_BLAS_Level1,MKL_VectorDotProductF)
{
    cemINT N = 1000;
    cemFLOAT* x = new cemFLOAT[N];
    cemFLOAT* y = new cemFLOAT[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemFLOAT a = static_cast<cemFLOAT>(i)*cem_const::PI2/999.0;
        x[i] = cos(a);
        y[i] = sin(a);
    }

    cemFLOAT result = MKL_VectorDotProduct(N,x,y);

    ASSERT_FLOAT_EQ(-9.653158e-07, result);

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
}

TEST(MKL_BLAS_Level1,MKL_VectorDotProductDC)
{
    cemINT N = 1000;
    cemDCOMPLEX* x = new cemDCOMPLEX[N];
    cemDCOMPLEX* y = new cemDCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemDOUBLE a = static_cast<cemDOUBLE>(i)*cem_const::PI2/999.0;
        x[i] = cemDCOMPLEX(cos(a),sin(a));
        y[i] = cemDCOMPLEX(sin(a),-cos(a));
    }

    cemDCOMPLEX result = MKL_VectorDotProduct(N,x,y);

    ASSERT_DOUBLE_EQ(-2.4179443169902726e-14, result.real());
    ASSERT_DOUBLE_EQ(-1.0, result.imag());

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
}

TEST(MKL_BLAS_Level1,MKL_VectorDotProductFC)
{
    cemINT N = 1000;
    cemFCOMPLEX* x = new cemFCOMPLEX[N];
    cemFCOMPLEX* y = new cemFCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemFLOAT a = static_cast<cemFLOAT>(i)*cem_const::PI2/999.0;
        x[i] = cemFCOMPLEX(cos(a),sin(a));
        y[i] = cemFCOMPLEX(sin(a),-cos(a));
    }

    cemFCOMPLEX result = MKL_VectorDotProduct(N,x,y);

    ASSERT_FLOAT_EQ(2.2919849e-06, result.real());
    ASSERT_FLOAT_EQ(-1.000061, result.imag());

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
}


//************************************************************************************************//
// MKL_VectorDotProductConjugated:
//************************************************************************************************//
TEST(MKL_BLAS_Level1,MKL_VectorDotProductConjugatedDC)
{
    cemINT N = 1000;
    cemDCOMPLEX* x = new cemDCOMPLEX[N];
    cemDCOMPLEX* y = new cemDCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemDOUBLE a = static_cast<cemDOUBLE>(i)*cem_const::PI2/999.0;
        x[i] = cemDCOMPLEX(cos(a),sin(a));
        y[i] = cemDCOMPLEX(sin(a),-cos(a));
    }

    cemDCOMPLEX result = MKL_VectorDotProduct(N,x,y);

    ASSERT_DOUBLE_EQ(-2.417944316990272e-14, result.real());
    ASSERT_DOUBLE_EQ(-1.0, result.imag());

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
}

TEST(MKL_BLAS_Level1,MKL_VectorDotProductConjugatedFC)
{
    cemINT N = 1000;
    cemFCOMPLEX* x = new cemFCOMPLEX[N];
    cemFCOMPLEX* y = new cemFCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemFLOAT a = static_cast<cemFLOAT>(i)*cem_const::PI2/999.0;
        x[i] = cemFCOMPLEX(cos(a),sin(a));
        y[i] = cemFCOMPLEX(sin(a),-cos(a));
    }

    cemFCOMPLEX result = MKL_VectorDotProduct(N,x,y);

    ASSERT_FLOAT_EQ(2.2919849e-06, result.real());
    ASSERT_FLOAT_EQ(-1.000061, result.imag());

    CLEAN_ARRAY(x);
    CLEAN_ARRAY(y);
}


//************************************************************************************************//
// MKL_VectorNorm2:
//************************************************************************************************//
TEST(MKL_BLAS_Level1,MKL_VectorNorm2D)
{
    cemINT N = 1000;
    cemDOUBLE* x = new cemDOUBLE[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemDOUBLE a = static_cast<cemDOUBLE>(i)*cem_const::PI2/999.0;
        x[i] = cos(a);
    }

    cemDOUBLE result = MKL_VectorNorm2(N,x);

    ASSERT_DOUBLE_EQ(22.371857321197083, result);

    CLEAN_ARRAY(x);
}

TEST(MKL_BLAS_Level1,MKL_VectorNorm2F)
{
    cemINT N = 1000;
    cemFLOAT* x = new cemFLOAT[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemFLOAT a = static_cast<cemFLOAT>(i)*cem_const::PI2/999.0;
        x[i] = cos(a);
    }

    cemFLOAT result = MKL_VectorNorm2(N,x);

    ASSERT_FLOAT_EQ(22.37185, result);

    CLEAN_ARRAY(x);
}

TEST(MKL_BLAS_Level1,MKL_VectorNorm2DC)
{
    cemINT N = 1000;
    cemDCOMPLEX* x = new cemDCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemDOUBLE a = static_cast<cemDOUBLE>(i)*cem_const::PI2/999.0;
        x[i] = cemDCOMPLEX(cos(a),sin(a));
    }

    cemDOUBLE result = MKL_VectorNorm2(N,x);

    ASSERT_DOUBLE_EQ(31.622776601683793, result);

    CLEAN_ARRAY(x);
}

TEST(MKL_BLAS_Level1,MKL_VectorNorm2FC)
{
    cemINT N = 1000;
    cemFCOMPLEX* x = new cemFCOMPLEX[N];

    for (cemINT i=0; i<N; ++i)
    {
        cemFLOAT a = static_cast<cemFLOAT>(i)*cem_const::PI2/999.0;
        x[i] = cemFCOMPLEX(cos(a),sin(a));
    }

    cemFLOAT result = MKL_VectorNorm2(N,x);

    ASSERT_FLOAT_EQ(31.62277, result);

    CLEAN_ARRAY(x);
}


//************************************************************************************************//
// DenseMatrix:
//************************************************************************************************//
TEST(DenseMatrix,DefaultConstructor)
{
    DenseMatrix<cemDOUBLE> Ad;
    ASSERT_EQ(0,Ad.num_rows());
    ASSERT_EQ(0,Ad.num_columns());

    DenseMatrix<cemFLOAT> Af;
    ASSERT_EQ(0,Af.num_rows());
    ASSERT_EQ(0,Af.num_columns());

    DenseMatrix<cemDCOMPLEX> Adc;
    ASSERT_EQ(0,Adc.num_rows());
    ASSERT_EQ(0,Adc.num_columns());

    DenseMatrix<cemFCOMPLEX> Afc;
    ASSERT_EQ(0,Afc.num_rows());
    ASSERT_EQ(0,Afc.num_columns());

}

TEST(DenseMatrix,ConstructorWithSize)
{
    DenseMatrix<cemDOUBLE> Ad(10,30);
    ASSERT_EQ(10,Ad.num_rows());
    ASSERT_EQ(30,Ad.num_columns());

    DenseMatrix<cemFLOAT> Af(10,30);
    ASSERT_EQ(10,Af.num_rows());
    ASSERT_EQ(30,Af.num_columns());

    DenseMatrix<cemDCOMPLEX> Adc(10,30);
    ASSERT_EQ(10,Adc.num_rows());
    ASSERT_EQ(30,Adc.num_columns());

    DenseMatrix<cemFCOMPLEX> Afc(10,30);
    ASSERT_EQ(10,Afc.num_rows());
    ASSERT_EQ(30,Afc.num_columns());
}

TEST(DenseMatrix,SetAndGetEntryD)
{
    DenseMatrix<cemDOUBLE> A(2,2);
    A(1,1) = 2.;
    A(1,2) = cem_const::PI4;
    A(2,1) = -1.5;
    A(2,2) = 1.3e-4;

    cemDOUBLE A11 = A(1,1);
    cemDOUBLE A12 = A(1,2);
    cemDOUBLE A21 = A(2,1);
    cemDOUBLE A22 = A(2,2);

    ASSERT_DOUBLE_EQ(2.,A11);
    ASSERT_DOUBLE_EQ(cem_const::PI4,A12);
    ASSERT_DOUBLE_EQ(-1.5,A21);
    ASSERT_DOUBLE_EQ(1.3e-4,A22);
}

TEST(DenseMatrix,SetAndGetEntryF)
{
    DenseMatrix<cemFLOAT> A(2,2);
    A(1,1) = 2.;
    A(1,2) = cem_const::PI4;
    A(2,1) = -1.5;
    A(2,2) = 1.3e-4;

    cemFLOAT A11 = A(1,1);
    cemFLOAT A12 = A(1,2);
    cemFLOAT A21 = A(2,1);
    cemDOUBLE A22 = A(2,2);

    ASSERT_FLOAT_EQ(2.,A11);
    ASSERT_FLOAT_EQ(cem_const::PI4,A12);
    ASSERT_FLOAT_EQ(-1.5,A21);
    ASSERT_FLOAT_EQ(1.3e-4,A22);
}

TEST(DenseMatrix,SetAndGetEntryDC)
{
    DenseMatrix<cemDCOMPLEX> A(2,2);
    A(1,1) = cemDCOMPLEX(2.,-2.);
    A(1,2) = cemDCOMPLEX(cem_const::PI4,-cem_const::PI4);
    A(2,1) = cemDCOMPLEX(-1.5,1.5);
    A(2,2) = cemDCOMPLEX(1.3e-4,-1.3e-4);

    cemDCOMPLEX A11 = A(1,1);
    cemDCOMPLEX A12 = A(1,2);
    cemDCOMPLEX A21 = A(2,1);
    cemDCOMPLEX A22 = A(2,2);

    ASSERT_DOUBLE_EQ(2.,A11.real());
    ASSERT_DOUBLE_EQ(-2.,A11.imag());
    ASSERT_DOUBLE_EQ(cem_const::PI4,A12.real());
    ASSERT_DOUBLE_EQ(-cem_const::PI4,A12.imag());
    ASSERT_DOUBLE_EQ(-1.5,A21.real());
    ASSERT_DOUBLE_EQ(1.5,A21.imag());
    ASSERT_DOUBLE_EQ(1.3e-4,A22.real());
    ASSERT_DOUBLE_EQ(-1.3e-4,A22.imag());
}

TEST(DenseMatrix,SetAndGetEntryFC)
{
    DenseMatrix<cemFCOMPLEX> A(2,2);
    A(1,1) = cemFCOMPLEX(2.,-2.);
    A(1,2) = cemFCOMPLEX(cem_const::PI4,-cem_const::PI4);
    A(2,1) = cemFCOMPLEX(-1.5,1.5);
    A(2,2) = cemFCOMPLEX(1.3e-4,-1.3e-4);

    cemFCOMPLEX A11 = A(1,1);
    cemFCOMPLEX A12 = A(1,2);
    cemFCOMPLEX A21 = A(2,1);
    cemFCOMPLEX A22 = A(2,2);

    ASSERT_FLOAT_EQ(2.,A11.real());
    ASSERT_FLOAT_EQ(-2.,A11.imag());
    ASSERT_FLOAT_EQ(cem_const::PI4,A12.real());
    ASSERT_FLOAT_EQ(-cem_const::PI4,A12.imag());
    ASSERT_FLOAT_EQ(-1.5,A21.real());
    ASSERT_FLOAT_EQ(1.5,A21.imag());
    ASSERT_FLOAT_EQ(1.3e-4,A22.real());
    ASSERT_FLOAT_EQ(-1.3e-4,A22.imag());
}

TEST(DenseMatrix,CopyConstructorD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            A(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
    }

    DenseMatrix<cemDOUBLE> B(A);

    ASSERT_EQ(A.num_rows(),B.num_rows());
    ASSERT_EQ(A.num_columns(),B.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            ASSERT_DOUBLE_EQ(A(i,j),B(i,j));
    }
}

TEST(DenseMatrix,CopyConstructorF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            A(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
    }

    DenseMatrix<cemFLOAT> B(A);

    ASSERT_EQ(A.num_rows(),B.num_rows());
    ASSERT_EQ(A.num_columns(),B.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            ASSERT_FLOAT_EQ(A(i,j),B(i,j));
    }
}

TEST(DenseMatrix,CopyConstructorDC)
{
    cemDOUBLE a,b;
    srand(time(NULL));

    DenseMatrix<cemDCOMPLEX> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            a = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            b = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            A(i,j) = cemDCOMPLEX(a,b);
        }
    }

    DenseMatrix<cemDCOMPLEX> B(A);

    ASSERT_EQ(A.num_rows(),B.num_rows());
    ASSERT_EQ(A.num_columns(),B.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            ASSERT_DOUBLE_EQ(A(i,j).real(),B(i,j).real());
            ASSERT_DOUBLE_EQ(A(i,j).imag(),B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,CopyConstructorFC)
{
    cemFLOAT a,b;
    srand(time(NULL));

    DenseMatrix<cemFCOMPLEX> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            a = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            b = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            A(i,j) = cemFCOMPLEX(a,b);
        }
    }

    DenseMatrix<cemFCOMPLEX> B(A);

    ASSERT_EQ(A.num_rows(),B.num_rows());
    ASSERT_EQ(A.num_columns(),B.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            ASSERT_FLOAT_EQ(A(i,j).real(),B(i,j).real());
            ASSERT_FLOAT_EQ(A(i,j).imag(),B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,CopyOperatorD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            A(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
    }

    DenseMatrix<cemDOUBLE> B = A;

    ASSERT_EQ(A.num_rows(),B.num_rows());
    ASSERT_EQ(A.num_columns(),B.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            ASSERT_DOUBLE_EQ(A(i,j),B(i,j));
    }
}

TEST(DenseMatrix,CopyOperatorF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            A(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
    }

    DenseMatrix<cemFLOAT> B = A;

    ASSERT_EQ(A.num_rows(),B.num_rows());
    ASSERT_EQ(A.num_columns(),B.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            ASSERT_FLOAT_EQ(A(i,j),B(i,j));
    }
}

TEST(DenseMatrix,CopyOperatorDC)
{
    cemDOUBLE a,b;
    srand(time(NULL));

    DenseMatrix<cemDCOMPLEX> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            a = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            b = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            A(i,j) = cemDCOMPLEX(a,b);
        }
    }

    DenseMatrix<cemDCOMPLEX> B = A;

    ASSERT_EQ(A.num_rows(),B.num_rows());
    ASSERT_EQ(A.num_columns(),B.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            ASSERT_DOUBLE_EQ(A(i,j).real(),B(i,j).real());
            ASSERT_DOUBLE_EQ(A(i,j).imag(),B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,CopyOperatorFC)
{
    cemFLOAT a,b;
    srand(time(NULL));

    DenseMatrix<cemFCOMPLEX> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            a = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            b = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            A(i,j) = cemFCOMPLEX(a,b);
        }
    }

    DenseMatrix<cemFCOMPLEX> B = A;

    ASSERT_EQ(A.num_rows(),B.num_rows());
    ASSERT_EQ(A.num_columns(),B.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            ASSERT_FLOAT_EQ(A(i,j).real(),B(i,j).real());
            ASSERT_FLOAT_EQ(A(i,j).imag(),B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,InitializeD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            A(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
    }

    A.initialize();

    ASSERT_EQ(10,A.num_rows());
    ASSERT_EQ(5,A.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            ASSERT_DOUBLE_EQ(0.0,A(i,j));
    }
}

TEST(DenseMatrix,InitializeF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            A(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
    }

    A.initialize();

    ASSERT_EQ(10,A.num_rows());
    ASSERT_EQ(5,A.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            ASSERT_FLOAT_EQ(0.0,A(i,j));
    }
}

TEST(DenseMatrix,InitializeDC)
{
    cemDOUBLE a,b;
    srand(time(NULL));

    DenseMatrix<cemDCOMPLEX> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            a = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            b = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            A(i,j) = cemDCOMPLEX(a,b);
        }
    }

    A.initialize();

    ASSERT_EQ(10,A.num_rows());
    ASSERT_EQ(5,A.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            ASSERT_DOUBLE_EQ(0.0,A(i,j).real());
            ASSERT_DOUBLE_EQ(0.0,A(i,j).imag());
        }
    }
}

TEST(DenseMatrix,InitializeFC)
{
    cemFLOAT a,b;
    srand(time(NULL));

    DenseMatrix<cemFCOMPLEX> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            a = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            b = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            A(i,j) = cemFCOMPLEX(a,b);
        }
    }

    A.initialize();

    ASSERT_EQ(10,A.num_rows());
    ASSERT_EQ(5,A.num_columns());
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            ASSERT_FLOAT_EQ(0.0,A(i,j).real());
            ASSERT_FLOAT_EQ(0.0,A(i,j).imag());
        }
    }
}

TEST(DenseMatrix,Resize)
{
    DenseMatrix<cemDOUBLE> Ad(10,10);
    Ad.resize(3,5);
    ASSERT_EQ(3,Ad.num_rows());
    ASSERT_EQ(5,Ad.num_columns());

    DenseMatrix<cemFLOAT> Af(10,10);
    Af.resize(3,5);
    ASSERT_EQ(3,Af.num_rows());
    ASSERT_EQ(5,Af.num_columns());

    DenseMatrix<cemDCOMPLEX> Adc(10,10);
    Adc.resize(3,5);
    ASSERT_EQ(3,Adc.num_rows());
    ASSERT_EQ(5,Adc.num_columns());

    DenseMatrix<cemFCOMPLEX> Afc(10,10);
    Afc.resize(3,5);
    ASSERT_EQ(3,Afc.num_rows());
    ASSERT_EQ(5,Afc.num_columns());
}

TEST(DenseMatrix,AdditionD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemDOUBLE> A_plus_B(A);
    A_plus_B.add(B);

    ASSERT_EQ(A.num_rows(),A_plus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_plus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
            ASSERT_DOUBLE_EQ(A(i,j)+B(i,j),A_plus_B(i,j));
    }
}

TEST(DenseMatrix,AdditionF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemFLOAT> A_plus_B(A);
    A_plus_B.add(B);

    ASSERT_EQ(A.num_rows(),A_plus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_plus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
            ASSERT_FLOAT_EQ(A(i,j)+B(i,j),A_plus_B(i,j));
    }
}

TEST(DenseMatrix,AdditionDC)
{
    srand(time(NULL));
    DenseMatrix<cemDCOMPLEX> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j).real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            A(i,j).imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j).real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j).imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemDCOMPLEX> A_plus_B(A);
    A_plus_B.add(B);

    ASSERT_EQ(A.num_rows(),A_plus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_plus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
        {
            ASSERT_DOUBLE_EQ((A(i,j)+B(i,j)).real(), A_plus_B(i,j).real());
            ASSERT_DOUBLE_EQ((A(i,j)+B(i,j)).imag(), A_plus_B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,AdditionFC)
{
    srand(time(NULL));
    DenseMatrix<cemFCOMPLEX> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j).real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            A(i,j).imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j).real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j).imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemFCOMPLEX> A_plus_B(A);
    A_plus_B.add(B);

    ASSERT_EQ(A.num_rows(),A_plus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_plus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
        {
            ASSERT_FLOAT_EQ((A(i,j)+B(i,j)).real(), A_plus_B(i,j).real());
            ASSERT_FLOAT_EQ((A(i,j)+B(i,j)).imag(), A_plus_B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,AdditionOperatorD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemDOUBLE> A_plus_B(A);
    A_plus_B += B;

    ASSERT_EQ(A.num_rows(),A_plus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_plus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
            ASSERT_DOUBLE_EQ(A(i,j)+B(i,j),A_plus_B(i,j));
    }
}

TEST(DenseMatrix,AdditionOperatorF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemFLOAT> A_plus_B(A);
    A_plus_B += B;

    ASSERT_EQ(A.num_rows(),A_plus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_plus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
            ASSERT_FLOAT_EQ(A(i,j)+B(i,j),A_plus_B(i,j));
    }
}

TEST(DenseMatrix,AdditionOperatorDC)
{
    srand(time(NULL));
    DenseMatrix<cemDCOMPLEX> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j).real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            A(i,j).imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j).real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j).imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemDCOMPLEX> A_plus_B(A);
    A_plus_B += B;

    ASSERT_EQ(A.num_rows(),A_plus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_plus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
        {
            ASSERT_DOUBLE_EQ((A(i,j)+B(i,j)).real(), A_plus_B(i,j).real());
            ASSERT_DOUBLE_EQ((A(i,j)+B(i,j)).imag(), A_plus_B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,AdditionOperatorFC)
{
    srand(time(NULL));
    DenseMatrix<cemFCOMPLEX> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j).real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            A(i,j).imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j).real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j).imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemFCOMPLEX> A_plus_B(A);
    A_plus_B += B;

    ASSERT_EQ(A.num_rows(),A_plus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_plus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
        {
            ASSERT_FLOAT_EQ((A(i,j)+B(i,j)).real(), A_plus_B(i,j).real());
            ASSERT_FLOAT_EQ((A(i,j)+B(i,j)).imag(), A_plus_B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,SubstractionD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemDOUBLE> A_minus_B(A);
    A_minus_B.substract(B);

    ASSERT_EQ(A.num_rows(),A_minus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_minus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
            ASSERT_DOUBLE_EQ(A(i,j)-B(i,j),A_minus_B(i,j));
    }
}

TEST(DenseMatrix,SubstractionF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemFLOAT> A_minus_B(A);
    A_minus_B.substract(B);

    ASSERT_EQ(A.num_rows(),A_minus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_minus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
            ASSERT_FLOAT_EQ(A(i,j)-B(i,j),A_minus_B(i,j));
    }
}

TEST(DenseMatrix,SubstractionDC)
{
    srand(time(NULL));
    DenseMatrix<cemDCOMPLEX> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j).real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            A(i,j).imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j).real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j).imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemDCOMPLEX> A_minus_B(A);
    A_minus_B.substract(B);

    ASSERT_EQ(A.num_rows(),A_minus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_minus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
        {
            ASSERT_DOUBLE_EQ((A(i,j)-B(i,j)).real(), A_minus_B(i,j).real());
            ASSERT_DOUBLE_EQ((A(i,j)-B(i,j)).imag(), A_minus_B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,SubstractionFC)
{
    srand(time(NULL));
    DenseMatrix<cemFCOMPLEX> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j).real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            A(i,j).imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j).real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j).imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemFCOMPLEX> A_minus_B(A);
    A_minus_B.substract(B);

    ASSERT_EQ(A.num_rows(),A_minus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_minus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
        {
            ASSERT_FLOAT_EQ((A(i,j)-B(i,j)).real(), A_minus_B(i,j).real());
            ASSERT_FLOAT_EQ((A(i,j)-B(i,j)).imag(), A_minus_B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,SubstractionOperatorD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j) = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemDOUBLE> A_minus_B(A);
    A_minus_B -= B;

    ASSERT_EQ(A.num_rows(),A_minus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_minus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
            ASSERT_DOUBLE_EQ(A(i,j)-B(i,j),A_minus_B(i,j));
    }
}

TEST(DenseMatrix,SubstractionOperatorF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j) = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemFLOAT> A_minus_B(A);
    A_minus_B -= B;

    ASSERT_EQ(A.num_rows(),A_minus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_minus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
            ASSERT_FLOAT_EQ(A(i,j)-B(i,j),A_minus_B(i,j));
    }
}

TEST(DenseMatrix,SubstractionOperatorDC)
{
    srand(time(NULL));
    DenseMatrix<cemDCOMPLEX> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j).real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            A(i,j).imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j).real() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
            B(i,j).imag() = static_cast<cemDOUBLE>(rand() % 2000 - 1000)/static_cast<cemDOUBLE>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemDCOMPLEX> A_minus_B(A);
    A_minus_B -= B;

    ASSERT_EQ(A.num_rows(),A_minus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_minus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
        {
            ASSERT_DOUBLE_EQ((A(i,j)-B(i,j)).real(), A_minus_B(i,j).real());
            ASSERT_DOUBLE_EQ((A(i,j)-B(i,j)).imag(), A_minus_B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,SubstractionOperatorFC)
{
    srand(time(NULL));
    DenseMatrix<cemFCOMPLEX> A(3,5),B(3,5);

    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=3; ++i)
        {
            A(i,j).real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            A(i,j).imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j).real() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
            B(i,j).imag() = static_cast<cemFLOAT>(rand() % 2000 - 1000)/static_cast<cemFLOAT>(rand() % 100 + 1);
        }
    }

    DenseMatrix<cemFCOMPLEX> A_minus_B(A);
    A_minus_B -= B;

    ASSERT_EQ(A.num_rows(),A_minus_B.num_rows());
    ASSERT_EQ(A.num_columns(),A_minus_B.num_columns());
    for (cemINT j=1; j<=A.num_columns(); ++j)
    {
        for (cemINT i=1; i<=A.num_rows(); ++i)
        {
            ASSERT_FLOAT_EQ((A(i,j)-B(i,j)).real(), A_minus_B(i,j).real());
            ASSERT_FLOAT_EQ((A(i,j)-B(i,j)).imag(), A_minus_B(i,j).imag());
        }
    }
}

TEST(DenseMatrix,MultiplyByScalarD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            A(i,j) = cemDOUBLE(rand() % 2000 - 1000)/cemDOUBLE(rand() % 100 + 1);
    }

    cemDOUBLE scalar = cemDOUBLE(rand() % 2000 - 1000)/cemDOUBLE(rand() % 100 + 1);
    DenseMatrix<cemDOUBLE> B(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            B(i,j) = scalar*A(i,j);
    }

    A.multiply_by_scalar(scalar);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            ASSERT_DOUBLE_EQ(B(i,j),A(i,j));
    }
}

TEST(DenseMatrix,MultiplyByScalarF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            A(i,j) = cemFLOAT(rand() % 2000 - 1000)/cemFLOAT(rand() % 100 + 1);
    }

    cemFLOAT scalar = cemFLOAT(rand() % 2000 - 1000)/cemFLOAT(rand() % 100 + 1);
    DenseMatrix<cemFLOAT> B(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            B(i,j) = scalar*A(i,j);
    }

    A.multiply_by_scalar(scalar);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            ASSERT_FLOAT_EQ(B(i,j),A(i,j));
    }
}

TEST(DenseMatrix,MultiplyByScalarDC)
{
    srand(time(NULL));
    DenseMatrix<cemDCOMPLEX> A(10,5);
    cemDOUBLE a,b;
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            a = cemDOUBLE(rand() % 2000 - 1000)/cemDOUBLE(rand() % 100 + 1);
            b = cemDOUBLE(rand() % 2000 - 1000)/cemDOUBLE(rand() % 100 + 1);
            A(i,j) = cemDCOMPLEX(a,b);
        }
    }

    a = cemDOUBLE(rand() % 2000 - 1000)/cemDOUBLE(rand() % 100 + 1);
    b = cemDOUBLE(rand() % 2000 - 1000)/cemDOUBLE(rand() % 100 + 1);
    cemDCOMPLEX scalar = cemDCOMPLEX(a,b);
    DenseMatrix<cemDCOMPLEX> B(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            B(i,j) = scalar*A(i,j);
    }

    A.multiply_by_scalar(scalar);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            // Check relative difference:
            ASSERT_NEAR(B(i,j).real()/B(i,j).real(),A(i,j).real()/B(i,j).real(),1.0e-14);
            ASSERT_NEAR(B(i,j).imag()/B(i,j).imag(),A(i,j).imag()/B(i,j).imag(),1.0e-14);
        }
    }
}

TEST(DenseMatrix,MultiplyByScalarFC)
{
    srand(time(NULL));
    DenseMatrix<cemFCOMPLEX> A(10,5);
    cemFLOAT a,b;
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            a = cemFLOAT(rand() % 2000 - 1000)/cemFLOAT(rand() % 100 + 1);
            b = cemFLOAT(rand() % 2000 - 1000)/cemFLOAT(rand() % 100 + 1);
            A(i,j) = cemFCOMPLEX(a,b);
        }
    }

    a = cemFLOAT(rand() % 2000 - 1000)/cemFLOAT(rand() % 100 + 1);
    b = cemFLOAT(rand() % 2000 - 1000)/cemFLOAT(rand() % 100 + 1);
    cemFCOMPLEX scalar = cemFCOMPLEX(a,b);
    DenseMatrix<cemFCOMPLEX> B(10,5);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
            B(i,j) = scalar*A(i,j);
    }

    A.multiply_by_scalar(scalar);
    for (cemINT j=1; j<=5; ++j)
    {
        for (cemINT i=1; i<=10; ++i)
        {
            ASSERT_NEAR(B(i,j).real()/B(i,j).real(),A(i,j).real()/B(i,j).real(),1.0e-5);
            ASSERT_NEAR(B(i,j).imag()/B(i,j).imag(),A(i,j).imag()/B(i,j).imag(),1.0e-5);
        }
    }
}

TEST(DenseMatrix,DeterminantD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(2,2);
    A(1,1) = 0.814723686393179;
    A(1,2) = 0.126986816293506;
    A(2,1) = 0.905791937075619;
    A(2,2) = 0.913375856139019;
    ASSERT_DOUBLE_EQ(0.629125310262547,A.determinant());

    A.resize(2,3);
    ASSERT_THROW(A.determinant(),Exception);

    A.resize(3,3);
    ASSERT_THROW(A.determinant(),Exception);
}

TEST(DenseMatrix,DeterminantF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(2,2);
    A(1,1) = 0.81472368;
    A(1,2) = 0.12698681;
    A(2,1) = 0.90579193;
    A(2,2) = 0.91337585;
    ASSERT_FLOAT_EQ(0.6291253,A.determinant());

    A.resize(2,3);
    ASSERT_THROW(A.determinant(),Exception);

    A.resize(3,3);
    ASSERT_THROW(A.determinant(),Exception);
}

TEST(DenseMatrix,DeterminantDC)
{
    srand(time(NULL));
    DenseMatrix<cemDCOMPLEX> A(2,2);
    A(1,1) = cemDCOMPLEX(0.814723686393179,0.632359246225410);
    A(1,2) = cemDCOMPLEX(0.126986816293506,0.278498218867048);
    A(2,1) = cemDCOMPLEX(0.905791937075619,0.097540404999410);
    A(2,2) = cemDCOMPLEX(0.913375856139019,0.546881519204984);

    ASSERT_NEAR(0.310464554063383,A.determinant().real(),1.0e-15);
    ASSERT_NEAR(0.758491208624997,A.determinant().imag(),1.0e-15);

    A.resize(2,3);
    ASSERT_THROW(A.determinant(),Exception);

    A.resize(3,3);
    ASSERT_THROW(A.determinant(),Exception);
}

TEST(DenseMatrix,DeterminantFC)
{
    srand(time(NULL));
    DenseMatrix<cemFCOMPLEX> A(2,2);
    A(1,1) = cemFCOMPLEX(0.81472368,0.63235924);
    A(1,2) = cemFCOMPLEX(0.12698681,0.27849821);
    A(2,1) = cemFCOMPLEX(0.90579193,0.09754040);
    A(2,2) = cemFCOMPLEX(0.91337585,0.54688151);

    ASSERT_NEAR(0.31046455,A.determinant().real(),1.0e-7);
    ASSERT_NEAR(0.75849121,A.determinant().imag(),1.0e-7);

    A.resize(2,3);
    ASSERT_THROW(A.determinant(),Exception);

    A.resize(3,3);
    ASSERT_THROW(A.determinant(),Exception);
}

TEST(DenseMatrix,InverseD)
{
    srand(time(NULL));
    DenseMatrix<cemDOUBLE> A(2,2);
    A(1,1) = 0.814723686393179;
    A(1,2) = 0.126986816293506;
    A(2,1) = 0.905791937075619;
    A(2,2) = 0.913375856139019;
    DenseMatrix<cemDOUBLE> B = A.inverse();

    ASSERT_NEAR(1.451818646046602,B(1,1),1.0e-15);
    ASSERT_NEAR(-0.201846618188850,B(1,2),1.0e-15);
    ASSERT_NEAR(-1.439763942572289,B(2,1),1.0e-15);
    ASSERT_NEAR(1.295010188118449,B(2,2),1.0e-15);

    A.resize(2,3);
    ASSERT_THROW(A.inverse(),Exception);

    A.resize(3,3);
    ASSERT_THROW(A.inverse(),Exception);
}

TEST(DenseMatrix,InverseF)
{
    srand(time(NULL));
    DenseMatrix<cemFLOAT> A(2,2);
    A(1,1) = 0.81472368;
    A(1,2) = 0.12698681;
    A(2,1) = 0.90579193;
    A(2,2) = 0.91337585;
    DenseMatrix<cemFLOAT> B = A.inverse();

    ASSERT_NEAR(1.45181864,B(1,1),1.0e-7);
    ASSERT_NEAR(-0.20184661,B(1,2),1.0e-7);
    ASSERT_NEAR(-1.43976394,B(2,1),1.0e-7);
    ASSERT_NEAR(1.295010188,B(2,2),1.0e-7);

    A.resize(2,3);
    ASSERT_THROW(A.inverse(),Exception);

    A.resize(3,3);
    ASSERT_THROW(A.inverse(),Exception);
}

TEST(DenseMatrix,InverseDC)
{
    srand(time(NULL));
    DenseMatrix<cemDCOMPLEX> A(2,2);
    A(1,1) = cemDCOMPLEX(0.814723686393179,0.632359246225410);
    A(1,2) = cemDCOMPLEX(0.126986816293506,0.278498218867048);
    A(2,1) = cemDCOMPLEX(0.905791937075619,0.097540404999410);
    A(2,2) = cemDCOMPLEX(0.913375856139019,0.546881519204984);
    DenseMatrix<cemDCOMPLEX> B = A.inverse();

    ASSERT_NEAR(1.039718047544057,B(1,1).real(),1.0e-14);
    ASSERT_NEAR(-0.778625051208193,B(1,1).imag(),1.0e-15);
    ASSERT_NEAR(-0.373179125208346,B(1,2).real(),1.0e-15);
    ASSERT_NEAR(0.014671133262186,B(1,2).imag(),1.0e-15);
    ASSERT_NEAR(-0.528809490954782,B(2,1).real(),1.0e-15);
    ASSERT_NEAR(0.977750731780093,B(2,1).imag(),1.0e-15);
    ASSERT_NEAR(1.090642936005292,B(2,2).real(),1.0e-15);
    ASSERT_NEAR(-0.627716851836727,B(2,2).imag(),1.0e-15);
}

TEST(DenseMatrix,InverseFC)
{
    srand(time(NULL));
    DenseMatrix<cemFCOMPLEX> A(2,2);
    A(1,1) = cemFCOMPLEX(0.81472368,0.63235924);
    A(1,2) = cemFCOMPLEX(0.12698681,0.27849821);
    A(2,1) = cemFCOMPLEX(0.90579193,0.09754040);
    A(2,2) = cemFCOMPLEX(0.91337585,0.54688151);
    DenseMatrix<cemFCOMPLEX> B = A.inverse();

    ASSERT_NEAR(1.03971804,B(1,1).real(),1.0e-7);
    ASSERT_NEAR(-0.77862505,B(1,1).imag(),1.0e-6);
    ASSERT_NEAR(-0.37317912,B(1,2).real(),1.0e-7);
    ASSERT_NEAR(0.01467113,B(1,2).imag(),1.0e-7);
    ASSERT_NEAR(-0.52880949,B(2,1).real(),1.0e-7);
    ASSERT_NEAR(0.97775073,B(2,1).imag(),1.0e-6);
    ASSERT_NEAR(1.09064293,B(2,2).real(),1.0e-7);
    ASSERT_NEAR(-0.62771685,B(2,2).imag(),1.0e-6);
}


int TestMathBasics()
{
    DenseMatrix<cemFCOMPLEX> A(2,2);
    A(1,1) = cemFCOMPLEX(0.81472368,0.63235924);
    A(1,2) = cemFCOMPLEX(0.12698681,0.27849821);
    A(2,1) = cemFCOMPLEX(0.90579193,0.09754040);
    A(2,2) = cemFCOMPLEX(0.91337585,0.54688151);

    std::ofstream myfile;
    myfile.open("TestMatrix.out",std::ofstream::out);
    myfile.precision(15);

    A.WriteToFileByColumns(myfile);
}
