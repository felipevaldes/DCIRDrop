#ifndef CEMERROR_H
#define CEMERROR_H

#pragma once

#include <iostream>
#include <string>



namespace cemcommon
{

class Exception
{
public:
    // Constructor:
    Exception(std::string tag_string, std::string prob_string);

    // Print Exception:
    void PrintException() const;

private:
    std::string tag_;
    std::string problem_;

};


}

#endif // CEMERROR_H

