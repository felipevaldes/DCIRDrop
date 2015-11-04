#include "test_cemMath.h"
#include "cemMesh.h"
#include "cemError.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cstring>

using namespace cem_mesh;
using cemcommon::Exception;

/////////////////////////////////////////////////////////////////////
/// Main Test Function:
/////////////////////////////////////////////////////////////////////
int RunTestCEMMath(int argc, char* argv[])
{
    std::cout << "Running cem_mesh Test" << std::endl;

    if (argc < 2)
        throw(Exception("INSUFFICIENT_INPUT_ARGUMENTS","Must specify test to run"));

    if (!strcmp(argv[1],"-Mesh_Basics"))
    {
        return TestMathBasics();
    }
    return 1;



    ::testing::InitGoogleTest(&argc, argv);
    ::testing::FLAGS_gtest_death_test_style = "fast";
    return RUN_ALL_TESTS();
}


int TestMathBasics()
{

    std::cout << "Hi Felipe, you are AWESEOME !!" << std::endl;

    return 0;
}
