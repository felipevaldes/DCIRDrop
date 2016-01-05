#include "MiscFunctions.h"


//************************************************************************************************//
/** @brief cem_math::Factorial : Computes n! */
//************************************************************************************************//
cemINT cem_math::Factorial(const cemINT& n)
{
    if (n == 0)
        return 1;
    return n*cem_math::Factorial(n-1);
}
