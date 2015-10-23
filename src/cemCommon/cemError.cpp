#include <iostream>
#include "cemError.h"

//************************************************************************************************//
/** @brief cemcommon::Exception::Exception : Constructor with parameters.
 * This is the only constructor to be used.
 * @param [in] tag_string : Short string tag for the error message
 * @param [in] prob_string : Long string that describes the error in more detail */
//************************************************************************************************//
cemcommon::Exception::Exception(std::string tag_string, std::string prob_string)
{
    tag_ = tag_string;
    problem_ = prob_string;
}


//************************************************************************************************//
/** @brief cemcommon::Exception::PrintException : Prints error message on screen. */
//************************************************************************************************//
void cemcommon::Exception::PrintException() const
{
    std::cerr << "** Error ("<<tag_<<") **\n";
    std::cerr << "Problem: " << problem_ << "\n\n";
}
