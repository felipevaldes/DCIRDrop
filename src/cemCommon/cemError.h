#ifndef CEMERROR_H
#define CEMERROR_H

#pragma once

#include <iostream>
#include <string>



namespace cemcommon
{

//************************************************************************************************//
/** @brief The Exception class : Used for error handling. */
//************************************************************************************************//
class Exception
{
public:
    Exception(std::string tag_string, std::string prob_string);

    void PrintException() const;

private:
    std::string tag_;       /**< Short string tag for the error message. */
    std::string problem_;   /**< Long string that describes the error in more detail. */

};


}

#endif // CEMERROR_H

