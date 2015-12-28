#ifndef TESTINTEGRATION_H
#define TESTINTEGRATION_H
#include "Quadrature/Quadrature.h"
#include "gtest/gtest.h"
#include "cemError.h"

int TestIntegrationBasics();




class TestLineQuadrature : public ::testing::Test
{
public:
    static cemDOUBLE Integrate(const cemDOUBLE& a,
                               const cemDOUBLE& b,
                               cemDOUBLE (*function)(cemDOUBLE),
                               const cemINT& num_points);

    static cemDOUBLE TestFunction_1(const cemDOUBLE x);
    static cemDOUBLE TestFunction_2(const cemDOUBLE x);
    static cemDOUBLE TestFunction_3(const cemDOUBLE x);
    static cemDOUBLE TestFunction_4(const cemDOUBLE x);
    static cemDOUBLE TestFunction_5(const cemDOUBLE x);
    static cemDOUBLE TestFunction_6(const cemDOUBLE x);
    static cemDOUBLE TestFunction_7(const cemDOUBLE x);
    static cemDOUBLE TestFunction_8(const cemDOUBLE x);

};


class TestTriQuadrature : public ::testing::Test
{
public:
    static cemDOUBLE Integrate(cemDOUBLE (*function)(cemDOUBLE,cemDOUBLE),
                               const cemINT& num_points);

    static cemDOUBLE TestFunction_1(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_2(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_3(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_4(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_5(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_6(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_7(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_8(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_9(const cemDOUBLE x,const cemDOUBLE y);
    static cemDOUBLE TestFunction_10(const cemDOUBLE x,const cemDOUBLE y);

};







#endif // TESTINTEGRATION_H

