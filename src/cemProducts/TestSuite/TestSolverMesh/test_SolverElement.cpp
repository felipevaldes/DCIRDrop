#include <iostream>
#include <fstream>
#include "cemError.h"
#include "test_SolverElement.h"


using cemcommon::Exception;

//************************************************************************************************//
// Main Test Function:
//************************************************************************************************//
int RunTestSolverElement(int argc, char* argv[])
{
    std::cout << "Running SolverElement Test" << std::endl;

    if (argc < 2)
        throw(Exception("INSUFFICIENT_INPUT_ARGUMENTS","Must specify test to run"));

    if (!strcmp(argv[1],"-SilvesterPolynomial"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "*.SilvesterPolynomial*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-SolverTriangle"))
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::FLAGS_gtest_death_test_style = "fast";
        ::testing::FLAGS_gtest_filter = "SolverTriangle.*";
        return RUN_ALL_TESTS();
    }
    if (!strcmp(argv[1],"-BasicTest"))
    {
        return TestSolverElementBasics();
    }
    return 1;
}



TEST(SolverTriangle,setUp_matrix_N_NxNx_0_1)
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,1,cem_core::SCALAR,cem_core::HIERARCHICAL,0);

    // Get matrices:
    solver_element.setUp_matrix_N_NxNx(false);
    DenseMatrix<cemDOUBLE> K_analytic = solver_element.matrix_N_NxNx(0);

    solver_element.setUp_matrix_N_NxNx(true);
    DenseMatrix<cemDOUBLE> K_numeric = solver_element.matrix_N_NxNx(0);

    // Compare matrices:
    for (cemINT i=1; i<=K_analytic.num_rows(); ++i)
    {
        for (cemINT j=1; j<=K_analytic.num_columns(); ++j)
        {
         if (K_analytic(i,j) != 0.0)
             ASSERT_NEAR(1.0,K_numeric(i,j)/K_analytic(i,j),1.0e-14);
         else
             ASSERT_NEAR(K_numeric(i,j),K_analytic(i,j),1.0e-14);
        }
    }
}

TEST(SolverTriangle,setUp_matrix_N_NxNx_0_2)
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,2,cem_core::SCALAR,cem_core::HIERARCHICAL,0);

    // Get matrices:
    solver_element.setUp_matrix_N_NxNx(false);
    DenseMatrix<cemDOUBLE> K_analytic = solver_element.matrix_N_NxNx(0);

    solver_element.setUp_matrix_N_NxNx(true);
    DenseMatrix<cemDOUBLE> K_numeric = solver_element.matrix_N_NxNx(0);

    // Compare matrices:
    for (cemINT i=1; i<=K_analytic.num_rows(); ++i)
    {
        for (cemINT j=1; j<=K_analytic.num_columns(); ++j)
        {
         if (K_analytic(i,j) != 0.0)
             ASSERT_NEAR(1.0,K_numeric(i,j)/K_analytic(i,j),1.0e-14);
         else
             ASSERT_NEAR(K_numeric(i,j),K_analytic(i,j),1.0e-14);
        }
    }
}

//TEST(SolverTriangle,setUp_matrix_N_NxNx_0_3)
//{

//}

TEST(SolverTriangle,setUp_matrix_N_NxNx_1_1)
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,1,cem_core::SCALAR,cem_core::HIERARCHICAL,1);

    // Get matrices:
    solver_element.setUp_matrix_N_NxNx(false);
    DenseMatrix<cemDOUBLE> K_analytic_0 = solver_element.matrix_N_NxNx(0);
    DenseMatrix<cemDOUBLE> K_analytic_1 = solver_element.matrix_N_NxNx(1);
    DenseMatrix<cemDOUBLE> K_analytic_2 = solver_element.matrix_N_NxNx(2);

    solver_element.setUp_matrix_N_NxNx(true);
    DenseMatrix<cemDOUBLE> K_numeric_0 = solver_element.matrix_N_NxNx(0);
    DenseMatrix<cemDOUBLE> K_numeric_1 = solver_element.matrix_N_NxNx(1);
    DenseMatrix<cemDOUBLE> K_numeric_2 = solver_element.matrix_N_NxNx(2);

    // Compare matrices:
    for (cemINT i=1; i<=K_analytic_0.num_rows(); ++i)
    {
        for (cemINT j=1; j<=K_analytic_0.num_columns(); ++j)
        {
         if (K_analytic_0(i,j) != 0.0)
             ASSERT_NEAR(1.0,K_numeric_0(i,j)/K_analytic_0(i,j),1.0e-14);
         else
             ASSERT_NEAR(K_numeric_0(i,j),K_analytic_0(i,j),1.0e-14);

         if (K_analytic_1(i,j) != 0.0)
             ASSERT_NEAR(1.0,K_numeric_1(i,j)/K_analytic_1(i,j),1.0e-14);
         else
             ASSERT_NEAR(K_numeric_1(i,j),K_analytic_1(i,j),1.0e-14);

         if (K_analytic_2(i,j) != 0.0)
             ASSERT_NEAR(1.0,K_numeric_2(i,j)/K_analytic_2(i,j),1.0e-14);
         else
             ASSERT_NEAR(K_numeric_2(i,j),K_analytic_2(i,j),1.0e-14);
        }
    }
}


TEST(SolverTriangle,setUp_matrix_N_NxNx_1_2)
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,2,cem_core::SCALAR,cem_core::HIERARCHICAL,1);

    // Get matrices:
    solver_element.setUp_matrix_N_NxNx(false);
    DenseMatrix<cemDOUBLE> K_analytic_0 = solver_element.matrix_N_NxNx(0);
    DenseMatrix<cemDOUBLE> K_analytic_1 = solver_element.matrix_N_NxNx(1);
    DenseMatrix<cemDOUBLE> K_analytic_2 = solver_element.matrix_N_NxNx(2);

    solver_element.setUp_matrix_N_NxNx(true);
    DenseMatrix<cemDOUBLE> K_numeric_0 = solver_element.matrix_N_NxNx(0);
    DenseMatrix<cemDOUBLE> K_numeric_1 = solver_element.matrix_N_NxNx(1);
    DenseMatrix<cemDOUBLE> K_numeric_2 = solver_element.matrix_N_NxNx(2);

    // Compare matrices:
    for (cemINT i=1; i<=K_analytic_0.num_rows(); ++i)
    {
        for (cemINT j=1; j<=K_analytic_0.num_columns(); ++j)
        {
         if (K_analytic_0(i,j) != 0.0)
             ASSERT_NEAR(1.0,K_numeric_0(i,j)/K_analytic_0(i,j),5.0e-14);
         else
             ASSERT_NEAR(K_numeric_0(i,j),K_analytic_0(i,j),1.0e-14);

         if (K_analytic_1(i,j) != 0.0)
             ASSERT_NEAR(1.0,K_numeric_1(i,j)/K_analytic_1(i,j),5.0e-14);
         else
             ASSERT_NEAR(K_numeric_1(i,j),K_analytic_1(i,j),1.0e-14);

         if (K_analytic_2(i,j) != 0.0)
             ASSERT_NEAR(1.0,K_numeric_2(i,j)/K_analytic_2(i,j),5.0e-14);
         else
             ASSERT_NEAR(K_numeric_2(i,j),K_analytic_2(i,j),1.0e-14);
        }
    }
}


//TEST(SolverTriangle,setUp_matrix_N_NxNx_1_3)
//{

//}



TEST(SolverTriangle,setUp_matrix_N_NyNy_0_1)
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,1,cem_core::SCALAR,cem_core::HIERARCHICAL,0);

    // Get matrices:
    solver_element.setUp_matrix_N_NyNy(false);
    DenseMatrix<cemDOUBLE> K_analytic = solver_element.matrix_N_NyNy(0);

    solver_element.setUp_matrix_N_NyNy(true);
    DenseMatrix<cemDOUBLE> K_numeric = solver_element.matrix_N_NyNy(0);

    // Compare matrices:
    for (cemINT i=1; i<=K_analytic.num_rows(); ++i)
    {
        for (cemINT j=1; j<=K_analytic.num_columns(); ++j)
        {
            if (K_analytic(i,j) != 0.0)
                ASSERT_NEAR(1.0,K_numeric(i,j)/K_analytic(i,j),1.0e-14);
            else
                ASSERT_NEAR(K_numeric(i,j),K_analytic(i,j),1.0e-14);
        }
    }
}

TEST(SolverTriangle,setUp_matrix_N_NyNy_0_2)
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,2,cem_core::SCALAR,cem_core::HIERARCHICAL,0);

    // Get matrices:
    solver_element.setUp_matrix_N_NyNy(false);
    DenseMatrix<cemDOUBLE> K_analytic = solver_element.matrix_N_NyNy(0);

    solver_element.setUp_matrix_N_NyNy(true);
    DenseMatrix<cemDOUBLE> K_numeric = solver_element.matrix_N_NyNy(0);

    // Compare matrices:
    for (cemINT i=1; i<=K_analytic.num_rows(); ++i)
    {
        for (cemINT j=1; j<=K_analytic.num_columns(); ++j)
        {
            if (K_analytic(i,j) != 0.0)
                ASSERT_NEAR(1.0,K_numeric(i,j)/K_analytic(i,j),1.0e-14);
            else
                ASSERT_NEAR(K_numeric(i,j),K_analytic(i,j),1.0e-14);
        }
    }}

//TEST(SolverTriangle,setUp_matrix_N_NyNy_0_3)
//{

//}

TEST(SolverTriangle,setUp_matrix_N_NyNy_1_1)
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,1,cem_core::SCALAR,cem_core::HIERARCHICAL,1);

    // Get matrices:
    solver_element.setUp_matrix_N_NyNy(false);
    DenseMatrix<cemDOUBLE> K_analytic_0 = solver_element.matrix_N_NyNy(0);
    DenseMatrix<cemDOUBLE> K_analytic_1 = solver_element.matrix_N_NyNy(1);
    DenseMatrix<cemDOUBLE> K_analytic_2 = solver_element.matrix_N_NyNy(2);

    solver_element.setUp_matrix_N_NyNy(true);
    DenseMatrix<cemDOUBLE> K_numeric_0 = solver_element.matrix_N_NyNy(0);
    DenseMatrix<cemDOUBLE> K_numeric_1 = solver_element.matrix_N_NyNy(1);
    DenseMatrix<cemDOUBLE> K_numeric_2 = solver_element.matrix_N_NyNy(2);

    // Compare matrices:
    for (cemINT i=1; i<=K_analytic_0.num_rows(); ++i)
    {
        for (cemINT j=1; j<=K_analytic_0.num_columns(); ++j)
        {
            if (K_analytic_0(i,j) != 0.0)
                ASSERT_NEAR(1.0,K_numeric_0(i,j)/K_analytic_0(i,j),1.0e-14);
            else
                ASSERT_NEAR(K_numeric_0(i,j),K_analytic_0(i,j),1.0e-14);

            if (K_analytic_1(i,j) != 0.0)
                ASSERT_NEAR(1.0,K_numeric_1(i,j)/K_analytic_1(i,j),1.0e-14);
            else
                ASSERT_NEAR(K_numeric_1(i,j),K_analytic_1(i,j),1.0e-14);

            if (K_analytic_2(i,j) != 0.0)
                ASSERT_NEAR(1.0,K_numeric_2(i,j)/K_analytic_2(i,j),1.0e-14);
            else
                ASSERT_NEAR(K_numeric_2(i,j),K_analytic_2(i,j),1.0e-14);
        }
    }
}

TEST(SolverTriangle,setUp_matrix_N_NyNy_1_2)
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,2,cem_core::SCALAR,cem_core::HIERARCHICAL,1);

    // Get matrices:
    solver_element.setUp_matrix_N_NyNy(false);
    DenseMatrix<cemDOUBLE> K_analytic_0 = solver_element.matrix_N_NyNy(0);
    DenseMatrix<cemDOUBLE> K_analytic_1 = solver_element.matrix_N_NyNy(1);
    DenseMatrix<cemDOUBLE> K_analytic_2 = solver_element.matrix_N_NyNy(2);

    solver_element.setUp_matrix_N_NyNy(true);
    DenseMatrix<cemDOUBLE> K_numeric_0 = solver_element.matrix_N_NyNy(0);
    DenseMatrix<cemDOUBLE> K_numeric_1 = solver_element.matrix_N_NyNy(1);
    DenseMatrix<cemDOUBLE> K_numeric_2 = solver_element.matrix_N_NyNy(2);

    // Compare matrices:
    for (cemINT i=1; i<=K_analytic_0.num_rows(); ++i)
    {
        for (cemINT j=1; j<=K_analytic_0.num_columns(); ++j)
        {
            if (K_analytic_0(i,j) != 0.0)
                ASSERT_NEAR(1.0,K_numeric_0(i,j)/K_analytic_0(i,j),5.0e-14);
            else
                ASSERT_NEAR(K_numeric_0(i,j),K_analytic_0(i,j),1.0e-14);

            if (K_analytic_1(i,j) != 0.0)
                ASSERT_NEAR(1.0,K_numeric_1(i,j)/K_analytic_1(i,j),5.0e-14);
            else
                ASSERT_NEAR(K_numeric_1(i,j),K_analytic_1(i,j),1.0e-14);

            if (K_analytic_2(i,j) != 0.0)
                ASSERT_NEAR(1.0,K_numeric_2(i,j)/K_analytic_2(i,j),5.0e-14);
            else
                ASSERT_NEAR(K_numeric_2(i,j),K_analytic_2(i,j),1.0e-14);
        }
    }
}

//TEST(SolverTriangle,setUp_matrix_N_NyNy_1_3)
//{

//}



//TEST(SolverTriangle,setUp_matrix_N_NN_0_1)
//{

//}

//TEST(SolverTriangle,setUp_matrix_N_NN_0_2)
//{

//}

//TEST(SolverTriangle,setUp_matrix_N_NN_0_3)
//{

//}

//TEST(SolverTriangle,setUp_matrix_N_NN_1_1)
//{

//}

//TEST(SolverTriangle,setUp_matrix_N_NN_1_2)
//{

//}

//TEST(SolverTriangle,setUp_matrix_N_NN_1_3)
//{

//}


int TestSolverElementBasics()
{
    // Create single element:
    Element test_element;
    CreateSingleElement(test_element);
    cem_core::SolverTriangle solver_element(&test_element,2,cem_core::SCALAR,cem_core::HIERARCHICAL,1);

    DenseMatrix<cemDOUBLE> K_analytic,K_numeric;

    std::ofstream file_analytic;
    file_analytic.open("K_analytic.out",std::ofstream::out);
    file_analytic.precision(15);

    solver_element.setUp_matrix_N_NyNy(false);
    K_analytic = solver_element.matrix_N_NyNy(0);
    K_analytic.WriteToFileByColumns(file_analytic);

    std::ofstream file_numeric;
    file_numeric.open("K_numeric.out",std::ofstream::out);
    file_numeric.precision(15);

    solver_element.setUp_matrix_N_NyNy(true);
    K_numeric = solver_element.matrix_N_NyNy(0);
    K_numeric.WriteToFileByColumns(file_numeric);

    return 0;
}


void CreateSingleElement(Element& elem)
{
    // Cretate nodes:
    std::vector<Node*> node_ptrs;
    node_ptrs.resize(3);
    node_ptrs[0] = new Node;
    node_ptrs[1] = new Node;
    node_ptrs[2] = new Node;
    (*node_ptrs[0]).set_coordinates(1.0,-0.5,0.0);
    (*node_ptrs[1]).set_coordinates(1.0,1.0,0.0);
    (*node_ptrs[2]).set_coordinates(-0.5,2.0,0.0);

    elem.set_node_ptrs(node_ptrs);
}
