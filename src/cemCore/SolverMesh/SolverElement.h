#ifndef BASIS_FUNCTIONS_H
#define BASIS_FUNCTIONS_H

#include <vector>
#include <iostream>
#include "cemMesh.h"
#include "BasisFunctions/BasisFunctions.h"
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
    void set_basis_function_order(const cemINT& order);
    void set_basis_function_field(const BasisFunctionField& function_field);
    void set_basis_function_type(const BasisFunctionType& function_type);
    void set_coefficient_order(const cemINT& order);

    // Matrices:
    virtual void setUp_matrix_N_NxNx() = 0;
    virtual void setUp_matrix_N_NyNy() = 0;
    virtual void setUp_matrix_N_NN() = 0;



protected:
    const Element*      element_ptr_;           //!< Element in mesh.
    cemINT              basis_function_order_;  //!< Polynomial order of the basis functions hosted.
    BasisFunctionField  basis_function_field_;  //!< Vector or Scalar basis function.
    BasisFunctionType   basis_function_type_;   //!< Interpolatory or Hierarchical basis function.
    cemINT              coefficient_order_;     //!< Polynomial order of the coefficients
                                                //!< scalling the basis functions.

    std::vector< DenseMatrix<cemDOUBLE> > matrix_N_NxNx_;   //!< Product of x-derivatives.
    std::vector< DenseMatrix<cemDOUBLE> > matrix_N_NyNy_;   //!< Product of y-derivatives.
    std::vector< DenseMatrix<cemDOUBLE> > matrix_N_NN_;     //!< Product of functions.


    // Protected member functions:
    void initialize();
    void copy(const SolverElement& other);

    // Default constructor:
    SolverElement();

    // Constructor with parameters:
    SolverElement(const cemINT& basis_order,
                  const BasisFunctionField& function_field,
                  const BasisFunctionType& function_type,
                  const cemINT& coefficient_order);

};
//************************************************************************************************//


//************************************************************************************************//
/** @brief The SolverTriangle class
 * @author Felipe Valdes V. */
//************************************************************************************************//
class SolverTriangle : public SolverElement
{
public:
    /** @brief SolverTriangle : Default constructor. */
    SolverTriangle() : SolverElement() {}

    // Constructor with parameters:
    SolverTriangle(const Element* element_ptr,
                   const cemINT& basis_order,
                   const BasisFunctionField& function_field,
                   const BasisFunctionType& function_type,
                   const cemINT& coefficient_order);

    // Set data members:
    void set_element_ptr(const Element* element_ptr);

    // Matrices:
    void setUp_matrix_N_NxNx();
    void setUp_matrix_N_NyNy();
    void setUp_matrix_N_NN();

private:
    cemBOOL geometry_is_Up_;    //!< TRUE if setUpGeometry() has been run succesfully

    cemDOUBLE x1_;      //!< X-coordinate of node 1
    cemDOUBLE y1_;      //!< Y-coordinate of node 1
    cemDOUBLE z1_;      //!< Z-coordinate of node 1
    cemDOUBLE x2_;      //!< X-coordinate of node 2
    cemDOUBLE y2_;      //!< Y-coordinate of node 2
    cemDOUBLE z2_;      //!< Z-coordinate of node 2
    cemDOUBLE x3_;      //!< X-coordinate of node 3
    cemDOUBLE y3_;      //!< Y-coordinate of node 3
    cemDOUBLE z3_;      //!< Z-coordinate of node 3
    cemDOUBLE a1_;      //!< \f$ a_1 = x_2*y_3 - y_3*x_3 \f$
    cemDOUBLE a2_;      //!< \f$ a_2 = x_3*y_1 - y_3*x_1 \f$
    cemDOUBLE a3_;      //!< \f$ a_3 = x_1*y_2 - y_1*x_2 \f$
    cemDOUBLE b1_;      //!< \f$ b_1 = y_2 - y_3 \f$
    cemDOUBLE b2_;      //!< \f$ b_2 = y_3 - y_1 \f$
    cemDOUBLE b3_;      //!< \f$ b_3 = y_1 - y_2 \f$
    cemDOUBLE c1_;      //!< \f$ c_1 = x_3 - x_2 \f$
    cemDOUBLE c2_;      //!< \f$ c_2 = x_1 - x_3 \f$
    cemDOUBLE c3_;      //!< \f$ c_3 = x_2 - x_1 \f$
    cemDOUBLE delta_;   //!< \f$ delta_ = (b_1*c_2 - b_2*c_1)/2 \f$

    // Private member functions:
    void setUpGeometry();



};


}




#endif // BASIS_FUNCTIONS_H
