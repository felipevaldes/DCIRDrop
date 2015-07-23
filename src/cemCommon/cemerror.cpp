#include <iostream>
#include "cemerror.h"

// Constructor:
cemcommon::Exception::Exception(std::string tag_string, std::string prob_string)
{
    tag_ = tag_string;
    problem_ = prob_string;
}

void cemcommon::Exception::PrintException() const
{
    std::cerr << "** Error ("<<tag_<<") **\n";
    std::cerr << "Problem: " << problem_ << "\n\n";
}
