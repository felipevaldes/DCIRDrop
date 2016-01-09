#ifndef TESTBASISFUNCTIONS_H
#define TESTBASISFUNCTIONS_H
#include "BasisFunctions/BasisFunctions.h"
#include "gtest/gtest.h"
#include "cemError.h"

int TestBasisFunctionsBasics();

cemDOUBLE IntegrateSilvesterDeriv(cemDOUBLE a,cemDOUBLE b,cemINT order,cemINT index);
void PlotShapeFunction();



#endif // TESTBASISFUNCTIONS_H

