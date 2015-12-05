#include "testcemspace.h"
#include "cemSpace.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cstring>

using namespace cem_space;

/////////////////////////////////////////////////////////////////////
/// Main Test Function:
/////////////////////////////////////////////////////////////////////
int RunTestCEMSpace(int argc, char* argv[])
{
    std::cout << "Running cem_space Test" << std::endl;

    if (argc < 2)
        throw("INSUFFICIENT_INPUT_ARGUMENTS","Must specify test to run");

    if (!strcmp(argv[1],"-V2D_Basics"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "V2D_Basics.*";
        return RUN_ALL_TESTS();
    }


    if (!strcmp(argv[1],"-V3D_Basics"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "V3D_Basics.*";
        return RUN_ALL_TESTS();
    }

    return 1;
}






//************************************************************************************************//
// Double precision 2D Vector:
//************************************************************************************************//
TEST(V2D_Basics, DefaultConstructor)
{
    V2D v1;
    ASSERT_DOUBLE_EQ(0.0, v1[0]);
    ASSERT_DOUBLE_EQ(0.0, v1[1]);
}

TEST(V2D_Basics, ConstructorFromCoordinates)
{
    V2D v1(1.0,-2.3);
    ASSERT_DOUBLE_EQ(1.0, v1[0]);
    ASSERT_DOUBLE_EQ(-2.3, v1[1]);
}

TEST(V2D_Basics, CopyConstructor)
{
    V2D v1(1.0,-2.3);
    V2D v2(v1);
    ASSERT_DOUBLE_EQ(1.0, v2[0]);
    ASSERT_DOUBLE_EQ(-2.3, v2[1]);
}

TEST(V2D_Basics, Copy_operator)
{
    V2D v1(1.0,-2.3);
    V2D v2 = v1;
    ASSERT_DOUBLE_EQ(1.0, v2[0]);
    ASSERT_DOUBLE_EQ(-2.3, v2[1]);
}

TEST(V2D_Basics, RandomAccessAssignment)
{
    V2D v1;
    v1[0] = 1.0; v1[1] = -2.3;
    ASSERT_DOUBLE_EQ(1.0, v1[0]);
    ASSERT_DOUBLE_EQ(-2.3, v1[1]);
}


TEST(V2D_Math, EqualOperator)
{
    V2D v1(4.5,0.0023);
    V2D v2(4.5,0.0021);
    V2D v3(v1);
    ASSERT_TRUE(v1 == v3);
    ASSERT_FALSE(v1 == v2);
}

TEST(V2D_Math, MultiplyByScalar)
{
    V2D v1(4.5,-3.2);
    v1 *= -2.0;
    EXPECT_DOUBLE_EQ(4.5*-2.0, v1[0]);
    EXPECT_DOUBLE_EQ(-3.2*-2.0, v1[1]);
}

TEST(V2D_Math, Addition)
{
    V2D v1(4.5,-3.2);
    v1.Add(V2D(1.233,0.2));
    EXPECT_DOUBLE_EQ(4.5+1.233, v1[0]);
    EXPECT_DOUBLE_EQ(-3.2+0.2, v1[1]);
}

TEST(V2D_Math, AdditionOperator)
{
    V2D v1(4.5,-3.2);
    V2D v2 = v1 + V2D(1.233,0.2);
    EXPECT_DOUBLE_EQ(4.5+1.233, v2[0]);
    EXPECT_DOUBLE_EQ(-3.2+0.2, v2[1]);
}

TEST(V2D_Math, Substraction)
{
    V2D v1(4.5,-3.2);
    v1.Substract(V2D(-1.233,0.2));
    EXPECT_DOUBLE_EQ(4.5-(-1.233), v1[0]);
    EXPECT_DOUBLE_EQ(-3.2-0.2, v1[1]);
}

TEST(V2D_Math, SubstractionOperator)
{
    V2D v1(4.5,-3.2);
    V2D v2 = v1 - V2D(6.233,-0.2);
    EXPECT_DOUBLE_EQ(4.5-6.233, v2[0]);
    EXPECT_DOUBLE_EQ(-3.2-(-0.2), v2[1]);
}

TEST(V2D_Math, DotProduct)
{
    V2D v1(0.5,0.5);
    V2D v2(1.0,0.0);
    V2D v3(1.0,-1.0);
    EXPECT_DOUBLE_EQ(0.5, v1.Dot(v2));
    EXPECT_DOUBLE_EQ(0.5, v1.Dot(v1));
    EXPECT_DOUBLE_EQ(0.0, v1.Dot(v3));
}

TEST(V2D_Math, Norm)
{
    V2D v1(0.5,0.5);
    V2D v2(1.0,0.0);
    V2D v3(1.0,-1.0);
    EXPECT_DOUBLE_EQ(sqrt(0.5), v1.Norm());
    EXPECT_DOUBLE_EQ(sqrt(1.0), v2.Norm());
    EXPECT_DOUBLE_EQ(sqrt(2.0), v3.Norm());
}

TEST(V2D_Math, CrossProduct)
{
    V2D v1(0.5,0.5);
    V2D v2(1.0,0.0);
    V2D v3(1.0,-1.0);
    EXPECT_DOUBLE_EQ(-0.5, v1.Cross(v2));
    EXPECT_DOUBLE_EQ(-1.0, v1.Cross(v3));
    EXPECT_DOUBLE_EQ(-1.0, v2.Cross(v3));
    EXPECT_DOUBLE_EQ(0.0, v2.Cross(v2));
}



//************************************************************************************************//
// Double precision 3D Vector:
//************************************************************************************************//
TEST(V3D_Basics, DefaultConstructor)
{
    V3D v1;
    ASSERT_DOUBLE_EQ(0.0, v1[0]);
    ASSERT_DOUBLE_EQ(0.0, v1[1]);
    ASSERT_DOUBLE_EQ(0.0, v1[2]);
}

TEST(V3D_Basics, ConstructorFromCoordinates)
{
    V3D v1(1.0,-2.3,5.2);
    ASSERT_DOUBLE_EQ(1.0, v1[0]);
    ASSERT_DOUBLE_EQ(-2.3, v1[1]);
    ASSERT_DOUBLE_EQ(5.2, v1[2]);
}

TEST(V3D_Basics, CopyConstructor)
{
    V3D v1(1.0,-2.3,5.2);
    V3D v2(v1);
    ASSERT_DOUBLE_EQ(1.0, v2[0]);
    ASSERT_DOUBLE_EQ(-2.3, v2[1]);
    ASSERT_DOUBLE_EQ(5.2, v2[2]);
}

TEST(V3D_Basics, CopyOperator)
{
    V3D v1(1.0,-2.3,5.2);
    V3D v2 = v1;
    ASSERT_DOUBLE_EQ(1.0, v2[0]);
    ASSERT_DOUBLE_EQ(-2.3, v2[1]);
    ASSERT_DOUBLE_EQ(5.2, v2[2]);
}

TEST(V3D_Basics, RandomAccessAssignment)
{
    V3D v1;
    v1[0] = 1.0; v1[1] = -2.3; v1[2] = 5.2;
    ASSERT_DOUBLE_EQ(1.0, v1[0]);
    ASSERT_DOUBLE_EQ(-2.3, v1[1]);
    ASSERT_DOUBLE_EQ(5.2, v1[2]);
}


TEST(V3D_Math, EqualOperator)
{
    V3D v1(4.5,0.0023,-0.02);
    V3D v2(4.5,0.0021,-0.02);
    V3D v3(v1);
    ASSERT_TRUE(v1 == v3);
    ASSERT_FALSE(v1 == v2);
}

TEST(V3D_Math, MultiplyByScalar)
{
    V3D v1(4.5,-3.2,5.2);
    v1 *= -2.0;
    EXPECT_DOUBLE_EQ(4.5*-2.0, v1[0]);
    EXPECT_DOUBLE_EQ(-3.2*-2.0, v1[1]);
    EXPECT_DOUBLE_EQ(5.2*-2.0, v1[2]);
}

TEST(V3D_Math, Addition)
{
    V3D v1(4.5,-3.2,5.2);
    v1.Add(V3D(1.233,0.2,1.2));
    EXPECT_DOUBLE_EQ(4.5+1.233, v1[0]);
    EXPECT_DOUBLE_EQ(-3.2+0.2, v1[1]);
    EXPECT_DOUBLE_EQ(5.2+1.2, v1[2]);
}

TEST(V3D_Math, AdditionOperator)
{
    V3D v1(4.5,-3.2,5.2);
    V3D v2 = v1 + V3D(1.233,0.2,1.2);
    EXPECT_DOUBLE_EQ(4.5+1.233, v2[0]);
    EXPECT_DOUBLE_EQ(-3.2+0.2, v2[1]);
    EXPECT_DOUBLE_EQ(5.2+1.2, v2[2]);
}

TEST(V3D_Math, Substraction)
{
    V3D v1(4.5,-3.2,5.2);
    v1.Substract(V3D(-1.233,0.2,1.2));
    EXPECT_DOUBLE_EQ(4.5-(-1.233), v1[0]);
    EXPECT_DOUBLE_EQ(-3.2-0.2, v1[1]);
    EXPECT_DOUBLE_EQ(5.2-1.2, v1[2]);
}

TEST(V3D_Math, SubstractionOperator)
{
    V3D v1(4.5,-3.2,5.2);
    V3D v2 = v1 - V3D(6.233,-0.2,1.2);
    EXPECT_DOUBLE_EQ(4.5-6.233, v2[0]);
    EXPECT_DOUBLE_EQ(-3.2-(-0.2), v2[1]);
    EXPECT_DOUBLE_EQ(5.2-1.2, v2[2]);
}

TEST(V3D_Math, DotProduct)
{
    V3D v1(0.5,0.5,2.1);
    V3D v2(1.0,0.0,0.0);
    V3D v3(1.0,-1.0,3.2);
    V3D v4(0.0,0.0,1.0);
    EXPECT_DOUBLE_EQ(0.5, v1.Dot(v2));
    EXPECT_DOUBLE_EQ(4.91, v1.Dot(v1));
    EXPECT_DOUBLE_EQ(6.72, v1.Dot(v3));
    EXPECT_DOUBLE_EQ(0.0, v2.Dot(v4));
}

TEST(V3D_Math, Norm)
{
    V3D v1(0.5,0.5,2.1);
    V3D v2(1.0,0.0,0.0);
    V3D v3(1.0,-1.0,3.2);
    EXPECT_DOUBLE_EQ(sqrt(4.91), v1.Norm());
    EXPECT_DOUBLE_EQ(sqrt(1.0), v2.Norm());
    EXPECT_DOUBLE_EQ(sqrt(12.24), v3.Norm());
}

TEST(V3D_Math, CrossProduct)
{
    V3D v1(0.5,0.5,2.1);
    V3D v2(1.0,0.0,3.4);
    V3D v3(0.0,-1.0,0.0);
    EXPECT_DOUBLE_EQ(1.7, v1.Cross(v2)[0]);
    EXPECT_DOUBLE_EQ(0.4, v1.Cross(v2)[1]);
    EXPECT_DOUBLE_EQ(-0.5, v1.Cross(v2)[2]);
}
