#ifndef BASIS_FUNCTIONS_H
#define BASIS_FUNCTIONS_H

#include <vector>
#include <iostream>
#include "cemMesh.h"

using cem_mesh::Element;

namespace cem_core {

enum BasisFunctionType
{
    INTERPOLATORY=0,
    HIERARCHICAL=1,
};

enum BasisFunctionField
{
    SCALAR=0,
    VECTOR=1,
};

//************************************************************************************************//
/** @brief The SolverElement class: Mesh element plus solver data.
 *
 * SolverElement is the entity that "hosts" the basis functions used to expand
 * the solution of the FEM formulation.
*/
//************************************************************************************************//
class SolverElement
{
public:


private:
    Element*            element_ptr_;           /**< Element in mesh. */
    cemINT              basis_function_order;   /**< Polynomial order ofthe basis functions hosted. */
    BasisFunctionField  basis_function_field_;  /**< Vector or Scalar basis function. */
    BasisFunctionType   basis_function_type_;   /**< Interpolatory or Hierarchical basis function. */


};







}




#endif // BASIS_FUNCTIONS_H
