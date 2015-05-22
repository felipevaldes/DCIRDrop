#ifndef CEMTYPE_H
#define CEMTYPE_H

#pragma once
#include <complex>

namespace CEMDef
{
// Basic type definitions:
typedef bool cemBOOL;
typedef int cemINT;
typedef float cemFLOAT;
typedef double cemDOUBLE;
typedef char cemCHAR;
typedef unsigned char cemUCHAR;
typedef unsigned int cemUINT;
typedef std::complex<cemFLOAT> cemFCOMPLEX;
typedef std::complex<cemDOUBLE> cemDCOMPLEX;
typedef size_t cemSIZE;

}


#endif // CEMTYPE_H
