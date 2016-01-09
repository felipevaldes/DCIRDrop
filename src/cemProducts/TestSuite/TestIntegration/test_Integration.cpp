#include "test_Integration.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "cemConsts.h"

using cemcommon::Exception;

//************************************************************************************************//
// Main Test Function:
//************************************************************************************************//
int RunTestIntegration(int argc, char* argv[])
{
    std::cout << "Running Integration Test" << std::endl;

    if (argc < 2)
        throw(Exception("INSUFFICIENT_INPUT_ARGUMENTS","Must specify test to run"));

    if (!strcmp(argv[1],"-LineQuadrature"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "TestLineQuadrature.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-TriQuadrature"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "TestTriQuadrature.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-QuadQuadrature"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "QuadQuadrature.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-TetraQuadrature"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "TetraQuadrature.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-HexaQuadrature"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "HexaQuadrature.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-PrismQuadrature"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "PrismQuadrature.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-PyraQuadrature"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "PyraQuadrature.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-BasicTest"))
    {
        return TestIntegrationBasics();
    }
    return 1;
}



//************************************************************************************************//
// LineQuadrature:
//************************************************************************************************//
TEST_F(TestLineQuadrature,getNumPointsForPolyOrder)
{
    cem_core::LineQuadrature line_quadrature;
    ASSERT_EQ(1,line_quadrature.getNumPointsForPolyOrder(1));
    ASSERT_EQ(2,line_quadrature.getNumPointsForPolyOrder(2));
    ASSERT_EQ(2,line_quadrature.getNumPointsForPolyOrder(3));
    ASSERT_EQ(3,line_quadrature.getNumPointsForPolyOrder(4));
    ASSERT_EQ(3,line_quadrature.getNumPointsForPolyOrder(5));
    ASSERT_EQ(5,line_quadrature.getNumPointsForPolyOrder(6));
    ASSERT_EQ(5,line_quadrature.getNumPointsForPolyOrder(7));
    ASSERT_EQ(5,line_quadrature.getNumPointsForPolyOrder(8));
    ASSERT_EQ(5,line_quadrature.getNumPointsForPolyOrder(9));
    ASSERT_EQ(7,line_quadrature.getNumPointsForPolyOrder(10));
    ASSERT_EQ(7,line_quadrature.getNumPointsForPolyOrder(13));
    ASSERT_EQ(9,line_quadrature.getNumPointsForPolyOrder(14));
    ASSERT_EQ(9,line_quadrature.getNumPointsForPolyOrder(17));
    ASSERT_EQ(32,line_quadrature.getNumPointsForPolyOrder(18));
    ASSERT_EQ(32,line_quadrature.getNumPointsForPolyOrder(50));
    ASSERT_EQ(32,line_quadrature.getNumPointsForPolyOrder(63));
    ASSERT_EQ(100,line_quadrature.getNumPointsForPolyOrder(64));
    ASSERT_EQ(100,line_quadrature.getNumPointsForPolyOrder(100));
    ASSERT_EQ(100,line_quadrature.getNumPointsForPolyOrder(199));
    ASSERT_EQ(100,line_quadrature.getNumPointsForPolyOrder(250));
}


TEST_F(TestLineQuadrature,getNumPointsAbove)
{
    cem_core::LineQuadrature line_quadrature;
    ASSERT_EQ(1,line_quadrature.getNumPointsAbove(0));
    ASSERT_EQ(2,line_quadrature.getNumPointsAbove(1));
    ASSERT_EQ(3,line_quadrature.getNumPointsAbove(2));
    ASSERT_EQ(5,line_quadrature.getNumPointsAbove(3));
    ASSERT_EQ(5,line_quadrature.getNumPointsAbove(4));
    ASSERT_EQ(7,line_quadrature.getNumPointsAbove(5));
    ASSERT_EQ(7,line_quadrature.getNumPointsAbove(6));
    ASSERT_EQ(9,line_quadrature.getNumPointsAbove(7));
    ASSERT_EQ(32,line_quadrature.getNumPointsAbove(9));
    ASSERT_EQ(32,line_quadrature.getNumPointsAbove(20));
    ASSERT_EQ(32,line_quadrature.getNumPointsAbove(31));
    ASSERT_EQ(100,line_quadrature.getNumPointsAbove(32));
    ASSERT_EQ(100,line_quadrature.getNumPointsAbove(100));
    ASSERT_EQ(100,line_quadrature.getNumPointsAbove(150));
}


TEST_F(TestLineQuadrature,getNumPointsBelow)
{
    cem_core::LineQuadrature line_quadrature;
    ASSERT_EQ(1,line_quadrature.getNumPointsBelow(0));
    ASSERT_EQ(1,line_quadrature.getNumPointsBelow(1));
    ASSERT_EQ(1,line_quadrature.getNumPointsBelow(2));
    ASSERT_EQ(2,line_quadrature.getNumPointsBelow(3));
    ASSERT_EQ(3,line_quadrature.getNumPointsBelow(4));
    ASSERT_EQ(3,line_quadrature.getNumPointsBelow(5));
    ASSERT_EQ(5,line_quadrature.getNumPointsBelow(6));
    ASSERT_EQ(5,line_quadrature.getNumPointsBelow(7));
    ASSERT_EQ(7,line_quadrature.getNumPointsBelow(9));
    ASSERT_EQ(9,line_quadrature.getNumPointsBelow(20));
    ASSERT_EQ(9,line_quadrature.getNumPointsBelow(32));
    ASSERT_EQ(32,line_quadrature.getNumPointsBelow(40));
    ASSERT_EQ(32,line_quadrature.getNumPointsBelow(100));
    ASSERT_EQ(100,line_quadrature.getNumPointsBelow(150));
}


TEST_F(TestLineQuadrature,getKsiCoordinates)
{
    cem_core::LineQuadrature line_quadrature;
    std::vector<cemDOUBLE> ksi = line_quadrature.getKsiCoordinates(0);
    ASSERT_EQ(1,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(1);
    ASSERT_EQ(1,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(2);
    ASSERT_EQ(2,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(3);
    ASSERT_EQ(3,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(4);
    ASSERT_EQ(5,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(5);
    ASSERT_EQ(5,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(6);
    ASSERT_EQ(7,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(7);
    ASSERT_EQ(7,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(8);
    ASSERT_EQ(9,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(9);
    ASSERT_EQ(9,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(10);
    ASSERT_EQ(32,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(32);
    ASSERT_EQ(32,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(33);
    ASSERT_EQ(100,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(100);
    ASSERT_EQ(100,ksi.size());

    ksi = line_quadrature.getKsiCoordinates(101);
    ASSERT_EQ(100,ksi.size());
}


TEST_F(TestLineQuadrature,getEtaCoordinates)
{
    cem_core::LineQuadrature line_quadrature;
    std::vector<cemDOUBLE> eta;
    ASSERT_THROW(eta = line_quadrature.getEtaCoordinates(3),Exception);
}


TEST_F(TestLineQuadrature,getZetaCoordinates)
{
    cem_core::LineQuadrature line_quadrature;
    std::vector<cemDOUBLE> zeta;
    ASSERT_THROW(zeta = line_quadrature.getZetaCoordinates(3),Exception);
}


TEST_F(TestLineQuadrature,getWeights)
{
    cem_core::LineQuadrature line_quadrature;
    std::vector<cemDOUBLE> weights = line_quadrature.getWeights(0);
    ASSERT_EQ(1,weights.size());

    weights = line_quadrature.getWeights(1);
    ASSERT_EQ(1,weights.size());

    weights = line_quadrature.getWeights(2);
    ASSERT_EQ(2,weights.size());

    weights = line_quadrature.getWeights(3);
    ASSERT_EQ(3,weights.size());

    weights = line_quadrature.getWeights(4);
    ASSERT_EQ(5,weights.size());

    weights = line_quadrature.getWeights(5);
    ASSERT_EQ(5,weights.size());

    weights = line_quadrature.getWeights(6);
    ASSERT_EQ(7,weights.size());

    weights = line_quadrature.getWeights(7);
    ASSERT_EQ(7,weights.size());

    weights = line_quadrature.getWeights(8);
    ASSERT_EQ(9,weights.size());

    weights = line_quadrature.getWeights(9);
    ASSERT_EQ(9,weights.size());

    weights = line_quadrature.getWeights(10);
    ASSERT_EQ(32,weights.size());

    weights = line_quadrature.getWeights(32);
    ASSERT_EQ(32,weights.size());

    weights = line_quadrature.getWeights(33);
    ASSERT_EQ(100,weights.size());

    weights = line_quadrature.getWeights(100);
    ASSERT_EQ(100,weights.size());

    weights = line_quadrature.getWeights(101);
    ASSERT_EQ(100,weights.size());
}


TEST_F(TestLineQuadrature,IntegrateCosine)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out");
    myfile.precision(15);

    myfile <<"Target function: cos(x) in [-1,1] \n";
    cemDOUBLE ref_integral = sin(1.0)-sin(-1.0);
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,cos,num_points);
    ASSERT_DOUBLE_EQ(2.000000000000000e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,cos,num_points);
    ASSERT_DOUBLE_EQ(1.675823655389986e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,cos,num_points);
    ASSERT_DOUBLE_EQ(1.683003547726917e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,cos,num_points);
    ASSERT_DOUBLE_EQ(1.682941970407192e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,cos,num_points);
    ASSERT_DOUBLE_EQ(1.682941969615795e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,cos,num_points);
    ASSERT_DOUBLE_EQ(1.682941969615793e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,cos,num_points);
    ASSERT_DOUBLE_EQ(1.682941969615793e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,cos,num_points);
    ASSERT_DOUBLE_EQ(1.682941969615793e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateExp)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: exp(x) in [-1,1] \n";
    cemDOUBLE ref_integral = exp(1.0)-exp(-1.0);
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,exp,num_points);
    ASSERT_DOUBLE_EQ(2.000000000000000e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,exp,num_points);
    ASSERT_DOUBLE_EQ(2.342696087909731e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,exp,num_points);
    ASSERT_DOUBLE_EQ(2.350336928680012e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,exp,num_points);
    ASSERT_DOUBLE_EQ(2.350402386462826e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,exp,num_points);
    ASSERT_DOUBLE_EQ(2.350402387287601e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,exp,num_points);
    ASSERT_DOUBLE_EQ(2.350402387287603e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,exp,num_points);
    ASSERT_DOUBLE_EQ(2.350402387287603e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(-1.0,1.0,exp,num_points);
    ASSERT_DOUBLE_EQ(2.350402387287603e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateFunction_1)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x*log(1+x) in [0,1] \n";
    cemDOUBLE ref_integral = 0.25;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(2.027325540540822e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(2.495545554442331e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(2.499921975044656e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(2.499999962581781e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(2.499999999977567e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(2.499999999999985e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(2.500000000000000e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(2.499999999999999e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateFunction_2)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x*x*atan(x) in [0,1] \n";
    cemDOUBLE ref_integral = (cem_const::PI - 2.0 + 2.0*log(2.0))/12.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(1.159119022502015e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(2.123380593966721e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(2.106302088281428e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(2.106572906063017e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(2.106572512483713e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(2.106572512256971e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(2.106572512258070e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(2.106572512258071e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateFunction_3)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: exp(x)*cos(x) in [0,Pi/2] \n";
    cemDOUBLE ref_integral = (exp(cem_const::PI_2) - 1.0)/2.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(0.0,cem_const::PI_2,TestLineQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(2.436121629006761e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(0.0,cem_const::PI_2,TestLineQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(1.918285395094117e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(0.0,cem_const::PI_2,TestLineQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(1.905088091687486e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(0.0,cem_const::PI_2,TestLineQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(1.905238693365986e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(0.0,cem_const::PI_2,TestLineQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(1.905238690482664e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(0.0,cem_const::PI_2,TestLineQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(1.905238690482676e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(0.0,cem_const::PI_2,TestLineQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(1.905238690482675e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(0.0,cem_const::PI_2,TestLineQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(1.905238690482676e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateFunction_4)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: atan(a)/(a*(1 + x*x)) with a = sqrt(2 + x*x) in [0,1.0] \n";
    cemDOUBLE ref_integral = 5.0*cem_const::PI*cem_const::PI/96.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(5.241566523985755e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(5.152190935363204e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(5.139389806310826e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(5.140418933025982e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(5.140418964131599e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(5.140418958897665e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(5.140418958900709e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(5.140418958900709e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateFunction_5)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: sqrt(x)*log(x) in [0,1] \n";
    cemDOUBLE ref_integral = -4.0/9.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(-4.901290717342736e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(-4.626847119368207e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(-4.526947822619530e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(-4.471135950315620e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(-4.456447772926272e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(-4.450908089417169e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(-4.444679097300714e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(-4.444454667349589e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateFunction_6)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: sqrt(1 - x*x) in [0,1] \n";
    cemDOUBLE ref_integral = cem_const::PI_4;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(8.660254037844386e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(7.961130193772735e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(7.890181737599545e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(7.862954439173374e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(7.857479195233215e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(7.855693956042623e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(7.854024078342015e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(7.853983068468604e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateFunction_7)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: log(x)*log(x) in [0,1] \n";
    cemDOUBLE ref_integral = 2.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(4.804530139182014e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.236195024460259e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.541266707265132e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.776878742816362e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.866199794951230e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.910032349753549e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.989379500480530e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(0.0,1.0,TestLineQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.998607174905489e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


TEST_F(TestLineQuadrature,IntegrateFunction_8)
{
    std::ofstream myfile;
    myfile.open("TestLineQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: 1/(x) in [0.1,1] \n";
    cemDOUBLE ref_integral = -log(0.1);
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestLineQuadrature::Integrate(0.1,1.0,TestLineQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(1.636363636363636e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 2 Point Rule:
    num_points = 2;
    integral = TestLineQuadrature::Integrate(0.1,1.0,TestLineQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(2.106382978723404e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestLineQuadrature::Integrate(0.1,1.0,TestLineQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(2.246609743847312e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 5 Point Rule:
    num_points = 5;
    integral = TestLineQuadrature::Integrate(0.1,1.0,TestLineQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(2.298283110737402e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 7 Point Rule:
    num_points = 7;
    integral = TestLineQuadrature::Integrate(0.1,1.0,TestLineQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(2.302264348289719e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 9 Point Rule:
    num_points = 9;
    integral = TestLineQuadrature::Integrate(0.1,1.0,TestLineQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(2.302561429363706e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 32 Point Rule:
    num_points = 32;
    integral = TestLineQuadrature::Integrate(0.1,1.0,TestLineQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(2.302585092994045e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 100 Point Rule:
    num_points = 100;
    integral = TestLineQuadrature::Integrate(0.1,1.0,TestLineQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(2.302585092994045e+00,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    myfile << std::endl;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::Integrate : Integrates function in the interval [a,b] using
 * num_points quadrature points. Computes \f$ \int\limits_{a}^{b}f(t)dt \f$
 * @param [in] a : lower limit of interation
 * @param [in] b : upper limit of integration
 * @param [in] num_points : number of points to be used in quadrature rule.
 * @return : \f$ \int\limits_{a}^{b}f(t)dt \f$ */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::Integrate(const cemDOUBLE &a,
                                        const cemDOUBLE &b,
                                        cemDOUBLE (*function)(cemDOUBLE),
                                        const cemINT& num_points)
{
    cem_core::LineQuadrature line_quadrature;
    std::vector<cemDOUBLE> ksi = line_quadrature.getKsiCoordinates(num_points);
    std::vector<cemDOUBLE> weights = line_quadrature.getWeights(num_points);

    // Transform points and weights to interval [a,b]:
    for (cemINT i=0; i<num_points; ++i)
    {
        ksi[i] = (a+b)/2.0 + (b-a)*ksi[i]/2.0;
        weights[i] = fabs(b-a)*weights[i]/2.0;
    }

    // Compute the integral:
    cemDOUBLE integral = 0.0;
    for (cemINT i=0; i<num_points; ++i)
        integral += function(ksi[i])*weights[i];

    return integral;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::TestFunction_1 : \f$ f(x) = x\log(1+x) \f$. */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::TestFunction_1(const cemDOUBLE x)
{
    cemDOUBLE y = x*log(1.0 + x);
    return y;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::TestFunction_2: \f$ f(x) = x^2\tan^{-1}(x) \f$ */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::TestFunction_2(const cemDOUBLE x)
{
    cemDOUBLE y = x*x*atan(x);
    return y;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::TestFunction_3 : \f$ f(x) = e^x\cos(x) \f$ */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::TestFunction_3(const cemDOUBLE x)
{
    cemDOUBLE y = exp(x)*cos(x);
    return y;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::TestFunction_4 : \f$ \tan^{-1}(a)/(a*(1 + x*x)) \f$, with
 * \f$ a = \sqrt(2 + x*x) \f$ */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::TestFunction_4(const cemDOUBLE x)
{
    cemDOUBLE a = sqrt(2.0 + x*x);
    cemDOUBLE y = atan(a)/(a*(1 + x*x));
    return y;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::TestFunction_5 : \f$ \sqrt(x)*\log(x) \f$ */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::TestFunction_5(const cemDOUBLE x)
{
    cemDOUBLE y = sqrt(x)*log(x);
    return y;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::TestFunction_6 : \f$ \sqrt(1 - x^2) \f$ */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::TestFunction_6(const cemDOUBLE x)
{
    cemDOUBLE y = sqrt(1 - x*x);
    return y;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::TestFunction_7 : \f$ \log(x)*\log(x) \f$ */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::TestFunction_7(const cemDOUBLE x)
{
    cemDOUBLE y = log(x)*log(x);
    return y;
}


//************************************************************************************************//
/** @brief TestLineQuadrature::TestFunction_8 : \f$ 1/x \f$ */
//************************************************************************************************//
cemDOUBLE TestLineQuadrature::TestFunction_8(const cemDOUBLE x)
{
    cemDOUBLE y = 1/x;
    return y;
}



//************************************************************************************************//
// TriQuadrature:
//************************************************************************************************//
TEST_F(TestTriQuadrature,getNumPointsForPolyOrder)
{
    cem_core::TriQuadrature tri_quadrature;
    ASSERT_EQ(1,tri_quadrature.getNumPointsForPolyOrder(1));
    ASSERT_EQ(3,tri_quadrature.getNumPointsForPolyOrder(2));
    ASSERT_EQ(6,tri_quadrature.getNumPointsForPolyOrder(3));
    ASSERT_EQ(6,tri_quadrature.getNumPointsForPolyOrder(4));
    ASSERT_EQ(12,tri_quadrature.getNumPointsForPolyOrder(5));
    ASSERT_EQ(12,tri_quadrature.getNumPointsForPolyOrder(6));
    ASSERT_EQ(13,tri_quadrature.getNumPointsForPolyOrder(7));
    ASSERT_EQ(16,tri_quadrature.getNumPointsForPolyOrder(8));
    ASSERT_EQ(19,tri_quadrature.getNumPointsForPolyOrder(9));
    ASSERT_EQ(25,tri_quadrature.getNumPointsForPolyOrder(10));
    ASSERT_EQ(33,tri_quadrature.getNumPointsForPolyOrder(11));
    ASSERT_EQ(33,tri_quadrature.getNumPointsForPolyOrder(12));
    ASSERT_EQ(37,tri_quadrature.getNumPointsForPolyOrder(13));
    ASSERT_EQ(42,tri_quadrature.getNumPointsForPolyOrder(14));
    ASSERT_EQ(42,tri_quadrature.getNumPointsForPolyOrder(15));
}


TEST_F(TestTriQuadrature,getNumPointsAbove)
{
    cem_core::TriQuadrature tri_quadrature;
    ASSERT_EQ(1,tri_quadrature.getNumPointsAbove(0));
    ASSERT_EQ(3,tri_quadrature.getNumPointsAbove(1));
    ASSERT_EQ(3,tri_quadrature.getNumPointsAbove(2));
    ASSERT_EQ(6,tri_quadrature.getNumPointsAbove(3));
    ASSERT_EQ(6,tri_quadrature.getNumPointsAbove(4));
    ASSERT_EQ(6,tri_quadrature.getNumPointsAbove(5));
    ASSERT_EQ(12,tri_quadrature.getNumPointsAbove(6));
    ASSERT_EQ(12,tri_quadrature.getNumPointsAbove(11));
    ASSERT_EQ(13,tri_quadrature.getNumPointsAbove(12));
    ASSERT_EQ(16,tri_quadrature.getNumPointsAbove(13));
    ASSERT_EQ(16,tri_quadrature.getNumPointsAbove(14));
    ASSERT_EQ(16,tri_quadrature.getNumPointsAbove(15));
    ASSERT_EQ(19,tri_quadrature.getNumPointsAbove(16));
    ASSERT_EQ(19,tri_quadrature.getNumPointsAbove(18));
    ASSERT_EQ(25,tri_quadrature.getNumPointsAbove(19));
    ASSERT_EQ(25,tri_quadrature.getNumPointsAbove(24));
    ASSERT_EQ(33,tri_quadrature.getNumPointsAbove(25));
    ASSERT_EQ(33,tri_quadrature.getNumPointsAbove(32));
    ASSERT_EQ(37,tri_quadrature.getNumPointsAbove(33));
    ASSERT_EQ(37,tri_quadrature.getNumPointsAbove(36));
    ASSERT_EQ(42,tri_quadrature.getNumPointsAbove(37));
    ASSERT_EQ(42,tri_quadrature.getNumPointsAbove(41));
    ASSERT_EQ(42,tri_quadrature.getNumPointsAbove(42));
    ASSERT_EQ(42,tri_quadrature.getNumPointsAbove(43));
}


TEST_F(TestTriQuadrature,getNumPointsBelow)
{
    cem_core::TriQuadrature tri_quadrature;
    ASSERT_EQ(1,tri_quadrature.getNumPointsBelow(0));
    ASSERT_EQ(1,tri_quadrature.getNumPointsBelow(1));
    ASSERT_EQ(1,tri_quadrature.getNumPointsBelow(3));
    ASSERT_EQ(3,tri_quadrature.getNumPointsBelow(6));
    ASSERT_EQ(6,tri_quadrature.getNumPointsBelow(12));
    ASSERT_EQ(12,tri_quadrature.getNumPointsBelow(13));
    ASSERT_EQ(13,tri_quadrature.getNumPointsBelow(16));
    ASSERT_EQ(16,tri_quadrature.getNumPointsBelow(19));
    ASSERT_EQ(19,tri_quadrature.getNumPointsBelow(25));
    ASSERT_EQ(25,tri_quadrature.getNumPointsBelow(33));
    ASSERT_EQ(33,tri_quadrature.getNumPointsBelow(37));
    ASSERT_EQ(37,tri_quadrature.getNumPointsBelow(42));
    ASSERT_EQ(42,tri_quadrature.getNumPointsBelow(43));
}


TEST_F(TestTriQuadrature,getKsiCoordinates)
{
    cem_core::TriQuadrature tri_quadrature;
    std::vector<cemDOUBLE> ksi = tri_quadrature.getKsiCoordinates(0);
    ASSERT_EQ(1,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(1);
    ASSERT_EQ(1,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(2);
    ASSERT_EQ(3,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(3);
    ASSERT_EQ(3,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(4);
    ASSERT_EQ(6,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(6);
    ASSERT_EQ(6,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(7);
    ASSERT_EQ(12,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(12);
    ASSERT_EQ(12,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(13);
    ASSERT_EQ(13,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(14);
    ASSERT_EQ(16,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(16);
    ASSERT_EQ(16,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(19);
    ASSERT_EQ(19,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(25);
    ASSERT_EQ(25,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(33);
    ASSERT_EQ(33,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(37);
    ASSERT_EQ(37,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(42);
    ASSERT_EQ(42,ksi.size());

    ksi = tri_quadrature.getKsiCoordinates(43);
    ASSERT_EQ(42,ksi.size());
}


TEST_F(TestTriQuadrature,getEtaCoordinates)
{
    cem_core::TriQuadrature tri_quadrature;
    std::vector<cemDOUBLE> eta = tri_quadrature.getEtaCoordinates(0);
    ASSERT_EQ(1,eta.size());

    eta = tri_quadrature.getEtaCoordinates(1);
    ASSERT_EQ(1,eta.size());

    eta = tri_quadrature.getEtaCoordinates(2);
    ASSERT_EQ(3,eta.size());

    eta = tri_quadrature.getEtaCoordinates(3);
    ASSERT_EQ(3,eta.size());

    eta = tri_quadrature.getEtaCoordinates(4);
    ASSERT_EQ(6,eta.size());

    eta = tri_quadrature.getEtaCoordinates(6);
    ASSERT_EQ(6,eta.size());

    eta = tri_quadrature.getEtaCoordinates(7);
    ASSERT_EQ(12,eta.size());

    eta = tri_quadrature.getEtaCoordinates(12);
    ASSERT_EQ(12,eta.size());

    eta = tri_quadrature.getEtaCoordinates(13);
    ASSERT_EQ(13,eta.size());

    eta = tri_quadrature.getEtaCoordinates(14);
    ASSERT_EQ(16,eta.size());

    eta = tri_quadrature.getEtaCoordinates(16);
    ASSERT_EQ(16,eta.size());

    eta = tri_quadrature.getEtaCoordinates(19);
    ASSERT_EQ(19,eta.size());

    eta = tri_quadrature.getEtaCoordinates(25);
    ASSERT_EQ(25,eta.size());

    eta = tri_quadrature.getEtaCoordinates(33);
    ASSERT_EQ(33,eta.size());

    eta = tri_quadrature.getEtaCoordinates(37);
    ASSERT_EQ(37,eta.size());

    eta = tri_quadrature.getEtaCoordinates(42);
    ASSERT_EQ(42,eta.size());

    eta = tri_quadrature.getEtaCoordinates(43);
    ASSERT_EQ(42,eta.size());
}


TEST_F(TestTriQuadrature,getZetaCoordinates)
{
    cem_core::LineQuadrature line_quadrature;
    std::vector<cemDOUBLE> zeta;
    ASSERT_THROW(zeta = line_quadrature.getZetaCoordinates(3),Exception);
}


TEST_F(TestTriQuadrature,getWeights)
{
    cem_core::TriQuadrature tri_quadrature;
    std::vector<cemDOUBLE> weights = tri_quadrature.getWeights(0);
    ASSERT_EQ(1,weights.size());

    weights = tri_quadrature.getWeights(1);
    ASSERT_EQ(1,weights.size());

    weights = tri_quadrature.getWeights(2);
    ASSERT_EQ(3,weights.size());

    weights = tri_quadrature.getWeights(3);
    ASSERT_EQ(3,weights.size());

    weights = tri_quadrature.getWeights(4);
    ASSERT_EQ(6,weights.size());

    weights = tri_quadrature.getWeights(6);
    ASSERT_EQ(6,weights.size());

    weights = tri_quadrature.getWeights(7);
    ASSERT_EQ(12,weights.size());

    weights = tri_quadrature.getWeights(12);
    ASSERT_EQ(12,weights.size());

    weights = tri_quadrature.getWeights(13);
    ASSERT_EQ(13,weights.size());

    weights = tri_quadrature.getWeights(14);
    ASSERT_EQ(16,weights.size());

    weights = tri_quadrature.getWeights(16);
    ASSERT_EQ(16,weights.size());

    weights = tri_quadrature.getWeights(19);
    ASSERT_EQ(19,weights.size());

    weights = tri_quadrature.getWeights(25);
    ASSERT_EQ(25,weights.size());

    weights = tri_quadrature.getWeights(33);
    ASSERT_EQ(33,weights.size());

    weights = tri_quadrature.getWeights(37);
    ASSERT_EQ(37,weights.size());

    weights = tri_quadrature.getWeights(42);
    ASSERT_EQ(42,weights.size());

    weights = tri_quadrature.getWeights(43);
    ASSERT_EQ(42,weights.size());
}


TEST_F(TestTriQuadrature,IntegrateFunction_1)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out");
    myfile.precision(15);

    myfile <<"Target function: 1.0-x-y in unit triangle \n";
    cemDOUBLE ref_integral = 1.0/6.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666667e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666667e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666664e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666671e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666663e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666667e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666658e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666666e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666660e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666666e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_1,num_points);
    ASSERT_DOUBLE_EQ(1.666666666666680e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_2)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x*y*(1.0-x-y) in unit triangle \n";
    cemDOUBLE ref_integral = 1.0/120.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(1.851851851851852e-02,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(9.259259259259260e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333307e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333328e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333323e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333333e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333302e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333326e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333302e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333328e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_2,num_points);
    ASSERT_DOUBLE_EQ(8.333333333333368e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_3)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x^2*y*(1.0-x-y)^2 in unit triangle \n";
    cemDOUBLE ref_integral = 4.0/5040.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(2.057613168724281e-03,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.716049382716051e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.685368180931346e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.936507936507929e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.936507936507932e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.936507936507943e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.936507936507913e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.936507936507937e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.936507936507912e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.936507936507938e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_3,num_points);
    ASSERT_DOUBLE_EQ(7.936507936507964e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_4)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x^2*y^2*(1.0-x-y)^2 in unit triangle \n";
    cemDOUBLE ref_integral = 8.0/40320.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(6.858710562414270e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.714677640603567e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.626043057670054e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.984126984126978e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.984126984126986e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.984126984126983e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.984126984126979e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.984126984126985e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.984126984126979e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.984126984126984e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_4,num_points);
    ASSERT_DOUBLE_EQ(1.984126984126991e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_5)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x^3*y^2*(1.0-x-y) in unit triangle \n";
    cemDOUBLE ref_integral = 12.0/40320.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(6.858710562414266e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(3.000685871056241e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(3.029662561630647e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(2.976190476190468e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(2.976190476190476e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(2.976190476190475e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(2.976190476190465e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(2.976190476190475e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(2.976190476190465e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(2.976190476190472e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_5,num_points);
    ASSERT_DOUBLE_EQ(2.976190476190486e-04,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_6)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x*y^3*(1.0-x-y)^5 in unit triangle \n";
    cemDOUBLE ref_integral = 720.0/39916800.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(2.540263171264546e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.805968348320886e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(2.148465488998503e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.828259272481520e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.826520159650364e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.793703259808663e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.803751803751796e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.803751803751802e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.803751803751797e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.803751803751802e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_6,num_points);
    ASSERT_DOUBLE_EQ(1.803751803751810e-05,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_7)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x^2*y^6*(1.0-x-y)^3 in unit triangle \n";
    cemDOUBLE ref_integral = 8640.0/6227020800.0;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(2.822514634738382e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.918427915798745e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.239639786228440e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.370853893746941e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.422838235215303e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.373541027319793e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.387495133307054e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.387900681231028e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.387501387501383e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.387501387501389e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_7,num_points);
    ASSERT_DOUBLE_EQ(1.387501387501394e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_8)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: x^2*y^10*(1.0-x-y)^2 in unit triangle \n";
    cemDOUBLE ref_integral = 14515200.0/2.0922789888e13;
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(1.045375790643845e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(2.230203078359907e-06,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(6.728325761410579e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(5.795974581627627e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(5.673354212230065e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(7.861347769004644e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(6.818354408873951e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(6.933411363839870e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(6.938169407056549e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(6.937512486745678e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_8,num_points);
    ASSERT_DOUBLE_EQ(6.937506937506979e-07,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_9)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: cos(Pi*(x+y)) in unit triangle \n";
    cemDOUBLE ref_integral = -2.0/pow(cem_const::PI,2);
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.499999999999999e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.053418012614795e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.023703540311838e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.026437361197842e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.026421980634653e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.026424083295346e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.026423679498464e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.026423670387499e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.026423672836888e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.026423672846817e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_9,num_points);
    ASSERT_DOUBLE_EQ(-2.026423672846764e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}


TEST_F(TestTriQuadrature,IntegrateFunction_10)
{
    std::ofstream myfile;
    myfile.open("TestTriQuadrature.out",std::ofstream::out | std::ofstream::app);
    myfile.precision(15);

    myfile <<"Target function: exp(x+y)*cos(Pi*(x+y)) in unit triangle \n";
    cemDOUBLE ref_integral = (1.0-(1.0+2.0*exp(1.0))*pow(cem_const::PI,2))/pow(1.0+pow(cem_const::PI,2),2);
    cemDOUBLE integral;

    // 1 Point Rule:
    cemINT num_points = 1;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-4.869335102636687e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 3 Point Rule:
    num_points = 3;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.479334895790646e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 6 Point Rule:
    num_points = 6;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.287515327121890e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 12 Point Rule:
    num_points = 12;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.292198182862208e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 13 Point Rule:
    num_points = 13;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.292211813991023e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 16 Point Rule:
    num_points = 16;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.292190044939685e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 19 Point Rule:
    num_points = 19;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.292190974957981e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 25 Point Rule:
    num_points = 25;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.292191014398939e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 33 Point Rule:
    num_points = 33;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.292191007675764e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 37 Point Rule:
    num_points = 37;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.292191007651471e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;

    // 42 Point Rule:
    num_points = 42;
    integral = TestTriQuadrature::Integrate(TestTriQuadrature::TestFunction_10,num_points);
    ASSERT_DOUBLE_EQ(-5.292191007649477e-01,integral);
    myfile << std::setw(3)  << num_points << std::scientific
           << std::setw(25) << integral
           << std::setw(25) << ref_integral
           << std::setw(25) << fabs(integral-ref_integral)/fabs(ref_integral) << std::endl;
}



//************************************************************************************************//
/** @brief TestTriQuadrature::Integrate : Integrates function on a unit triangle using
 * num_points quadrature points. Computes \f$ \int\limits_{0}^{1}\int\limits_{0}^{1-x}f(x,y)dydx \f$
 * @param [in] num_points : number of points to be used in quadrature rule.
 * @return : \f$ \int\limits_{0}^{1}\int\limits_{0}^{1-x}f(x,y)dydx \f$  */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::Integrate(cemDOUBLE (*function)(cemDOUBLE, cemDOUBLE),
                                       const cemINT &num_points)
{
    cem_core::TriQuadrature tri_quadrature;
    std::vector<cemDOUBLE> ksi = tri_quadrature.getKsiCoordinates(num_points);
    std::vector<cemDOUBLE> eta = tri_quadrature.getEtaCoordinates(num_points);
    std::vector<cemDOUBLE> weights = tri_quadrature.getWeights(num_points);

    // Compute the integral:
    cemDOUBLE integral = 0.0;
    for (cemINT i=0; i<num_points; ++i)
        integral += function(ksi[i],eta[i])*weights[i];

    return integral/2.0; // Multiplied by the area of the unit triangle.
}


//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_1 : \f$ f(x,y) = 1-x-y \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_1(const cemDOUBLE x, const cemDOUBLE y)
{
    cemDOUBLE L1 = x;
    cemDOUBLE L2 = y;
    cemDOUBLE L3 = 1.0 - x - y;

    return L3;
}

//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_2 : \f$ f(x,y) = xy(1-x-y) \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_2(const cemDOUBLE x, const cemDOUBLE y)
{
    cemDOUBLE L1 = x;
    cemDOUBLE L2 = y;
    cemDOUBLE L3 = 1.0 - x - y;

    return L1*L2*L3;
}

//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_3 : \f$ f(x,y) = x^2y(1-x-y)^2 \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_3(const cemDOUBLE x, const cemDOUBLE y)
{
    cemDOUBLE L1 = x;
    cemDOUBLE L2 = y;
    cemDOUBLE L3 = 1.0 - x - y;

    return pow(L1,2)*L2*pow(L3,2);
}

//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_4 : \f$ f(x,y) = x^2y^2(1-x-y)^2 \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_4(const cemDOUBLE x, const cemDOUBLE y)
{
    cemDOUBLE L1 = x;
    cemDOUBLE L2 = y;
    cemDOUBLE L3 = 1.0 - x - y;

    return pow(L1,2)*pow(L2,2)*pow(L3,2);
}

//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_5 : \f$ f(x,y) = x^3y^2(1-x-y) \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_5(const cemDOUBLE x, const cemDOUBLE y)
{
    cemDOUBLE L1 = x;
    cemDOUBLE L2 = y;
    cemDOUBLE L3 = 1.0 - x - y;

    return pow(L1,3)*pow(L2,2)*pow(L3,1);
}

//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_6 : \f$ f(x,y) = xy^3(1-x-y)^5 \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_6(const cemDOUBLE x, const cemDOUBLE y)
{
    cemDOUBLE L1 = x;
    cemDOUBLE L2 = y;
    cemDOUBLE L3 = 1.0 - x - y;

    return pow(L1,1)*pow(L2,3)*pow(L3,5);
}

//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_7 : \f$ f(x,y) = x^2y^6(1-x-y)^3 \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_7(const cemDOUBLE x, const cemDOUBLE y)
{
    cemDOUBLE L1 = x;
    cemDOUBLE L2 = y;
    cemDOUBLE L3 = 1.0 - x - y;

    return pow(L1,2)*pow(L2,6)*pow(L3,3);
}

//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_8 : \f$ f(x,y) = x^2y^10(1-x-y)^2 \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_8(const cemDOUBLE x, const cemDOUBLE y)
{
    cemDOUBLE L1 = x;
    cemDOUBLE L2 = y;
    cemDOUBLE L3 = 1.0 - x - y;

    return pow(L1,2)*pow(L2,10)*pow(L3,2);
}

//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_9 : \f$ f(x,y) = \cos(\pi(x+y)) \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_9(const cemDOUBLE x, const cemDOUBLE y)
{
    return cos(cem_const::PI*(x+y));
}


//************************************************************************************************//
/** @brief TestTriQuadrature::TestFunction_10 : \f$ e^{x+y}\cos(\pi(x+y)) \f$. */
//************************************************************************************************//
cemDOUBLE TestTriQuadrature::TestFunction_10(const cemDOUBLE x, const cemDOUBLE y)
{
    return exp(x+y)*cos(cem_const::PI*(x+y));
}








int TestIntegrationBasics()
{
    cem_core::LineQuadrature line_quadrature;
    const std::vector<cemDOUBLE> eta_points = line_quadrature.getKsiCoordinates(200);
    for (cemINT i=0; i<eta_points.size(); ++i)
        std::cout << eta_points[i] << std::endl;
    return 0;
}
