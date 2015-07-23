#include "testcemspace.h"
#include "cemspace.h"
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
        return TestV2D();
    }
    return 1;
}



int TestV2D()
{
    // Test Constructors::
    std::cout << "Testing V2D constructors:" << std::endl;
    V2D v1;
    std::cout << "Default Constructor: v1 = " << v1 << std::endl;

    V2D v2(1.0,-2.3);
    std::cout << "Constructor from coordinates: v2 = " << v2 << std::endl;

    V2D v3(v2);
    std::cout << "Copy Constructor: v3 = " << v3 << std::endl;

    v1 = v3;
    std::cout << "Copy operator: v1 = " << v1 << std::endl;

    v1[0] = 0.25; v1[1] = -1.0/8.0;
    std::cout << "Random access assignment: v1 = " << v1 << std::endl;

    // Test Math Operations:
    std::cout << "v1 == v2: " << (v1 == v2) << std::endl;
    std::cout << "v2 == v3: " << (v2 == v3) << std::endl;

    v1 *= 4.0;
    std::cout << "Multiply by scalar: 4*v1 = " << v1 << std::endl;

    std::cout << "Add vector: v2 + v1 = " << (v1 + v2) << std::endl;


    return 0;
}
