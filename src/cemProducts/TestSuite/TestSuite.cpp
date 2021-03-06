#include <iostream>
#include "gtest/gtest.h"
#include "testcasedeclarations.h"
#include "cemError.h"

int main(int argc,char *argv[])
{
    int sub_argc;
    char **sub_argv = NULL;
    int return_result = 0;

    try
    {
        if (argc < 2)
            throw("INSUFFICIENT_INPUT_ARGUMENTS","Must specify test suite to run");

        std::string test_case_name = argv[1];

        // Make a copy of all input arguments except the test case name
        sub_argc = argc-1;
        sub_argv = new char*[sub_argc];
        sub_argv[0] = argv[0];

        std::cout << "Running TestSuite '" << test_case_name << "' with arguments:" << std::endl;
        for (int i=2; i < argc; ++i)
        {
            sub_argv[i-1] = argv[i];
            std::cout << argv[i] << std::endl;
        }
        if (test_case_name == "TEST_ALL")
        {
            ::testing::InitGoogleTest(&argc, argv);
            ::testing::FLAGS_gtest_death_test_style = "fast";
            return RUN_ALL_TESTS();
        }

        if (test_case_name == "TEST_CEMSPACE")
            return_result = RunTestCEMSpace(sub_argc,sub_argv);

        if (test_case_name == "TEST_CEMMESH")
            return_result = RunTestCEMMesh(sub_argc,sub_argv);

        if (test_case_name == "TEST_CEMMATH")
            return_result = RunTestCEMMath(sub_argc,sub_argv);

        if (test_case_name == "TEST_INTEGRATION")
            return_result = RunTestIntegration(sub_argc,sub_argv);

        if (test_case_name == "TEST_BASISFUNCTIONS")
            return_result = RunTestBasisFunctions(sub_argc,sub_argv);

        if (test_case_name == "TEST_SOLVERELEMENT")
            return_result = RunTestSolverElement(sub_argc,sub_argv);

    }
    catch (cemcommon::Exception& error)
    {
        error.PrintException();
    }

    delete sub_argv;
    return return_result;
}
