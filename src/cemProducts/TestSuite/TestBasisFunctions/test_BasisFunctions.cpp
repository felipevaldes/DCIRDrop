#include "test_BasisFunctions.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "cemConsts.h"
#include "Quadrature/Quadrature.h"

using cemcommon::Exception;

//************************************************************************************************//
// Main Test Function:
//************************************************************************************************//
int RunTestBasisFunctions(int argc, char* argv[])
{
    std::cout << "Running BasisFunctions Test" << std::endl;

    if (argc < 2)
        throw(Exception("INSUFFICIENT_INPUT_ARGUMENTS","Must specify test to run"));

    if (!strcmp(argv[1],"-SilvesterPolynomial"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "*.SilvesterPolynomial*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-TriShapeFunction"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "TriShapeFunction.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-BasicTest"))
    {
        return TestBasisFunctionsBasics();
    }
    return 1;
}


//************************************************************************************************//
// ShapeFunction:
//************************************************************************************************//

TEST(ShapeFunction,SilvesterPolynomial)
{
    cem_core::ShapeFunction silvester_poly(4);
    // Zeros of polynomial order 4, index 3
    ASSERT_DOUBLE_EQ(0.0,silvester_poly.SilvesterPolynomial(3,0.0));
    ASSERT_DOUBLE_EQ(0.0,silvester_poly.SilvesterPolynomial(3,0.25));
    ASSERT_DOUBLE_EQ(0.0,silvester_poly.SilvesterPolynomial(3,0.5));
    // Unity of polynomial order 4, index 3
    ASSERT_DOUBLE_EQ(1.0,silvester_poly.SilvesterPolynomial(3,0.75));
    // POlynomial of index 0 is 1 everywhere
    ASSERT_DOUBLE_EQ(1.0,silvester_poly.SilvesterPolynomial(0,0.9));
    ASSERT_DOUBLE_EQ(1.0,silvester_poly.SilvesterPolynomial(0,0.25));
    ASSERT_DOUBLE_EQ(1.0,silvester_poly.SilvesterPolynomial(0,0.5));
    ASSERT_DOUBLE_EQ(1.0,silvester_poly.SilvesterPolynomial(0,0.75));
    ASSERT_DOUBLE_EQ(1.0,silvester_poly.SilvesterPolynomial(0,1.0));
    // Polynomial order 4, index 3 at a few random points:
    ASSERT_DOUBLE_EQ(2.039411434636285e-03,silvester_poly.SilvesterPolynomial(3,0.001543829598320));
    ASSERT_DOUBLE_EQ(-1.938480422774855e-02,silvester_poly.SilvesterPolynomial(3,0.483948596305930));
    ASSERT_DOUBLE_EQ(3.169139075451275e+00,silvester_poly.SilvesterPolynomial(3,0.948473819182819));
    ASSERT_DOUBLE_EQ(1.875130946015111e+00,silvester_poly.SilvesterPolynomial(3,0.847327458294832));
    ASSERT_DOUBLE_EQ(4.101757899136337e-02,silvester_poly.SilvesterPolynomial(3,0.183840202895423));
}


TEST(ShapeFunction,SilvesterPolynomialDeriv)
{
    // Test SilvesterPolynomialDeriv by integrating it and comparing the result with
    // the Silvester Polynomial itself.
    cem_core::ShapeFunction silvester_poly(4);
    ASSERT_NEAR(silvester_poly.SilvesterPolynomial(3,0.25),IntegrateSilvesterDeriv(0.0,0.25,4,3),1.0e-15);
    ASSERT_NEAR(silvester_poly.SilvesterPolynomial(3,0.5),IntegrateSilvesterDeriv(0.0,0.5,4,3),1.0e-15);
    ASSERT_DOUBLE_EQ(silvester_poly.SilvesterPolynomial(3,0.75),IntegrateSilvesterDeriv(0.0,0.75,4,3));
    ASSERT_DOUBLE_EQ(2.039411434636285e-03,IntegrateSilvesterDeriv(0.0,0.001543829598320,4,3));
    ASSERT_NEAR(-1.938480422774855e-02,IntegrateSilvesterDeriv(0.0,0.483948596305930,4,3),1.0e-15);
    ASSERT_DOUBLE_EQ(3.169139075451275e+00,IntegrateSilvesterDeriv(0.0,0.948473819182819,4,3));
    ASSERT_DOUBLE_EQ(1.875130946015111e+00,IntegrateSilvesterDeriv(0.0,0.847327458294832,4,3));
    ASSERT_DOUBLE_EQ(4.101757899136337e-02,IntegrateSilvesterDeriv(0.0,0.183840202895423,4,3));
}

//************************************************************************************************//
/** @brief IntegrateSilvesterDeriv : Integrates Silvester Polynomial's derivative along
 * the segment [a,b] using quadrature rules for lines.
 * @param a : lower limit of integration
 * @param b : upper limit of integration
 * @param order : order of the Silvester Polynomial whose derivative is being integrated
 * @param index : index of the Silvester Polynomial whose derivative is being integrated
 * @return */
//************************************************************************************************//
cemDOUBLE IntegrateSilvesterDeriv(cemDOUBLE a,cemDOUBLE b,cemINT order,cemINT index)
{
    cem_core::LineQuadrature line_quadrature;
    cemINT num_points = line_quadrature.getNumPointsForPolyOrder(order);
    std::vector<cemDOUBLE> ksi = line_quadrature.getKsiCoordinates(num_points);
    std::vector<cemDOUBLE> weights = line_quadrature.getWeights(num_points);

    // Transform points and weights to interval [a,b]:
    for (cemINT i=0; i<num_points; ++i)
    {
        ksi[i] = (a+b)/2.0 + (b-a)*ksi[i]/2.0;
        weights[i] = fabs(b-a)*weights[i]/2.0;
    }

    // Compute the integral:
    cem_core::ShapeFunction silvester_poly(order);
    cemDOUBLE integral = 0.0;
    for (cemINT i=0; i<num_points; ++i)
        integral += silvester_poly.SilvesterPolynomialDeriv(index,ksi[i])*weights[i];

    return integral;
}



//************************************************************************************************//
// TriShapeFunction:
//************************************************************************************************//

TEST(TriShapeFunction,Evaluate)
{
    cem_core::TriShapeFunction shape_function(6);
    ASSERT_DOUBLE_EQ(0.0,shape_function.Evaluate(2,1,2,0.0,0.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.Evaluate(2,1,2,1.0,0.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.Evaluate(2,1,2,0.0,1.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.Evaluate(2,1,2,0.5,0.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.Evaluate(2,1,2,0.5,0.5));
    ASSERT_DOUBLE_EQ(0.0,shape_function.Evaluate(2,1,2,0.0,0.5));
    ASSERT_DOUBLE_EQ(-6.566400000000004e-01,shape_function.Evaluate(2,1,2,0.8,0.1));
    ASSERT_DOUBLE_EQ(-6.566400000000004e-01,shape_function.Evaluate(2,1,2,0.1,0.1));
    ASSERT_DOUBLE_EQ(6.912000000000001e-02,shape_function.Evaluate(2,1,2,0.1,0.8));
    ASSERT_DOUBLE_EQ(2.177279999999999e+00,shape_function.Evaluate(2,1,2,0.3,0.3));
}


TEST(TriShapeFunction,EvaluateKsiDeriv)
{
    cem_core::TriShapeFunction shape_function(6);
    ASSERT_DOUBLE_EQ(0.0,shape_function.EvaluateKsiDeriv(2,1,2,0.0,0.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.EvaluateKsiDeriv(2,1,2,1.0,0.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.EvaluateKsiDeriv(2,1,2,0.0,1.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.EvaluateKsiDeriv(2,1,2,0.5,0.0));
    ASSERT_DOUBLE_EQ(27.0,shape_function.EvaluateKsiDeriv(2,1,2,0.5,0.5));
    ASSERT_DOUBLE_EQ(-27.0,shape_function.EvaluateKsiDeriv(2,1,2,0.0,0.5));
    ASSERT_NEAR(-5.1408e+00,shape_function.EvaluateKsiDeriv(2,1,2,0.8,0.1),1.0e-14);
    ASSERT_NEAR(5.1408e+00,shape_function.EvaluateKsiDeriv(2,1,2,0.1,0.1),1.0e-14);
    ASSERT_NEAR(0.0,shape_function.EvaluateKsiDeriv(2,1,2,0.1,0.8),1.0e-15);
    ASSERT_DOUBLE_EQ(8.8128e+00,shape_function.EvaluateKsiDeriv(2,1,2,0.3,0.3));
}


TEST(TriShapeFunction,EvaluateEtaDeriv)
{
    cem_core::TriShapeFunction shape_function(6);
    ASSERT_DOUBLE_EQ(0.0,shape_function.EvaluateEtaDeriv(2,1,2,0.0,0.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.EvaluateEtaDeriv(2,1,2,1.0,0.0));
    ASSERT_DOUBLE_EQ(0.0,shape_function.EvaluateEtaDeriv(2,1,2,0.0,1.0));
    ASSERT_DOUBLE_EQ(54.0,shape_function.EvaluateEtaDeriv(2,1,2,0.5,0.0));
    ASSERT_DOUBLE_EQ(27.0,shape_function.EvaluateEtaDeriv(2,1,2,0.5,0.5));
    ASSERT_DOUBLE_EQ(0.0,shape_function.EvaluateEtaDeriv(2,1,2,0.0,0.5));
    ASSERT_NEAR(-9.8496e+00,shape_function.EvaluateEtaDeriv(2,1,2,0.8,0.1),1.0e-14);
    ASSERT_NEAR(-4.7088e+00,shape_function.EvaluateEtaDeriv(2,1,2,0.1,0.1),1.0e-14);
    ASSERT_NEAR(4.32e-01,shape_function.EvaluateEtaDeriv(2,1,2,0.1,0.8),1.0e-15);
    ASSERT_NEAR(-7.5168e+00,shape_function.EvaluateEtaDeriv(2,1,2,0.3,0.3),1.0e-14);
}


//************************************************************************************************//
/** @brief PlotShapeFunction : Writes file with x,y points and ShapeFunction(x,y) for plotting. */
//************************************************************************************************//
void PlotShapeFunction()
{
    std::ofstream myfile;
    myfile.open("TestShapeFunctions.out");
    myfile.precision(15);

    cem_core::TriShapeFunction shape_function(5);
    cemINT N = 100;
    std::vector<cemDOUBLE> x,y;
    for (cemINT i=0; i<N; ++i)
    {
        for (cemINT j=0; j<N; ++j)
        {
            if (cemDOUBLE(j)/cemDOUBLE(N-1) <= 1-cemDOUBLE(i)/cemDOUBLE(N-1))
            {
                x.push_back(cemDOUBLE(i)/cemDOUBLE(N-1));
                y.push_back(cemDOUBLE(j)/cemDOUBLE(N-1));
            }
        }
    }

    for (cemINT i=0; i<x.size(); ++i)
        myfile << std::scientific << std::setw(25) << x[i]
               << std::setw(25) << y[i] <<
                  std::setw(25) << shape_function.EvaluateEtaDeriv(1,2,2,x[i],y[i]) << std::endl;
}




int TestBasisFunctionsBasics()
{
    std::ofstream myfile;
    myfile.open("TestShapeFunctions.out");
    myfile.precision(15);

    cem_core::TriShapeFunction shape_function(6);

    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.0,0.0) << std::endl;
    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,1.0,0.0) << std::endl;
    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.0,1.0) << std::endl;
    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.5,0.0) << std::endl;
    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.0,0.5) << std::endl;
    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.5,0.5) << std::endl;

    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.8,0.1) << std::endl;
    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.1,0.1) << std::endl;
    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.1,0.8) << std::endl;
    myfile << std::scientific << std::setw(25) << shape_function.EvaluateEtaDeriv(2,1,2,0.3,0.3) << std::endl;


    return 0;
}
