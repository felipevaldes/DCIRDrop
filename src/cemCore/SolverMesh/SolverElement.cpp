#include "SolverElement.h"
#include "cemError.h"

using namespace cem_core;
using cemcommon::Exception;

//************************************************************************************************//
/** @brief SolverElement::initialize : Initializes SolverElement with default data. */
//************************************************************************************************//
void SolverElement::initialize()
{
    element_ptr_ = NULL;
    basis_function_order_ = 1;
    basis_function_field_ = SCALAR;
    basis_function_type_ = INTERPOLATORY;
    coefficient_order_ = 0;
}


//************************************************************************************************//
/** @brief SolverElement::copy : Deep copy of a SolverElement.
 * @param other : SolverElement to be copied */
//************************************************************************************************//
void SolverElement::copy(const SolverElement &other)
{
    element_ptr_ = other.element_ptr_;
    basis_function_order_ = other.basis_function_order_;
    basis_function_field_ = other.basis_function_field_;
    basis_function_type_ = other.basis_function_type_;
    coefficient_order_ = other.coefficient_order_;

    // Make sure matrices are cleared before copying:
    matrix_N_NxNx_.clear();
    matrix_N_NyNy_.clear();
    matrix_N_NN_.clear();

    if (!other.matrix_N_NxNx_.empty())
    {
        cemINT N = matrix_N_NxNx_.size();
        matrix_N_NxNx_.resize(N);
        for (cemINT i=0; i<N; ++i)
            matrix_N_NxNx_[i] = other.matrix_N_NxNx_[i];
    }

    if (!other.matrix_N_NyNy_.empty())
    {
        cemINT N = matrix_N_NyNy_.size();
        matrix_N_NyNy_.resize(N);
        for (cemINT i=0; i<N; ++i)
            matrix_N_NyNy_[i] = other.matrix_N_NyNy_[i];
    }

    if (!other.matrix_N_NN_.empty())
    {
        cemINT N = matrix_N_NN_.size();
        matrix_N_NN_.resize(N);
        for (cemINT i=0; i<N; ++i)
            matrix_N_NN_[i] = other.matrix_N_NN_[i];
    }
}


//************************************************************************************************//
/** @brief SolverElement::SolverElement : Constructor with parameters
 * @param [in] element_ptr : Pointer to element in mesh
 * @param [in] order : polynomial order of basis functions
 * @param [in] function_field : basis function field (scalar or vector)
 * @param [in] function_type : basis function type (interpolatory or hierarchical) */
//************************************************************************************************//
SolverElement::SolverElement(const cem_mesh::Element* element_ptr,
                             const cemINT& basis_order,
                             const BasisFunctionField& function_field,
                             const BasisFunctionType& function_type,
                             const cemINT& coefficient_order)
{
    element_ptr_ = element_ptr;
    basis_function_order_ = basis_order;
    basis_function_field_ = function_field;
    basis_function_type_ = function_type;

    if (coefficient_order > 1)
        throw(Exception("FEATURE NOT INPLEMENTED","Coefficient order > 1 is not implemented"));

    coefficient_order_ = coefficient_order;
}


//************************************************************************************************//
/** @brief SolverElement::SolverElement : Copy constructor.
 * @param [in] other : SolverElement to be copied */
//************************************************************************************************//
SolverElement::SolverElement(const SolverElement &other) {copy(other);}


//************************************************************************************************//
/** @brief SolverElement::operator = : Copy operator.
 * @param [in] other : SolverElement to be copied
 * @return : A new SolverElement, identical to the one given */
//************************************************************************************************//
SolverElement& SolverElement::operator = (const SolverElement& other) {copy(other);}


//************************************************************************************************//
/** @brief SolverElement::element_ptr : Gets pointer to element in mesh.
 * @return : element_ptr_ */
//************************************************************************************************//
const Element* SolverElement::element_ptr() const {return element_ptr_;}


//************************************************************************************************//
/** @brief SolverElement::basis_function_order : Gets polynomial order of basis functions.
 * @return : basis_function_order_ */
//************************************************************************************************//
cemINT SolverElement::basis_function_order() const {return basis_function_order_;}


//************************************************************************************************//
/** @brief SolverElement::basis_function_field : Gets type of field of the basis function.
 * @return : basis_function_field_ */
//************************************************************************************************//
BasisFunctionField SolverElement::basis_function_field() const {return basis_function_field_;}


//************************************************************************************************//
/** @brief SolverElement::basis_function_type : Gets type of basis function.
 * @return : basis_function_type_ */
//************************************************************************************************//
BasisFunctionType SolverElement::basis_function_type() const {return basis_function_type_;}


//************************************************************************************************//
/** @brief SolverElement::coefficient_order : Gets polynomial order of the coefficients
 * multiplying the basis functions.
 * @return : coefficient_order_ */
//************************************************************************************************//
cemINT SolverElement::coefficient_order() const {return coefficient_order_;}


//************************************************************************************************//
/** @brief SolverElement::matrix_N_NxNx
 * @param i
 * @return
 */
//************************************************************************************************//
const DenseMatrix<cemDOUBLE>& SolverElement::matrix_N_NxNx(cemINT i) const
{

}


//************************************************************************************************//
/**
 * @brief SolverElement::matrix_N_NyNy
 * @param i
 * @return
 */
//************************************************************************************************//
const DenseMatrix<cemDOUBLE>& SolverElement::matrix_N_NyNy(cemINT i) const
{

}


//************************************************************************************************//
/**
 * @brief SolverElement::matrix_N_NN
 * @param i
 * @return
 */
//************************************************************************************************//
const DenseMatrix<cemDOUBLE>& SolverElement::matrix_N_NN(cemINT i) const
{

}




//************************************************************************************************//
/**
 * @brief SolverElement::set_element_ptr
 * @param element_ptr
 */
//************************************************************************************************//
void SolverElement::set_element_ptr(const Element* element_ptr)
{

}


//************************************************************************************************//
/**
 * @brief SolverElement::set_basis_function_order
 * @param order
 */
//************************************************************************************************//
void SolverElement::set_basis_function_order(const cemINT& order)
{

}


//************************************************************************************************//
/**
 * @brief SolverElement::set_basis_function_field
 * @param function_field
 */
//************************************************************************************************//
void SolverElement::set_basis_function_field(const BasisFunctionField& function_field)
{

}


//************************************************************************************************//
/**
 * @brief SolverElement::set_basis_function_type
 * @param function_type
 */
//************************************************************************************************//
void SolverElement::set_basis_function_type(const BasisFunctionType& function_type)
{

}


//************************************************************************************************//
/**
 * @brief SolverElement::setUp_matrix_N_NxNx
 */
//************************************************************************************************//
void SolverElement::setUp_matrix_N_NxNx()
{

}


//************************************************************************************************//
/**
 * @brief SolverElement::setUp_matrix_N_NyNy
 */
//************************************************************************************************//
void SolverElement::setUp_matrix_N_NyNy()
{

}


//************************************************************************************************//
/** @brief SolverElement::setUp_matrix_N_NN
 */
//************************************************************************************************//
void SolverElement::setUp_matrix_N_NN()
{

}


