#include <iostream>
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

        if (test_case_name == "TESTCEMSPACE")
            return_result = RunTestCEMSpace(sub_argc,sub_argv);

        if (test_case_name == "TESTCEMMESH")
            return_result = RunTestCEMMesh(sub_argc,sub_argv);

        if (test_case_name == "TESTCEMMATH")
            return_result = RunTestCEMMath(sub_argc,sub_argv);

    }
    catch (cemcommon::Exception& error)
    {
        error.PrintException();
    }

    delete sub_argv;
    return return_result;
}
