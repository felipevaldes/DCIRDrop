#ifndef BLASLEVEL1_H
#define BLASLEVEL1_H
#pragma once

#include "cemTypes.h"
#include <iostream>

using namespace cem_def;


namespace cem_math {

void myFunction(const cemINT N, cemDOUBLE* y, cemDOUBLE* x);


// Vector-vector sum:
void MKL_VectorPlusEqualVector(const cemINT N, cemDOUBLE* y, const cemDOUBLE* x);
void MKL_VectorPlusEqualVector(const cemINT N, cemFLOAT* y, const cemFLOAT* x);
void MKL_VectorPlusEqualVector(const cemINT N, cemDCOMPLEX* y, const cemDCOMPLEX* x);
void MKL_VectorPlusEqualVector(const cemINT N, cemFCOMPLEX* y, const cemFCOMPLEX* x);

void MKL_VectorMinusEqualVector(const cemINT N, cemDOUBLE* y, const cemDOUBLE* x);
void MKL_VectorMinusEqualVector(const cemINT N, cemFLOAT* y, const cemFLOAT* x);
void MKL_VectorMinusEqualVector(const cemINT N, cemDCOMPLEX* y, const cemDCOMPLEX* x);
void MKL_VectorMinusEqualVector(const cemINT N, cemFCOMPLEX* y, const cemFCOMPLEX* x);

// Scalar-vector product:
void MKL_ScalarTimesEqualVector(const cemINT N, cemDOUBLE* x, const cemDOUBLE alpha);
void MKL_ScalarTimesEqualVector(const cemINT N, cemFLOAT* x, const cemFLOAT alpha);
void MKL_ScalarTimesEqualVector(const cemINT N, cemDCOMPLEX* x, const cemDCOMPLEX alpha);
void MKL_ScalarTimesEqualVector(const cemINT N, cemFCOMPLEX* x, const cemFCOMPLEX alpha);
void MKL_ScalarTimesEqualVector(const cemINT N, cemDCOMPLEX* x, const cemDOUBLE alpha);
void MKL_ScalarTimesEqualVector(const cemINT N, cemFCOMPLEX* x, const cemFLOAT alpha);

// Copy vector:
void MKL_VectorCopy(const cemINT N, const cemDOUBLE* x, const cemINT incx, cemDOUBLE* y, const cemINT incy);
void MKL_VectorCopy(const cemINT N, const cemFLOAT* x, const cemINT incx, cemFLOAT* y, const cemINT incy);
void MKL_VectorCopy(const cemINT N, const cemDCOMPLEX* x, const cemINT incx, cemDCOMPLEX* y, const cemINT incy);
void MKL_VectorCopy(const cemINT N, const cemFCOMPLEX* x, const cemINT incx, cemFCOMPLEX* y, const cemINT incy);

// Dot product:
cemDOUBLE MKL_VectorDotProduct(const cemINT N, const cemDOUBLE* x, const cemDOUBLE* y);
cemFLOAT MKL_VectorDotProduct(const cemINT N, const cemFLOAT* x, const cemFLOAT* y);

// Dot product conjugated:
cemDCOMPLEX MKL_VectorDotProductConjugated(const cemINT N, const cemDCOMPLEX* x, const cemDCOMPLEX* y);
cemFCOMPLEX MKL_VectorDotProductConjugated(const cemINT N, const cemFCOMPLEX* x, const cemFCOMPLEX* y);

// Dot product unconjugated:
cemDCOMPLEX MKL_VectorDotProduct(const cemINT N, const cemDCOMPLEX* x, const cemDCOMPLEX* y);
cemFCOMPLEX MKL_VectorDotProduct(const cemINT N, const cemFCOMPLEX* x, const cemFCOMPLEX* y);

// Vector 2-norm (Euclidean norm):
cemDOUBLE MKL_VectorNorm2(const cemINT N, const cemDOUBLE* x);
cemFLOAT MKL_VectorNorm2(const cemINT N, const cemFLOAT* x);
cemDOUBLE MKL_VectorNorm2(const cemINT N, const cemDCOMPLEX* x);
cemFLOAT MKL_VectorNorm2(const cemINT N, const cemFCOMPLEX* x);
}



#endif // BLASLEVEL1_H
