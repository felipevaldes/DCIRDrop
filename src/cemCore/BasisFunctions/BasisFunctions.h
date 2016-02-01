#ifndef BASIS_FUNCTIONS_H
#define BASIS_FUNCTIONS_H

#include <vector>
#include <iostream>
#include "cemMesh.h"

namespace cem_core {

//************************************************************************************************//
/**
 * @brief The ShapeFunction class
 */
//************************************************************************************************//
class ShapeFunction
{
public:
    // Constructor with parameters:
    ShapeFunction(const cemINT& order);

    // Get data members:
    cemINT order() const;

    // Set data members:
    void set_order(const cemINT& order);

    cemDOUBLE SilvesterPolynomial(const cemINT& index,
                                  const cemDOUBLE& ksi) const;

    cemDOUBLE SilvesterPolynomialDeriv(const cemINT& index,
                                       const cemDOUBLE& ksi) const;

protected:
    cemINT order_;  //!< Polynomial order of the shape function.

private:
    // Private member functions:
    ShapeFunction(); // Default constructor private so only parameterized constructor can be used.
};


//************************************************************************************************//
/**
 * @brief The TriShapeFunction class
 */
//************************************************************************************************//
class TriShapeFunction : public ShapeFunction
{
public:
    // Constructor with parameters:
    TriShapeFunction(const cemINT& order) : ShapeFunction(order) {}

    // Single point evaluation of shape function and derivatives:
    cemDOUBLE Evaluate(const cemINT& index_i,
                       const cemINT& index_j,
                       const cemINT& index_k,
                       const cemDOUBLE& ksi,
                       const cemDOUBLE& eta) const;

    cemDOUBLE EvaluateKsiDeriv(const cemINT& index_i,
                               const cemINT& index_j,
                               const cemINT& index_k,
                               const cemDOUBLE& ksi,
                               const cemDOUBLE& eta) const;

    cemDOUBLE EvaluateEtaDeriv(const cemINT& index_i,
                               const cemINT& index_j,
                               const cemINT& index_k,
                               const cemDOUBLE& ksi,
                               const cemDOUBLE& eta) const;


    // Multiple point evaluation of shape function and derivatives:
    std::vector<cemDOUBLE> Evaluate(const cemINT& index_i,
                                    const cemINT& index_j,
                                    const cemINT& index_k,
                                    const std::vector<cemDOUBLE>& ksi,
                                    const std::vector<cemDOUBLE>& eta) const;

    std::vector<cemDOUBLE> EvaluateKsiDeriv(const cemINT& index_i,
                                            const cemINT& index_j,
                                            const cemINT& index_k,
                                            const std::vector<cemDOUBLE>& ksi,
                                            const std::vector<cemDOUBLE>& eta) const;

    std::vector<cemDOUBLE> EvaluateEtaDeriv(const cemINT& index_i,
                                            const cemINT& index_j,
                                            const cemINT& index_k,
                                            const std::vector<cemDOUBLE>& ksi,
                                            const std::vector<cemDOUBLE>& eta) const;

private:
    // Private member functions:
    TriShapeFunction(); // Default constructor private so only parameterized constructor can be used.
};


}


#endif // BASIS_FUNCTIONS_H
