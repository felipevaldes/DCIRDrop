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
// STRING UTILITIES
//************************************************************************************************//

template <class T>
inline std::string NumberToString(T x);

template <class T>
inline std::string NumberToString(T x, cemUINT precision);





}





#endif // CEMUTILS_H
