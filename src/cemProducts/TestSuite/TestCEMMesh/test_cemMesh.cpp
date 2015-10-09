#include "test_cemMesh.h"
#include "cemMesh.h"
#include "cemerror.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cstring>

using namespace cem_mesh;
using cemcommon::Exception;

/////////////////////////////////////////////////////////////////////
/// Main Test Function:
/////////////////////////////////////////////////////////////////////
int RunTestCEMMesh(int argc, char* argv[])
{
    std::cout << "Running cem_mesh Test" << std::endl;

    if (argc < 2)
        throw(Exception("INSUFFICIENT_INPUT_ARGUMENTS","Must specify test to run"));

    if (!strcmp(argv[1],"-Mesh_Basics"))
    {
        return TestMeshBasics();
    }
    return 1;



    ::testing::InitGoogleTest(&argc, argv);
    ::testing::FLAGS_gtest_death_test_style = "fast";
    return RUN_ALL_TESTS();
}


int TestMeshBasics()
{
    std::cout << "Hi Felipe, you are AWESEOME !!" << std::endl;

    Mesh mesh1;

    mesh1.ReadFromGmshFile("airbus380_blade.msh");
    mesh1.WriteToGmshFile("output.msh");

    return 0;
}
