#include "cemUtils.h"

using namespace cem_utils;



//************************************************************************************************//
/** @brief NumberToString : Transforms number into string.
 * @param x : Number to be transformed
 * @author Felipe Valdes */
//************************************************************************************************//
template<class T>
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
inline std::string NumberToString(T x, cemUINT precision)
{
    std::ostringstream outstring;
    outstring.precision(precision);
    outstring << x;
    return outstring.str();
}


