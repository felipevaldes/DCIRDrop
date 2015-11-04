#ifndef MATRIX_H
#define MATRIX_H
#pragma once

#include "cemTypes.h"

using namespace cem_def;

namespace cem_math
{


template<class T>
class Matrix
{
public:
    typedef T value_type_;      /**< Allows to see what type of elements are stored in Matrix */

    /** @brief Matrix : Default constructor */
    Matrix() {}

    /** @brief Matrix : Constructor with matrix dimensions */
    Matrix(cemUINT, cemUINT) {}

    /** @brief ~Matrix : (Virtual) destructor */
    virtual ~Matrix() {}

    /** @brief operator () : (Virtual) Random access operator. */
    virtual const T& operator() (cemUINT, cemUINT) const = 0;

    /** @brief operator () : (Virtual) Random access asignment. */
    virtual T& operator () (cemUINT, cemUINT) = 0;

    /** @brief resize : (Virtual) Resize dimensions */
    virtual void resize(cemUINT, cemUINT) = 0;

    /** @brief rowSize : (Virtual) Get number of rows */
    virtual cemUINT num_rows(void) const = 0;

    /** @brief colSize : (Virtual) Get number of columns */
    virtual cemUINT num_columns(void) const = 0;

    /** @brief operator *= : (Virtual) Multiply matrix by scalar. */
    virtual void operator *= (const T& scalar) = 0;

    /** @brief initialize : (Virtual) Initializes all entries to a given value. */
    virtual void initialize(T value) = 0;

};


}

#endif // MATRIX_H
