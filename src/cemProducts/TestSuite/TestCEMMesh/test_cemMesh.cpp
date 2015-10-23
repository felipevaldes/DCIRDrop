#include "test_cemMesh.h"
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

    Mesh mesh1;

    mesh1.ReadFromGmshFile("airbus380_blade.msh");

    Mesh mesh2(mesh1);



    mesh2.WriteToGmshFile("output.msh");

    std::cout << "Hi Felipe, you are AWESEOME !!" << std::endl;

    return 0;
}
