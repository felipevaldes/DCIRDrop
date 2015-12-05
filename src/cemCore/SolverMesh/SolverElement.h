#ifndef BASIS_FUNCTIONS_H
#define BASIS_FUNCTIONS_H

#include <vector>
#include <iostream>
#include "cemMesh.h"
#include "Matrix/DenseMatrix.h"

using cem_mesh::Element;
using cem_math::DenseMatrix;

namespace cem_core {

/** @brief The BasisFunctionType enum : Defines the type of basis function */
enum BasisFunctionType
{
    INTERPOLATORY=0,
    HIERARCHICAL=1,
};

/** @brief The BasisFunctionField enum : Defines the type of field of basis function */
enum BasisFunctionField
{
    SCALAR=0,
    VECTOR=1,
};

//************************************************************************************************//
/** @brief The SolverElement class: Mesh element plus solver data.
 * SolverElement is the entity that "hosts" the basis functions used to expand
 * the solution of the FEM formulation. */
//************************************************************************************************//
class SolverElement
{
public:
    /** @brief SolverElement : Default constructor */
    SolverElement() {initialize();}

    // Constructor with parameters:
    SolverElement(const Element* element_ptr,
                  const cemINT& basis_order,
                  const BasisFunctionField& function_field,
                  const BasisFunctionType& function_type,
                  const cemINT& coefficient_order);

    // Copy constructor:
    SolverElement(const SolverElement& other);
    SolverElement& operator = (const SolverElement& other);

    // Get data members:
    const Element* element_ptr() const;
    cemINT basis_function_order() const;
    BasisFunctionField basis_function_field() const;
    BasisFunctionType basis_function_type() const;
    cemINT coefficient_order() const;
    const DenseMatrix<cemDOUBLE>& matrix_N_NxNx(cemINT i) const;
    const DenseMatrix<cemDOUBLE>& matrix_N_NyNy(cemINT i) const;
    const DenseMatrix<cemDOUBLE>& matrix_N_NN(cemINT i) const;

    // Set data members:
    void set_element_ptr(const Element* element_ptr);
    void set_basis_function_order(const cemINT& order);
    void set_basis_function_field(const BasisFunctionField& function_field);
    void set_basis_function_type(const BasisFunctionType& function_type);
    void set_coefficient_order(const cemINT& order);

    // Matrices:
    void setUp_matrix_N_NxNx();
    void setUp_matrix_N_NyNy();
    void setUp_matrix_N_NN();



protected:
    const Element*      element_ptr_;           /**< Element in mesh. */
    cemINT              basis_function_order_;  /**< Polynomial order of the basis functions hosted. */
    BasisFunctionField  basis_function_field_;  /**< Vector or Scalar basis function. */
    BasisFunctionType   basis_function_type_;   /**< Interpolatory or Hierarchical basis function. */
    cemINT              coefficient_order_;

    std::vector< DenseMatrix<cemDOUBLE> > matrix_N_NxNx_; /**< Product of x-derivatives */
    std::vector< DenseMatrix<cemDOUBLE> > matrix_N_NyNy_; /**< Product of y-derivatives */
    std::vector< DenseMatrix<cemDOUBLE> > matrix_N_NN_; /**< Product of functions */


    // Protected member functions:
    void initialize();
    void copy(const SolverElement& other);
};
//************************************************************************************************//



class SolverTriangle : public SolverElement
{
public:
    SolverTriangle(const Element* element_ptr,
                   const cemINT& basis_order,
                   const BasisFunctionField& function_field,
                   const BasisFunctionType& function_type,
                   const cemINT& coefficient_order);

private:
};


}




#endif // BASIS_FUNCTIONS_H
