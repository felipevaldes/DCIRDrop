#include "SolverElement.h"
#include "cemError.h"

using namespace cem_core;
using cemcommon::Exception;

///***********************************************************************************************//
/// CLASS SolverElement:
///***********************************************************************************************//

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
/** @brief SolverElement::SolverElement : Default constructor. */
//************************************************************************************************//
SolverElement::SolverElement() {initialize();}


//************************************************************************************************//
/** @brief SolverElement::SolverElement : Constructor with parameters.
 * @param [in] basis_order : polynomial order of basis functions
 * @param [in] function_field : basis function field (scalar or vector)
 * @param [in] function_type : basis function type (interpolatory or hierarchical)
 * @param [in] coefficient_order : polynomial order of coefficients */
//************************************************************************************************//
SolverElement::SolverElement(const cemINT& basis_order,
                             const BasisFunctionField& function_field,
                             const BasisFunctionType& function_type,
                             const cemINT& coefficient_order)
{
    if (basis_order < 1)
        throw(Exception("INPUT ERROR","basis_order must be > 0"));

    if (basis_order > 3)
        throw(Exception("FEATURE NOT INPLEMENTED","basis_order > 3 not implemented"));

    if (coefficient_order < 0)
        throw(Exception("INPUT ERROR","coefficient_order must be >= 0"));

    if (coefficient_order > 1)
        throw(Exception("FEATURE NOT INPLEMENTED","Coefficient order > 1 not implemented"));

    basis_function_order_ = basis_order;
    basis_function_field_ = function_field;
    basis_function_type_ = function_type;
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
/** @brief SolverElement::matrix_N_NxNx : Gets i-th NxNx matrix.
 * @param [in] i : index of matrix to be returned
 * @return : matrix_N_NxNx_[i] */
//************************************************************************************************//
const DenseMatrix<cemDOUBLE>& SolverElement::matrix_N_NxNx(cemINT i) const
{
    if (i >= (coefficient_order_+1)*(coefficient_order_+2)/2)
        throw(Exception("INPUT ERROR","Input is higher than number of matrices"));

    return matrix_N_NxNx_[i];
}


//************************************************************************************************//
/** @brief SolverElement::matrix_N_NyNy : Gets i-th NyNy matrix.
 * @param [in] i : index of matrix to be returned
 * @return : matrix_N_NyNy_[i] */
//************************************************************************************************//
const DenseMatrix<cemDOUBLE>& SolverElement::matrix_N_NyNy(cemINT i) const
{
    if (i >= (coefficient_order_+1)*(coefficient_order_+2)/2)
        throw(Exception("INPUT ERROR","Input is higher than number of matrices"));

    return matrix_N_NyNy_[i];
}


//************************************************************************************************//
/** @brief SolverElement::matrix_N_NN : Gets i-th NN matrix.
 * @param [in] i : index of matrix to be returned
 * @return : matrix_N_NN_[i] */
//************************************************************************************************//
const DenseMatrix<cemDOUBLE>& SolverElement::matrix_N_NN(cemINT i) const
{
    if (i >= (coefficient_order_+1)*(coefficient_order_+2)/2)
        throw(Exception("INPUT ERROR","Input is higher than number of matrices"));

    return matrix_N_NN_[i];
}


//************************************************************************************************//
/** @brief SolverElement::set_basis_function_order : Sets polynomial order of basis functions.
 * @param [in] order : polynomial order (between 1 and 3)  */
//************************************************************************************************//
void SolverElement::set_basis_function_order(const cemINT& order)
{
    if (order < 1)
        throw(Exception("INPUT ERROR","basis_order must be > 0"));

    if (order > 3)
        throw(Exception("FEATURE NOT INPLEMENTED","basis_order > 3 not implemented"));

    basis_function_order_ = order;
}


//************************************************************************************************//
/** @brief SolverElement::set_basis_function_field : Sets type of field of the basis function.
 * @param [in] function_field : SCALAR or VECTOR */
//************************************************************************************************//
void SolverElement::set_basis_function_field(const BasisFunctionField& function_field)
{
    basis_function_field_ = function_field;
}


//************************************************************************************************//
/** @brief SolverElement::set_basis_function_type : Sets type of basis function.
 * @param function_type : INTERPOLATORY or HIERARCHICAL */
//************************************************************************************************//
void SolverElement::set_basis_function_type(const BasisFunctionType& function_type)
{
    basis_function_type_ = function_type;
}


//************************************************************************************************//
/** @brief SolverElement::set_coefficient_order : Sets polynomial order of the coefficients.
 * @param [in] order : polynomial order (0 or 1) */
//************************************************************************************************//
void SolverElement::set_coefficient_order(const cemINT &order)
{
    if (order < 0)
        throw(Exception("INPUT ERROR","coefficient_order must be >= 0"));

    if (order > 1)
        throw(Exception("FEATURE NOT INPLEMENTED","Coefficient order > 1 not implemented"));

    coefficient_order_ = order;
}



///***********************************************************************************************//
/// CLASS SolverTriangle:
///***********************************************************************************************//

//************************************************************************************************//
/** @brief SolverTriangle::SolverTriangle : Constructor with parameters.
 * @param [in] element_ptr : pointer to element in mesh
 * @param [in] basis_order : polynomial order of basis functions
 * @param [in] function_field : basis function field (scalar or vector)
 * @param [in] function_type : basis function type (interpolatory or hierarchical)
 * @param [in] coefficient_order : polynomial order of coefficients */
//************************************************************************************************//
SolverTriangle::SolverTriangle(const cem_mesh::Element* element_ptr,
                               const cemINT& basis_order,
                               const BasisFunctionField& function_field,
                               const BasisFunctionType& function_type,
                               const cemINT& coefficient_order) : SolverElement(basis_order,
                                                                                function_field,
                                                                                function_type,
                                                                                coefficient_order)

{
    // Check that element is a triangle:
    if (element_ptr->type() != Element::TRI)
        throw(Exception("WRONG ELEMENT TYPE","Expected a Triangle (TRI)"));

    element_ptr_ = element_ptr;
}


//************************************************************************************************//
/** @brief SolverTriangle::set_element_ptr : Sets pointer to mesh element (triangle)
 * @param [in] element_ptr : pointer to element in mesh */
//************************************************************************************************//
void SolverTriangle::set_element_ptr(const cem_mesh::Element *element_ptr)
{
    // Check that element is a triangle:
    if (element_ptr->type() != Element::TRI)
        throw(Exception("WRONG ELEMENT TYPE","Expected a Triangle (TRI)"));

    element_ptr_ = element_ptr;
    geometry_is_Up_ = false;
}


//************************************************************************************************//
/** @brief SolverTriangle::setUp_matrix_N_NxNx : Set up vector of matrices N_NxNx.
 * @author Felipe Valdes V. */
//************************************************************************************************//
void SolverTriangle::setUp_matrix_N_NxNx()
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    // Number of matrices depends on the polynomial order of the coefficients:
    cemINT num_matrices = 0;
    if (coefficient_order_ == 0)
        num_matrices = 1;
    else if (coefficient_order_ == 1)
        num_matrices = 3;

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;

    matrix_N_NxNx_.resize(num_matrices);
    if (coefficient_order_ == 0)
    {
        matrix_N_NxNx_[0].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](1,1) = pow(b1_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](2,1) = (b1_*b2_)/(4.0*delta_);
            matrix_N_NxNx_[0](3,1) = (b1_*b3_)/(4.0*delta_);

            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = pow(b2_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](3,2) = (b2_*b3_)/(4.0*delta_);

            matrix_N_NxNx_[0](1,3) = matrix_N_NxNx_[0](3,1);
            matrix_N_NxNx_[0](2,3) = matrix_N_NxNx_[0](3,2);
            matrix_N_NxNx_[0](3,3) = pow(b3_,2)/(4.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](1,1) = pow(b1_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](2,1) = -(b1_*b2_)/(12.0*delta_);
            matrix_N_NxNx_[0](3,1) = -(b1_*b3_)/(12.0*delta_);
            matrix_N_NxNx_[0](4,1) = (b1_*b2_)/(3.0*delta_);
            matrix_N_NxNx_[0](5,1) = 0.0;
            matrix_N_NxNx_[0](6,1) = (b1_*b3_)/(3.0*delta_);

            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = pow(b2_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](3,2) = -(b2_*b3_)/(12.0*delta_);
            matrix_N_NxNx_[0](4,2) = (b1_*b2_)/(3.0*delta_);
            matrix_N_NxNx_[0](5,2) = (b2_*b3_)/(3.0*delta_);
            matrix_N_NxNx_[0](6,2) = 0.0;

            matrix_N_NxNx_[0](1,3) = matrix_N_NxNx_[0](3,1);
            matrix_N_NxNx_[0](2,3) = matrix_N_NxNx_[0](3,2);
            matrix_N_NxNx_[0](3,3) = pow(b3_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](4,3) = 0.0;
            matrix_N_NxNx_[0](5,3) = (b2_*b3_)/(3.0*delta_);
            matrix_N_NxNx_[0](6,3) = (b1_*b3_)/(3.0*delta_);

            matrix_N_NxNx_[0](1,4) = matrix_N_NxNx_[0](4,1);
            matrix_N_NxNx_[0](2,4) = matrix_N_NxNx_[0](4,2);
            matrix_N_NxNx_[0](3,4) = matrix_N_NxNx_[0](4,3);
            matrix_N_NxNx_[0](4,4) = (2.0*pow(b1_,2))/(3.0*delta_) + (2.0*b1_*b2_)/(3.0*delta_) + (2.0*pow(b2_,2))/(3.0*delta_);
            matrix_N_NxNx_[0](5,4) = (b1_*b2_)/(3.0*delta_) + pow(b2_,2)/(3.0*delta_) + (2.0*b1_*b3_)/(3.0*delta_) + (b2_*b3_)/(3.0*delta_);
            matrix_N_NxNx_[0](6,4) = pow(b1_,2)/(3.0*delta_) + (b1_*b2_)/(3.0*delta_) + (b1_*b3_)/(3.0*delta_) + (2.0*b2_*b3_)/(3.0*delta_);

            matrix_N_NxNx_[0](1,5) = matrix_N_NxNx_[0](5,1);
            matrix_N_NxNx_[0](2,5) = matrix_N_NxNx_[0](5,2);
            matrix_N_NxNx_[0](3,5) = matrix_N_NxNx_[0](5,3);
            matrix_N_NxNx_[0](4,5) = matrix_N_NxNx_[0](5,4);
            matrix_N_NxNx_[0](5,5) = (2.0*pow(b2_,2))/(3.0*delta_) + (2.0*b2_*b3_)/(3.0*delta_) + (2.0*pow(b3_,2))/(3.0*delta_);
            matrix_N_NxNx_[0](6,5) = (2.0*b1_*b2_)/(3.0*delta_) + (b1_*b3_)/(3.0*delta_) + (b2_*b3_)/(3.0*delta_) + pow(b3_,2)/(3.0*delta_);

            matrix_N_NxNx_[0](1,6) = matrix_N_NxNx_[0](6,1);
            matrix_N_NxNx_[0](2,6) = matrix_N_NxNx_[0](6,2);
            matrix_N_NxNx_[0](3,6) = matrix_N_NxNx_[0](6,3);
            matrix_N_NxNx_[0](4,6) = matrix_N_NxNx_[0](6,4);
            matrix_N_NxNx_[0](5,6) = matrix_N_NxNx_[0](6,5);
            matrix_N_NxNx_[0](6,6) = (2.0*pow(b1_,2))/(3.0*delta_) + (2.0*b1_*b3_)/(3.0*delta_) + (2.0*pow(b3_,2))/(3.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }
    }
    else if (coefficient_order_ == 1)
    {
        matrix_N_NxNx_[0].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](1,1) = pow(b1_,2)/(12.0*delta_);
            matrix_N_NxNx_[0](2,1) = (b1_*b2_)/(12.0*delta_);
            matrix_N_NxNx_[0](3,1) = (b1_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = pow(b2_,2)/(12.0*delta_);
            matrix_N_NxNx_[0](3,2) = (b2_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[0](1,3) = matrix_N_NxNx_[0](3,1);
            matrix_N_NxNx_[0](2,3) = matrix_N_NxNx_[0](3,2);
            matrix_N_NxNx_[0](3,3) = pow(b3_,2)/(12.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](1,1) = (3.0*pow(b1_,2))/(20.0*delta_);
            matrix_N_NxNx_[0](2,1) = -(b1_*b2_)/(30.0*delta_);
            matrix_N_NxNx_[0](3,1) = -(b1_*b3_)/(30.0*delta_);
            matrix_N_NxNx_[0](4,1) = (b1_*(3.0*b1_ + 14.0*b2_))/(60.0*delta_);
            matrix_N_NxNx_[0](5,1) = (b1_*(b2_ + b3_))/(20.0*delta_);
            matrix_N_NxNx_[0](6,1) = (b1_*(3.0*b1_ + 14.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = pow(b2_,2)/(20.0*delta_);
            matrix_N_NxNx_[0](3,2) = -(b2_*b3_)/(60.0*delta_);
            matrix_N_NxNx_[0](4,2) = ((3.0*b1_ - 2.0*b2_)*b2_)/(60.0*delta_);
            matrix_N_NxNx_[0](5,2) = -(b2_*(b2_ - 3.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[0](6,2) = -(b2_*(b1_ + 2.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[0](1,3) = matrix_N_NxNx_[0](3,1);
            matrix_N_NxNx_[0](2,3) = matrix_N_NxNx_[0](3,2);
            matrix_N_NxNx_[0](3,3) = pow(b3_,2)/(20.0*delta_);
            matrix_N_NxNx_[0](4,3) = -((b1_ + 2.0*b2_)*b3_)/(60.0*delta_);
            matrix_N_NxNx_[0](5,3) = ((3.0*b2_ - b3_)*b3_)/(60.0*delta_);
            matrix_N_NxNx_[0](6,3) = ((3.0*b1_ - 2.0*b3_)*b3_)/(60.0*delta_);

            matrix_N_NxNx_[0](1,4) = matrix_N_NxNx_[0](4,1);
            matrix_N_NxNx_[0](2,4) = matrix_N_NxNx_[0](4,3);
            matrix_N_NxNx_[0](3,4) = matrix_N_NxNx_[0](4,3);
            matrix_N_NxNx_[0](4,4) = (2.0*(pow(b1_,2) + 2.0*b1_*b2_ + 3.0*pow(b2_,2)))/(15.0*delta_);
            matrix_N_NxNx_[0](5,4) = (2.0*b2_*(b2_ + b3_) + b1_*(b2_ + 2.0*b3_))/(15.0*delta_);
            matrix_N_NxNx_[0](6,4) = (pow(b1_,2) + 6.0*b2_*b3_ + 2.0*b1_*(b2_ + b3_))/(15.0*delta_);

            matrix_N_NxNx_[0](1,5) = matrix_N_NxNx_[0](5,1);
            matrix_N_NxNx_[0](2,5) = matrix_N_NxNx_[0](5,2);
            matrix_N_NxNx_[0](3,5) = matrix_N_NxNx_[0](5,3);
            matrix_N_NxNx_[0](4,5) = matrix_N_NxNx_[0](5,4);
            matrix_N_NxNx_[0](5,5) = (2.0*(pow(b2_,2) + b2_*b3_ + pow(b3_,2)))/(15.0*delta_);
            matrix_N_NxNx_[0](6,5) = (2.0*b3_*(b2_ + b3_) + b1_*(2.0*b2_ + b3_))/(15.0*delta_);

            matrix_N_NxNx_[0](1,6) = matrix_N_NxNx_[0](6,1);
            matrix_N_NxNx_[0](2,6) = matrix_N_NxNx_[0](6,2);
            matrix_N_NxNx_[0](3,6) = matrix_N_NxNx_[0](6,3);
            matrix_N_NxNx_[0](4,6) = matrix_N_NxNx_[0](6,4);
            matrix_N_NxNx_[0](5,6) = matrix_N_NxNx_[0](6,5);
            matrix_N_NxNx_[0](6,6) = (2.0*(pow(b1_,2) + 2.0*b1_*b3_ + 3.0*pow(b3_,2)))/(15.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }


        matrix_N_NxNx_[1].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[1](1,1) = pow(b1_,2)/(12.0*delta_);
            matrix_N_NxNx_[1](2,1) = (b1_*b2_)/(12.0*delta_);
            matrix_N_NxNx_[1](3,1) = (b1_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[1](1,2) = matrix_N_NxNx_[1](2,1);
            matrix_N_NxNx_[1](2,2) = pow(b2_,2)/(12.0*delta_);
            matrix_N_NxNx_[1](3,2) = (b2_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[1](1,3) = matrix_N_NxNx_[1](3,1);
            matrix_N_NxNx_[1](2,3) = matrix_N_NxNx_[1](3,2);
            matrix_N_NxNx_[1](3,3) = pow(b3_,2)/(12.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[1](1,1) = pow(b1_,2)/(20.0*delta_);
            matrix_N_NxNx_[1](2,1) = -(b1_*b2_)/(30.0*delta_);
            matrix_N_NxNx_[1](3,1) = -(b1_*b3_)/(60.0*delta_);
            matrix_N_NxNx_[1](4,1) = (b1_*(-2.0*b1_ + 3.0*b2_))/(60.0*delta_);
            matrix_N_NxNx_[1](5,1) = -(b1_*(b2_ + 2.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[1](6,1) = -(b1_*(b1_ - 3.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[1](1,2) = matrix_N_NxNx_[1](2,1);
            matrix_N_NxNx_[1](2,2) = (3.0*pow(b2_,2))/(20.0*delta_);
            matrix_N_NxNx_[1](3,2) = -(b2_*b3_)/(30.0*delta_);
            matrix_N_NxNx_[1](4,2) = (b2_*(14.0*b1_ + 3.0*b2_))/(60.0*delta_);
            matrix_N_NxNx_[1](5,2) = (b2_*(3.0*b2_ + 14.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[1](6,2) = (b2_*(b1_ + b3_))/(20.0*delta_);

            matrix_N_NxNx_[1](1,3) = matrix_N_NxNx_[1](3,1);
            matrix_N_NxNx_[1](2,3) = matrix_N_NxNx_[1](3,2);
            matrix_N_NxNx_[1](3,3) = pow(b3_,2)/(20.0*delta_);
            matrix_N_NxNx_[1](4,3) = -((2.0*b1_ + b2_)*b3_)/(60.0*delta_);
            matrix_N_NxNx_[1](5,3) = ((3.0*b2_ - 2.0*b3_)*b3_)/(60.0*delta_);
            matrix_N_NxNx_[1](6,3) = ((3.0*b1_ - b3_)*b3_)/(60.0*delta_);

            matrix_N_NxNx_[1](1,4) = matrix_N_NxNx_[1](4,1);
            matrix_N_NxNx_[1](2,4) = matrix_N_NxNx_[1](4,2);
            matrix_N_NxNx_[1](3,4) = matrix_N_NxNx_[1](4,3);
            matrix_N_NxNx_[1](4,4) = (2.0*(3.0*pow(b1_,2) + 2.0*b1_*b2_ + pow(b2_,2)))/(15.0*delta_);
            matrix_N_NxNx_[1](5,4) = (2.0*b1_*b2_ + pow(b2_,2) + 6.0*b1_*b3_ + 2.0*b2_*b3_)/(15.0*delta_);
            matrix_N_NxNx_[1](6,4) = (2.0*pow(b1_,2) + b1_*b2_ + 2.0*b1_*b3_ + 2.0*b2_*b3_)/(15.0*delta_);

            matrix_N_NxNx_[1](1,5) = matrix_N_NxNx_[1](4,1);
            matrix_N_NxNx_[1](2,5) = matrix_N_NxNx_[1](5,2);
            matrix_N_NxNx_[1](3,5) = matrix_N_NxNx_[1](5,3);
            matrix_N_NxNx_[1](4,5) = matrix_N_NxNx_[1](5,4);
            matrix_N_NxNx_[1](5,5) = (2.0*(pow(b2_,2) + 2.0*b2_*b3_ + 3.0*pow(b3_,2)))/(15.0*delta_);
            matrix_N_NxNx_[1](6,5) = (2.0*b1_*(b2_ + b3_) + b3_*(b2_ + 2.0*b3_))/(15.0*delta_);

            matrix_N_NxNx_[1](1,6) = matrix_N_NxNx_[1](6,1);
            matrix_N_NxNx_[1](2,6) = matrix_N_NxNx_[1](6,2);
            matrix_N_NxNx_[1](3,6) = matrix_N_NxNx_[1](6,3);
            matrix_N_NxNx_[1](4,6) = matrix_N_NxNx_[1](6,4);
            matrix_N_NxNx_[1](5,6) = matrix_N_NxNx_[1](6,5);
            matrix_N_NxNx_[1](6,6) = (2.0*(pow(b1_,2) + b1_*b3_ + pow(b3_,2)))/(15.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }


        matrix_N_NxNx_[2].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[2](1,1) = pow(b1_,2)/(12.0*delta_);
            matrix_N_NxNx_[2](2,1) = (b1_*b2_)/(12.0*delta_);
            matrix_N_NxNx_[2](3,1) = (b1_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[2](1,2) = matrix_N_NxNx_[2](2,1);
            matrix_N_NxNx_[2](2,2) = pow(b2_,2)/(12.0*delta_);
            matrix_N_NxNx_[2](3,2) = (b2_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[2](1,3) = matrix_N_NxNx_[2](3,1);
            matrix_N_NxNx_[2](2,3) = matrix_N_NxNx_[2](3,2);
            matrix_N_NxNx_[2](3,3) = pow(b3_,2)/(12.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[2](1,1) = pow(b1_,2)/(20.0*delta_);
            matrix_N_NxNx_[2](2,1) = -(b1_*b2_)/(60.0*delta_);
            matrix_N_NxNx_[2](3,1) = -(b1_*b3_)/(30.0*delta_);
            matrix_N_NxNx_[2](4,1) = -(b1_*(b1_ - 3.0*b2_))/(60.0*delta_);
            matrix_N_NxNx_[2](5,1) = -(b1_*(2.0*b2_ + b3_))/(60.0*delta_);
            matrix_N_NxNx_[2](6,1) = (b1_*(-2.0*b1_ + 3.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[2](1,2) = matrix_N_NxNx_[2](2,1);
            matrix_N_NxNx_[2](2,2) = pow(b2_,2)/(20.0*delta_);
            matrix_N_NxNx_[2](3,2) = -(b2_*b3_)/(30.0*delta_);
            matrix_N_NxNx_[2](4,2) = ((3.0*b1_ - b2_)*b2_)/(60.0*delta_);
            matrix_N_NxNx_[2](5,2) = (b2_*(-2.0*b2_ + 3.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[2](6,2) = -(b2_*(2.0*b1_ + b3_))/(60.0*delta_);

            matrix_N_NxNx_[2](1,3) = matrix_N_NxNx_[2](3,1);
            matrix_N_NxNx_[2](2,3) = matrix_N_NxNx_[2](2,3);
            matrix_N_NxNx_[2](3,3) = (3.0*pow(b3_,2))/(20.0*delta_);
            matrix_N_NxNx_[2](4,3) = ((b1_ + b2_)*b3_)/(20.0*delta_);
            matrix_N_NxNx_[2](5,3) = (b3_*(14.0*b2_ + 3.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[2](6,3) = (b3_*(14.0*b1_ + 3.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[2](1,4) = matrix_N_NxNx_[2](4,1);
            matrix_N_NxNx_[2](2,4) = matrix_N_NxNx_[2](4,2);
            matrix_N_NxNx_[2](3,4) = matrix_N_NxNx_[2](4,3);
            matrix_N_NxNx_[2](4,4) = (2.0*(pow(b1_,2) + b1_*b2_ + pow(b2_,2)))/(15.0*delta_);
            matrix_N_NxNx_[2](5,4) = (2.0*b1_*(b2_ + b3_) + b2_*(2.0*b2_ + b3_))/(15.0*delta_);
            matrix_N_NxNx_[2](6,4) = (2.0*pow(b1_,2) + 2.0*b1_*b2_ + b1_*b3_ + 2.0*b2_*b3_)/(15.0*delta_);

            matrix_N_NxNx_[2](1,5) = matrix_N_NxNx_[2](5,1);
            matrix_N_NxNx_[2](2,5) = matrix_N_NxNx_[2](5,2);
            matrix_N_NxNx_[2](3,5) = matrix_N_NxNx_[2](5,3);
            matrix_N_NxNx_[2](4,5) = matrix_N_NxNx_[2](5,4);
            matrix_N_NxNx_[2](5,5) = (2.0*(3.0*pow(b2_,2) + 2.0*b2_*b3_ + pow(b3_,2)))/(15.0*delta_);
            matrix_N_NxNx_[2](6,5) = (6.0*b1_*b2_ + 2.0*b1_*b3_ + 2.0*b2_*b3_ + pow(b3_,2))/(15.0*delta_);

            matrix_N_NxNx_[2](1,6) = matrix_N_NxNx_[2](6,1);
            matrix_N_NxNx_[2](2,6) = matrix_N_NxNx_[2](6,2);
            matrix_N_NxNx_[2](3,6) = matrix_N_NxNx_[2](6,3);
            matrix_N_NxNx_[2](4,6) = matrix_N_NxNx_[2](6,4);
            matrix_N_NxNx_[2](5,6) = matrix_N_NxNx_[2](6,5);
            matrix_N_NxNx_[2](6,6) = (2.0*(3.0*pow(b1_,2) + 2.0*b1_*b3_ + pow(b3_,2)))/(15.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }
    }

}


//************************************************************************************************//
/** @brief SolverTriangle::setUp_matrix_N_NyNy : Set up vector of matrices N_NyNy.
 * @author Felipe Valdes V. */
//************************************************************************************************//
void SolverTriangle::setUp_matrix_N_NyNy()
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    // Number of matrices depends on the polynomial order of the coefficients:
    cemINT num_matrices = 0;
    if (coefficient_order_ == 0)
        num_matrices = 1;
    else if (coefficient_order_ == 1)
        num_matrices = 3;

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;

    matrix_N_NyNy_.resize(num_matrices);
    if (coefficient_order_ == 0)
    {
        matrix_N_NyNy_[0].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](1,1) = pow(c1_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](2,1) = (c1_*c2_)/(4.0*delta_);
            matrix_N_NyNy_[0](3,1) = (c1_*c3_)/(4.0*delta_);

            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = pow(c2_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](3,2) = (c2_*c3_)/(4.0*delta_);

            matrix_N_NyNy_[0](1,3) = matrix_N_NyNy_[0](3,1);
            matrix_N_NyNy_[0](2,3) = matrix_N_NyNy_[0](3,2);
            matrix_N_NyNy_[0](3,3) = pow(c3_,2)/(4.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](1,1) = pow(c1_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](2,1) = -(c1_*c2_)/(12.0*delta_);
            matrix_N_NyNy_[0](3,1) = -(c1_*c3_)/(12.0*delta_);
            matrix_N_NyNy_[0](4,1) = (c1_*c2_)/(3.0*delta_);
            matrix_N_NyNy_[0](5,1) = 0.0;
            matrix_N_NyNy_[0](6,1) = (c1_*c3_)/(3.0*delta_);

            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = pow(c2_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](3,2) = -(c2_*c3_)/(12.0*delta_);
            matrix_N_NyNy_[0](4,2) = (c1_*c2_)/(3.0*delta_);
            matrix_N_NyNy_[0](5,2) = (c2_*c3_)/(3.0*delta_);
            matrix_N_NyNy_[0](6,2) = 0.0;

            matrix_N_NyNy_[0](1,3) = matrix_N_NyNy_[0](3,1);
            matrix_N_NyNy_[0](2,3) = matrix_N_NyNy_[0](3,2);
            matrix_N_NyNy_[0](3,3) = pow(c3_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](4,3) = 0.0;
            matrix_N_NyNy_[0](5,3) = (c2_*c3_)/(3.0*delta_);
            matrix_N_NyNy_[0](6,3) = (c1_*c3_)/(3.0*delta_);

            matrix_N_NyNy_[0](1,4) = matrix_N_NyNy_[0](4,1);
            matrix_N_NyNy_[0](2,4) = matrix_N_NyNy_[0](4,2);
            matrix_N_NyNy_[0](3,4) = matrix_N_NyNy_[0](4,3);
            matrix_N_NyNy_[0](4,4) = (2.0*pow(c1_,2))/(3.0*delta_) + (2.0*c1_*c2_)/(3.0*delta_) + (2.0*pow(c2_,2))/(3.0*delta_);
            matrix_N_NyNy_[0](5,3) = (c1_*c2_)/(3.0*delta_) + pow(c2_,2)/(3.0*delta_) + (2.0*c1_*c3_)/(3.0*delta_) + (c2_*c3_)/(3.0*delta_);
            matrix_N_NyNy_[0](6,4) = pow(c1_,2)/(3.0*delta_) + (c1_*c2_)/(3.0*delta_) + (c1_*c3_)/(3.0*delta_) + (2.0*c2_*c3_)/(3.0*delta_);

            matrix_N_NyNy_[0](1,5) = matrix_N_NyNy_[0](5,1);
            matrix_N_NyNy_[0](2,5) = matrix_N_NyNy_[0](5,2);
            matrix_N_NyNy_[0](3,5) = matrix_N_NyNy_[0](5,3);
            matrix_N_NyNy_[0](4,5) = matrix_N_NyNy_[0](5,4);
            matrix_N_NyNy_[0](5,5) = (2.0*pow(c2_,2))/(3.0*delta_) + (2.0*c2_*c3_)/(3.0*delta_) + (2.0*pow(c3_,2))/(3.0*delta_);
            matrix_N_NyNy_[0](6,5) = (2.0*c1_*c2_)/(3.0*delta_) + (c1_*c3_)/(3.0*delta_) + (c2_*c3_)/(3.0*delta_) + pow(c3_,2)/(3.0*delta_);

            matrix_N_NyNy_[0](1,6) = matrix_N_NyNy_[0](6,1);
            matrix_N_NyNy_[0](2,6) = matrix_N_NyNy_[0](6,2);
            matrix_N_NyNy_[0](3,6) = matrix_N_NyNy_[0](6,3);
            matrix_N_NyNy_[0](4,6) = matrix_N_NyNy_[0](6,4);
            matrix_N_NyNy_[0](5,6) = matrix_N_NyNy_[0](6,5);
            matrix_N_NyNy_[0](6,6) = (2.0*pow(c1_,2))/(3.0*delta_) + (2.0*c1_*c3_)/(3.0*delta_) + (2.0*pow(c3_,2))/(3.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }
    }
    else if (coefficient_order_ == 1)
    {
        matrix_N_NyNy_[0].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](1,1) = pow(c1_,2)/(12.0*delta_);
            matrix_N_NyNy_[0](2,1) = (c1_*c2_)/(12.0*delta_);
            matrix_N_NyNy_[0](3,1) = (c1_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = pow(c2_,2)/(12.0*delta_);
            matrix_N_NyNy_[0](3,2) = (c2_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[0](1,3) = matrix_N_NyNy_[0](3,1);
            matrix_N_NyNy_[0](2,3) = matrix_N_NyNy_[0](3,2);
            matrix_N_NyNy_[0](3,3) = pow(c3_,2)/(12.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](1,1) = (3.0*pow(c1_,2))/(20.0*delta_);
            matrix_N_NyNy_[0](2,1) = -(c1_*c2_)/(30.0*delta_);
            matrix_N_NyNy_[0](3,1) = -(c1_*c3_)/(30.0*delta_);
            matrix_N_NyNy_[0](4,1) = (c1_*(3.0*c1_ + 14.0*c2_))/(60.0*delta_);
            matrix_N_NyNy_[0](5,1) = (c1_*(c2_ + c3_))/(20.0*delta_);
            matrix_N_NyNy_[0](6,1) = (c1_*(3.0*c1_ + 14.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = pow(c2_,2)/(20.0*delta_);
            matrix_N_NyNy_[0](3,2) = -(c2_*c3_)/(60.0*delta_);
            matrix_N_NyNy_[0](4,2) = ((3.0*c1_ - 2.0*c2_)*c2_)/(60.0*delta_);
            matrix_N_NyNy_[0](5,2) = -(c2_*(c2_ - 3.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[0](6,2) = -(c2_*(c1_ + 2.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[0](1,3) = matrix_N_NyNy_[0](3,1);
            matrix_N_NyNy_[0](2,3) = matrix_N_NyNy_[0](3,2);
            matrix_N_NyNy_[0](3,3) = pow(c3_,2)/(20.0*delta_);
            matrix_N_NyNy_[0](4,3) = -((c1_ + 2.0*c2_)*c3_)/(60.0*delta_);
            matrix_N_NyNy_[0](5,3) = ((3.0*c2_ - c3_)*c3_)/(60.0*delta_);
            matrix_N_NyNy_[0](6,3) = ((3.0*c1_ - 2.0*c3_)*c3_)/(60.0*delta_);

            matrix_N_NyNy_[0](1,4) = matrix_N_NyNy_[0](4,1);
            matrix_N_NyNy_[0](2,4) = matrix_N_NyNy_[0](4,2);
            matrix_N_NyNy_[0](3,4) = matrix_N_NyNy_[0](4,3);
            matrix_N_NyNy_[0](4,4) = (2.0*(pow(c1_,2) + 2.0*c1_*c2_ + 3.0*pow(c2_,2)))/(15.0*delta_);
            matrix_N_NyNy_[0](5,4) = (2.0*c2_*(c2_ + c3_) + c1_*(c2_ + 2.0*c3_))/(15.0*delta_);
            matrix_N_NyNy_[0](4,4) = (pow(c1_,2) + 6.0*c2_*c3_ + 2.0*c1_*(c2_ + c3_))/(15.0*delta_);

            matrix_N_NyNy_[0](1,5) = matrix_N_NyNy_[0](5,1);
            matrix_N_NyNy_[0](2,5) = matrix_N_NyNy_[0](5,2);
            matrix_N_NyNy_[0](3,5) = matrix_N_NyNy_[0](5,3);
            matrix_N_NyNy_[0](4,5) = matrix_N_NyNy_[0](5,4);
            matrix_N_NyNy_[0](5,5) = (2.0*(pow(c2_,2) + c2_*c3_ + pow(c3_,2)))/(15.0*delta_);
            matrix_N_NyNy_[0](6,5) = (2.0*c3_*(c2_ + c3_) + c1_*(2.0*c2_ + c3_))/(15.0*delta_);

            matrix_N_NyNy_[0](1,6) = matrix_N_NyNy_[0](6,1);
            matrix_N_NyNy_[0](2,6) = matrix_N_NyNy_[0](6,2);
            matrix_N_NyNy_[0](3,6) = matrix_N_NyNy_[0](6,3);
            matrix_N_NyNy_[0](4,6) = matrix_N_NyNy_[0](6,4);
            matrix_N_NyNy_[0](5,6) = matrix_N_NyNy_[0](6,5);
            matrix_N_NyNy_[0](6,6) = (2.0*(pow(c1_,2) + 2.0*c1_*c3_ + 3.0*pow(c3_,2)))/(15.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }

        matrix_N_NyNy_[1].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[1](1,1) = pow(c1_,2)/(12.0*delta_);
            matrix_N_NyNy_[1](2,1) = (c1_*c2_)/(12.0*delta_);
            matrix_N_NyNy_[1](3,1) = (c1_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[1](1,2) = matrix_N_NyNy_[1](2,1);
            matrix_N_NyNy_[1](2,2) = pow(c2_,2)/(12.0*delta_);
            matrix_N_NyNy_[1](3,2) = (c2_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[1](1,3) = matrix_N_NyNy_[1](3,1);
            matrix_N_NyNy_[1](2,3) = matrix_N_NyNy_[1](3,2);
            matrix_N_NyNy_[1](3,3) = pow(c3_,2)/(12.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[1](1,1) = pow(c1_,2)/(20.0*delta_);
            matrix_N_NyNy_[1](1,2) = -(c1_*c2_)/(30.0*delta_);
            matrix_N_NyNy_[1](1,3) = -(c1_*c3_)/(60.0*delta_);
            matrix_N_NyNy_[1](1,4) = (c1_*(-2.0*c1_ + 3.0*c2_))/(60.0*delta_);
            matrix_N_NyNy_[1](1,5) = -(c1_*(c2_ + 2.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[1](1,6) = -(c1_*(c1_ - 3.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[1](2,1) = matrix_N_NyNy_[1](1,2);
            matrix_N_NyNy_[1](2,2) = (3.0*pow(c2_,2))/(20.0*delta_);
            matrix_N_NyNy_[1](2,3) = -(c2_*c3_)/(30.0*delta_);
            matrix_N_NyNy_[1](2,4) = (c2_*(14.0*c1_ + 3.0*c2_))/(60.0*delta_);
            matrix_N_NyNy_[1](2,5) = (c2_*(3.0*c2_ + 14.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[1](2,6) = (c2_*(c1_ + c3_))/(20.0*delta_);

            matrix_N_NyNy_[1](3,1) = matrix_N_NyNy_[1](1,3);
            matrix_N_NyNy_[1](3,2) = matrix_N_NyNy_[1](2,3);
            matrix_N_NyNy_[1](3,3) = pow(c3_,2)/(20.0*delta_);
            matrix_N_NyNy_[1](3,4) = -((2.0*c1_ + c2_)*c3_)/(60.0*delta_);
            matrix_N_NyNy_[1](3,5) = ((3.0*c2_ - 2.0*c3_)*c3_)/(60.0*delta_);
            matrix_N_NyNy_[1](3,6) = ((3.0*c1_ - c3_)*c3_)/(60.0*delta_);

            matrix_N_NyNy_[1](4,1) = matrix_N_NyNy_[1](1,4);
            matrix_N_NyNy_[1](4,2) = matrix_N_NyNy_[1](2,4);
            matrix_N_NyNy_[1](4,3) = matrix_N_NyNy_[1](3,4);
            matrix_N_NyNy_[1](4,4) = (2.0*(3.0*pow(c1_,2) + 2.0*c1_*c2_ + pow(c2_,2)))/(15.0*delta_);
            matrix_N_NyNy_[1](4,5) = (2.0*c1_*c2_ + pow(c2_,2) + 6.0*c1_*c3_ + 2.0*c2_*c3_)/(15.0*delta_);
            matrix_N_NyNy_[1](4,6) = (2.0*pow(c1_,2) + c1_*c2_ + 2.0*c1_*c3_ + 2.0*c2_*c3_)/(15.0*delta_);

            matrix_N_NyNy_[1](5,1) = matrix_N_NyNy_[1](1,5);
            matrix_N_NyNy_[1](5,2) = matrix_N_NyNy_[1](2,5);
            matrix_N_NyNy_[1](5,3) = matrix_N_NyNy_[1](3,5);
            matrix_N_NyNy_[1](5,4) = matrix_N_NyNy_[1](4,5);
            matrix_N_NyNy_[1](5,5) = (2.0*(pow(c2_,2) + 2.0*c2_*c3_ + 3.0*pow(c3_,2)))/(15.0*delta_);
            matrix_N_NyNy_[1](5,6) = (2.0*c1_*(c2_ + c3_) + c3_*(c2_ + 2.0*c3_))/(15.0*delta_);

            matrix_N_NyNy_[1](6,1) = matrix_N_NyNy_[1](1,6);
            matrix_N_NyNy_[1](6,2) = matrix_N_NyNy_[1](2,6);
            matrix_N_NyNy_[1](6,3) = matrix_N_NyNy_[1](3,6);
            matrix_N_NyNy_[1](6,4) = matrix_N_NyNy_[1](4,6);
            matrix_N_NyNy_[1](6,5) = matrix_N_NyNy_[1](5,6);
            matrix_N_NyNy_[1](6,6) = (2.0*(pow(c1_,2) + c1_*c3_ + pow(c3_,2)))/(15.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }

        matrix_N_NyNy_[2].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[2](1,1) = pow(c1_,2)/(12.0*delta_);
            matrix_N_NyNy_[2](2,1) = (c1_*c2_)/(12.0*delta_);
            matrix_N_NyNy_[2](3,1) = (c1_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[2](1,2) = matrix_N_NyNy_[2](2,1);
            matrix_N_NyNy_[2](2,2) = pow(c2_,2)/(12.0*delta_);
            matrix_N_NyNy_[2](3,2) = (c2_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[2](1,3) = matrix_N_NyNy_[2](3,1);
            matrix_N_NyNy_[2](2,3) = matrix_N_NyNy_[2](3,2);
            matrix_N_NyNy_[2](3,3) = pow(c3_,2)/(12.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[2](1,1) = pow(c1_,2)/(20.0*delta_);
            matrix_N_NyNy_[2](1,2) = -(c1_*c2_)/(60.0*delta_);
            matrix_N_NyNy_[2](1,3) = -(c1_*c3_)/(30.0*delta_);
            matrix_N_NyNy_[2](1,4) = -(c1_*(c1_ - 3.0*c2_))/(60.0*delta_);
            matrix_N_NyNy_[2](1,5) = -(c1_*(2.0*c2_ + c3_))/(60.0*delta_);
            matrix_N_NyNy_[2](1,6) = (c1_*(-2.0*c1_ + 3.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[2](2,1) = matrix_N_NyNy_[2](1,2);
            matrix_N_NyNy_[2](2,2) = pow(c2_,2)/(20.0*delta_);
            matrix_N_NyNy_[2](2,3) = -(c2_*c3_)/(30.0*delta_);
            matrix_N_NyNy_[2](2,4) = ((3.0*c1_ - c2_)*c2_)/(60.0*delta_);
            matrix_N_NyNy_[2](2,5) = (c2_*(-2.0*c2_ + 3.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[2](2,6) = -(c2_*(2.0*c1_ + c3_))/(60.*delta_);

            matrix_N_NyNy_[2](3,1) = matrix_N_NyNy_[2](21,3);
            matrix_N_NyNy_[2](3,2) = matrix_N_NyNy_[2](2,3);
            matrix_N_NyNy_[2](3,3) = (3.0*pow(c3_,2))/(20.0*delta_);
            matrix_N_NyNy_[2](3,4) = ((c1_ + c2_)*c3_)/(20.0*delta_);
            matrix_N_NyNy_[2](3,5) = (c3_*(14.0*c2_ + 3.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[2](3,6) = (c3_*(14.0*c1_ + 3.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[2](4,1) = matrix_N_NyNy_[2](1,4);
            matrix_N_NyNy_[2](4,2) = matrix_N_NyNy_[2](2,4);
            matrix_N_NyNy_[2](4,3) = matrix_N_NyNy_[2](3,4);
            matrix_N_NyNy_[2](4,4) = (2.0*(pow(c1_,2) + c1_*c2_ + pow(c2_,2)))/(15.0*delta_);
            matrix_N_NyNy_[2](4,5) = (2.0*c1_*(c2_ + c3_) + c2_*(2.0*c2_ + c3_))/(15.0*delta_);
            matrix_N_NyNy_[2](4,6) = (2.0*pow(c1_,2) + 2.0*c1_*c2_ + c1_*c3_ + 2.0*c2_*c3_)/(15.0*delta_);

            matrix_N_NyNy_[2](5,1) = matrix_N_NyNy_[2](1,5);
            matrix_N_NyNy_[2](5,2) = matrix_N_NyNy_[2](2,5);
            matrix_N_NyNy_[2](5,3) = matrix_N_NyNy_[2](3,5);
            matrix_N_NyNy_[2](5,4) = matrix_N_NyNy_[2](4,5);
            matrix_N_NyNy_[2](5,5) = (2.0*(3.0*pow(c2_,2) + 2.0*c2_*c3_ + pow(c3_,2)))/(15.0*delta_);
            matrix_N_NyNy_[2](5,6) = (6.0*c1_*c2_ + 2.0*c1_*c3_ + 2.0*c2_*c3_ + pow(c3_,2))/(15.0*delta_);

            matrix_N_NyNy_[2](6,1) = matrix_N_NyNy_[2](1,6);
            matrix_N_NyNy_[2](6,2) = matrix_N_NyNy_[2](2,6);
            matrix_N_NyNy_[2](6,3) = matrix_N_NyNy_[2](3,6);
            matrix_N_NyNy_[2](6,4) = matrix_N_NyNy_[2](4,6);
            matrix_N_NyNy_[2](6,5) = matrix_N_NyNy_[2](5,6);
            matrix_N_NyNy_[2](6,6) = (2.0*(3.0*pow(c1_,2) + 2.0*c1_*c3_ + pow(c3_,2)))/(15.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }
    }
}


//************************************************************************************************//
/** @brief SolverTriangle::setUp_matrix_N_NN : Set up vector of matrices N_NN.
 * @author Felipe Valdes V. */
//************************************************************************************************//
void SolverTriangle::setUp_matrix_N_NN()
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    // Number of matrices depends on the polynomial order of the coefficients:
    cemINT num_matrices = 0;
    if (coefficient_order_ == 0)
        num_matrices = 1;
    else if (coefficient_order_ == 1)
        num_matrices = 3;

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;

    matrix_N_NN_.resize(num_matrices);
    if (coefficient_order_ == 0)
    {
         matrix_N_NN_[0].resize(num_basis_functions,num_basis_functions);

         if (basis_function_order_ == 1)
         {
             // Fill matrix column-wise (Matrix is simmetric):
             matrix_N_NN_[0](1,1) = delta_/6.0;
             matrix_N_NN_[0](2,1) = delta_/12.0;
             matrix_N_NN_[0](3,1) = delta_/12.0;

             matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
             matrix_N_NN_[0](2,2) = delta_/6.0;
             matrix_N_NN_[0](3,2) = delta_/12.0;

             matrix_N_NN_[0](1,3) = matrix_N_NN_[0](3,1);
             matrix_N_NN_[0](2,3) = matrix_N_NN_[0](3,2);
             matrix_N_NN_[0](3,3) = delta_/6.0;
         }
         else if (basis_function_order_ == 2)
         {
             // Fill matrix column-wise (Matrix is simmetric):
             matrix_N_NN_[0](1,1) = delta_/30.0;
             matrix_N_NN_[0](2,1) = -delta_/180.0;
             matrix_N_NN_[0](3,1) = -delta_/180.0;
             matrix_N_NN_[0](4,1) = 0.0;
             matrix_N_NN_[0](5,1) = -delta_/45.0;
             matrix_N_NN_[0](6,1) = 0.0;

             matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
             matrix_N_NN_[0](2,2) = delta_/30.0;
             matrix_N_NN_[0](3,2) = -delta_/180.0;
             matrix_N_NN_[0](4,2) = 0.0;
             matrix_N_NN_[0](5,2) = 0.0;
             matrix_N_NN_[0](6,2) = -delta_/45.0;

             matrix_N_NN_[0](1,3) = matrix_N_NN_[0](3,1);
             matrix_N_NN_[0](2,3) = matrix_N_NN_[0](3,2);
             matrix_N_NN_[0](3,3) = delta_/30.0;
             matrix_N_NN_[0](4,3) = -delta_/45.0;
             matrix_N_NN_[0](5,3) = 0.0;
             matrix_N_NN_[0](6,3) = 0.0;

             matrix_N_NN_[0](1,4) = matrix_N_NN_[0](4,1);
             matrix_N_NN_[0](2,4) = matrix_N_NN_[0](4,2);
             matrix_N_NN_[0](3,4) = matrix_N_NN_[0](4,3);
             matrix_N_NN_[0](4,4) = (8*delta_)/45.0;
             matrix_N_NN_[0](5,4) = (4*delta_)/45.0;
             matrix_N_NN_[0](6,4) = (4*delta_)/45.0;

             matrix_N_NN_[0](1,5) = matrix_N_NN_[0](5,1);
             matrix_N_NN_[0](2,5) = matrix_N_NN_[0](5,2);
             matrix_N_NN_[0](3,5) = matrix_N_NN_[0](5,3);
             matrix_N_NN_[0](4,5) = matrix_N_NN_[0](5,4);
             matrix_N_NN_[0](5,5) = (8*delta_)/45.0;
             matrix_N_NN_[0](6,5) = (4*delta_)/45.0;

             matrix_N_NN_[0](1,6) = matrix_N_NN_[0](6,1);
             matrix_N_NN_[0](2,6) = matrix_N_NN_[0](6,2);
             matrix_N_NN_[0](3,6) = matrix_N_NN_[0](6,3);
             matrix_N_NN_[0](4,6) = matrix_N_NN_[0](6,4);
             matrix_N_NN_[0](5,6) = matrix_N_NN_[0](6,5);
             matrix_N_NN_[0](6,6) = (8*delta_)/45.0;
         }
         else if (basis_function_order_ == 3)
         {
             // Fill matrix column-wise (Matrix is simmetric):
             throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
         }
    }
    else if (coefficient_order_ == 1)
    {
        matrix_N_NN_[0].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[0](1,1) = delta_/10.0;
            matrix_N_NN_[0](2,1) = delta_/30.0;
            matrix_N_NN_[0](3,1) = delta_/30.0;

            matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
            matrix_N_NN_[0](2,2) = delta_/30.0;
            matrix_N_NN_[0](3,2) = delta_/60.0;

            matrix_N_NN_[0](1,3) = matrix_N_NN_[0](3,1);
            matrix_N_NN_[0](2,3) = matrix_N_NN_[0](3,2);
            matrix_N_NN_[0](3,3) = delta_/30.;
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[0](1,1) = delta_/42.0;
            matrix_N_NN_[0](2,1) = -delta_/315.0;
            matrix_N_NN_[0](3,1) = -delta_/315.0;
            matrix_N_NN_[0](4,1) = delta_/105.0;
            matrix_N_NN_[0](5,1) = -delta_/315.0;
            matrix_N_NN_[0](6,1) = delta_/105.0;

            matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
            matrix_N_NN_[0](2,2) = delta_/210.0;
            matrix_N_NN_[0](3,2) = delta_/1260.0;
            matrix_N_NN_[0](4,2) = (-2.0*delta_)/315.0;
            matrix_N_NN_[0](5,2) = -delta_/315.0;
            matrix_N_NN_[0](6,2) = -delta_/105.0;

            matrix_N_NN_[0](1,3) = matrix_N_NN_[0](3,1);
            matrix_N_NN_[0](2,3) = matrix_N_NN_[0](3,2);
            matrix_N_NN_[0](3,3) = delta_/210.0;
            matrix_N_NN_[0](4,3) = -delta_/105.0;
            matrix_N_NN_[0](5,3) = -delta_/315.0;
            matrix_N_NN_[0](6,3) = (-2.0*delta_)/315.0;

            matrix_N_NN_[0](1,4) = matrix_N_NN_[0](4,1);
            matrix_N_NN_[0](2,4) = matrix_N_NN_[0](4,2);
            matrix_N_NN_[0](3,4) = matrix_N_NN_[0](4,3);
            matrix_N_NN_[0](4,4) = (8.0*delta_)/105.0;
            matrix_N_NN_[0](5,4) = (8.0*delta_)/315.0;
            matrix_N_NN_[0](6,4) = (4.0*delta_)/105.0;

            matrix_N_NN_[0](1,5) = matrix_N_NN_[0](5,1);
            matrix_N_NN_[0](2,5) = matrix_N_NN_[0](5,2);
            matrix_N_NN_[0](3,5) = matrix_N_NN_[0](5,3);
            matrix_N_NN_[0](4,5) = matrix_N_NN_[0](5,4);
            matrix_N_NN_[0](5,5) = (8.0*delta_)/315.0;
            matrix_N_NN_[0](6,5) = (8.0*delta_)/315.0;

            matrix_N_NN_[0](1,6) = matrix_N_NN_[0](6,1);
            matrix_N_NN_[0](2,6) = matrix_N_NN_[0](6,2);
            matrix_N_NN_[0](3,6) = matrix_N_NN_[0](6,3);
            matrix_N_NN_[0](4,6) = matrix_N_NN_[0](6,4);
            matrix_N_NN_[0](5,6) = matrix_N_NN_[0](6,5);
            matrix_N_NN_[0](6,6) = (8.0*delta_)/105.0;
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }

        matrix_N_NN_[1].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[1](1,1) = delta_/30.;
            matrix_N_NN_[1](2,1) = delta_/30.;
            matrix_N_NN_[1](3,1) = delta_/60.;

            matrix_N_NN_[1](1,2) = matrix_N_NN_[1](2,1);
            matrix_N_NN_[1](2,2) = delta_/10.;
            matrix_N_NN_[1](3,2) = delta_/30.;

            matrix_N_NN_[1](1,3) = matrix_N_NN_[1](3,1);
            matrix_N_NN_[1](2,3) = matrix_N_NN_[1](3,2);
            matrix_N_NN_[1](3,3) = delta_/30.;
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[1](1,1) = delta_/210.0;
            matrix_N_NN_[1](2,1) = -delta_/315.0;
            matrix_N_NN_[1](3,1) = delta_/1260.0;
            matrix_N_NN_[1](4,1) = (-2.0*delta_)/315.0;
            matrix_N_NN_[1](5,1) = -delta_/105.0;
            matrix_N_NN_[1](6,1) = -delta_/315.0;

            matrix_N_NN_[1](1,2) = matrix_N_NN_[1](2,1);
            matrix_N_NN_[1](2,2) = delta_/42.0;
            matrix_N_NN_[1](3,2) = -delta_/315.0;
            matrix_N_NN_[1](4,2) = delta_/105.0;
            matrix_N_NN_[1](5,2) = delta_/105.0;
            matrix_N_NN_[1](6,2) = -delta_/315.0;

            matrix_N_NN_[1](1,3) = matrix_N_NN_[1](3,1);
            matrix_N_NN_[1](2,3) = matrix_N_NN_[1](3,2);
            matrix_N_NN_[1](3,3) = delta_/210.0;
            matrix_N_NN_[1](4,3) = -delta_/105.0;
            matrix_N_NN_[1](5,3) = (-2.0*delta_)/315.0;
            matrix_N_NN_[1](6,3) = -delta_/315.0;

            matrix_N_NN_[1](1,4) = matrix_N_NN_[1](4,1);
            matrix_N_NN_[1](2,4) = matrix_N_NN_[1](4,2);
            matrix_N_NN_[1](3,4) = matrix_N_NN_[1](4,3);
            matrix_N_NN_[1](4,4) = (8.0*delta_)/105.0;
            matrix_N_NN_[1](5,4) = (4.0*delta_)/105.0;
            matrix_N_NN_[1](6,4) = (8.0*delta_)/315.0;

            matrix_N_NN_[1](1,5) = matrix_N_NN_[1](5,1);
            matrix_N_NN_[1](2,5) = matrix_N_NN_[1](5,2);
            matrix_N_NN_[1](3,5) = matrix_N_NN_[1](5,3);
            matrix_N_NN_[1](4,5) = matrix_N_NN_[1](5,4);
            matrix_N_NN_[1](5,5) = (8.0*delta_)/105.0;
            matrix_N_NN_[1](6,5) = (8.0*delta_)/315.0;

            matrix_N_NN_[1](1,6) = matrix_N_NN_[1](6,1);
            matrix_N_NN_[1](2,6) = matrix_N_NN_[1](6,2);
            matrix_N_NN_[1](3,6) = matrix_N_NN_[1](6,3);
            matrix_N_NN_[1](4,6) = matrix_N_NN_[1](6,4);
            matrix_N_NN_[1](5,6) = matrix_N_NN_[1](6,5);
            matrix_N_NN_[1](6,6) = (8.0*delta_)/315.0;
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }

        matrix_N_NN_[2].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[2](1,1) = delta_/30.;
            matrix_N_NN_[2](2,1) = delta_/60.;
            matrix_N_NN_[2](3,1) = delta_/30.;

            matrix_N_NN_[2](1,2) = matrix_N_NN_[2](2,1);
            matrix_N_NN_[2](2,2) = delta_/30.;
            matrix_N_NN_[2](3,2) = delta_/30.;

            matrix_N_NN_[2](1,3) = matrix_N_NN_[2](3,1);
            matrix_N_NN_[2](2,3) = matrix_N_NN_[2](3,2);
            matrix_N_NN_[2](3,3) = delta_/10.;

        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[2](1,1) = delta_/210.0;
            matrix_N_NN_[2](2,1) = delta_/1260.0;
            matrix_N_NN_[2](3,1) = -delta_/315.0;
            matrix_N_NN_[2](4,1) = -delta_/315.0;
            matrix_N_NN_[2](5,1) = -delta_/105.0;
            matrix_N_NN_[2](6,1) = (-2.0*delta_)/315.0;

            matrix_N_NN_[2](1,2) = matrix_N_NN_[2](2,1);
            matrix_N_NN_[2](2,2) = delta_/210.0;
            matrix_N_NN_[2](3,2) = -delta_/315.0;
            matrix_N_NN_[2](4,2) = -delta_/315.0;
            matrix_N_NN_[2](5,2) = (-2.0*delta_)/315.0;
            matrix_N_NN_[2](6,2) = -delta_/105.0;

            matrix_N_NN_[2](1,3) = matrix_N_NN_[2](3,1);
            matrix_N_NN_[2](2,3) = matrix_N_NN_[2](3,2);
            matrix_N_NN_[2](3,3) = delta_/42.0;
            matrix_N_NN_[2](4,3) = -delta_/315.0;
            matrix_N_NN_[2](5,3) = delta_/105.0;
            matrix_N_NN_[2](6,3) = delta_/105.0;

            matrix_N_NN_[2](1,4) = matrix_N_NN_[2](4,1);
            matrix_N_NN_[2](2,4) = matrix_N_NN_[2](4,2);
            matrix_N_NN_[2](3,4) = matrix_N_NN_[2](4,3);
            matrix_N_NN_[2](4,4) = (8.0*delta_)/315.0;
            matrix_N_NN_[2](5,4) = (8.0*delta_)/315.0;
            matrix_N_NN_[2](6,4) = (8.0*delta_)/315.0;

            matrix_N_NN_[2](1,5) = matrix_N_NN_[2](5,1);
            matrix_N_NN_[2](2,5) = matrix_N_NN_[2](5,2);
            matrix_N_NN_[2](3,5) = matrix_N_NN_[2](5,3);
            matrix_N_NN_[2](4,5) = matrix_N_NN_[2](5,4);
            matrix_N_NN_[2](5,5) = (8.0*delta_)/105.0;
            matrix_N_NN_[2](6,5) = (4.0*delta_)/105.0;

            matrix_N_NN_[2](1,6) = matrix_N_NN_[2](6,1);
            matrix_N_NN_[2](2,6) = matrix_N_NN_[2](6,2);
            matrix_N_NN_[2](3,6) = matrix_N_NN_[2](6,3);
            matrix_N_NN_[2](4,6) = matrix_N_NN_[2](6,4);
            matrix_N_NN_[2](5,6) = matrix_N_NN_[2](6,5);
            matrix_N_NN_[2](6,6) = (8.0*delta_)/105.0;
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            throw(Exception("FEATURE NOT INPLEMENTED","basis_order = 3 not implemented"));
        }
    }
}


//************************************************************************************************//
/** @brief SolverTriangle::setUpGeometry : Computes a few terms that are used in matrix setUp */
//************************************************************************************************//
void SolverTriangle::setUpGeometry()
{
    if (!geometry_is_Up_)
    {
        // Check that the element is a flat triangle: (anything else is not supported yet):
        if (element_ptr_->order() != 1)
            throw(Exception("FEATURE NOT IMPLEMENTED","Curvilinear triangles not supported"));

        // Check that the element is in the X-Y plane:
        z1_ = element_ptr_->node(0)->operator [](2);
        z2_ = element_ptr_->node(1)->operator [](2);
        z3_ = element_ptr_->node(2)->operator [](2);
        if (z1_-z2_ != 0.0 || z1_-z3_ != 0.0)
            throw(Exception("FEATURE NOT IMPLEMENTED","Triangle must be in the XY plane"));

        // Get nodes XY coordinates:
        x1_ = element_ptr_->node(0)->operator [](0);
        x2_ = element_ptr_->node(1)->operator [](0);
        x3_ = element_ptr_->node(2)->operator [](0);
        y1_ = element_ptr_->node(0)->operator [](1);
        y2_ = element_ptr_->node(1)->operator [](1);
        y3_ = element_ptr_->node(2)->operator [](1);

        a1_ = x2_*y3_ - y3_*x3_;
        a2_ = x3_*y1_ - y3_*x1_;
        a3_ = x1_*y2_ - y1_*x2_;
        b1_ = y2_ - y3_;
        b2_ = y3_ - y1_;
        b3_ = y1_ - y2_;
        c1_ = x3_ - x2_;
        c2_ = x1_ - x3_;
        c3_ = x2_ - x1_;

        delta_ = 0.5*(b1_*c2_ - b2_*c1_);

        geometry_is_Up_ = true;
    }
}
