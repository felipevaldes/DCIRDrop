#ifndef TESTSOLVERELEMENT_H
#define TESTSOLVERELEMENT_H
#include "gtest/gtest.h"
#include "cemMesh.h"
#include "SolverMesh/SolverElement.h"

using namespace cem_mesh;


int TestSolverElementBasics();

void CreateSingleElement(Element& elem);

#endif // TESTSOLVERELEMENT_H
