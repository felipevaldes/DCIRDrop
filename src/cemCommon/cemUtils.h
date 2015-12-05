#ifndef CEMUTILS_H
#define CEMUTILS_H
#pragma once

#include <iostream>
#include <fstream>
#include "cemTypes.h"

using namespace cem_def;
namespace cem_utils
{
//************************************************************************************************//
/** @brief NumberToString : Transforms number into string.
 * @param x : Number to be transformed
 * @author Felipe Valdes */
//************************************************************************************************//
template<typename T>
inline std::string NumberToString(T x)
{
    std::ostringstream outstring;
    outstring.precision(6);
    outstring << x;
    return outstring.str();
}

//************************************************************************************************//
/** @brief NumberToString : Transforms number into string up to a given precision.
 * @param x : Number to be transformed
 * @param precision : Number of digits to be transformed into string
 * @author Felipe Valdes */
//************************************************************************************************//
template <class T>
inline std::string NumberToString(T x, cemINT precision)
{
    std::ostringstream outstring;
    outstring.precision(precision);
    outstring << x;
    return outstring.str();
}
}





#endif // CEMUTILS_H
