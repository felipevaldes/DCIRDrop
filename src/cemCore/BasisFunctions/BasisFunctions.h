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
protected:
    cemDOUBLE SilvesterPolynomial(const cemINT& order,
                                  const cemINT& index,
                                  const cemDOUBLE& ksi) const;

    cemDOUBLE SilvesterPolynomialDeriv(const cemINT& order,
                                       const cemINT& index,
                                       const cemDOUBLE& ksi) const;
};


//************************************************************************************************//
/**
 * @brief The TriShapeFunction class
 */
//************************************************************************************************//
class TriShapeFunction : public ShapeFunction
{
public:
    // Single point evaluation of shape function and derivatives:
    cemDOUBLE Evaluate(const cemINT& order,
                       const cemINT& index_i,
                       const cemINT& index_j,
                       const cemINT& index_k,
                       const cemDOUBLE& ksi,
                       const cemDOUBLE& eta) const;

    cemDOUBLE EvaluateKsiDeriv(const cemINT& order,
                               const cemINT& index_i,
                               const cemINT& index_j,
                               const cemINT& index_k,
                               const cemDOUBLE& ksi,
                               const cemDOUBLE& eta) const;

    cemDOUBLE EvaluateEtaDeriv(const cemINT& order,
                               const cemINT& index_i,
                               const cemINT& index_j,
                               const cemINT& index_k,
                               const cemDOUBLE& ksi,
                               const cemDOUBLE& eta) const;


    // Multiple point evaluation of shape function and derivatives:
    std::vector<cemDOUBLE> Evaluate(const cemINT& order,
                                    const cemINT& index_i,
                                    const cemINT& index_j,
                                    const cemINT& index_k,
                                    const std::vector<cemDOUBLE>& ksi,
                                    const std::vector<cemDOUBLE>& eta) const;

    std::vector<cemDOUBLE> EvaluateKsiDeriv(const cemINT& order,
                                            const cemINT& index_i,
                                            const cemINT& index_j,
                                            const cemINT& index_k,
                                            const std::vector<cemDOUBLE>& ksi,
                                            const std::vector<cemDOUBLE>& eta) const;

    std::vector<cemDOUBLE> EvaluateEtaDeriv(const cemINT& order,
                                            const cemINT& index_i,
                                            const cemINT& index_j,
                                            const cemINT& index_k,
                                            const std::vector<cemDOUBLE>& ksi,
                                            const std::vector<cemDOUBLE>& eta) const;
};


}


#endif // BASIS_FUNCTIONS_H
