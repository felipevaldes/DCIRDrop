#ifndef CEMTYPE_H
#define CEMTYPE_H

#pragma once
#include <complex>
#include <stdint.h>



#define CLEAN(p) { delete p; p=NULL; }
#define CLEAN_ARRAY(p) { delete [] p; p=NULL; }

namespace cem_def
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

#if defined(WINDOWS)
    typedef __int32 cemLINT;
    typedef __int64     cemINT8;
    typedef unsigned __int64 cemUINT8;
#else
    typedef int32_t cemLINT;
    typedef long long  cemINT8;
    typedef unsigned long long cemUINT8;
#endif

}


#endif // CEMTYPE_H
