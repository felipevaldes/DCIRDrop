#include "SolverElement.h"
#include "cemError.h"
#include "Quadrature/Quadrature.h"
#include "BasisFunctions/BasisFunctions.h"

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
void SolverTriangle::setUp_matrix_N_NxNx(cemBOOL force_numerical_integration)
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    // Number of matrices depends on the polynomial order of the coefficients:
    cemINT num_matrices = (coefficient_order_+1)*(coefficient_order_+2)/2;
    matrix_N_NxNx_.resize(num_matrices);

    if (coefficient_order_ <= 1 && basis_function_order_ <= 3 && !force_numerical_integration)
        Compute_N_NxNx_matrix_analytically();

    else
    {
        for (cemINT i=0; i<num_matrices; ++i)
            Compute_N_NxNx_matrix_numerically(i);
    }
}


//************************************************************************************************//
/** @brief SolverTriangle::setUp_matrix_N_NyNy : Set up vector of matrices N_NyNy.
 * @author Felipe Valdes V. */
//************************************************************************************************//
void SolverTriangle::setUp_matrix_N_NyNy(cemBOOL force_numerical_integration)
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    // Number of matrices depends on the polynomial order of the coefficients:
    cemINT num_matrices = (coefficient_order_+1)*(coefficient_order_+2)/2;
    matrix_N_NyNy_.resize(num_matrices);

    if (coefficient_order_ <= 1 && basis_function_order_ <= 3 && !force_numerical_integration)
        Compute_N_NyNy_matrix_analytically();

    else
    {
        for (cemINT i=0; i<num_matrices; ++i)
            Compute_N_NyNy_matrix_numerically(i);
    }
}


//************************************************************************************************//
/** @brief SolverTriangle::setUp_matrix_N_NN : Set up vector of matrices N_NN.
 * @author Felipe Valdes V. */
//************************************************************************************************//
void SolverTriangle::setUp_matrix_N_NN(cemBOOL force_numerical_integration)
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    // Number of matrices depends on the polynomial order of the coefficients:
    cemINT num_matrices = (coefficient_order_+1)*(coefficient_order_+2)/2;
    matrix_N_NN_.resize(num_matrices);

    if (coefficient_order_ <= 1 && basis_function_order_ <= 3 && !force_numerical_integration)
        Compute_N_NN_matrix_analytically();

    else
    {
        for (cemINT i=0; i<num_matrices; ++i)
            Compute_N_NN_matrix_numerically(i);
    }
}


//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NxNx_matrix_analytically : Computes all N_NxNx matrices using
 * analytic integration.
 *
 * Analytical integration is limited to basis functions of order not greater than 2, and
 * coefficient functions of order not greater than one (i.e. constant and linear coefficients) */
//************************************************************************************************//
void SolverTriangle::Compute_N_NxNx_matrix_analytically()
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;

    if (coefficient_order_ == 0)
    {
        matrix_N_NxNx_[0].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](0,0) = pow(b1_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](1,0) = (b1_*b2_)/(4.0*delta_);
            matrix_N_NxNx_[0](2,0) = (b1_*b3_)/(4.0*delta_);

            matrix_N_NxNx_[0](0,1) = matrix_N_NxNx_[0](1,0);
            matrix_N_NxNx_[0](1,1) = pow(b2_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](2,1) = (b2_*b3_)/(4.0*delta_);

            matrix_N_NxNx_[0](0,2) = matrix_N_NxNx_[0](2,0);
            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = pow(b3_,2)/(4.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](0,0) = pow(b1_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](1,0) = -(b1_*b2_)/(12.0*delta_);
            matrix_N_NxNx_[0](2,0) = -(b1_*b3_)/(12.0*delta_);
            matrix_N_NxNx_[0](3,0) = (b1_*b2_)/(3.0*delta_);
            matrix_N_NxNx_[0](4,0) = 0.0;
            matrix_N_NxNx_[0](5,0) = (b1_*b3_)/(3.0*delta_);

            matrix_N_NxNx_[0](0,1) = matrix_N_NxNx_[0](1,0);
            matrix_N_NxNx_[0](1,1) = pow(b2_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](2,1) = -(b2_*b3_)/(12.0*delta_);
            matrix_N_NxNx_[0](3,1) = (b1_*b2_)/(3.0*delta_);
            matrix_N_NxNx_[0](4,1) = (b2_*b3_)/(3.0*delta_);
            matrix_N_NxNx_[0](5,1) = 0.0;

            matrix_N_NxNx_[0](0,2) = matrix_N_NxNx_[0](2,0);
            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = pow(b3_,2)/(4.0*delta_);
            matrix_N_NxNx_[0](3,2) = 0.0;
            matrix_N_NxNx_[0](4,2) = (b2_*b3_)/(3.0*delta_);
            matrix_N_NxNx_[0](5,2) = (b1_*b3_)/(3.0*delta_);

            matrix_N_NxNx_[0](0,3) = matrix_N_NxNx_[0](3,0);
            matrix_N_NxNx_[0](1,3) = matrix_N_NxNx_[0](3,1);
            matrix_N_NxNx_[0](2,3) = matrix_N_NxNx_[0](3,2);
            matrix_N_NxNx_[0](3,3) = (2.0*pow(b1_,2))/(3.0*delta_) + (2.0*b1_*b2_)/(3.0*delta_) + (2.0*pow(b2_,2))/(3.0*delta_);
            matrix_N_NxNx_[0](4,3) = (b1_*b2_)/(3.0*delta_) + pow(b2_,2)/(3.0*delta_) + (2.0*b1_*b3_)/(3.0*delta_) + (b2_*b3_)/(3.0*delta_);
            matrix_N_NxNx_[0](5,3) = pow(b1_,2)/(3.0*delta_) + (b1_*b2_)/(3.0*delta_) + (b1_*b3_)/(3.0*delta_) + (2.0*b2_*b3_)/(3.0*delta_);

            matrix_N_NxNx_[0](0,4) = matrix_N_NxNx_[0](4,0);
            matrix_N_NxNx_[0](1,4) = matrix_N_NxNx_[0](4,1);
            matrix_N_NxNx_[0](2,4) = matrix_N_NxNx_[0](4,2);
            matrix_N_NxNx_[0](3,4) = matrix_N_NxNx_[0](4,3);
            matrix_N_NxNx_[0](4,4) = (2.0*pow(b2_,2))/(3.0*delta_) + (2.0*b2_*b3_)/(3.0*delta_) + (2.0*pow(b3_,2))/(3.0*delta_);
            matrix_N_NxNx_[0](5,4) = (2.0*b1_*b2_)/(3.0*delta_) + (b1_*b3_)/(3.0*delta_) + (b2_*b3_)/(3.0*delta_) + pow(b3_,2)/(3.0*delta_);

            matrix_N_NxNx_[0](0,5) = matrix_N_NxNx_[0](5,0);
            matrix_N_NxNx_[0](1,5) = matrix_N_NxNx_[0](5,1);
            matrix_N_NxNx_[0](2,5) = matrix_N_NxNx_[0](5,2);
            matrix_N_NxNx_[0](3,5) = matrix_N_NxNx_[0](5,3);
            matrix_N_NxNx_[0](4,5) = matrix_N_NxNx_[0](5,4);
            matrix_N_NxNx_[0](5,5) = (2.0*pow(b1_,2))/(3.0*delta_) + (2.0*b1_*b3_)/(3.0*delta_) + (2.0*pow(b3_,2))/(3.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](0,0) = (17*pow(b1_,2))/(80.*delta_);
            matrix_N_NxNx_[0](1,0) = (7*b1_*b2_)/(160.*delta_);
            matrix_N_NxNx_[0](2,0) = (7*b1_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](3,0) = (3*pow(b1_,2))/(160.*delta_) + (57*b1_*b2_)/(160.*delta_);
            matrix_N_NxNx_[0](4,0) = (3*pow(b1_,2))/(160.*delta_) - (3*b1_*b2_)/(20.*delta_);
            matrix_N_NxNx_[0](5,0) = (3*b1_*b2_)/(160.*delta_) + (3*b1_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](6,0) = (3*b1_*b2_)/(160.*delta_) + (3*b1_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](7,0) = (3*pow(b1_,2))/(160.*delta_) - (3*b1_*b3_)/(20.*delta_);
            matrix_N_NxNx_[0](8,0) = (3*pow(b1_,2))/(160.*delta_) + (57*b1_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](9,0) = (9*pow(b1_,2))/(160.*delta_) + (9*b1_*b2_)/(160.*delta_) +
                                     (9*b1_*b3_)/(160.*delta_);

            matrix_N_NxNx_[0](0,1) = matrix_N_NxNx_[0](1,0);
            matrix_N_NxNx_[0](1,1) = (17*pow(b2_,2))/(80.*delta_);
            matrix_N_NxNx_[0](2,1) = (7*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](3,1) = (-3*b1_*b2_)/(20.*delta_) + (3*pow(b2_,2))/(160.*delta_);
            matrix_N_NxNx_[0](4,1) = (57*b1_*b2_)/(160.*delta_) + (3*pow(b2_,2))/(160.*delta_);
            matrix_N_NxNx_[0](5,1) = (3*pow(b2_,2))/(160.*delta_) + (57*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](6,1) = (3*pow(b2_,2))/(160.*delta_) - (3*b2_*b3_)/(20.*delta_);
            matrix_N_NxNx_[0](7,1) = (3*b1_*b2_)/(160.*delta_) + (3*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](8,1) = (3*b1_*b2_)/(160.*delta_) + (3*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](9,1) = (9*b1_*b2_)/(160.*delta_) + (9*pow(b2_,2))/(160.*delta_) + (9*b2_*b3_)/(160.*delta_);

            matrix_N_NxNx_[0](0,2) = matrix_N_NxNx_[0](2,0);
            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = (17*pow(b3_,2))/(80.*delta_);
            matrix_N_NxNx_[0](3,2) = (3*b1_*b3_)/(160.*delta_) + (3*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](4,2) = (3*b1_*b3_)/(160.*delta_) + (3*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](5,2) = (-3*b2_*b3_)/(20.*delta_) + (3*pow(b3_,2))/(160.*delta_);
            matrix_N_NxNx_[0](6,2) = (57*b2_*b3_)/(160.*delta_) + (3*pow(b3_,2))/(160.*delta_);
            matrix_N_NxNx_[0](7,2) = (57*b1_*b3_)/(160.*delta_) + (3*pow(b3_,2))/(160.*delta_);
            matrix_N_NxNx_[0](8,2) = (-3*b1_*b3_)/(20.*delta_) + (3*pow(b3_,2))/(160.*delta_);
            matrix_N_NxNx_[0](9,2) = (9*b1_*b3_)/(160.*delta_) + (9*b2_*b3_)/(160.*delta_) + (9*pow(b3_,2))/(160.*delta_);

            matrix_N_NxNx_[0](0,3) = matrix_N_NxNx_[0](3,0);
            matrix_N_NxNx_[0](1,3) = matrix_N_NxNx_[0](3,1);
            matrix_N_NxNx_[0](2,3) = matrix_N_NxNx_[0](3,2);
            matrix_N_NxNx_[0](3,3) = (27*pow(b1_,2))/(32.*delta_) + (27*b1_*b2_)/(32.*delta_) + (27*pow(b2_,2))/(32.*delta_);
            matrix_N_NxNx_[0](4,3) = (-27*pow(b1_,2))/(160.*delta_) + (27*b1_*b2_)/(80.*delta_) - (27*pow(b2_,2))/(160.*delta_);
            matrix_N_NxNx_[0](5,3) = (-27*b1_*b2_)/(320.*delta_) - (27*pow(b2_,2))/(320.*delta_) - (27*b1_*b3_)/(160.*delta_) - (27*b2_*b3_)/(320.*delta_);
            matrix_N_NxNx_[0](6,3) = (-27*b1_*b2_)/(320.*delta_) - (27*pow(b2_,2))/(320.*delta_) - (27*b1_*b3_)/(160.*delta_) - (27*b2_*b3_)/(320.*delta_);
            matrix_N_NxNx_[0](7,3) = (-27*pow(b1_,2))/(320.*delta_) - (27*b1_*b2_)/(320.*delta_) - (27*b1_*b3_)/(320.*delta_) - (27*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](8,3) = (27*pow(b1_,2))/(64.*delta_) + (27*b1_*b2_)/(64.*delta_) + (27*b1_*b3_)/(64.*delta_) + (27*b2_*b3_)/(32.*delta_);
            matrix_N_NxNx_[0](9,3) = (81*b1_*b2_)/(160.*delta_) + (81*pow(b2_,2))/(160.*delta_) + (81*b1_*b3_)/(80.*delta_) + (81*b2_*b3_)/(160.*delta_);

            matrix_N_NxNx_[0](0,4) = matrix_N_NxNx_[0](4,0);
            matrix_N_NxNx_[0](1,4) = matrix_N_NxNx_[0](4,1);
            matrix_N_NxNx_[0](2,4) = matrix_N_NxNx_[0](4,2);
            matrix_N_NxNx_[0](3,4) = matrix_N_NxNx_[0](4,3);
            matrix_N_NxNx_[0](4,4) = (27*pow(b1_,2))/(32.*delta_) + (27*b1_*b2_)/(32.*delta_) + (27*pow(b2_,2))/(32.*delta_);
            matrix_N_NxNx_[0](5,4) = (27*b1_*b2_)/(64.*delta_) + (27*pow(b2_,2))/(64.*delta_) + (27*b1_*b3_)/(32.*delta_) + (27*b2_*b3_)/(64.*delta_);
            matrix_N_NxNx_[0](6,4) = (-27*b1_*b2_)/(320.*delta_) - (27*pow(b2_,2))/(320.*delta_) - (27*b1_*b3_)/(160.*delta_) - (27*b2_*b3_)/(320.*delta_);
            matrix_N_NxNx_[0](7,4) = (-27*pow(b1_,2))/(320.*delta_) - (27*b1_*b2_)/(320.*delta_) - (27*b1_*b3_)/(320.*delta_) - (27*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](8,4) = (-27*pow(b1_,2))/(320.*delta_) - (27*b1_*b2_)/(320.*delta_) - (27*b1_*b3_)/(320.*delta_) - (27*b2_*b3_)/(160.*delta_);
            matrix_N_NxNx_[0](9,4) = (81*pow(b1_,2))/(160.*delta_) + (81*b1_*b2_)/(160.*delta_) + (81*b1_*b3_)/(160.*delta_) + (81*b2_*b3_)/(80.*delta_);

            matrix_N_NxNx_[0](0,5) = matrix_N_NxNx_[0](5,0);
            matrix_N_NxNx_[0](1,5) = matrix_N_NxNx_[0](5,1);
            matrix_N_NxNx_[0](2,5) = matrix_N_NxNx_[0](5,2);
            matrix_N_NxNx_[0](3,5) = matrix_N_NxNx_[0](5,3);
            matrix_N_NxNx_[0](4,5) = matrix_N_NxNx_[0](5,4);
            matrix_N_NxNx_[0](5,5) = (27*pow(b2_,2))/(32.*delta_) + (27*b2_*b3_)/(32.*delta_) + (27*pow(b3_,2))/(32.*delta_);
            matrix_N_NxNx_[0](6,5) = (-27*pow(b2_,2))/(160.*delta_) + (27*b2_*b3_)/(80.*delta_) - (27*pow(b3_,2))/(160.*delta_);
            matrix_N_NxNx_[0](7,5) = (-27*b1_*b2_)/(160.*delta_) - (27*b1_*b3_)/(320.*delta_) - (27*b2_*b3_)/(320.*delta_) - (27*pow(b3_,2))/(320.*delta_);
            matrix_N_NxNx_[0](8,5) = (-27*b1_*b2_)/(160.*delta_) - (27*b1_*b3_)/(320.*delta_) - (27*b2_*b3_)/(320.*delta_) - (27*pow(b3_,2))/(320.*delta_);
            matrix_N_NxNx_[0](9,5) = (81*b1_*b2_)/(80.*delta_) + (81*b1_*b3_)/(160.*delta_) + (81*b2_*b3_)/(160.*delta_) + (81*pow(b3_,2))/(160.*delta_);

            matrix_N_NxNx_[0](0,6) = matrix_N_NxNx_[0](6,0);
            matrix_N_NxNx_[0](1,6) = matrix_N_NxNx_[0](6,1);
            matrix_N_NxNx_[0](2,6) = matrix_N_NxNx_[0](6,2);
            matrix_N_NxNx_[0](3,6) = matrix_N_NxNx_[0](6,3);
            matrix_N_NxNx_[0](4,6) = matrix_N_NxNx_[0](6,4);
            matrix_N_NxNx_[0](5,6) = matrix_N_NxNx_[0](6,5);
            matrix_N_NxNx_[0](6,6) = (27*pow(b2_,2))/(32.*delta_) + (27*b2_*b3_)/(32.*delta_) + (27*pow(b3_,2))/(32.*delta_);
            matrix_N_NxNx_[0](7,6) = (27*b1_*b2_)/(32.*delta_) + (27*b1_*b3_)/(64.*delta_) + (27*b2_*b3_)/(64.*delta_) + (27*pow(b3_,2))/(64.*delta_);
            matrix_N_NxNx_[0](8,6) = (-27*b1_*b2_)/(160.*delta_) - (27*b1_*b3_)/(320.*delta_) - (27*b2_*b3_)/(320.*delta_) - (27*pow(b3_,2))/(320.*delta_);
            matrix_N_NxNx_[0](9,6) = (81*b1_*b2_)/(160.*delta_) + (81*pow(b2_,2))/(160.*delta_) + (81*b1_*b3_)/(80.*delta_) + (81*b2_*b3_)/(160.*delta_);

            matrix_N_NxNx_[0](0,7) = matrix_N_NxNx_[0](7,0);
            matrix_N_NxNx_[0](1,7) = matrix_N_NxNx_[0](7,1);
            matrix_N_NxNx_[0](2,7) = matrix_N_NxNx_[0](7,2);
            matrix_N_NxNx_[0](3,7) = matrix_N_NxNx_[0](7,3);
            matrix_N_NxNx_[0](4,7) = matrix_N_NxNx_[0](7,4);
            matrix_N_NxNx_[0](5,7) = matrix_N_NxNx_[0](7,5);
            matrix_N_NxNx_[0](6,7) = matrix_N_NxNx_[0](7,6);
            matrix_N_NxNx_[0](7,7) = (27*pow(b1_,2))/(32.*delta_) + (27*b1_*b3_)/(32.*delta_) + (27*pow(b3_,2))/(32.*delta_);
            matrix_N_NxNx_[0](8,7) = (-27*pow(b1_,2))/(160.*delta_) + (27*b1_*b3_)/(80.*delta_) - (27*pow(b3_,2))/(160.*delta_);
            matrix_N_NxNx_[0](9,7) = (81*pow(b1_,2))/(160.*delta_) + (81*b1_*b2_)/(160.*delta_) + (81*b1_*b3_)/(160.*delta_) + (81*b2_*b3_)/(80.*delta_);

            matrix_N_NxNx_[0](0,8) = matrix_N_NxNx_[0](8,0);
            matrix_N_NxNx_[0](1,8) = matrix_N_NxNx_[0](8,1);
            matrix_N_NxNx_[0](2,8) = matrix_N_NxNx_[0](8,2);
            matrix_N_NxNx_[0](3,8) = matrix_N_NxNx_[0](8,3);
            matrix_N_NxNx_[0](4,8) = matrix_N_NxNx_[0](8,4);
            matrix_N_NxNx_[0](5,8) = matrix_N_NxNx_[0](8,5);
            matrix_N_NxNx_[0](6,8) = matrix_N_NxNx_[0](8,6);
            matrix_N_NxNx_[0](7,8) = matrix_N_NxNx_[0](8,7);
            matrix_N_NxNx_[0](8,8) = (27*pow(b1_,2))/(32.*delta_) + (27*b1_*b3_)/(32.*delta_) + (27*pow(b3_,2))/(32.*delta_);
            matrix_N_NxNx_[0](9,8) = (81*b1_*b2_)/(80.*delta_) + (81*b1_*b3_)/(160.*delta_) + (81*b2_*b3_)/(160.*delta_) + (81*pow(b3_,2))/(160.*delta_);

            matrix_N_NxNx_[0](0,9) = matrix_N_NxNx_[0](9,0);
            matrix_N_NxNx_[0](1,9) = matrix_N_NxNx_[0](9,1);
            matrix_N_NxNx_[0](2,9) = matrix_N_NxNx_[0](9,2);
            matrix_N_NxNx_[0](3,9) = matrix_N_NxNx_[0](9,3);
            matrix_N_NxNx_[0](4,9) = matrix_N_NxNx_[0](9,4);
            matrix_N_NxNx_[0](5,9) = matrix_N_NxNx_[0](9,5);
            matrix_N_NxNx_[0](6,9) = matrix_N_NxNx_[0](9,6);
            matrix_N_NxNx_[0](7,9) = matrix_N_NxNx_[0](9,7);
            matrix_N_NxNx_[0](8,9) = matrix_N_NxNx_[0](9,8);
            matrix_N_NxNx_[0](9,9) = (81*pow(b1_,2))/(40.*delta_) + (81*b1_*b2_)/(40.*delta_) + (81*pow(b2_,2))/(40.*delta_) + (81*b1_*b3_)/(40.*delta_) + (81*b2_*b3_)/(40.*delta_) + (81*pow(b3_,2))/(40.*delta_);
        }
        else
            throw(Exception("FEATURE NOT INPLEMENTED","basis_function_order >= 4 not implemented"));
    }
    else if (coefficient_order_ == 1)
    {
        matrix_N_NxNx_[0].resize(num_basis_functions,num_basis_functions);
        matrix_N_NxNx_[1].resize(num_basis_functions,num_basis_functions);
        matrix_N_NxNx_[2].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](0,0) = pow(b1_,2)/(12.0*delta_);
            matrix_N_NxNx_[0](1,0) = (b1_*b2_)/(12.0*delta_);
            matrix_N_NxNx_[0](2,0) = (b1_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[0](0,1) = matrix_N_NxNx_[0](1,0);
            matrix_N_NxNx_[0](1,1) = pow(b2_,2)/(12.0*delta_);
            matrix_N_NxNx_[0](2,1) = (b2_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[0](0,2) = matrix_N_NxNx_[0](2,0);
            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = pow(b3_,2)/(12.0*delta_);


            // Fill second matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[1](0,0) = pow(b1_,2)/(12.0*delta_);
            matrix_N_NxNx_[1](1,0) = (b1_*b2_)/(12.0*delta_);
            matrix_N_NxNx_[1](2,0) = (b1_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[1](0,1) = matrix_N_NxNx_[1](1,0);
            matrix_N_NxNx_[1](1,1) = pow(b2_,2)/(12.0*delta_);
            matrix_N_NxNx_[1](2,1) = (b2_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[1](0,2) = matrix_N_NxNx_[1](2,0);
            matrix_N_NxNx_[1](1,2) = matrix_N_NxNx_[1](2,1);
            matrix_N_NxNx_[1](2,2) = pow(b3_,2)/(12.0*delta_);


            // Fill third matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[2](0,0) = pow(b1_,2)/(12.0*delta_);
            matrix_N_NxNx_[2](1,0) = (b1_*b2_)/(12.0*delta_);
            matrix_N_NxNx_[2](2,0) = (b1_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[2](0,1) = matrix_N_NxNx_[2](1,0);
            matrix_N_NxNx_[2](1,1) = pow(b2_,2)/(12.0*delta_);
            matrix_N_NxNx_[2](2,1) = (b2_*b3_)/(12.0*delta_);

            matrix_N_NxNx_[2](0,2) = matrix_N_NxNx_[2](2,0);
            matrix_N_NxNx_[2](1,2) = matrix_N_NxNx_[2](2,1);
            matrix_N_NxNx_[2](2,2) = pow(b3_,2)/(12.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](0,0) = (3.0*pow(b1_,2))/(20.0*delta_);
            matrix_N_NxNx_[0](1,0) = -(b1_*b2_)/(30.0*delta_);
            matrix_N_NxNx_[0](2,0) = -(b1_*b3_)/(30.0*delta_);
            matrix_N_NxNx_[0](3,0) = (b1_*(3.0*b1_ + 14.0*b2_))/(60.0*delta_);
            matrix_N_NxNx_[0](4,0) = (b1_*(b2_ + b3_))/(20.0*delta_);
            matrix_N_NxNx_[0](5,0) = (b1_*(3.0*b1_ + 14.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[0](0,1) = matrix_N_NxNx_[0](1,0);
            matrix_N_NxNx_[0](1,1) = pow(b2_,2)/(20.0*delta_);
            matrix_N_NxNx_[0](2,1) = -(b2_*b3_)/(60.0*delta_);
            matrix_N_NxNx_[0](3,1) = ((3.0*b1_ - 2.0*b2_)*b2_)/(60.0*delta_);
            matrix_N_NxNx_[0](4,1) = -(b2_*(b2_ - 3.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[0](5,1) = -(b2_*(b1_ + 2.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[0](0,2) = matrix_N_NxNx_[0](2,0);
            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = pow(b3_,2)/(20.0*delta_);
            matrix_N_NxNx_[0](3,2) = -((b1_ + 2.0*b2_)*b3_)/(60.0*delta_);
            matrix_N_NxNx_[0](4,2) = ((3.0*b2_ - b3_)*b3_)/(60.0*delta_);
            matrix_N_NxNx_[0](5,2) = ((3.0*b1_ - 2.0*b3_)*b3_)/(60.0*delta_);

            matrix_N_NxNx_[0](0,3) = matrix_N_NxNx_[0](3,0);
            matrix_N_NxNx_[0](1,3) = matrix_N_NxNx_[0](3,1);
            matrix_N_NxNx_[0](2,3) = matrix_N_NxNx_[0](3,2);
            matrix_N_NxNx_[0](3,3) = (2.0*(pow(b1_,2) + 2.0*b1_*b2_ + 3.0*pow(b2_,2)))/(15.0*delta_);
            matrix_N_NxNx_[0](4,3) = (2.0*b2_*(b2_ + b3_) + b1_*(b2_ + 2.0*b3_))/(15.0*delta_);
            matrix_N_NxNx_[0](5,3) = (pow(b1_,2) + 6.0*b2_*b3_ + 2.0*b1_*(b2_ + b3_))/(15.0*delta_);

            matrix_N_NxNx_[0](0,4) = matrix_N_NxNx_[0](4,0);
            matrix_N_NxNx_[0](1,4) = matrix_N_NxNx_[0](4,1);
            matrix_N_NxNx_[0](2,4) = matrix_N_NxNx_[0](4,2);
            matrix_N_NxNx_[0](3,4) = matrix_N_NxNx_[0](4,3);
            matrix_N_NxNx_[0](4,4) = (2.0*(pow(b2_,2) + b2_*b3_ + pow(b3_,2)))/(15.0*delta_);
            matrix_N_NxNx_[0](5,4) = (2.0*b3_*(b2_ + b3_) + b1_*(2.0*b2_ + b3_))/(15.0*delta_);

            matrix_N_NxNx_[0](0,5) = matrix_N_NxNx_[0](5,0);
            matrix_N_NxNx_[0](1,5) = matrix_N_NxNx_[0](5,1);
            matrix_N_NxNx_[0](2,5) = matrix_N_NxNx_[0](5,2);
            matrix_N_NxNx_[0](3,5) = matrix_N_NxNx_[0](5,3);
            matrix_N_NxNx_[0](4,5) = matrix_N_NxNx_[0](5,4);
            matrix_N_NxNx_[0](5,5) = (2.0*(pow(b1_,2) + 2.0*b1_*b3_ + 3.0*pow(b3_,2)))/(15.0*delta_);


            // Fill second matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[1](0,0) = pow(b1_,2)/(20.0*delta_);
            matrix_N_NxNx_[1](1,0) = -(b1_*b2_)/(30.0*delta_);
            matrix_N_NxNx_[1](2,0) = -(b1_*b3_)/(60.0*delta_);
            matrix_N_NxNx_[1](3,0) = (b1_*(-2.0*b1_ + 3.0*b2_))/(60.0*delta_);
            matrix_N_NxNx_[1](4,0) = -(b1_*(b2_ + 2.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[1](5,0) = -(b1_*(b1_ - 3.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[1](0,1) = matrix_N_NxNx_[1](1,0);
            matrix_N_NxNx_[1](1,1) = (3.0*pow(b2_,2))/(20.0*delta_);
            matrix_N_NxNx_[1](2,1) = -(b2_*b3_)/(30.0*delta_);
            matrix_N_NxNx_[1](3,1) = (b2_*(14.0*b1_ + 3.0*b2_))/(60.0*delta_);
            matrix_N_NxNx_[1](4,1) = (b2_*(3.0*b2_ + 14.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[1](5,1) = (b2_*(b1_ + b3_))/(20.0*delta_);

            matrix_N_NxNx_[1](0,2) = matrix_N_NxNx_[1](2,0);
            matrix_N_NxNx_[1](1,2) = matrix_N_NxNx_[1](2,1);
            matrix_N_NxNx_[1](2,2) = pow(b3_,2)/(20.0*delta_);
            matrix_N_NxNx_[1](3,2) = -((2.0*b1_ + b2_)*b3_)/(60.0*delta_);
            matrix_N_NxNx_[1](4,2) = ((3.0*b2_ - 2.0*b3_)*b3_)/(60.0*delta_);
            matrix_N_NxNx_[1](5,2) = ((3.0*b1_ - b3_)*b3_)/(60.0*delta_);

            matrix_N_NxNx_[1](0,3) = matrix_N_NxNx_[1](3,0);
            matrix_N_NxNx_[1](1,3) = matrix_N_NxNx_[1](3,1);
            matrix_N_NxNx_[1](2,3) = matrix_N_NxNx_[1](3,2);
            matrix_N_NxNx_[1](3,3) = (2.0*(3.0*pow(b1_,2) + 2.0*b1_*b2_ + pow(b2_,2)))/(15.0*delta_);
            matrix_N_NxNx_[1](4,3) = (2.0*b1_*b2_ + pow(b2_,2) + 6.0*b1_*b3_ + 2.0*b2_*b3_)/(15.0*delta_);
            matrix_N_NxNx_[1](5,3) = (2.0*pow(b1_,2) + b1_*b2_ + 2.0*b1_*b3_ + 2.0*b2_*b3_)/(15.0*delta_);

            matrix_N_NxNx_[1](0,4) = matrix_N_NxNx_[1](4,0);
            matrix_N_NxNx_[1](1,4) = matrix_N_NxNx_[1](4,1);
            matrix_N_NxNx_[1](2,4) = matrix_N_NxNx_[1](4,2);
            matrix_N_NxNx_[1](3,4) = matrix_N_NxNx_[1](4,3);
            matrix_N_NxNx_[1](4,4) = (2.0*(pow(b2_,2) + 2.0*b2_*b3_ + 3.0*pow(b3_,2)))/(15.0*delta_);
            matrix_N_NxNx_[1](5,4) = (2.0*b1_*(b2_ + b3_) + b3_*(b2_ + 2.0*b3_))/(15.0*delta_);

            matrix_N_NxNx_[1](0,5) = matrix_N_NxNx_[1](5,0);
            matrix_N_NxNx_[1](1,5) = matrix_N_NxNx_[1](5,1);
            matrix_N_NxNx_[1](2,5) = matrix_N_NxNx_[1](5,2);
            matrix_N_NxNx_[1](3,5) = matrix_N_NxNx_[1](5,3);
            matrix_N_NxNx_[1](4,5) = matrix_N_NxNx_[1](5,4);
            matrix_N_NxNx_[1](5,5) = (2.0*(pow(b1_,2) + b1_*b3_ + pow(b3_,2)))/(15.0*delta_);


            // Fill third matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[2](0,0) = pow(b1_,2)/(20.0*delta_);
            matrix_N_NxNx_[2](1,0) = -(b1_*b2_)/(60.0*delta_);
            matrix_N_NxNx_[2](2,0) = -(b1_*b3_)/(30.0*delta_);
            matrix_N_NxNx_[2](3,0) = -(b1_*(b1_ - 3.0*b2_))/(60.0*delta_);
            matrix_N_NxNx_[2](4,0) = -(b1_*(2.0*b2_ + b3_))/(60.0*delta_);
            matrix_N_NxNx_[2](5,0) = (b1_*(-2.0*b1_ + 3.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[2](0,1) = matrix_N_NxNx_[2](1,0);
            matrix_N_NxNx_[2](1,1) = pow(b2_,2)/(20.0*delta_);
            matrix_N_NxNx_[2](2,1) = -(b2_*b3_)/(30.0*delta_);
            matrix_N_NxNx_[2](3,1) = ((3.0*b1_ - b2_)*b2_)/(60.0*delta_);
            matrix_N_NxNx_[2](4,1) = (b2_*(-2.0*b2_ + 3.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[2](5,1) = -(b2_*(2.0*b1_ + b3_))/(60.0*delta_);

            matrix_N_NxNx_[2](0,2) = matrix_N_NxNx_[2](2,0);
            matrix_N_NxNx_[2](1,2) = matrix_N_NxNx_[2](2,1);
            matrix_N_NxNx_[2](2,2) = (3.0*pow(b3_,2))/(20.0*delta_);
            matrix_N_NxNx_[2](3,2) = ((b1_ + b2_)*b3_)/(20.0*delta_);
            matrix_N_NxNx_[2](4,2) = (b3_*(14.0*b2_ + 3.0*b3_))/(60.0*delta_);
            matrix_N_NxNx_[2](5,2) = (b3_*(14.0*b1_ + 3.0*b3_))/(60.0*delta_);

            matrix_N_NxNx_[2](0,3) = matrix_N_NxNx_[2](3,0);
            matrix_N_NxNx_[2](1,3) = matrix_N_NxNx_[2](3,1);
            matrix_N_NxNx_[2](2,3) = matrix_N_NxNx_[2](3,2);
            matrix_N_NxNx_[2](3,3) = (2.0*(pow(b1_,2) + b1_*b2_ + pow(b2_,2)))/(15.0*delta_);
            matrix_N_NxNx_[2](4,3) = (2.0*b1_*(b2_ + b3_) + b2_*(2.0*b2_ + b3_))/(15.0*delta_);
            matrix_N_NxNx_[2](5,3) = (2.0*pow(b1_,2) + 2.0*b1_*b2_ + b1_*b3_ + 2.0*b2_*b3_)/(15.0*delta_);

            matrix_N_NxNx_[2](0,4) = matrix_N_NxNx_[2](4,0);
            matrix_N_NxNx_[2](1,4) = matrix_N_NxNx_[2](4,1);
            matrix_N_NxNx_[2](2,4) = matrix_N_NxNx_[2](4,2);
            matrix_N_NxNx_[2](3,4) = matrix_N_NxNx_[2](4,3);
            matrix_N_NxNx_[2](4,4) = (2.0*(3.0*pow(b2_,2) + 2.0*b2_*b3_ + pow(b3_,2)))/(15.0*delta_);
            matrix_N_NxNx_[2](5,4) = (6.0*b1_*b2_ + 2.0*b1_*b3_ + 2.0*b2_*b3_ + pow(b3_,2))/(15.0*delta_);

            matrix_N_NxNx_[2](0,5) = matrix_N_NxNx_[2](5,0);
            matrix_N_NxNx_[2](1,5) = matrix_N_NxNx_[2](5,1);
            matrix_N_NxNx_[2](2,5) = matrix_N_NxNx_[2](5,2);
            matrix_N_NxNx_[2](3,5) = matrix_N_NxNx_[2](5,3);
            matrix_N_NxNx_[2](4,5) = matrix_N_NxNx_[2](5,4);
            matrix_N_NxNx_[2](5,5) = (2.0*(3.0*pow(b1_,2) + 2.0*b1_*b3_ + pow(b3_,2)))/(15.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[0](0,0) = (257*pow(b1_,2))/(1680.*delta_);
            matrix_N_NxNx_[0](1,0) = (2*b1_*b2_)/(105.*delta_);
            matrix_N_NxNx_[0](2,0) = (2*b1_*b3_)/(105.*delta_);
            matrix_N_NxNx_[0](3,0) = (3*b1_*(53*b1_ + 220*b2_))/(2240.*delta_);
            matrix_N_NxNx_[0](4,0) = (-3*b1_*(13*b1_ + 80*b2_))/(2240.*delta_);
            matrix_N_NxNx_[0](5,0) = (-39*b1_*(b2_ + b3_))/(2240.*delta_);
            matrix_N_NxNx_[0](6,0) = (-39*b1_*(b2_ + b3_))/(2240.*delta_);
            matrix_N_NxNx_[0](7,0) = (-3*b1_*(13*b1_ + 80*b3_))/(2240.*delta_);
            matrix_N_NxNx_[0](8,0) = (3*b1_*(53*b1_ + 220*b3_))/(2240.*delta_);
            matrix_N_NxNx_[0](9,0) = (-9*b1_*(b1_ - 10*(b2_ + b3_)))/(1120.*delta_);

            matrix_N_NxNx_[0](0,1) = matrix_N_NxNx_[0](1,0);
            matrix_N_NxNx_[0](1,1) = (5*pow(b2_,2))/(168.*delta_);
            matrix_N_NxNx_[0](2,1) = (19*b2_*b3_)/(3360.*delta_);
            matrix_N_NxNx_[0](3,1) = (-57*b1_*b2_ + 66*pow(b2_,2))/(2240.*delta_);
            matrix_N_NxNx_[0](4,1) = (3*(23*b1_ - 26*b2_)*b2_)/(2240.*delta_);
            matrix_N_NxNx_[0](5,1) = (-39*pow(b2_,2) + 69*b2_*b3_)/(2240.*delta_);
            matrix_N_NxNx_[0](6,1) = (3*b2_*(5*b2_ - 13*b3_))/(2240.*delta_);
            matrix_N_NxNx_[0](7,1) = (3*b2_*(b1_ + 2*b3_))/(448.*delta_);
            matrix_N_NxNx_[0](8,1) = (3*b2_*(17*b1_ + 22*b3_))/(2240.*delta_);
            matrix_N_NxNx_[0](9,1) = (-9*b2_*(b1_  - 4*b2_ + 2*b3_))/(1120.*delta_);

            matrix_N_NxNx_[0](0,2) = matrix_N_NxNx_[0](2,0);
            matrix_N_NxNx_[0](1,2) = matrix_N_NxNx_[0](2,1);
            matrix_N_NxNx_[0](2,2) = (5*pow(b3_,2))/(168.*delta_);
            matrix_N_NxNx_[0](3,2) = (3*(17*b1_ + 22*b2_)*b3_)/(2240.*delta_);
            matrix_N_NxNx_[0](4,2) = (3*(b1_ + 2*b2_)*b3_)/(448.*delta_);
            matrix_N_NxNx_[0](5,2) = (3*b3_*(-13*b2_ + 5*b3_))/(2240.*delta_);
            matrix_N_NxNx_[0](6,2) = (3*(23*b2_ - 13*b3_)*b3_)/(2240.*delta_);
            matrix_N_NxNx_[0](7,2) = (3*(23*b1_ - 26*b3_)*b3_)/(2240.*delta_);
            matrix_N_NxNx_[0](8,2) = (-57*b1_*b3_ + 66*pow(b3_,2))/(2240.*delta_);
            matrix_N_NxNx_[0](9,2) = (-9*(b1_ + 2*b2_ - 4*b3_)*b3_)/(1120.*delta_);

            matrix_N_NxNx_[0](0,3) = matrix_N_NxNx_[0](3,0);
            matrix_N_NxNx_[0](1,3) = matrix_N_NxNx_[0](3,1);
            matrix_N_NxNx_[0](2,3) = matrix_N_NxNx_[0](3,2);
            matrix_N_NxNx_[0](3,3) = (27*(15*pow(b1_,2) + 23*b1_*b2_ + 27*pow(b2_,2)))/(1120.*delta_);
            matrix_N_NxNx_[0](4,3) = (27*(pow(b1_,2) + 13*b1_*b2_ - 12*pow(b2_,2)))/(2240.*delta_);
            matrix_N_NxNx_[0](5,3) = (27*(-3*b2_*(b2_ + b3_) + b1_*(3*b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](6,3) = (-27*(3*b2_*(b2_ + b3_) + 2*b1_*(b2_ + 2*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](7,3) = (-27*(2*pow(b1_,2) + 12*b2_*b3_ + 3*b1_*(b2_ + 2*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](8,3) = (27*(15*pow(b1_,2) + 54*b2_*b3_ + 23*b1_*(b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](9,3) = (27*(5*pow(b1_,2) + 15*b2_*(b2_ + b3_) + b1_*(13*b2_ + 22*b3_)))/(1120.*delta_);

            matrix_N_NxNx_[0](0,4) = matrix_N_NxNx_[0](4,0);
            matrix_N_NxNx_[0](1,4) = matrix_N_NxNx_[0](4,1);
            matrix_N_NxNx_[0](2,4) = matrix_N_NxNx_[0](4,2);
            matrix_N_NxNx_[0](3,4) = matrix_N_NxNx_[0](4,3);
            matrix_N_NxNx_[0](4,4) = (27*(4*pow(b1_,2) + 8*b1_*b2_ + 15*pow(b2_,2)))/(1120.*delta_);
            matrix_N_NxNx_[0](5,4) = (27*(2*b1_*(b2_ + 2*b3_) + b2_*(5*b2_ + 4*b3_)))/(1120.*delta_);
            matrix_N_NxNx_[0](6,4) = (-27*(2*b2_*(b2_ + 2*b3_) + b1_*(b2_ + 3*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](7,4) = (-27*(pow(b1_,2) + 6*b2_*b3_ + 2*b1_*(b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](8,4) = (-27*(2*pow(b1_,2) + 12*b2_*b3_ + 3*b1_*(2*b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](9,4) = (27*(2*pow(b1_,2) - 3*b2_*(b2_ - 5*b3_) + 4*b1_*(b2_ + b3_)))/(1120.*delta_);

            matrix_N_NxNx_[0](0,5) = matrix_N_NxNx_[0](5,0);
            matrix_N_NxNx_[0](1,5) = matrix_N_NxNx_[0](5,1);
            matrix_N_NxNx_[0](2,5) = matrix_N_NxNx_[0](5,2);
            matrix_N_NxNx_[0](3,5) = matrix_N_NxNx_[0](5,3);
            matrix_N_NxNx_[0](4,5) = matrix_N_NxNx_[0](5,4);
            matrix_N_NxNx_[0](5,5) = (27*(5*pow(b2_,2) + 4*b2_*b3_ + 4*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[0](6,5) = (-27*(3*pow(b2_,2) - 2*b2_*b3_ + 3*pow(b3_,2)))/(2240.*delta_);
            matrix_N_NxNx_[0](7,5) = (-27*(2*b3_*(2*b2_ + b3_) + b1_*(3*b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](8,5) = (-27*(3*b3_*(b2_ + b3_) + 2*b1_*(2*b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](9,5) = (27*(5*b1_*b2_ - 2*pow(b2_,2) + 2*b1_*b3_ + 4*b2_*b3_ + 4*pow(b3_,2)))/(1120.*delta_);

            matrix_N_NxNx_[0](0,6) = matrix_N_NxNx_[0](6,0);
            matrix_N_NxNx_[0](1,6) = matrix_N_NxNx_[0](6,1);
            matrix_N_NxNx_[0](2,6) = matrix_N_NxNx_[0](6,2);
            matrix_N_NxNx_[0](3,6) = matrix_N_NxNx_[0](6,3);
            matrix_N_NxNx_[0](4,6) = matrix_N_NxNx_[0](6,4);
            matrix_N_NxNx_[0](5,6) = matrix_N_NxNx_[0](6,5);
            matrix_N_NxNx_[0](6,6) = (27*(4*pow(b2_,2) + 4*b2_*b3_ + 5*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[0](7,6) = (27*(2*b1_*(2*b2_ + b3_) + b3_*(4*b2_ + 5*b3_)))/(1120.*delta_);
            matrix_N_NxNx_[0](8,6) = (27*(-3*b3_*(b2_ + b3_) + b1_*(b2_ + 3*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[0](9,6) = (27*(2*b1_*b2_ + 4*pow(b2_,2) + 5*b1_*b3_ + 4*b2_*b3_ - 2*pow(b3_,2)))/(1120.*delta_);

            matrix_N_NxNx_[0](0,7) = matrix_N_NxNx_[0](7,0);
            matrix_N_NxNx_[0](1,7) = matrix_N_NxNx_[0](7,1);
            matrix_N_NxNx_[0](2,7) = matrix_N_NxNx_[0](7,2);
            matrix_N_NxNx_[0](3,7) = matrix_N_NxNx_[0](7,3);
            matrix_N_NxNx_[0](4,7) = matrix_N_NxNx_[0](7,4);
            matrix_N_NxNx_[0](5,7) = matrix_N_NxNx_[0](7,5);
            matrix_N_NxNx_[0](6,7) = matrix_N_NxNx_[0](7,6);
            matrix_N_NxNx_[0](7,7) = (27*(4*pow(b1_,2) + 8*b1_*b3_ + 15*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[0](8,7) = (27*(pow(b1_,2) + 13*b1_*b3_ - 12*pow(b3_,2)))/(2240.*delta_);
            matrix_N_NxNx_[0](9,7) = (27*(2*pow(b1_,2) + 3*(5*b2_ - b3_)*b3_ + 4*b1_*(b2_ + b3_)))/(1120.*delta_);

            matrix_N_NxNx_[0](0,8) = matrix_N_NxNx_[0](8,0);
            matrix_N_NxNx_[0](1,8) = matrix_N_NxNx_[0](8,1);
            matrix_N_NxNx_[0](2,8) = matrix_N_NxNx_[0](8,2);
            matrix_N_NxNx_[0](3,8) = matrix_N_NxNx_[0](8,3);
            matrix_N_NxNx_[0](4,8) = matrix_N_NxNx_[0](8,4);
            matrix_N_NxNx_[0](5,8) = matrix_N_NxNx_[0](8,5);
            matrix_N_NxNx_[0](6,8) = matrix_N_NxNx_[0](8,6);
            matrix_N_NxNx_[0](7,8) = matrix_N_NxNx_[0](8,7);
            matrix_N_NxNx_[0](8,8) = (27*(15*pow(b1_,2) + 23*b1_*b3_ + 27*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[0](9,8) = (27*(5*pow(b1_,2) + 15*b3_*(b2_ + b3_) + b1_*(22*b2_ + 13*b3_)))/(1120.*delta_);

            matrix_N_NxNx_[0](0,9) = matrix_N_NxNx_[0](9,0);
            matrix_N_NxNx_[0](1,9) = matrix_N_NxNx_[0](9,1);
            matrix_N_NxNx_[0](2,9) = matrix_N_NxNx_[0](9,2);
            matrix_N_NxNx_[0](3,9) = matrix_N_NxNx_[0](9,3);
            matrix_N_NxNx_[0](4,9) = matrix_N_NxNx_[0](9,4);
            matrix_N_NxNx_[0](5,9) = matrix_N_NxNx_[0](9,5);
            matrix_N_NxNx_[0](6,9) = matrix_N_NxNx_[0](9,6);
            matrix_N_NxNx_[0](7,9) = matrix_N_NxNx_[0](9,7);
            matrix_N_NxNx_[0](8,9) = matrix_N_NxNx_[0](9,8);
            matrix_N_NxNx_[0](9,9) = (81*(pow(b1_,2) + 2*b1_*(b2_ + b3_) + 3*(pow(b2_,2) + b2_*b3_ + pow(b3_,2))))/(280.*delta_);

            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[1](0,0) = (5*pow(b1_,2))/(168.*delta_);
            matrix_N_NxNx_[1](1,0) = (2*b1_*b2_)/(105.*delta_);
            matrix_N_NxNx_[1](2,0) = (19*b1_*b3_)/(3360.*delta_);
            matrix_N_NxNx_[1](3,0) = (-78*pow(b1_,2) + 69*b1_*b2_)/(2240.*delta_);
            matrix_N_NxNx_[1](4,0) = (3*b1_*(22*b1_ - 19*b2_))/(2240.*delta_);
            matrix_N_NxNx_[1](5,0) = (3*b1_*(17*b2_ + 22*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](6,0) = (3*b1_*(b2_ + 2*b3_))/(448.*delta_);
            matrix_N_NxNx_[1](7,0) = (3*b1_*(5*b1_ - 13*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](8,0) = (-39*pow(b1_,2) + 69*b1_*b3_)/(2240.*delta_);
            matrix_N_NxNx_[1](9,0) = (9*b1_*(4*b1_ - b2_ - 2*b3_))/(1120.*delta_);

            matrix_N_NxNx_[1](0,1) = matrix_N_NxNx_[1](1,0);
            matrix_N_NxNx_[1](1,1) = (257*pow(b2_,2))/(1680.*delta_);
            matrix_N_NxNx_[1](2,1) = (2*b2_*b3_)/(105.*delta_);
            matrix_N_NxNx_[1](3,1) = (-3*b2_*(80*b1_ + 13*b2_))/(2240.*delta_);
            matrix_N_NxNx_[1](4,1) = (3*b2_*(220*b1_ + 53*b2_))/(2240.*delta_);
            matrix_N_NxNx_[1](5,1) = (3*b2_*(53*b2_ + 220*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](6,1) = (-3*b2_*(13*b2_ + 80*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](7,1) = (-39*b2_*(b1_ + b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](8,1) = (-39*b2_*(b1_ + b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](9,1) = (-9*b2_*(-10*b1_ + b2_ - 10*b3_))/(1120.*delta_);

            matrix_N_NxNx_[1](0,2) = matrix_N_NxNx_[1](2,0);
            matrix_N_NxNx_[1](1,2) = matrix_N_NxNx_[1](2,1);
            matrix_N_NxNx_[1](2,2) = (5*pow(b3_,2))/(168.*delta_);
            matrix_N_NxNx_[1](3,2) = (3*(2*b1_ + b2_)*b3_)/(448.*delta_);
            matrix_N_NxNx_[1](4,2) = (3*(22*b1_ + 17*b2_)*b3_)/(2240.*delta_);
            matrix_N_NxNx_[1](5,2) = (-57*b2_*b3_ + 66*pow(b3_,2))/(2240.*delta_);
            matrix_N_NxNx_[1](6,2) = (3*(23*b2_ - 26*b3_)*b3_)/(2240.*delta_);
            matrix_N_NxNx_[1](7,2) = (3*(23*b1_ - 13*b3_)*b3_)/(2240.*delta_);
            matrix_N_NxNx_[1](8,2) = (3*b3_*(-13*b1_ + 5*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](9,2) = (-9*(2*b1_ + b2_ - 4*b3_)*b3_)/(1120.*delta_);

            matrix_N_NxNx_[1](0,3) = matrix_N_NxNx_[1](3,0);
            matrix_N_NxNx_[1](1,3) = matrix_N_NxNx_[1](3,1);
            matrix_N_NxNx_[1](2,3) = matrix_N_NxNx_[1](3,2);
            matrix_N_NxNx_[1](3,3) = (27*(15*pow(b1_,2) + 8*b1_*b2_ + 4*pow(b2_,2)))/(1120.*delta_);
            matrix_N_NxNx_[1](4,3) = (27*(-12*pow(b1_,2) + 13*b1_*b2_ + pow(b2_,2)))/(2240.*delta_);
            matrix_N_NxNx_[1](5,3) = (-27*(6*b1_*(b2_ + 2*b3_) + b2_*(2*b2_ + 3*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[1](6,3) = (-27*(b2_*(b2_ + 2*b3_) + 2*b1_*(b2_ + 3*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[1](7,3) = (-27*(2*pow(b1_,2) + 3*b2_*b3_ + b1_*(b2_ + 4*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[1](8,3) = (27*(5*pow(b1_,2) + 4*b2_*b3_ + 2*b1_*(b2_ + 2*b3_)))/(1120.*delta_);
            matrix_N_NxNx_[1](9,3) = (-27*(3*pow(b1_,2) - 2*b2_*(b2_ + 2*b3_) - b1_*(4*b2_ + 15*b3_)))/(1120.*delta_);

            matrix_N_NxNx_[1](0,4) = matrix_N_NxNx_[1](4,0);
            matrix_N_NxNx_[1](1,4) = matrix_N_NxNx_[1](4,1);
            matrix_N_NxNx_[1](2,4) = matrix_N_NxNx_[1](4,2);
            matrix_N_NxNx_[1](3,4) = matrix_N_NxNx_[1](4,3);
            matrix_N_NxNx_[1](4,4) = (27*(27*pow(b1_,2) + 23*b1_*b2_ + 15*pow(b2_,2)))/(1120.*delta_);
            matrix_N_NxNx_[1](5,4) = (27*(23*b1_*b2_ + 15*pow(b2_,2) + 54*b1_*b3_ + 23*b2_*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](6,4) = (-27*(2*b2_*(b2_ + 3*b3_) + 3*b1_*(b2_ + 4*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[1](7,4) = (-27*(3*pow(b1_,2) + 2*b1_*b2_ + 3*b1_*b3_ + 4*b2_*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](8,4) = (-27*(3*pow(b1_,2) - 3*b1_*b2_ + 3*b1_*b3_ - b2_*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](9,4) = (27*(15*pow(b1_,2) + 13*b1_*b2_ + 5*pow(b2_,2) + 15*b1_*b3_ + 22*b2_*b3_))/(1120.*delta_);

            matrix_N_NxNx_[1](0,5) = matrix_N_NxNx_[1](5,0);
            matrix_N_NxNx_[1](1,5) = matrix_N_NxNx_[1](5,1);
            matrix_N_NxNx_[1](2,5) = matrix_N_NxNx_[1](5,2);
            matrix_N_NxNx_[1](3,5) = matrix_N_NxNx_[1](5,3);
            matrix_N_NxNx_[1](4,5) = matrix_N_NxNx_[1](5,4);
            matrix_N_NxNx_[1](5,5) = (27*(15*pow(b2_,2) + 23*b2_*b3_ + 27*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[1](6,5) = (27*(pow(b2_,2) + 13*b2_*b3_ - 12*pow(b3_,2)))/(2240.*delta_);
            matrix_N_NxNx_[1](7,5) = (27*(b1_*(b2_ - 3*b3_) + 3*(b2_ - b3_)*b3_))/(2240.*delta_);
            matrix_N_NxNx_[1](8,5) = (-27*(4*b1_*b2_ + 3*b1_*b3_ + 2*b2_*b3_ + 3*pow(b3_,2)))/(2240.*delta_);
            matrix_N_NxNx_[1](9,5) = (27*(22*b1_*b2_ + 5*pow(b2_,2) + 15*b1_*b3_ + 13*b2_*b3_ + 15*pow(b3_,2)))/(1120.*delta_);

            matrix_N_NxNx_[1](0,6) = matrix_N_NxNx_[1](6,0);
            matrix_N_NxNx_[1](1,6) = matrix_N_NxNx_[1](6,1);
            matrix_N_NxNx_[1](2,6) = matrix_N_NxNx_[1](6,2);
            matrix_N_NxNx_[1](3,6) = matrix_N_NxNx_[1](6,3);
            matrix_N_NxNx_[1](4,6) = matrix_N_NxNx_[1](6,4);
            matrix_N_NxNx_[1](5,6) = matrix_N_NxNx_[1](6,5);
            matrix_N_NxNx_[1](6,6) = (27*(4*pow(b2_,2) + 8*b2_*b3_ + 15*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[1](7,6) = (27*(4*b1_*(b2_ + b3_) + b3_*(2*b2_ + 5*b3_)))/(1120.*delta_);
            matrix_N_NxNx_[1](8,6) = (-27*(b3_*(b2_ + 2*b3_) + b1_*(3*b2_ + 4*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[1](9,6) = (27*(4*b1_*b2_ + 2*pow(b2_,2) + 15*b1_*b3_ + 4*b2_*b3_ - 3*pow(b3_,2)))/(1120.*delta_);

            matrix_N_NxNx_[1](0,7) = matrix_N_NxNx_[1](7,0);
            matrix_N_NxNx_[1](1,7) = matrix_N_NxNx_[1](7,1);
            matrix_N_NxNx_[1](2,7) = matrix_N_NxNx_[1](7,2);
            matrix_N_NxNx_[1](3,7) = matrix_N_NxNx_[1](7,3);
            matrix_N_NxNx_[1](4,7) = matrix_N_NxNx_[1](7,4);
            matrix_N_NxNx_[1](5,7) = matrix_N_NxNx_[1](7,5);
            matrix_N_NxNx_[1](6,7) = matrix_N_NxNx_[1](7,6);
            matrix_N_NxNx_[1](7,7) = (27*(4*pow(b1_,2) + 4*b1_*b3_ + 5*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[1](8,7) = (-27*(3*pow(b1_,2) - 2*b1_*b3_ + 3*pow(b3_,2)))/(2240.*delta_);
            matrix_N_NxNx_[1](9,7) = (27*(4*pow(b1_,2) + (5*b2_ - 2*b3_)*b3_ + 2*b1_*(b2_ + 2*b3_)))/(1120.*delta_);

            matrix_N_NxNx_[1](0,8) = matrix_N_NxNx_[1](8,0);
            matrix_N_NxNx_[1](1,8) = matrix_N_NxNx_[1](8,1);
            matrix_N_NxNx_[1](2,8) = matrix_N_NxNx_[1](8,2);
            matrix_N_NxNx_[1](3,8) = matrix_N_NxNx_[1](8,3);
            matrix_N_NxNx_[1](4,8) = matrix_N_NxNx_[1](8,4);
            matrix_N_NxNx_[1](5,8) = matrix_N_NxNx_[1](8,5);
            matrix_N_NxNx_[1](6,8) = matrix_N_NxNx_[1](8,6);
            matrix_N_NxNx_[1](7,8) = matrix_N_NxNx_[1](8,7);
            matrix_N_NxNx_[1](8,8) = (27*(5*pow(b1_,2) + 4*b1_*b3_ + 4*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[1](9,8) = (-27*(2*pow(b1_,2) - 2*b3_*(b2_ + 2*b3_) - b1_*(5*b2_ + 4*b3_)))/(1120.*delta_);

            matrix_N_NxNx_[1](0,9) = matrix_N_NxNx_[1](9,0);
            matrix_N_NxNx_[1](1,9) = matrix_N_NxNx_[1](9,1);
            matrix_N_NxNx_[1](2,9) = matrix_N_NxNx_[1](9,2);
            matrix_N_NxNx_[1](3,9) = matrix_N_NxNx_[1](9,3);
            matrix_N_NxNx_[1](4,9) = matrix_N_NxNx_[1](9,4);
            matrix_N_NxNx_[1](5,9) = matrix_N_NxNx_[1](9,5);
            matrix_N_NxNx_[1](6,9) = matrix_N_NxNx_[1](9,6);
            matrix_N_NxNx_[1](7,9) = matrix_N_NxNx_[1](9,7);
            matrix_N_NxNx_[1](8,9) = matrix_N_NxNx_[1](9,8);
            matrix_N_NxNx_[1](9,9) = (81*(3*pow(b1_,2) + 2*b1_*b2_ + pow(b2_,2) + 3*b1_*b3_ + 2*b2_*b3_ + 3*pow(b3_,2)))/(280.*delta_);

            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NxNx_[2](0,0) = (5*pow(b1_,2))/(168.*delta_);
            matrix_N_NxNx_[2](1,0) = (19*b1_*b2_)/(3360.*delta_);
            matrix_N_NxNx_[2](2,0) = (2*b1_*b3_)/(105.*delta_);
            matrix_N_NxNx_[2](3,0) = (-39*pow(b1_,2) + 69*b1_*b2_)/(2240.*delta_);
            matrix_N_NxNx_[2](4,0) = (3*b1_*(5*b1_ - 13*b2_))/(2240.*delta_);
            matrix_N_NxNx_[2](5,0) = (3*b1_*(2*b2_ + b3_))/(448.*delta_);
            matrix_N_NxNx_[2](6,0) = (3*b1_*(22*b2_ + 17*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](7,0) = (3*b1_*(22*b1_ - 19*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](8,0) = (-78*pow(b1_,2) + 69*b1_*b3_)/(2240.*delta_);
            matrix_N_NxNx_[2](9,0) = (9*b1_*(4*b1_ - 2*b2_ - b3_))/(1120.*delta_);

            matrix_N_NxNx_[2](0,1) = matrix_N_NxNx_[2](1,0);
            matrix_N_NxNx_[2](1,1) = (5*pow(b2_,2))/(168.*delta_);
            matrix_N_NxNx_[2](2,1) = (2*b2_*b3_)/(105.*delta_);
            matrix_N_NxNx_[2](3,1) = (3*b2_*(-13*b1_ + 5*b2_))/(2240.*delta_);
            matrix_N_NxNx_[2](4,1) = (3*(23*b1_ - 13*b2_)*b2_)/(2240.*delta_);
            matrix_N_NxNx_[2](5,1) = (-78*pow(b2_,2) + 69*b2_*b3_)/(2240.*delta_);
            matrix_N_NxNx_[2](6,1) = (3*b2_*(22*b2_ - 19*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](7,1) = (3*b2_*(22*b1_ + 17*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](8,1) = (3*b2_*(2*b1_ + b3_))/(448.*delta_);
            matrix_N_NxNx_[2](9,1) = (-9*b2_*(2*b1_ - 4*b2_ + b3_))/(1120.*delta_);

            matrix_N_NxNx_[2](0,2) = matrix_N_NxNx_[2](2,0);
            matrix_N_NxNx_[2](1,2) = matrix_N_NxNx_[2](2,1);
            matrix_N_NxNx_[2](2,2) = (257*pow(b3_,2))/(1680.*delta_);
            matrix_N_NxNx_[2](3,2) = (-39*(b1_ + b2_)*b3_)/(2240.*delta_);
            matrix_N_NxNx_[2](4,2) = (-39*(b1_ + b2_)*b3_)/(2240.*delta_);
            matrix_N_NxNx_[2](5,2) = (-3*b3_*(80*b2_ + 13*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](6,2) = (3*b3_*(220*b2_ + 53*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](7,2) = (3*b3_*(220*b1_ + 53*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](8,2) = (-3*b3_*(80*b1_ + 13*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](9,2) = (9*(10*b1_ + 10*b2_ - b3_)*b3_)/(1120.*delta_);

            matrix_N_NxNx_[2](0,3) = matrix_N_NxNx_[2](3,0);
            matrix_N_NxNx_[2](1,3) = matrix_N_NxNx_[2](3,1);
            matrix_N_NxNx_[2](2,3) = matrix_N_NxNx_[2](3,2);
            matrix_N_NxNx_[2](3,3) = (27*(5*pow(b1_,2) + 4*b1_*b2_ + 4*pow(b2_,2)))/(1120.*delta_);
            matrix_N_NxNx_[2](4,3) = (-27*(3*pow(b1_,2) - 2*b1_*b2_ + 3*pow(b2_,2)))/(2240.*delta_);
            matrix_N_NxNx_[2](5,3) = (-27*(b2_*(2*b2_ + b3_) + b1_*(4*b2_ + 3*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[2](6,3) = (-27*(3*b1_*b2_ + 3*pow(b2_,2) + 4*b1_*b3_ + 2*b2_*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](7,3) = (-27*(3*pow(b1_,2) + 3*b1_*(b2_ - b3_) - b2_*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](8,3) = (27*(5*pow(b1_,2) + 4*b2_*b3_ + 2*b1_*(2*b2_ + b3_)))/(1120.*delta_);
            matrix_N_NxNx_[2](9,3) = (-27*(2*pow(b1_,2) - 2*b2_*(2*b2_ + b3_) - b1_*(4*b2_ + 5*b3_)))/(1120.*delta_);

            matrix_N_NxNx_[2](0,4) = matrix_N_NxNx_[2](4,0);
            matrix_N_NxNx_[2](1,4) = matrix_N_NxNx_[2](4,1);
            matrix_N_NxNx_[2](2,4) = matrix_N_NxNx_[2](4,2);
            matrix_N_NxNx_[2](3,4) = matrix_N_NxNx_[2](4,3);
            matrix_N_NxNx_[2](4,4) = (27*(4*pow(b1_,2) + 4*b1_*b2_ + 5*pow(b2_,2)))/(1120.*delta_);
            matrix_N_NxNx_[2](5,4) = (27*(4*b1_*(b2_ + b3_) + b2_*(5*b2_ + 2*b3_)))/(1120.*delta_);
            matrix_N_NxNx_[2](6,4) = (-27*(3*b2_*(b2_ - b3_) + b1_*(3*b2_ - b3_)))/(2240.*delta_);
            matrix_N_NxNx_[2](7,4) = (-27*(3*pow(b1_,2) + 3*b1_*b2_ + 2*b1_*b3_ + 4*b2_*b3_))/(2240.*delta_);
            matrix_N_NxNx_[2](8,4) = (-27*(2*pow(b1_,2) + 3*b2_*b3_ + b1_*(4*b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[2](9,4) = (27*(4*pow(b1_,2) + 2*b1_*(2*b2_ + b3_) + b2_*(-2*b2_ + 5*b3_)))/(1120.*delta_);

            matrix_N_NxNx_[2](0,5) = matrix_N_NxNx_[2](5,0);
            matrix_N_NxNx_[2](1,5) = matrix_N_NxNx_[2](5,1);
            matrix_N_NxNx_[2](2,5) = matrix_N_NxNx_[2](5,2);
            matrix_N_NxNx_[2](3,5) = matrix_N_NxNx_[2](5,3);
            matrix_N_NxNx_[2](4,5) = matrix_N_NxNx_[2](5,4);
            matrix_N_NxNx_[2](5,5) = (27*(15*pow(b2_,2) + 8*b2_*b3_ + 4*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[2](6,5) = (27*(-12*pow(b2_,2) + 13*b2_*b3_ + pow(b3_,2)))/(2240.*delta_);
            matrix_N_NxNx_[2](7,5) = (-27*(2*b3_*(3*b2_ + b3_) + 3*b1_*(4*b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[2](8,5) = (-27*(b3_*(2*b2_ + b3_) + 2*b1_*(3*b2_ + b3_)))/(2240.*delta_);
            matrix_N_NxNx_[2](9,5) = (27*(15*b1_*b2_ - 3*pow(b2_,2) + 4*b1_*b3_ + 4*b2_*b3_ + 2*pow(b3_,2)))/(1120.*delta_);

            matrix_N_NxNx_[2](0,6) = matrix_N_NxNx_[2](6,0);
            matrix_N_NxNx_[2](1,6) = matrix_N_NxNx_[2](6,1);
            matrix_N_NxNx_[2](2,6) = matrix_N_NxNx_[2](6,2);
            matrix_N_NxNx_[2](3,6) = matrix_N_NxNx_[2](6,3);
            matrix_N_NxNx_[2](4,6) = matrix_N_NxNx_[2](6,4);
            matrix_N_NxNx_[2](5,6) = matrix_N_NxNx_[2](6,5);
            matrix_N_NxNx_[2](6,6) = (27*(27*pow(b2_,2) + 23*b2_*b3_ + 15*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[2](7,6) = (27*(54*b1_*b2_ + 23*b1_*b3_ + 23*b2_*b3_ + 15*pow(b3_,2)))/(2240.*delta_);
            matrix_N_NxNx_[2](8,6) = (-27*(6*b1_*(2*b2_ + b3_) + b3_*(3*b2_ + 2*b3_)))/(2240.*delta_);
            matrix_N_NxNx_[2](9,6) = (27*(15*b1_*b2_ + 15*pow(b2_,2) + 22*b1_*b3_ + 13*b2_*b3_ + 5*pow(b3_,2)))/(1120.*delta_);

            matrix_N_NxNx_[2](0,7) = matrix_N_NxNx_[2](7,0);
            matrix_N_NxNx_[2](1,7) = matrix_N_NxNx_[2](7,1);
            matrix_N_NxNx_[2](2,7) = matrix_N_NxNx_[2](7,2);
            matrix_N_NxNx_[2](3,7) = matrix_N_NxNx_[2](7,3);
            matrix_N_NxNx_[2](4,7) = matrix_N_NxNx_[2](7,4);
            matrix_N_NxNx_[2](5,7) = matrix_N_NxNx_[2](7,5);
            matrix_N_NxNx_[2](6,7) = matrix_N_NxNx_[2](7,6);
            matrix_N_NxNx_[2](7,7) = (27*(27*pow(b1_,2) + 23*b1_*b3_ + 15*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[2](8,7) = (27*(-12*pow(b1_,2) + 13*b1_*b3_ + pow(b3_,2)))/(2240.*delta_);
            matrix_N_NxNx_[2](9,7) = (27*(15*pow(b1_,2) + 15*b1_*b2_ + 13*b1_*b3_ + 22*b2_*b3_ + 5*pow(b3_,2)))/(1120.*delta_);

            matrix_N_NxNx_[2](0,8) = matrix_N_NxNx_[2](8,0);
            matrix_N_NxNx_[2](1,8) = matrix_N_NxNx_[2](8,1);
            matrix_N_NxNx_[2](2,8) = matrix_N_NxNx_[2](8,2);
            matrix_N_NxNx_[2](3,8) = matrix_N_NxNx_[2](8,3);
            matrix_N_NxNx_[2](4,8) = matrix_N_NxNx_[2](8,4);
            matrix_N_NxNx_[2](5,8) = matrix_N_NxNx_[2](8,5);
            matrix_N_NxNx_[2](6,8) = matrix_N_NxNx_[2](8,6);
            matrix_N_NxNx_[2](7,8) = matrix_N_NxNx_[2](8,7);
            matrix_N_NxNx_[2](8,8) = (27*(15*pow(b1_,2) + 8*b1_*b3_ + 4*pow(b3_,2)))/(1120.*delta_);
            matrix_N_NxNx_[2](9,8) = (-27*(3*pow(b1_,2) - 2*b3_*(2*b2_ + b3_) - b1_*(15*b2_ + 4*b3_)))/(1120.*delta_);

            matrix_N_NxNx_[2](0,9) = matrix_N_NxNx_[2](9,0);
            matrix_N_NxNx_[2](1,9) = matrix_N_NxNx_[2](9,1);
            matrix_N_NxNx_[2](2,9) = matrix_N_NxNx_[2](9,2);
            matrix_N_NxNx_[2](3,9) = matrix_N_NxNx_[2](9,3);
            matrix_N_NxNx_[2](4,9) = matrix_N_NxNx_[2](9,4);
            matrix_N_NxNx_[2](5,9) = matrix_N_NxNx_[2](9,5);
            matrix_N_NxNx_[2](6,9) = matrix_N_NxNx_[2](9,6);
            matrix_N_NxNx_[2](7,9) = matrix_N_NxNx_[2](9,7);
            matrix_N_NxNx_[2](8,9) = matrix_N_NxNx_[2](9,8);
            matrix_N_NxNx_[2](9,9) = (81*(3*pow(b1_,2) + 3*b1_*b2_ + 3*pow(b2_,2) + 2*b1_*b3_ + 2*b2_*b3_ + pow(b3_,2)))/(280.*delta_);
        }
        else
            throw(Exception("FEATURE NOT INPLEMENTED","basis_function_order >= 4 not implemented"));
    }
    else
        throw(Exception("FEATURE NOT INPLEMENTED","coefficient_order_ > 1 not implemented"));
}



//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NyNy_matrix_analytically : Computes all N_NyNy matrices using
 * analytic integration.
 *
 * Analytical integration is limited to basis functions of order not greater than 2, and
 * coefficient functions of order not greater than one (i.e. constant and linear coefficients) */
//************************************************************************************************//
void SolverTriangle::Compute_N_NyNy_matrix_analytically()
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;

    if (coefficient_order_ == 0)
    {
        matrix_N_NyNy_[0].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](0,0) = pow(c1_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](1,0) = (c1_*c2_)/(4.0*delta_);
            matrix_N_NyNy_[0](2,0) = (c1_*c3_)/(4.0*delta_);

            matrix_N_NyNy_[0](0,1) = matrix_N_NyNy_[0](1,0);
            matrix_N_NyNy_[0](1,1) = pow(c2_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](2,1) = (c2_*c3_)/(4.0*delta_);

            matrix_N_NyNy_[0](0,2) = matrix_N_NyNy_[0](2,0);
            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = pow(c3_,2)/(4.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](0,0) = pow(c1_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](1,0) = -(c1_*c2_)/(12.0*delta_);
            matrix_N_NyNy_[0](2,0) = -(c1_*c3_)/(12.0*delta_);
            matrix_N_NyNy_[0](3,0) = (c1_*c2_)/(3.0*delta_);
            matrix_N_NyNy_[0](4,0) = 0.0;
            matrix_N_NyNy_[0](5,0) = (c1_*c3_)/(3.0*delta_);

            matrix_N_NyNy_[0](0,1) = matrix_N_NyNy_[0](1,0);
            matrix_N_NyNy_[0](1,1) = pow(c2_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](2,1) = -(c2_*c3_)/(12.0*delta_);
            matrix_N_NyNy_[0](3,1) = (c1_*c2_)/(3.0*delta_);
            matrix_N_NyNy_[0](4,1) = (c2_*c3_)/(3.0*delta_);
            matrix_N_NyNy_[0](5,1) = 0.0;

            matrix_N_NyNy_[0](0,2) = matrix_N_NyNy_[0](2,0);
            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = pow(c3_,2)/(4.0*delta_);
            matrix_N_NyNy_[0](3,2) = 0.0;
            matrix_N_NyNy_[0](4,2) = (c2_*c3_)/(3.0*delta_);
            matrix_N_NyNy_[0](5,2) = (c1_*c3_)/(3.0*delta_);

            matrix_N_NyNy_[0](0,3) = matrix_N_NyNy_[0](3,0);
            matrix_N_NyNy_[0](1,3) = matrix_N_NyNy_[0](3,1);
            matrix_N_NyNy_[0](2,3) = matrix_N_NyNy_[0](3,2);
            matrix_N_NyNy_[0](3,3) = (2.0*pow(c1_,2))/(3.0*delta_) + (2.0*c1_*c2_)/(3.0*delta_) + (2.0*pow(c2_,2))/(3.0*delta_);
            matrix_N_NyNy_[0](4,3) = (c1_*c2_)/(3.0*delta_) + pow(c2_,2)/(3.0*delta_) + (2.0*c1_*c3_)/(3.0*delta_) + (c2_*c3_)/(3.0*delta_);
            matrix_N_NyNy_[0](5,3) = pow(c1_,2)/(3.0*delta_) + (c1_*c2_)/(3.0*delta_) + (c1_*c3_)/(3.0*delta_) + (2.0*c2_*c3_)/(3.0*delta_);

            matrix_N_NyNy_[0](0,4) = matrix_N_NyNy_[0](4,0);
            matrix_N_NyNy_[0](1,4) = matrix_N_NyNy_[0](4,1);
            matrix_N_NyNy_[0](2,4) = matrix_N_NyNy_[0](4,2);
            matrix_N_NyNy_[0](3,4) = matrix_N_NyNy_[0](4,3);
            matrix_N_NyNy_[0](4,4) = (2.0*pow(c2_,2))/(3.0*delta_) + (2.0*c2_*c3_)/(3.0*delta_) + (2.0*pow(c3_,2))/(3.0*delta_);
            matrix_N_NyNy_[0](5,4) = (2.0*c1_*c2_)/(3.0*delta_) + (c1_*c3_)/(3.0*delta_) + (c2_*c3_)/(3.0*delta_) + pow(c3_,2)/(3.0*delta_);

            matrix_N_NyNy_[0](0,5) = matrix_N_NyNy_[0](5,0);
            matrix_N_NyNy_[0](1,5) = matrix_N_NyNy_[0](5,1);
            matrix_N_NyNy_[0](2,5) = matrix_N_NyNy_[0](5,2);
            matrix_N_NyNy_[0](3,5) = matrix_N_NyNy_[0](5,3);
            matrix_N_NyNy_[0](4,5) = matrix_N_NyNy_[0](5,4);
            matrix_N_NyNy_[0](5,5) = (2.0*pow(c1_,2))/(3.0*delta_) + (2.0*c1_*c3_)/(3.0*delta_) + (2.0*pow(c3_,2))/(3.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](0,0) = (17*pow(c1_,2))/(80.*delta_);
            matrix_N_NyNy_[0](1,0) = (7*c1_*c2_)/(160.*delta_);
            matrix_N_NyNy_[0](2,0) = (7*c1_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](3,0) = (3*pow(c1_,2))/(160.*delta_) + (57*c1_*c2_)/(160.*delta_);
            matrix_N_NyNy_[0](4,0) = (3*pow(c1_,2))/(160.*delta_) - (3*c1_*c2_)/(20.*delta_);
            matrix_N_NyNy_[0](5,0) = (3*c1_*c2_)/(160.*delta_) + (3*c1_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](6,0) = (3*c1_*c2_)/(160.*delta_) + (3*c1_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](7,0) = (3*pow(c1_,2))/(160.*delta_) - (3*c1_*c3_)/(20.*delta_);
            matrix_N_NyNy_[0](8,0) = (3*pow(c1_,2))/(160.*delta_) + (57*c1_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](9,0) = (9*pow(c1_,2))/(160.*delta_) + (9*c1_*c2_)/(160.*delta_) + (9*c1_*c3_)/(160.*delta_);

            matrix_N_NyNy_[0](0,1) = matrix_N_NyNy_[0](1,0);
            matrix_N_NyNy_[0](1,1) = (17*pow(c2_,2))/(80.*delta_);
            matrix_N_NyNy_[0](2,1) = (7*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](3,1) = (-3*c1_*c2_)/(20.*delta_) + (3*pow(c2_,2))/(160.*delta_);
            matrix_N_NyNy_[0](4,1) = (57*c1_*c2_)/(160.*delta_) + (3*pow(c2_,2))/(160.*delta_);
            matrix_N_NyNy_[0](5,1) = (3*pow(c2_,2))/(160.*delta_) + (57*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](6,1) = (3*pow(c2_,2))/(160.*delta_) - (3*c2_*c3_)/(20.*delta_);
            matrix_N_NyNy_[0](7,1) = (3*c1_*c2_)/(160.*delta_) + (3*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](8,1) = (3*c1_*c2_)/(160.*delta_) + (3*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](9,1) = (9*c1_*c2_)/(160.*delta_) + (9*pow(c2_,2))/(160.*delta_) + (9*c2_*c3_)/(160.*delta_);

            matrix_N_NyNy_[0](0,2) = matrix_N_NyNy_[0](2,0);
            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = (17*pow(c3_,2))/(80.*delta_);
            matrix_N_NyNy_[0](3,2) = (3*c1_*c3_)/(160.*delta_) + (3*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](4,2) = (3*c1_*c3_)/(160.*delta_) + (3*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](5,2) = (-3*c2_*c3_)/(20.*delta_) + (3*pow(c3_,2))/(160.*delta_);
            matrix_N_NyNy_[0](6,2) = (57*c2_*c3_)/(160.*delta_) + (3*pow(c3_,2))/(160.*delta_);
            matrix_N_NyNy_[0](7,2) = (57*c1_*c3_)/(160.*delta_) + (3*pow(c3_,2))/(160.*delta_);
            matrix_N_NyNy_[0](8,2) = (-3*c1_*c3_)/(20.*delta_) + (3*pow(c3_,2))/(160.*delta_);
            matrix_N_NyNy_[0](9,2) = (9*c1_*c3_)/(160.*delta_) + (9*c2_*c3_)/(160.*delta_) + (9*pow(c3_,2))/(160.*delta_);

            matrix_N_NyNy_[0](0,3) = matrix_N_NyNy_[0](3,0);
            matrix_N_NyNy_[0](1,3) = matrix_N_NyNy_[0](3,1);
            matrix_N_NyNy_[0](2,3) = matrix_N_NyNy_[0](3,2);
            matrix_N_NyNy_[0](3,3) = (27*pow(c1_,2))/(32.*delta_) + (27*c1_*c2_)/(32.*delta_) + (27*pow(c2_,2))/(32.*delta_);
            matrix_N_NyNy_[0](4,3) = (-27*pow(c1_,2))/(160.*delta_) + (27*c1_*c2_)/(80.*delta_) - (27*pow(c2_,2))/(160.*delta_);
            matrix_N_NyNy_[0](5,3) = (-27*c1_*c2_)/(320.*delta_) - (27*pow(c2_,2))/(320.*delta_) - (27*c1_*c3_)/(160.*delta_) - (27*c2_*c3_)/(320.*delta_);
            matrix_N_NyNy_[0](6,3) = (-27*c1_*c2_)/(320.*delta_) - (27*pow(c2_,2))/(320.*delta_) - (27*c1_*c3_)/(160.*delta_) - (27*c2_*c3_)/(320.*delta_);
            matrix_N_NyNy_[0](7,3) = (-27*pow(c1_,2))/(320.*delta_) - (27*c1_*c2_)/(320.*delta_) - (27*c1_*c3_)/(320.*delta_) - (27*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](8,3) = (27*pow(c1_,2))/(64.*delta_) + (27*c1_*c2_)/(64.*delta_) + (27*c1_*c3_)/(64.*delta_) + (27*c2_*c3_)/(32.*delta_);
            matrix_N_NyNy_[0](9,3) = (81*c1_*c2_)/(160.*delta_) + (81*pow(c2_,2))/(160.*delta_) + (81*c1_*c3_)/(80.*delta_) + (81*c2_*c3_)/(160.*delta_);

            matrix_N_NyNy_[0](0,4) = matrix_N_NyNy_[0](4,0);
            matrix_N_NyNy_[0](1,4) = matrix_N_NyNy_[0](4,1);
            matrix_N_NyNy_[0](2,4) = matrix_N_NyNy_[0](4,2);
            matrix_N_NyNy_[0](3,4) = matrix_N_NyNy_[0](4,3);
            matrix_N_NyNy_[0](4,4) = (27*pow(c1_,2))/(32.*delta_) + (27*c1_*c2_)/(32.*delta_) + (27*pow(c2_,2))/(32.*delta_);
            matrix_N_NyNy_[0](5,4) = (27*c1_*c2_)/(64.*delta_) + (27*pow(c2_,2))/(64.*delta_) + (27*c1_*c3_)/(32.*delta_) + (27*c2_*c3_)/(64.*delta_);
            matrix_N_NyNy_[0](6,4) = (-27*c1_*c2_)/(320.*delta_) - (27*pow(c2_,2))/(320.*delta_) - (27*c1_*c3_)/(160.*delta_) - (27*c2_*c3_)/(320.*delta_);
            matrix_N_NyNy_[0](7,4) = (-27*pow(c1_,2))/(320.*delta_) - (27*c1_*c2_)/(320.*delta_) - (27*c1_*c3_)/(320.*delta_) - (27*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](8,4) = (-27*pow(c1_,2))/(320.*delta_) - (27*c1_*c2_)/(320.*delta_) - (27*c1_*c3_)/(320.*delta_) - (27*c2_*c3_)/(160.*delta_);
            matrix_N_NyNy_[0](9,4) = (81*pow(c1_,2))/(160.*delta_) + (81*c1_*c2_)/(160.*delta_) + (81*c1_*c3_)/(160.*delta_) + (81*c2_*c3_)/(80.*delta_);

            matrix_N_NyNy_[0](0,5) = matrix_N_NyNy_[0](5,0);
            matrix_N_NyNy_[0](1,5) = matrix_N_NyNy_[0](5,1);
            matrix_N_NyNy_[0](2,5) = matrix_N_NyNy_[0](5,2);
            matrix_N_NyNy_[0](3,5) = matrix_N_NyNy_[0](5,3);
            matrix_N_NyNy_[0](4,5) = matrix_N_NyNy_[0](5,4);
            matrix_N_NyNy_[0](5,5) = (27*pow(c2_,2))/(32.*delta_) + (27*c2_*c3_)/(32.*delta_) + (27*pow(c3_,2))/(32.*delta_);
            matrix_N_NyNy_[0](6,5) = (-27*pow(c2_,2))/(160.*delta_) + (27*c2_*c3_)/(80.*delta_) - (27*pow(c3_,2))/(160.*delta_);
            matrix_N_NyNy_[0](7,5) = (-27*c1_*c2_)/(160.*delta_) - (27*c1_*c3_)/(320.*delta_) - (27*c2_*c3_)/(320.*delta_) - (27*pow(c3_,2))/(320.*delta_);
            matrix_N_NyNy_[0](8,5) = (-27*c1_*c2_)/(160.*delta_) - (27*c1_*c3_)/(320.*delta_) - (27*c2_*c3_)/(320.*delta_) - (27*pow(c3_,2))/(320.*delta_);
            matrix_N_NyNy_[0](9,5) = (81*c1_*c2_)/(80.*delta_) + (81*c1_*c3_)/(160.*delta_) + (81*c2_*c3_)/(160.*delta_) + (81*pow(c3_,2))/(160.*delta_);

            matrix_N_NyNy_[0](0,6) = matrix_N_NyNy_[0](6,0);
            matrix_N_NyNy_[0](1,6) = matrix_N_NyNy_[0](6,1);
            matrix_N_NyNy_[0](2,6) = matrix_N_NyNy_[0](6,2);
            matrix_N_NyNy_[0](3,6) = matrix_N_NyNy_[0](6,3);
            matrix_N_NyNy_[0](4,6) = matrix_N_NyNy_[0](6,4);
            matrix_N_NyNy_[0](5,6) = matrix_N_NyNy_[0](6,5);
            matrix_N_NyNy_[0](6,6) = (27*pow(c2_,2))/(32.*delta_) + (27*c2_*c3_)/(32.*delta_) + (27*pow(c3_,2))/(32.*delta_);
            matrix_N_NyNy_[0](7,6) = (27*c1_*c2_)/(32.*delta_) + (27*c1_*c3_)/(64.*delta_) + (27*c2_*c3_)/(64.*delta_) + (27*pow(c3_,2))/(64.*delta_);
            matrix_N_NyNy_[0](8,6) = (-27*c1_*c2_)/(160.*delta_) - (27*c1_*c3_)/(320.*delta_) - (27*c2_*c3_)/(320.*delta_) - (27*pow(c3_,2))/(320.*delta_);
            matrix_N_NyNy_[0](9,6) = (81*c1_*c2_)/(160.*delta_) + (81*pow(c2_,2))/(160.*delta_) + (81*c1_*c3_)/(80.*delta_) + (81*c2_*c3_)/(160.*delta_);

            matrix_N_NyNy_[0](0,7) = matrix_N_NyNy_[0](7,0);
            matrix_N_NyNy_[0](1,7) = matrix_N_NyNy_[0](7,1);
            matrix_N_NyNy_[0](2,7) = matrix_N_NyNy_[0](7,2);
            matrix_N_NyNy_[0](3,7) = matrix_N_NyNy_[0](7,3);
            matrix_N_NyNy_[0](4,7) = matrix_N_NyNy_[0](7,4);
            matrix_N_NyNy_[0](5,7) = matrix_N_NyNy_[0](7,5);
            matrix_N_NyNy_[0](6,7) = matrix_N_NyNy_[0](7,6);
            matrix_N_NyNy_[0](7,7) = (27*pow(c1_,2))/(32.*delta_) + (27*c1_*c3_)/(32.*delta_) + (27*pow(c3_,2))/(32.*delta_);
            matrix_N_NyNy_[0](8,7) = (-27*pow(c1_,2))/(160.*delta_) + (27*c1_*c3_)/(80.*delta_) - (27*pow(c3_,2))/(160.*delta_);
            matrix_N_NyNy_[0](9,7) = (81*pow(c1_,2))/(160.*delta_) + (81*c1_*c2_)/(160.*delta_) + (81*c1_*c3_)/(160.*delta_) + (81*c2_*c3_)/(80.*delta_);

            matrix_N_NyNy_[0](0,8) = matrix_N_NyNy_[0](8,0);
            matrix_N_NyNy_[0](1,8) = matrix_N_NyNy_[0](8,1);
            matrix_N_NyNy_[0](2,8) = matrix_N_NyNy_[0](8,2);
            matrix_N_NyNy_[0](3,8) = matrix_N_NyNy_[0](8,3);
            matrix_N_NyNy_[0](4,8) = matrix_N_NyNy_[0](8,4);
            matrix_N_NyNy_[0](5,8) = matrix_N_NyNy_[0](8,5);
            matrix_N_NyNy_[0](6,8) = matrix_N_NyNy_[0](8,6);
            matrix_N_NyNy_[0](7,8) = matrix_N_NyNy_[0](8,7);
            matrix_N_NyNy_[0](8,8) = (27*pow(c1_,2))/(32.*delta_) + (27*c1_*c3_)/(32.*delta_) + (27*pow(c3_,2))/(32.*delta_);
            matrix_N_NyNy_[0](9,8) = (81*c1_*c2_)/(80.*delta_) + (81*c1_*c3_)/(160.*delta_) + (81*c2_*c3_)/(160.*delta_) + (81*pow(c3_,2))/(160.*delta_);

            matrix_N_NyNy_[0](0,9) = matrix_N_NyNy_[0](9,0);
            matrix_N_NyNy_[0](1,9) = matrix_N_NyNy_[0](9,1);
            matrix_N_NyNy_[0](2,9) = matrix_N_NyNy_[0](9,2);
            matrix_N_NyNy_[0](3,9) = matrix_N_NyNy_[0](9,3);
            matrix_N_NyNy_[0](4,9) = matrix_N_NyNy_[0](9,4);
            matrix_N_NyNy_[0](5,9) = matrix_N_NyNy_[0](9,5);
            matrix_N_NyNy_[0](6,9) = matrix_N_NyNy_[0](9,6);
            matrix_N_NyNy_[0](7,9) = matrix_N_NyNy_[0](9,7);
            matrix_N_NyNy_[0](8,9) = matrix_N_NyNy_[0](9,8);
            matrix_N_NyNy_[0](9,9) = (81*pow(c1_,2))/(40.*delta_) + (81*c1_*c2_)/(40.*delta_) + (81*pow(c2_,2))/(40.*delta_) + (81*c1_*c3_)/(40.*delta_) + (81*c2_*c3_)/(40.*delta_) + (81*pow(c3_,2))/(40.*delta_);
        }
        else
            throw(Exception("FEATURE NOT INPLEMENTED","basis_function_order >= 4 not implemented"));
    }
    else if (coefficient_order_ == 1)
    {
        matrix_N_NyNy_[0].resize(num_basis_functions,num_basis_functions);
        matrix_N_NyNy_[1].resize(num_basis_functions,num_basis_functions);
        matrix_N_NyNy_[2].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](0,0) = pow(c1_,2)/(12.0*delta_);
            matrix_N_NyNy_[0](1,0) = (c1_*c2_)/(12.0*delta_);
            matrix_N_NyNy_[0](2,0) = (c1_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[0](0,1) = matrix_N_NyNy_[0](1,0);
            matrix_N_NyNy_[0](1,1) = pow(c2_,2)/(12.0*delta_);
            matrix_N_NyNy_[0](2,1) = (c2_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[0](0,2) = matrix_N_NyNy_[0](2,0);
            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = pow(c3_,2)/(12.0*delta_);


            // Fill second matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[1](0,0) = pow(c1_,2)/(12.0*delta_);
            matrix_N_NyNy_[1](1,0) = (c1_*c2_)/(12.0*delta_);
            matrix_N_NyNy_[1](2,0) = (c1_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[1](0,1) = matrix_N_NyNy_[1](1,0);
            matrix_N_NyNy_[1](1,1) = pow(c2_,2)/(12.0*delta_);
            matrix_N_NyNy_[1](2,1) = (c2_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[1](0,2) = matrix_N_NyNy_[1](2,0);
            matrix_N_NyNy_[1](1,2) = matrix_N_NyNy_[1](2,1);
            matrix_N_NyNy_[1](2,2) = pow(c3_,2)/(12.0*delta_);


            // Fill third matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[2](0,0) = pow(c1_,2)/(12.0*delta_);
            matrix_N_NyNy_[2](1,0) = (c1_*c2_)/(12.0*delta_);
            matrix_N_NyNy_[2](2,0) = (c1_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[2](0,1) = matrix_N_NyNy_[2](1,0);
            matrix_N_NyNy_[2](1,1) = pow(c2_,2)/(12.0*delta_);
            matrix_N_NyNy_[2](2,1) = (c2_*c3_)/(12.0*delta_);

            matrix_N_NyNy_[2](0,2) = matrix_N_NyNy_[2](2,0);
            matrix_N_NyNy_[2](1,2) = matrix_N_NyNy_[2](2,1);
            matrix_N_NyNy_[2](2,2) = pow(c3_,2)/(12.0*delta_);
        }
        else if (basis_function_order_ == 2)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](0,0) = (3.0*pow(c1_,2))/(20.0*delta_);
            matrix_N_NyNy_[0](1,0) = -(c1_*c2_)/(30.0*delta_);
            matrix_N_NyNy_[0](2,0) = -(c1_*c3_)/(30.0*delta_);
            matrix_N_NyNy_[0](3,0) = (c1_*(3.0*c1_ + 14.0*c2_))/(60.0*delta_);
            matrix_N_NyNy_[0](4,0) = (c1_*(c2_ + c3_))/(20.0*delta_);
            matrix_N_NyNy_[0](5,0) = (c1_*(3.0*c1_ + 14.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[0](0,1) = matrix_N_NyNy_[0](1,0);
            matrix_N_NyNy_[0](1,1) = pow(c2_,2)/(20.0*delta_);
            matrix_N_NyNy_[0](2,1) = -(c2_*c3_)/(60.0*delta_);
            matrix_N_NyNy_[0](3,1) = ((3.0*c1_ - 2.0*c2_)*c2_)/(60.0*delta_);
            matrix_N_NyNy_[0](4,1) = -(c2_*(c2_ - 3.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[0](5,1) = -(c2_*(c1_ + 2.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[0](0,2) = matrix_N_NyNy_[0](2,0);
            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = pow(c3_,2)/(20.0*delta_);
            matrix_N_NyNy_[0](3,2) = -((c1_ + 2.0*c2_)*c3_)/(60.0*delta_);
            matrix_N_NyNy_[0](4,2) = ((3.0*c2_ - c3_)*c3_)/(60.0*delta_);
            matrix_N_NyNy_[0](5,2) = ((3.0*c1_ - 2.0*c3_)*c3_)/(60.0*delta_);

            matrix_N_NyNy_[0](0,3) = matrix_N_NyNy_[0](3,0);
            matrix_N_NyNy_[0](1,3) = matrix_N_NyNy_[0](3,1);
            matrix_N_NyNy_[0](2,3) = matrix_N_NyNy_[0](3,2);
            matrix_N_NyNy_[0](3,3) = (2.0*(pow(c1_,2) + 2.0*c1_*c2_ + 3.0*pow(c2_,2)))/(15.0*delta_);
            matrix_N_NyNy_[0](4,3) = (2.0*c2_*(c2_ + c3_) + c1_*(c2_ + 2.0*c3_))/(15.0*delta_);
            matrix_N_NyNy_[0](5,3) = (pow(c1_,2) + 6.0*c2_*c3_ + 2.0*c1_*(c2_ + c3_))/(15.0*delta_);

            matrix_N_NyNy_[0](0,4) = matrix_N_NyNy_[0](4,0);
            matrix_N_NyNy_[0](1,4) = matrix_N_NyNy_[0](4,1);
            matrix_N_NyNy_[0](2,4) = matrix_N_NyNy_[0](4,2);
            matrix_N_NyNy_[0](3,4) = matrix_N_NyNy_[0](4,3);
            matrix_N_NyNy_[0](4,4) = (2.0*(pow(c2_,2) + c2_*c3_ + pow(c3_,2)))/(15.0*delta_);
            matrix_N_NyNy_[0](5,4) = (2.0*c3_*(c2_ + c3_) + c1_*(2.0*c2_ + c3_))/(15.0*delta_);

            matrix_N_NyNy_[0](0,5) = matrix_N_NyNy_[0](5,0);
            matrix_N_NyNy_[0](1,5) = matrix_N_NyNy_[0](5,1);
            matrix_N_NyNy_[0](2,5) = matrix_N_NyNy_[0](5,2);
            matrix_N_NyNy_[0](3,5) = matrix_N_NyNy_[0](5,3);
            matrix_N_NyNy_[0](4,5) = matrix_N_NyNy_[0](5,4);
            matrix_N_NyNy_[0](5,5) = (2.0*(pow(c1_,2) + 2.0*c1_*c3_ + 3.0*pow(c3_,2)))/(15.0*delta_);


            // Fill second matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[1](0,0) = pow(c1_,2)/(20.0*delta_);
            matrix_N_NyNy_[1](0,1) = -(c1_*c2_)/(30.0*delta_);
            matrix_N_NyNy_[1](0,2) = -(c1_*c3_)/(60.0*delta_);
            matrix_N_NyNy_[1](0,3) = (c1_*(-2.0*c1_ + 3.0*c2_))/(60.0*delta_);
            matrix_N_NyNy_[1](0,4) = -(c1_*(c2_ + 2.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[1](0,5) = -(c1_*(c1_ - 3.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[1](1,0) = matrix_N_NyNy_[1](0,1);
            matrix_N_NyNy_[1](1,1) = (3.0*pow(c2_,2))/(20.0*delta_);
            matrix_N_NyNy_[1](1,2) = -(c2_*c3_)/(30.0*delta_);
            matrix_N_NyNy_[1](1,3) = (c2_*(14.0*c1_ + 3.0*c2_))/(60.0*delta_);
            matrix_N_NyNy_[1](1,4) = (c2_*(3.0*c2_ + 14.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[1](1,5) = (c2_*(c1_ + c3_))/(20.0*delta_);

            matrix_N_NyNy_[1](2,0) = matrix_N_NyNy_[1](0,2);
            matrix_N_NyNy_[1](2,1) = matrix_N_NyNy_[1](1,2);
            matrix_N_NyNy_[1](2,2) = pow(c3_,2)/(20.0*delta_);
            matrix_N_NyNy_[1](2,3) = -((2.0*c1_ + c2_)*c3_)/(60.0*delta_);
            matrix_N_NyNy_[1](2,4) = ((3.0*c2_ - 2.0*c3_)*c3_)/(60.0*delta_);
            matrix_N_NyNy_[1](2,5) = ((3.0*c1_ - c3_)*c3_)/(60.0*delta_);

            matrix_N_NyNy_[1](3,0) = matrix_N_NyNy_[1](0,3);
            matrix_N_NyNy_[1](3,1) = matrix_N_NyNy_[1](1,3);
            matrix_N_NyNy_[1](3,2) = matrix_N_NyNy_[1](2,3);
            matrix_N_NyNy_[1](3,3) = (2.0*(3.0*pow(c1_,2) + 2.0*c1_*c2_ + pow(c2_,2)))/(15.0*delta_);
            matrix_N_NyNy_[1](3,4) = (2.0*c1_*c2_ + pow(c2_,2) + 6.0*c1_*c3_ + 2.0*c2_*c3_)/(15.0*delta_);
            matrix_N_NyNy_[1](3,5) = (2.0*pow(c1_,2) + c1_*c2_ + 2.0*c1_*c3_ + 2.0*c2_*c3_)/(15.0*delta_);

            matrix_N_NyNy_[1](4,0) = matrix_N_NyNy_[1](0,4);
            matrix_N_NyNy_[1](4,1) = matrix_N_NyNy_[1](1,4);
            matrix_N_NyNy_[1](4,2) = matrix_N_NyNy_[1](2,4);
            matrix_N_NyNy_[1](4,3) = matrix_N_NyNy_[1](3,4);
            matrix_N_NyNy_[1](4,4) = (2.0*(pow(c2_,2) + 2.0*c2_*c3_ + 3.0*pow(c3_,2)))/(15.0*delta_);
            matrix_N_NyNy_[1](4,5) = (2.0*c1_*(c2_ + c3_) + c3_*(c2_ + 2.0*c3_))/(15.0*delta_);

            matrix_N_NyNy_[1](5,0) = matrix_N_NyNy_[1](0,5);
            matrix_N_NyNy_[1](5,1) = matrix_N_NyNy_[1](1,5);
            matrix_N_NyNy_[1](5,2) = matrix_N_NyNy_[1](2,5);
            matrix_N_NyNy_[1](5,3) = matrix_N_NyNy_[1](3,5);
            matrix_N_NyNy_[1](5,4) = matrix_N_NyNy_[1](4,5);
            matrix_N_NyNy_[1](5,5) = (2.0*(pow(c1_,2) + c1_*c3_ + pow(c3_,2)))/(15.0*delta_);


            // Fill third matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[2](0,0) = pow(c1_,2)/(20.0*delta_);
            matrix_N_NyNy_[2](0,1) = -(c1_*c2_)/(60.0*delta_);
            matrix_N_NyNy_[2](0,2) = -(c1_*c3_)/(30.0*delta_);
            matrix_N_NyNy_[2](0,3) = -(c1_*(c1_ - 3.0*c2_))/(60.0*delta_);
            matrix_N_NyNy_[2](0,4) = -(c1_*(2.0*c2_ + c3_))/(60.0*delta_);
            matrix_N_NyNy_[2](0,5) = (c1_*(-2.0*c1_ + 3.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[2](1,0) = matrix_N_NyNy_[2](0,1);
            matrix_N_NyNy_[2](1,1) = pow(c2_,2)/(20.0*delta_);
            matrix_N_NyNy_[2](1,2) = -(c2_*c3_)/(30.0*delta_);
            matrix_N_NyNy_[2](1,3) = ((3.0*c1_ - c2_)*c2_)/(60.0*delta_);
            matrix_N_NyNy_[2](1,4) = (c2_*(-2.0*c2_ + 3.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[2](1,5) = -(c2_*(2.0*c1_ + c3_))/(60.*delta_);

            matrix_N_NyNy_[2](2,0) = matrix_N_NyNy_[2](0,2);
            matrix_N_NyNy_[2](2,1) = matrix_N_NyNy_[2](1,2);
            matrix_N_NyNy_[2](2,2) = (3.0*pow(c3_,2))/(20.0*delta_);
            matrix_N_NyNy_[2](2,3) = ((c1_ + c2_)*c3_)/(20.0*delta_);
            matrix_N_NyNy_[2](2,4) = (c3_*(14.0*c2_ + 3.0*c3_))/(60.0*delta_);
            matrix_N_NyNy_[2](2,5) = (c3_*(14.0*c1_ + 3.0*c3_))/(60.0*delta_);

            matrix_N_NyNy_[2](3,0) = matrix_N_NyNy_[2](0,3);
            matrix_N_NyNy_[2](3,1) = matrix_N_NyNy_[2](1,3);
            matrix_N_NyNy_[2](3,2) = matrix_N_NyNy_[2](2,3);
            matrix_N_NyNy_[2](3,3) = (2.0*(pow(c1_,2) + c1_*c2_ + pow(c2_,2)))/(15.0*delta_);
            matrix_N_NyNy_[2](3,4) = (2.0*c1_*(c2_ + c3_) + c2_*(2.0*c2_ + c3_))/(15.0*delta_);
            matrix_N_NyNy_[2](3,5) = (2.0*pow(c1_,2) + 2.0*c1_*c2_ + c1_*c3_ + 2.0*c2_*c3_)/(15.0*delta_);

            matrix_N_NyNy_[2](4,0) = matrix_N_NyNy_[2](0,4);
            matrix_N_NyNy_[2](4,1) = matrix_N_NyNy_[2](1,4);
            matrix_N_NyNy_[2](4,2) = matrix_N_NyNy_[2](2,4);
            matrix_N_NyNy_[2](4,3) = matrix_N_NyNy_[2](3,4);
            matrix_N_NyNy_[2](4,4) = (2.0*(3.0*pow(c2_,2) + 2.0*c2_*c3_ + pow(c3_,2)))/(15.0*delta_);
            matrix_N_NyNy_[2](4,5) = (6.0*c1_*c2_ + 2.0*c1_*c3_ + 2.0*c2_*c3_ + pow(c3_,2))/(15.0*delta_);

            matrix_N_NyNy_[2](5,0) = matrix_N_NyNy_[2](0,5);
            matrix_N_NyNy_[2](5,1) = matrix_N_NyNy_[2](1,5);
            matrix_N_NyNy_[2](5,2) = matrix_N_NyNy_[2](2,5);
            matrix_N_NyNy_[2](5,3) = matrix_N_NyNy_[2](3,5);
            matrix_N_NyNy_[2](5,4) = matrix_N_NyNy_[2](4,5);
            matrix_N_NyNy_[2](5,5) = (2.0*(3.0*pow(c1_,2) + 2.0*c1_*c3_ + pow(c3_,2)))/(15.0*delta_);
        }
        else if (basis_function_order_ == 3)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[0](0,0) = (257*pow(c1_,2))/(1680.*delta_);
            matrix_N_NyNy_[0](1,0) = (2*c1_*c2_)/(105.*delta_);
            matrix_N_NyNy_[0](2,0) = (2*c1_*c3_)/(105.*delta_);
            matrix_N_NyNy_[0](3,0) = (3*c1_*(53*c1_ + 220*c2_))/(2240.*delta_);
            matrix_N_NyNy_[0](4,0) = (-3*c1_*(13*c1_ + 80*c2_))/(2240.*delta_);
            matrix_N_NyNy_[0](5,0) = (-39*c1_*(c2_ + c3_))/(2240.*delta_);
            matrix_N_NyNy_[0](6,0) = (-39*c1_*(c2_ + c3_))/(2240.*delta_);
            matrix_N_NyNy_[0](7,0) = (-3*c1_*(13*c1_ + 80*c3_))/(2240.*delta_);
            matrix_N_NyNy_[0](8,0) = (3*c1_*(53*c1_ + 220*c3_))/(2240.*delta_);
            matrix_N_NyNy_[0](9,0) = (-9*c1_*(c1_ - 10*(c2_ + c3_)))/(1120.*delta_);

            matrix_N_NyNy_[0](0,1) = matrix_N_NyNy_[0](1,0);
            matrix_N_NyNy_[0](1,1) = (5*pow(c2_,2))/(168.*delta_);
            matrix_N_NyNy_[0](2,1) = (19*c2_*c3_)/(3360.*delta_);
            matrix_N_NyNy_[0](3,1) = (-57*c1_*c2_ + 66*pow(c2_,2))/(2240.*delta_);
            matrix_N_NyNy_[0](4,1) = (3*(23*c1_ - 26*c2_)*c2_)/(2240.*delta_);
            matrix_N_NyNy_[0](5,1) = (-39*pow(c2_,2) + 69*c2_*c3_)/(2240.*delta_);
            matrix_N_NyNy_[0](6,1) = (3*c2_*(5*c2_ - 13*c3_))/(2240.*delta_);
            matrix_N_NyNy_[0](7,1) = (3*c2_*(c1_ + 2*c3_))/(448.*delta_);
            matrix_N_NyNy_[0](8,1) = (3*c2_*(17*c1_ + 22*c3_))/(2240.*delta_);
            matrix_N_NyNy_[0](9,1) = (-9*c2_*(c1_ - 4*c2_ + 2*c3_))/(1120.*delta_);

            matrix_N_NyNy_[0](0,2) = matrix_N_NyNy_[0](2,0);
            matrix_N_NyNy_[0](1,2) = matrix_N_NyNy_[0](2,1);
            matrix_N_NyNy_[0](2,2) = (5*pow(c3_,2))/(168.*delta_);
            matrix_N_NyNy_[0](3,2) = (3*(17*c1_ + 22*c2_)*c3_)/(2240.*delta_);
            matrix_N_NyNy_[0](4,2) = (3*(c1_ + 2*c2_)*c3_)/(448.*delta_);
            matrix_N_NyNy_[0](5,2) = (3*c3_*(-13*c2_ + 5*c3_))/(2240.*delta_);
            matrix_N_NyNy_[0](6,2) = (3*(23*c2_ - 13*c3_)*c3_)/(2240.*delta_);
            matrix_N_NyNy_[0](7,2) = (3*(23*c1_ - 26*c3_)*c3_)/(2240.*delta_);
            matrix_N_NyNy_[0](8,2) = (-57*c1_*c3_ + 66*pow(c3_,2))/(2240.*delta_);
            matrix_N_NyNy_[0](9,2) = (-9*(c1_ + 2*c2_ - 4*c3_)*c3_)/(1120.*delta_);

            matrix_N_NyNy_[0](0,3) = matrix_N_NyNy_[0](3,0);
            matrix_N_NyNy_[0](1,3) = matrix_N_NyNy_[0](3,1);
            matrix_N_NyNy_[0](2,3) = matrix_N_NyNy_[0](3,2);
            matrix_N_NyNy_[0](3,3) = (27*(15*pow(c1_,2) + 23*c1_*c2_ + 27*pow(c2_,2)))/(1120.*delta_);
            matrix_N_NyNy_[0](4,3) = (27*(pow(c1_,2) + 13*c1_*c2_ - 12*pow(c2_,2)))/(2240.*delta_);
            matrix_N_NyNy_[0](5,3) = (27*(-3*c2_*(c2_ + c3_) + c1_*(3*c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](6,3) = (-27*(3*c2_*(c2_ + c3_) + 2*c1_*(c2_ + 2*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](7,3) = (-27*(2*pow(c1_,2) + 12*c2_*c3_ + 3*c1_*(c2_ + 2*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](8,3) = (27*(15*pow(c1_,2) + 54*c2_*c3_ + 23*c1_*(c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](9,3) = (27*(5*pow(c1_,2) + 15*c2_*(c2_ + c3_) + c1_*(13*c2_ + 22*c3_)))/(1120.*delta_);

            matrix_N_NyNy_[0](0,4) = matrix_N_NyNy_[0](4,0);
            matrix_N_NyNy_[0](1,4) = matrix_N_NyNy_[0](4,1);
            matrix_N_NyNy_[0](2,4) = matrix_N_NyNy_[0](4,2);
            matrix_N_NyNy_[0](3,4) = matrix_N_NyNy_[0](4,3);
            matrix_N_NyNy_[0](4,4) = (27*(4*pow(c1_,2) + 8*c1_*c2_ + 15*pow(c2_,2)))/(1120.*delta_);
            matrix_N_NyNy_[0](5,4) = (27*(2*c1_*(c2_ + 2*c3_) + c2_*(5*c2_ + 4*c3_)))/(1120.*delta_);
            matrix_N_NyNy_[0](6,4) = (-27*(2*c2_*(c2_ + 2*c3_) + c1_*(c2_ + 3*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](7,4) = (-27*(pow(c1_,2) + 6*c2_*c3_ + 2*c1_*(c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](8,4) = (-27*(2*pow(c1_,2) + 12*c2_*c3_ + 3*c1_*(2*c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](9,4) = (27*(2*pow(c1_,2) - 3*c2_*(c2_ - 5*c3_) + 4*c1_*(c2_ + c3_)))/(1120.*delta_);

            matrix_N_NyNy_[0](0,5) = matrix_N_NyNy_[0](5,0);
            matrix_N_NyNy_[0](1,5) = matrix_N_NyNy_[0](5,1);
            matrix_N_NyNy_[0](2,5) = matrix_N_NyNy_[0](5,2);
            matrix_N_NyNy_[0](3,5) = matrix_N_NyNy_[0](5,3);
            matrix_N_NyNy_[0](4,5) = matrix_N_NyNy_[0](5,4);
            matrix_N_NyNy_[0](5,5) = (27*(5*pow(c2_,2) + 4*c2_*c3_ + 4*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[0](6,5) = (-27*(3*pow(c2_,2) - 2*c2_*c3_ + 3*pow(c3_,2)))/(2240.*delta_);
            matrix_N_NyNy_[0](7,5) = (-27*(2*c3_*(2*c2_ + c3_) + c1_*(3*c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](8,5) = (-27*(3*c3_*(c2_ + c3_) + 2*c1_*(2*c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](9,5) = (27*(5*c1_*c2_ - 2*pow(c2_,2) + 2*c1_*c3_ + 4*c2_*c3_ + 4*pow(c3_,2)))/(1120.*delta_);

            matrix_N_NyNy_[0](0,6) = matrix_N_NyNy_[0](6,0);
            matrix_N_NyNy_[0](1,6) = matrix_N_NyNy_[0](6,1);
            matrix_N_NyNy_[0](2,6) = matrix_N_NyNy_[0](6,2);
            matrix_N_NyNy_[0](3,6) = matrix_N_NyNy_[0](6,3);
            matrix_N_NyNy_[0](4,6) = matrix_N_NyNy_[0](6,4);
            matrix_N_NyNy_[0](5,6) = matrix_N_NyNy_[0](6,5);
            matrix_N_NyNy_[0](6,6) = (27*(4*pow(c2_,2) + 4*c2_*c3_ + 5*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[0](7,6) = (27*(2*c1_*(2*c2_ + c3_) + c3_*(4*c2_ + 5*c3_)))/(1120.*delta_);
            matrix_N_NyNy_[0](8,6) = (27*(-3*c3_*(c2_ + c3_) + c1_*(c2_ + 3*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[0](9,6) = (27*(2*c1_*c2_ + 4*pow(c2_,2) + 5*c1_*c3_ + 4*c2_*c3_ - 2*pow(c3_,2)))/(1120.*delta_);

            matrix_N_NyNy_[0](0,7) = matrix_N_NyNy_[0](7,0);
            matrix_N_NyNy_[0](1,7) = matrix_N_NyNy_[0](7,1);
            matrix_N_NyNy_[0](2,7) = matrix_N_NyNy_[0](7,2);
            matrix_N_NyNy_[0](3,7) = matrix_N_NyNy_[0](7,3);
            matrix_N_NyNy_[0](4,7) = matrix_N_NyNy_[0](7,4);
            matrix_N_NyNy_[0](5,7) = matrix_N_NyNy_[0](7,5);
            matrix_N_NyNy_[0](6,7) = matrix_N_NyNy_[0](7,6);
            matrix_N_NyNy_[0](7,7) = (27*(4*pow(c1_,2) + 8*c1_*c3_ + 15*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[0](8,7) = (27*(pow(c1_,2) + 13*c1_*c3_ - 12*pow(c3_,2)))/(2240.*delta_);
            matrix_N_NyNy_[0](9,7) = (27*(2*pow(c1_,2) + 3*(5*c2_ - c3_)*c3_ + 4*c1_*(c2_ + c3_)))/(1120.*delta_);

            matrix_N_NyNy_[0](0,8) = matrix_N_NyNy_[0](8,0);
            matrix_N_NyNy_[0](1,8) = matrix_N_NyNy_[0](8,1);
            matrix_N_NyNy_[0](2,8) = matrix_N_NyNy_[0](8,2);
            matrix_N_NyNy_[0](3,8) = matrix_N_NyNy_[0](8,3);
            matrix_N_NyNy_[0](4,8) = matrix_N_NyNy_[0](8,4);
            matrix_N_NyNy_[0](5,8) = matrix_N_NyNy_[0](8,5);
            matrix_N_NyNy_[0](6,8) = matrix_N_NyNy_[0](8,6);
            matrix_N_NyNy_[0](7,8) = matrix_N_NyNy_[0](8,7);
            matrix_N_NyNy_[0](8,8) = (27*(15*pow(c1_,2) + 23*c1_*c3_ + 27*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[0](9,8) = (27*(5*pow(c1_,2) + 15*c3_*(c2_ + c3_) + c1_*(22*c2_ + 13*c3_)))/(1120.*delta_);

            matrix_N_NyNy_[0](0,9) = matrix_N_NyNy_[0](9,0);
            matrix_N_NyNy_[0](1,9) = matrix_N_NyNy_[0](9,1);
            matrix_N_NyNy_[0](2,9) = matrix_N_NyNy_[0](9,2);
            matrix_N_NyNy_[0](3,9) = matrix_N_NyNy_[0](9,3);
            matrix_N_NyNy_[0](4,9) = matrix_N_NyNy_[0](9,4);
            matrix_N_NyNy_[0](5,9) = matrix_N_NyNy_[0](9,5);
            matrix_N_NyNy_[0](6,9) = matrix_N_NyNy_[0](9,6);
            matrix_N_NyNy_[0](7,9) = matrix_N_NyNy_[0](9,7);
            matrix_N_NyNy_[0](8,9) = matrix_N_NyNy_[0](9,8);
            matrix_N_NyNy_[0](9,9) = (81*(pow(c1_,2) + 2*c1_*(c2_ + c3_) + 3*(pow(c2_,2) + c2_*c3_ + pow(c3_,2))))/(280.*delta_);

            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[1](0,0) = (5*pow(c1_,2))/(168.*delta_);
            matrix_N_NyNy_[1](1,0) = (2*c1_*c2_)/(105.*delta_);
            matrix_N_NyNy_[1](2,0) = (19*c1_*c3_)/(3360.*delta_);
            matrix_N_NyNy_[1](3,0) = (-78*pow(c1_,2) + 69*c1_*c2_)/(2240.*delta_);
            matrix_N_NyNy_[1](4,0) = (3*c1_*(22*c1_ - 19*c2_))/(2240.*delta_);
            matrix_N_NyNy_[1](5,0) = (3*c1_*(17*c2_ + 22*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](6,0) = (3*c1_*(c2_ + 2*c3_))/(448.*delta_);
            matrix_N_NyNy_[1](7,0) = (3*c1_*(5*c1_ - 13*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](8,0) = (-39*pow(c1_,2) + 69*c1_*c3_)/(2240.*delta_);
            matrix_N_NyNy_[1](9,0) = (9*c1_*(4*c1_ - c2_ - 2*c3_))/(1120.*delta_);

            matrix_N_NyNy_[1](0,1) = matrix_N_NyNy_[1](1,0);
            matrix_N_NyNy_[1](1,1) = (257*pow(c2_,2))/(1680.*delta_);
            matrix_N_NyNy_[1](2,1) = (2*c2_*c3_)/(105.*delta_);
            matrix_N_NyNy_[1](3,1) = (-3*c2_*(80*c1_ + 13*c2_))/(2240.*delta_);
            matrix_N_NyNy_[1](4,1) = (3*c2_*(220*c1_ + 53*c2_))/(2240.*delta_);
            matrix_N_NyNy_[1](5,1) = (3*c2_*(53*c2_ + 220*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](6,1) = (-3*c2_*(13*c2_ + 80*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](7,1) = (-39*c2_*(c1_ + c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](8,1) = (-39*c2_*(c1_ + c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](9,1) = (-9*c2_*(-10*c1_ + c2_ - 10*c3_))/(1120.*delta_);

            matrix_N_NyNy_[1](0,2) = matrix_N_NyNy_[1](2,0);
            matrix_N_NyNy_[1](1,2) = matrix_N_NyNy_[1](2,1);
            matrix_N_NyNy_[1](2,2) = (5*pow(c3_,2))/(168.*delta_);
            matrix_N_NyNy_[1](3,2) = (3*(2*c1_ + c2_)*c3_)/(448.*delta_);
            matrix_N_NyNy_[1](4,2) = (3*(22*c1_ + 17*c2_)*c3_)/(2240.*delta_);
            matrix_N_NyNy_[1](5,2) = (-57*c2_*c3_ + 66*pow(c3_,2))/(2240.*delta_);
            matrix_N_NyNy_[1](6,2) = (3*(23*c2_ - 26*c3_)*c3_)/(2240.*delta_);
            matrix_N_NyNy_[1](7,2) = (3*(23*c1_ - 13*c3_)*c3_)/(2240.*delta_);
            matrix_N_NyNy_[1](8,2) = (3*c3_*(-13*c1_ + 5*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](9,2) = (-9*(2*c1_ + c2_ - 4*c3_)*c3_)/(1120.*delta_);

            matrix_N_NyNy_[1](0,3) = matrix_N_NyNy_[1](3,0);
            matrix_N_NyNy_[1](1,3) = matrix_N_NyNy_[1](3,1);
            matrix_N_NyNy_[1](2,3) = matrix_N_NyNy_[1](3,2);
            matrix_N_NyNy_[1](3,3) = (27*(15*pow(c1_,2) + 8*c1_*c2_ + 4*pow(c2_,2)))/(1120.*delta_);
            matrix_N_NyNy_[1](4,3) = (27*(-12*pow(c1_,2) + 13*c1_*c2_ + pow(c2_,2)))/(2240.*delta_);
            matrix_N_NyNy_[1](5,3) = (-27*(6*c1_*(c2_ + 2*c3_) + c2_*(2*c2_ + 3*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[1](6,3) = (-27*(c2_*(c2_ + 2*c3_) + 2*c1_*(c2_ + 3*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[1](7,3) = (-27*(2*pow(c1_,2) + 3*c2_*c3_ + c1_*(c2_ + 4*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[1](8,3) = (27*(5*pow(c1_,2) + 4*c2_*c3_ + 2*c1_*(c2_ + 2*c3_)))/(1120.*delta_);
            matrix_N_NyNy_[1](9,3) = (-27*(3*pow(c1_,2) - 2*c2_*(c2_ + 2*c3_) - c1_*(4*c2_ + 15*c3_)))/(1120.*delta_);

            matrix_N_NyNy_[1](0,4) = matrix_N_NyNy_[1](4,0);
            matrix_N_NyNy_[1](1,4) = matrix_N_NyNy_[1](4,1);
            matrix_N_NyNy_[1](2,4) = matrix_N_NyNy_[1](4,2);
            matrix_N_NyNy_[1](3,4) = matrix_N_NyNy_[1](4,3);
            matrix_N_NyNy_[1](4,4) = (27*(27*pow(c1_,2) + 23*c1_*c2_ + 15*pow(c2_,2)))/(1120.*delta_);
            matrix_N_NyNy_[1](5,4) = (27*(23*c1_*c2_ + 15*pow(c2_,2) + 54*c1_*c3_ + 23*c2_*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](6,4) = (-27*(2*c2_*(c2_ + 3*c3_) + 3*c1_*(c2_ + 4*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[1](7,4) = (-27*(3*pow(c1_,2) + 2*c1_*c2_ + 3*c1_*c3_ + 4*c2_*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](8,4) = (-27*(3*pow(c1_,2) - 3*c1_*c2_ + 3*c1_*c3_ - c2_*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](9,4) = (27*(15*pow(c1_,2) + 13*c1_*c2_ + 5*pow(c2_,2) + 15*c1_*c3_ + 22*c2_*c3_))/(1120.*delta_);

            matrix_N_NyNy_[1](0,5) = matrix_N_NyNy_[1](5,0);
            matrix_N_NyNy_[1](1,5) = matrix_N_NyNy_[1](5,1);
            matrix_N_NyNy_[1](2,5) = matrix_N_NyNy_[1](5,2);
            matrix_N_NyNy_[1](3,5) = matrix_N_NyNy_[1](5,3);
            matrix_N_NyNy_[1](4,5) = matrix_N_NyNy_[1](5,4);
            matrix_N_NyNy_[1](5,5) = (27*(15*pow(c2_,2) + 23*c2_*c3_ + 27*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[1](6,5) = (27*(pow(c2_,2) + 13*c2_*c3_ - 12*pow(c3_,2)))/(2240.*delta_);
            matrix_N_NyNy_[1](7,5) = (27*(c1_*(c2_ - 3*c3_) + 3*(c2_ - c3_)*c3_))/(2240.*delta_);
            matrix_N_NyNy_[1](8,5) = (-27*(4*c1_*c2_ + 3*c1_*c3_ + 2*c2_*c3_ + 3*pow(c3_,2)))/(2240.*delta_);
            matrix_N_NyNy_[1](9,5) = (27*(22*c1_*c2_ + 5*pow(c2_,2) + 15*c1_*c3_ + 13*c2_*c3_ + 15*pow(c3_,2)))/(1120.*delta_);

            matrix_N_NyNy_[1](0,6) = matrix_N_NyNy_[1](6,0);
            matrix_N_NyNy_[1](1,6) = matrix_N_NyNy_[1](6,1);
            matrix_N_NyNy_[1](2,6) = matrix_N_NyNy_[1](6,2);
            matrix_N_NyNy_[1](3,6) = matrix_N_NyNy_[1](6,3);
            matrix_N_NyNy_[1](4,6) = matrix_N_NyNy_[1](6,4);
            matrix_N_NyNy_[1](5,6) = matrix_N_NyNy_[1](6,5);
            matrix_N_NyNy_[1](6,6) = (27*(4*pow(c2_,2) + 8*c2_*c3_ + 15*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[1](7,6) = (27*(4*c1_*(c2_ + c3_) + c3_*(2*c2_ + 5*c3_)))/(1120.*delta_);
            matrix_N_NyNy_[1](8,6) = (-27*(c3_*(c2_ + 2*c3_) + c1_*(3*c2_ + 4*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[1](9,6) = (27*(4*c1_*c2_ + 2*pow(c2_,2) + 15*c1_*c3_ + 4*c2_*c3_ - 3*pow(c3_,2)))/(1120.*delta_);

            matrix_N_NyNy_[1](0,7) = matrix_N_NyNy_[1](7,0);
            matrix_N_NyNy_[1](1,7) = matrix_N_NyNy_[1](7,1);
            matrix_N_NyNy_[1](2,7) = matrix_N_NyNy_[1](7,2);
            matrix_N_NyNy_[1](3,7) = matrix_N_NyNy_[1](7,3);
            matrix_N_NyNy_[1](4,7) = matrix_N_NyNy_[1](7,4);
            matrix_N_NyNy_[1](5,7) = matrix_N_NyNy_[1](7,5);
            matrix_N_NyNy_[1](6,7) = matrix_N_NyNy_[1](7,6);
            matrix_N_NyNy_[1](7,7) = (27*(4*pow(c1_,2) + 4*c1_*c3_ + 5*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[1](8,7) = (-27*(3*pow(c1_,2) - 2*c1_*c3_ + 3*pow(c3_,2)))/(2240.*delta_);
            matrix_N_NyNy_[1](9,7) = (27*(4*pow(c1_,2) + (5*c2_ - 2*c3_)*c3_ + 2*c1_*(c2_ + 2*c3_)))/(1120.*delta_);

            matrix_N_NyNy_[1](0,8) = matrix_N_NyNy_[1](8,0);
            matrix_N_NyNy_[1](1,8) = matrix_N_NyNy_[1](8,1);
            matrix_N_NyNy_[1](2,8) = matrix_N_NyNy_[1](8,2);
            matrix_N_NyNy_[1](3,8) = matrix_N_NyNy_[1](8,3);
            matrix_N_NyNy_[1](4,8) = matrix_N_NyNy_[1](8,4);
            matrix_N_NyNy_[1](5,8) = matrix_N_NyNy_[1](8,5);
            matrix_N_NyNy_[1](6,8) = matrix_N_NyNy_[1](8,6);
            matrix_N_NyNy_[1](7,8) = matrix_N_NyNy_[1](8,7);
            matrix_N_NyNy_[1](8,8) = (27*(5*pow(c1_,2) + 4*c1_*c3_ + 4*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[1](9,8) = (-27*(2*pow(c1_,2) - 2*c3_*(c2_ + 2*c3_) - c1_*(5*c2_ + 4*c3_)))/(1120.*delta_);

            matrix_N_NyNy_[1](0,9) = matrix_N_NyNy_[1](9,0);
            matrix_N_NyNy_[1](1,9) = matrix_N_NyNy_[1](9,1);
            matrix_N_NyNy_[1](2,9) = matrix_N_NyNy_[1](9,2);
            matrix_N_NyNy_[1](3,9) = matrix_N_NyNy_[1](9,3);
            matrix_N_NyNy_[1](4,9) = matrix_N_NyNy_[1](9,4);
            matrix_N_NyNy_[1](5,9) = matrix_N_NyNy_[1](9,5);
            matrix_N_NyNy_[1](6,9) = matrix_N_NyNy_[1](9,6);
            matrix_N_NyNy_[1](7,9) = matrix_N_NyNy_[1](9,7);
            matrix_N_NyNy_[1](8,9) = matrix_N_NyNy_[1](9,8);
            matrix_N_NyNy_[1](9,9) = (81*(3*pow(c1_,2) + 2*c1_*c2_ + pow(c2_,2) + 3*c1_*c3_ + 2*c2_*c3_ + 3*pow(c3_,2)))/(280.*delta_);

            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NyNy_[2](0,0) = (5*pow(c1_,2))/(168.*delta_);
            matrix_N_NyNy_[2](1,0) = (19*c1_*c2_)/(3360.*delta_);
            matrix_N_NyNy_[2](2,0) = (2*c1_*c3_)/(105.*delta_);
            matrix_N_NyNy_[2](3,0) = (-39*pow(c1_,2) + 69*c1_*c2_)/(2240.*delta_);
            matrix_N_NyNy_[2](4,0) = (3*c1_*(5*c1_ - 13*c2_))/(2240.*delta_);
            matrix_N_NyNy_[2](5,0) = (3*c1_*(2*c2_ + c3_))/(448.*delta_);
            matrix_N_NyNy_[2](6,0) = (3*c1_*(22*c2_ + 17*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](7,0) = (3*c1_*(22*c1_ - 19*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](8,0) = (-78*pow(c1_,2) + 69*c1_*c3_)/(2240.*delta_);
            matrix_N_NyNy_[2](9,0) = (9*c1_*(4*c1_ - 2*c2_ - c3_))/(1120.*delta_);

            matrix_N_NyNy_[2](0,1) = matrix_N_NyNy_[2](1,0);
            matrix_N_NyNy_[2](1,1) = (5*pow(c2_,2))/(168.*delta_);
            matrix_N_NyNy_[2](2,1) = (2*c2_*c3_)/(105.*delta_);
            matrix_N_NyNy_[2](3,1) = (3*c2_*(-13*c1_ + 5*c2_))/(2240.*delta_);
            matrix_N_NyNy_[2](4,1) = (3*(23*c1_ - 13*c2_)*c2_)/(2240.*delta_);
            matrix_N_NyNy_[2](5,1) = (-78*pow(c2_,2) + 69*c2_*c3_)/(2240.*delta_);
            matrix_N_NyNy_[2](6,1) = (3*c2_*(22*c2_ - 19*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](7,1) = (3*c2_*(22*c1_ + 17*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](8,1) = (3*c2_*(2*c1_ + c3_))/(448.*delta_);
            matrix_N_NyNy_[2](9,1) = (-9*c2_*(2*c1_ - 4*c2_ + c3_))/(1120.*delta_);

            matrix_N_NyNy_[2](0,2) = matrix_N_NyNy_[2](2,0);
            matrix_N_NyNy_[2](1,2) = matrix_N_NyNy_[2](2,1);
            matrix_N_NyNy_[2](2,2) = (257*pow(c3_,2))/(1680.*delta_);
            matrix_N_NyNy_[2](3,2) = (-39*(c1_ + c2_)*c3_)/(2240.*delta_);
            matrix_N_NyNy_[2](4,2) = (-39*(c1_ + c2_)*c3_)/(2240.*delta_);
            matrix_N_NyNy_[2](5,2) = (-3*c3_*(80*c2_ + 13*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](6,2) = (3*c3_*(220*c2_ + 53*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](7,2) = (3*c3_*(220*c1_ + 53*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](8,2) = (-3*c3_*(80*c1_ + 13*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](9,2) = (9*(10*c1_ + 10*c2_ - c3_)*c3_)/(1120.*delta_);

            matrix_N_NyNy_[2](0,3) = matrix_N_NyNy_[2](3,0);
            matrix_N_NyNy_[2](1,3) = matrix_N_NyNy_[2](3,1);
            matrix_N_NyNy_[2](2,3) = matrix_N_NyNy_[2](3,2);
            matrix_N_NyNy_[2](3,3) = (27*(5*pow(c1_,2) + 4*c1_*c2_ + 4*pow(c2_,2)))/(1120.*delta_);
            matrix_N_NyNy_[2](4,3) = (-27*(3*pow(c1_,2) - 2*c1_*c2_ + 3*pow(c2_,2)))/(2240.*delta_);
            matrix_N_NyNy_[2](5,3) = (-27*(c2_*(2*c2_ + c3_) + c1_*(4*c2_ + 3*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[2](6,3) = (-27*(3*c1_*c2_ + 3*pow(c2_,2) + 4*c1_*c3_ + 2*c2_*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](7,3) = (-27*(3*pow(c1_,2) + 3*c1_*(c2_ - c3_) - c2_*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](8,3) = (27*(5*pow(c1_,2) + 4*c2_*c3_ + 2*c1_*(2*c2_ + c3_)))/(1120.*delta_);
            matrix_N_NyNy_[2](9,3) = (-27*(2*pow(c1_,2) - 2*c2_*(2*c2_ + c3_) - c1_*(4*c2_ + 5*c3_)))/(1120.*delta_);

            matrix_N_NyNy_[2](0,4) = matrix_N_NyNy_[2](4,0);
            matrix_N_NyNy_[2](1,4) = matrix_N_NyNy_[2](4,1);
            matrix_N_NyNy_[2](2,4) = matrix_N_NyNy_[2](4,2);
            matrix_N_NyNy_[2](3,4) = matrix_N_NyNy_[2](4,3);
            matrix_N_NyNy_[2](4,4) = (27*(4*pow(c1_,2) + 4*c1_*c2_ + 5*pow(c2_,2)))/(1120.*delta_);
            matrix_N_NyNy_[2](5,4) = (27*(4*c1_*(c2_ + c3_) + c2_*(5*c2_ + 2*c3_)))/(1120.*delta_);
            matrix_N_NyNy_[2](6,4) = (-27*(3*c2_*(c2_ - c3_) + c1_*(3*c2_ - c3_)))/(2240.*delta_);
            matrix_N_NyNy_[2](7,4) = (-27*(3*pow(c1_,2) + 3*c1_*c2_ + 2*c1_*c3_ + 4*c2_*c3_))/(2240.*delta_);
            matrix_N_NyNy_[2](8,4) = (-27*(2*pow(c1_,2) + 3*c2_*c3_ + c1_*(4*c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[2](9,4) = (27*(4*pow(c1_,2) + 2*c1_*(2*c2_ + c3_) + c2_*(-2*c2_ + 5*c3_)))/(1120.*delta_);

            matrix_N_NyNy_[2](0,5) = matrix_N_NyNy_[2](5,0);
            matrix_N_NyNy_[2](1,5) = matrix_N_NyNy_[2](5,1);
            matrix_N_NyNy_[2](2,5) = matrix_N_NyNy_[2](5,2);
            matrix_N_NyNy_[2](3,5) = matrix_N_NyNy_[2](5,3);
            matrix_N_NyNy_[2](4,5) = matrix_N_NyNy_[2](5,4);
            matrix_N_NyNy_[2](5,5) = (27*(15*pow(c2_,2) + 8*c2_*c3_ + 4*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[2](6,5) = (27*(-12*pow(c2_,2) + 13*c2_*c3_ + pow(c3_,2)))/(2240.*delta_);
            matrix_N_NyNy_[2](7,5) = (-27*(2*c3_*(3*c2_ + c3_) + 3*c1_*(4*c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[2](8,5) = (-27*(c3_*(2*c2_ + c3_) + 2*c1_*(3*c2_ + c3_)))/(2240.*delta_);
            matrix_N_NyNy_[2](9,5) = (27*(15*c1_*c2_ - 3*pow(c2_,2) + 4*c1_*c3_ + 4*c2_*c3_ + 2*pow(c3_,2)))/(1120.*delta_);

            matrix_N_NyNy_[2](0,6) = matrix_N_NyNy_[2](6,0);
            matrix_N_NyNy_[2](1,6) = matrix_N_NyNy_[2](6,1);
            matrix_N_NyNy_[2](2,6) = matrix_N_NyNy_[2](6,2);
            matrix_N_NyNy_[2](3,6) = matrix_N_NyNy_[2](6,3);
            matrix_N_NyNy_[2](4,6) = matrix_N_NyNy_[2](6,4);
            matrix_N_NyNy_[2](5,6) = matrix_N_NyNy_[2](6,5);
            matrix_N_NyNy_[2](6,6) = (27*(27*pow(c2_,2) + 23*c2_*c3_ + 15*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[2](7,6) = (27*(54*c1_*c2_ + 23*c1_*c3_ + 23*c2_*c3_ + 15*pow(c3_,2)))/(2240.*delta_);
            matrix_N_NyNy_[2](8,6) = (-27*(6*c1_*(2*c2_ + c3_) + c3_*(3*c2_ + 2*c3_)))/(2240.*delta_);
            matrix_N_NyNy_[2](9,6) = (27*(15*c1_*c2_ + 15*pow(c2_,2) + 22*c1_*c3_ + 13*c2_*c3_ + 5*pow(c3_,2)))/(1120.*delta_);

            matrix_N_NyNy_[2](0,7) = matrix_N_NyNy_[2](7,0);
            matrix_N_NyNy_[2](1,7) = matrix_N_NyNy_[2](7,1);
            matrix_N_NyNy_[2](2,7) = matrix_N_NyNy_[2](7,2);
            matrix_N_NyNy_[2](3,7) = matrix_N_NyNy_[2](7,3);
            matrix_N_NyNy_[2](4,7) = matrix_N_NyNy_[2](7,4);
            matrix_N_NyNy_[2](5,7) = matrix_N_NyNy_[2](7,5);
            matrix_N_NyNy_[2](6,7) = matrix_N_NyNy_[2](7,6);
            matrix_N_NyNy_[2](7,7) = (27*(27*pow(c1_,2) + 23*c1_*c3_ + 15*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[2](8,7) = (27*(-12*pow(c1_,2) + 13*c1_*c3_ + pow(c3_,2)))/(2240.*delta_);
            matrix_N_NyNy_[2](9,7) = (27*(15*pow(c1_,2) + 15*c1_*c2_ + 13*c1_*c3_ + 22*c2_*c3_ + 5*pow(c3_,2)))/(1120.*delta_);

            matrix_N_NyNy_[2](0,8) = matrix_N_NyNy_[2](8,0);
            matrix_N_NyNy_[2](1,8) = matrix_N_NyNy_[2](8,1);
            matrix_N_NyNy_[2](2,8) = matrix_N_NyNy_[2](8,2);
            matrix_N_NyNy_[2](3,8) = matrix_N_NyNy_[2](8,3);
            matrix_N_NyNy_[2](4,8) = matrix_N_NyNy_[2](8,4);
            matrix_N_NyNy_[2](5,8) = matrix_N_NyNy_[2](8,5);
            matrix_N_NyNy_[2](6,8) = matrix_N_NyNy_[2](8,6);
            matrix_N_NyNy_[2](7,8) = matrix_N_NyNy_[2](8,7);
            matrix_N_NyNy_[2](8,8) = (27*(15*pow(c1_,2) + 8*c1_*c3_ + 4*pow(c3_,2)))/(1120.*delta_);
            matrix_N_NyNy_[2](9,8) = (-27*(3*pow(c1_,2) - 2*c3_*(2*c2_ + c3_) - c1_*(15*c2_ + 4*c3_)))/(1120.*delta_);

            matrix_N_NyNy_[2](0,9) = matrix_N_NyNy_[2](9,0);
            matrix_N_NyNy_[2](1,9) = matrix_N_NyNy_[2](9,1);
            matrix_N_NyNy_[2](2,9) = matrix_N_NyNy_[2](9,2);
            matrix_N_NyNy_[2](3,9) = matrix_N_NyNy_[2](9,3);
            matrix_N_NyNy_[2](4,9) = matrix_N_NyNy_[2](9,4);
            matrix_N_NyNy_[2](5,9) = matrix_N_NyNy_[2](9,5);
            matrix_N_NyNy_[2](6,9) = matrix_N_NyNy_[2](9,6);
            matrix_N_NyNy_[2](7,9) = matrix_N_NyNy_[2](9,7);
            matrix_N_NyNy_[2](8,9) = matrix_N_NyNy_[2](9,8);
            matrix_N_NyNy_[2](9,9) = (81*(3*pow(c1_,2) + 3*c1_*c2_ + 3*pow(c2_,2) + 2*c1_*c3_ + 2*c2_*c3_ + pow(c3_,2)))/(280.*delta_);
        }
        else
            throw(Exception("FEATURE NOT INPLEMENTED","basis_function_order >= 4 not implemented"));
    }
    else
        throw(Exception("FEATURE NOT INPLEMENTED","coefficient_order_ > 1 not implemented"));
}


//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NN_matrix_analytically : Computes all N_NN matrices using
 * analytic integration.
 *
 * Analytical integration is limited to basis functions of order not greater than 2, and
 * coefficient functions of order not greater than one (i.e. constant and linear coefficients) */
//************************************************************************************************//
void SolverTriangle::Compute_N_NN_matrix_analytically()
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;

    if (coefficient_order_ == 0)
    {
        matrix_N_NN_[0].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[0](0,0) = delta_/6.0;
            matrix_N_NN_[0](1,0) = delta_/12.0;
            matrix_N_NN_[0](2,0) = delta_/12.0;

            matrix_N_NN_[0](0,1) = matrix_N_NN_[0](1,0);
            matrix_N_NN_[0](1,1) = delta_/6.0;
            matrix_N_NN_[0](2,1) = delta_/12.0;

            matrix_N_NN_[0](0,2) = matrix_N_NN_[0](2,0);
            matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
            matrix_N_NN_[0](2,2) = delta_/6.0;
        }
        else if (basis_function_order_ == 2)
        {
            // Fill matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[0](0,0) = delta_/30.0;
            matrix_N_NN_[0](1,0) = -delta_/180.0;
            matrix_N_NN_[0](2,0) = -delta_/180.0;
            matrix_N_NN_[0](3,0) = 0.0;
            matrix_N_NN_[0](4,0) = -delta_/45.0;
            matrix_N_NN_[0](5,0) = 0.0;

            matrix_N_NN_[0](0,1) = matrix_N_NN_[0](1,0);
            matrix_N_NN_[0](1,1) = delta_/30.0;
            matrix_N_NN_[0](2,1) = -delta_/180.0;
            matrix_N_NN_[0](3,1) = 0.0;
            matrix_N_NN_[0](4,1) = 0.0;
            matrix_N_NN_[0](5,1) = -delta_/45.0;

            matrix_N_NN_[0](0,2) = matrix_N_NN_[0](2,0);
            matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
            matrix_N_NN_[0](2,2) = delta_/30.0;
            matrix_N_NN_[0](3,2) = -delta_/45.0;
            matrix_N_NN_[0](4,2) = 0.0;
            matrix_N_NN_[0](5,2) = 0.0;

            matrix_N_NN_[0](0,3) = matrix_N_NN_[0](3,0);
            matrix_N_NN_[0](1,3) = matrix_N_NN_[0](3,1);
            matrix_N_NN_[0](2,3) = matrix_N_NN_[0](3,2);
            matrix_N_NN_[0](3,3) = (8*delta_)/45.0;
            matrix_N_NN_[0](4,3) = (4*delta_)/45.0;
            matrix_N_NN_[0](5,3) = (4*delta_)/45.0;

            matrix_N_NN_[0](0,4) = matrix_N_NN_[0](4,0);
            matrix_N_NN_[0](1,4) = matrix_N_NN_[0](4,1);
            matrix_N_NN_[0](2,4) = matrix_N_NN_[0](4,2);
            matrix_N_NN_[0](3,4) = matrix_N_NN_[0](4,3);
            matrix_N_NN_[0](4,4) = (8*delta_)/45.0;
            matrix_N_NN_[0](5,4) = (4*delta_)/45.0;

            matrix_N_NN_[0](0,5) = matrix_N_NN_[0](5,0);
            matrix_N_NN_[0](1,5) = matrix_N_NN_[0](5,1);
            matrix_N_NN_[0](2,5) = matrix_N_NN_[0](5,2);
            matrix_N_NN_[0](3,5) = matrix_N_NN_[0](5,3);
            matrix_N_NN_[0](4,5) = matrix_N_NN_[0](5,4);
            matrix_N_NN_[0](5,5) = (8*delta_)/45.0;
        }
        else if (basis_function_order_ == 3)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[0](0,0) = (19*delta_)/1680.;
            matrix_N_NN_[0](1,0) = (11*delta_)/6720.;
            matrix_N_NN_[0](2,0) = (11*delta_)/6720.;
            matrix_N_NN_[0](3,0) = (3*delta_)/1120.;
            matrix_N_NN_[0](4,0) = 0.0;
            matrix_N_NN_[0](5,0) = (9*delta_)/2240.;
            matrix_N_NN_[0](6,0) = (9*delta_)/2240.;
            matrix_N_NN_[0](7,0) = 0.0;
            matrix_N_NN_[0](8,0) = (3*delta_)/1120.;
            matrix_N_NN_[0](9,0) = (3*delta_)/560.;

            matrix_N_NN_[0](0,1) = matrix_N_NN_[0](1,0);
            matrix_N_NN_[0](1,1) = (19*delta_)/1680.;
            matrix_N_NN_[0](2,1) = (11*delta_)/6720.;
            matrix_N_NN_[0](3,1) = 0.0;
            matrix_N_NN_[0](4,1) = (3*delta_)/1120.;
            matrix_N_NN_[0](5,1) = (3*delta_)/1120.;
            matrix_N_NN_[0](6,1) = 0.0;
            matrix_N_NN_[0](7,1) = (9*delta_)/2240.;
            matrix_N_NN_[0](8,1) = (9*delta_)/2240.;
            matrix_N_NN_[0](9,1) = (3*delta_)/560.;

            matrix_N_NN_[0](0,2) = matrix_N_NN_[0](2,0);
            matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
            matrix_N_NN_[0](2,2) = (19*delta_)/1680.;
            matrix_N_NN_[0](3,2) = (9*delta_)/2240.;
            matrix_N_NN_[0](4,2) = (9*delta_)/2240.;
            matrix_N_NN_[0](5,2) = 0.0;
            matrix_N_NN_[0](6,2) = (3*delta_)/1120.;
            matrix_N_NN_[0](7,2) = (3*delta_)/1120.;
            matrix_N_NN_[0](8,2) = 0.0;
            matrix_N_NN_[0](9,2) = (3*delta_)/560.;

            matrix_N_NN_[0](0,3) = matrix_N_NN_[0](3,0);
            matrix_N_NN_[0](1,3) = matrix_N_NN_[0](3,1);
            matrix_N_NN_[0](2,3) = matrix_N_NN_[0](3,2);
            matrix_N_NN_[0](3,3) = (9*delta_)/112.;
            matrix_N_NN_[0](4,3) = (-9*delta_)/320.;
            matrix_N_NN_[0](5,3) = (-9*delta_)/448.;
            matrix_N_NN_[0](6,3) = (-9*delta_)/1120.;
            matrix_N_NN_[0](7,3) = (-9*delta_)/448.;
            matrix_N_NN_[0](8,3) = (9*delta_)/224.;
            matrix_N_NN_[0](9,3) = (27*delta_)/1120.;

            matrix_N_NN_[0](0,4) = matrix_N_NN_[0](4,0);
            matrix_N_NN_[0](1,4) = matrix_N_NN_[0](4,1);
            matrix_N_NN_[0](2,4) = matrix_N_NN_[0](4,2);
            matrix_N_NN_[0](3,4) = matrix_N_NN_[0](4,3);
            matrix_N_NN_[0](4,4) = (9*delta_)/112.;
            matrix_N_NN_[0](5,4) = (9*delta_)/224.;
            matrix_N_NN_[0](6,4) = (-9*delta_)/448.;
            matrix_N_NN_[0](7,4) = (-9*delta_)/1120.;
            matrix_N_NN_[0](8,4) = (-9*delta_)/448.;
            matrix_N_NN_[0](9,4) = (27*delta_)/1120.;

            matrix_N_NN_[0](0,5) = matrix_N_NN_[0](5,0);
            matrix_N_NN_[0](1,5) = matrix_N_NN_[0](5,1);
            matrix_N_NN_[0](2,5) = matrix_N_NN_[0](5,2);
            matrix_N_NN_[0](3,5) = matrix_N_NN_[0](5,3);
            matrix_N_NN_[0](4,5) = matrix_N_NN_[0](5,4);
            matrix_N_NN_[0](5,5) = (9*delta_)/112.;
            matrix_N_NN_[0](6,5) = (-9*delta_)/320.;
            matrix_N_NN_[0](7,5) = (-9*delta_)/448.;
            matrix_N_NN_[0](8,5) = (-9*delta_)/1120.;
            matrix_N_NN_[0](9,5) = (27*delta_)/1120.;

            matrix_N_NN_[0](0,6) = matrix_N_NN_[0](6,0);
            matrix_N_NN_[0](1,6) = matrix_N_NN_[0](6,1);
            matrix_N_NN_[0](2,6) = matrix_N_NN_[0](6,2);
            matrix_N_NN_[0](3,6) = matrix_N_NN_[0](6,3);
            matrix_N_NN_[0](4,6) = matrix_N_NN_[0](6,4);
            matrix_N_NN_[0](5,6) = matrix_N_NN_[0](6,5);
            matrix_N_NN_[0](6,6) = (9*delta_)/112.;
            matrix_N_NN_[0](7,6) = (9*delta_)/224.;
            matrix_N_NN_[0](8,6) = (-9*delta_)/448.;
            matrix_N_NN_[0](9,6) = (27*delta_)/1120.;

            matrix_N_NN_[0](0,7) = matrix_N_NN_[0](7,0);
            matrix_N_NN_[0](1,7) = matrix_N_NN_[0](7,1);
            matrix_N_NN_[0](2,7) = matrix_N_NN_[0](7,2);
            matrix_N_NN_[0](3,7) = matrix_N_NN_[0](7,3);
            matrix_N_NN_[0](4,7) = matrix_N_NN_[0](7,4);
            matrix_N_NN_[0](5,7) = matrix_N_NN_[0](7,5);
            matrix_N_NN_[0](6,7) = matrix_N_NN_[0](7,6);
            matrix_N_NN_[0](7,7) = (9*delta_)/112.;
            matrix_N_NN_[0](8,7) = (-9*delta_)/320.;
            matrix_N_NN_[0](9,7) = (27*delta_)/1120.;

            matrix_N_NN_[0](0,8) = matrix_N_NN_[0](8,0);
            matrix_N_NN_[0](1,8) = matrix_N_NN_[0](8,1);
            matrix_N_NN_[0](2,8) = matrix_N_NN_[0](8,2);
            matrix_N_NN_[0](3,8) = matrix_N_NN_[0](8,3);
            matrix_N_NN_[0](4,8) = matrix_N_NN_[0](8,4);
            matrix_N_NN_[0](5,8) = matrix_N_NN_[0](8,5);
            matrix_N_NN_[0](6,8) = matrix_N_NN_[0](8,6);
            matrix_N_NN_[0](7,8) = matrix_N_NN_[0](8,7);
            matrix_N_NN_[0](8,8) = (9*delta_)/112.;
            matrix_N_NN_[0](9,8) = (27*delta_)/1120.;

            matrix_N_NN_[0](0,9) = matrix_N_NN_[0](9,0);
            matrix_N_NN_[0](1,9) = matrix_N_NN_[0](9,1);
            matrix_N_NN_[0](2,9) = matrix_N_NN_[0](9,2);
            matrix_N_NN_[0](3,9) = matrix_N_NN_[0](9,3);
            matrix_N_NN_[0](4,9) = matrix_N_NN_[0](9,4);
            matrix_N_NN_[0](5,9) = matrix_N_NN_[0](9,5);
            matrix_N_NN_[0](6,9) = matrix_N_NN_[0](9,6);
            matrix_N_NN_[0](7,9) = matrix_N_NN_[0](9,7);
            matrix_N_NN_[0](8,9) = matrix_N_NN_[0](9,8);
            matrix_N_NN_[0](9,9) = (81*delta_)/280.;
        }
        else
            throw(Exception("FEATURE NOT INPLEMENTED","basis_function_order >= 4 not implemented"));
    }
    else if (coefficient_order_ == 1)
    {
        matrix_N_NN_[0].resize(num_basis_functions,num_basis_functions);
        matrix_N_NN_[1].resize(num_basis_functions,num_basis_functions);
        matrix_N_NN_[2].resize(num_basis_functions,num_basis_functions);

        if (basis_function_order_ == 1)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[0](0,0) = delta_/10.0;
            matrix_N_NN_[0](1,0) = delta_/30.0;
            matrix_N_NN_[0](2,0) = delta_/30.0;

            matrix_N_NN_[0](0,1) = matrix_N_NN_[0](1,0);
            matrix_N_NN_[0](1,1) = delta_/30.0;
            matrix_N_NN_[0](2,1) = delta_/60.0;

            matrix_N_NN_[0](0,2) = matrix_N_NN_[0](2,0);
            matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
            matrix_N_NN_[0](2,2) = delta_/30.0;


            // Fill second matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[1](0,0) = delta_/30.0;
            matrix_N_NN_[1](1,0) = delta_/30.0;
            matrix_N_NN_[1](2,0) = delta_/60.0;

            matrix_N_NN_[1](0,1) = matrix_N_NN_[1](1,0);
            matrix_N_NN_[1](1,1) = delta_/10.0;
            matrix_N_NN_[1](2,1) = delta_/30.0;

            matrix_N_NN_[1](0,2) = matrix_N_NN_[1](2,0);
            matrix_N_NN_[1](1,2) = matrix_N_NN_[1](2,1);
            matrix_N_NN_[1](2,2) = delta_/30.0;


            // Fill third matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[2](0,0) = delta_/30.0;
            matrix_N_NN_[2](1,0) = delta_/60.0;
            matrix_N_NN_[2](2,0) = delta_/30.0;

            matrix_N_NN_[2](0,1) = matrix_N_NN_[2](1,0);
            matrix_N_NN_[2](1,1) = delta_/30.0;
            matrix_N_NN_[2](2,1) = delta_/30.0;

            matrix_N_NN_[2](0,2) = matrix_N_NN_[2](2,0);
            matrix_N_NN_[2](1,2) = matrix_N_NN_[2](2,1);
            matrix_N_NN_[2](2,2) = delta_/10.0;
        }
        else if (basis_function_order_ == 2)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[0](0,0) = delta_/42.0;
            matrix_N_NN_[0](1,0) = -delta_/315.0;
            matrix_N_NN_[0](2,0) = -delta_/315.0;
            matrix_N_NN_[0](3,0) = delta_/105.0;
            matrix_N_NN_[0](4,0) = -delta_/315.0;
            matrix_N_NN_[0](5,0) = delta_/105.0;

            matrix_N_NN_[0](0,1) = matrix_N_NN_[0](1,0);
            matrix_N_NN_[0](1,1) = delta_/210.0;
            matrix_N_NN_[0](2,1) = delta_/1260.0;
            matrix_N_NN_[0](3,1) = (-2.0*delta_)/315.0;
            matrix_N_NN_[0](4,1) = -delta_/315.0;
            matrix_N_NN_[0](5,1) = -delta_/105.0;

            matrix_N_NN_[0](0,2) = matrix_N_NN_[0](2,0);
            matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
            matrix_N_NN_[0](2,2) = delta_/210.0;
            matrix_N_NN_[0](3,2) = -delta_/105.0;
            matrix_N_NN_[0](4,2) = -delta_/315.0;
            matrix_N_NN_[0](5,2) = (-2.0*delta_)/315.0;

            matrix_N_NN_[0](0,3) = matrix_N_NN_[0](3,0);
            matrix_N_NN_[0](1,3) = matrix_N_NN_[0](3,1);
            matrix_N_NN_[0](2,3) = matrix_N_NN_[0](3,2);
            matrix_N_NN_[0](3,3) = (8.0*delta_)/105.0;
            matrix_N_NN_[0](4,3) = (8.0*delta_)/315.0;
            matrix_N_NN_[0](5,3) = (4.0*delta_)/105.0;

            matrix_N_NN_[0](0,4) = matrix_N_NN_[0](4,0);
            matrix_N_NN_[0](1,4) = matrix_N_NN_[0](4,1);
            matrix_N_NN_[0](2,4) = matrix_N_NN_[0](4,2);
            matrix_N_NN_[0](3,4) = matrix_N_NN_[0](4,3);
            matrix_N_NN_[0](4,4) = (8.0*delta_)/315.0;
            matrix_N_NN_[0](5,4) = (8.0*delta_)/315.0;

            matrix_N_NN_[0](0,5) = matrix_N_NN_[0](5,0);
            matrix_N_NN_[0](1,5) = matrix_N_NN_[0](5,1);
            matrix_N_NN_[0](2,5) = matrix_N_NN_[0](5,2);
            matrix_N_NN_[0](3,5) = matrix_N_NN_[0](5,3);
            matrix_N_NN_[0](4,5) = matrix_N_NN_[0](5,4);
            matrix_N_NN_[0](5,5) = (8.0*delta_)/105.0;


            // Fill second matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[1](0,0) = delta_/210.0;
            matrix_N_NN_[1](1,0) = -delta_/315.0;
            matrix_N_NN_[1](2,0) = delta_/1260.0;
            matrix_N_NN_[1](3,0) = (-2.0*delta_)/315.0;
            matrix_N_NN_[1](4,0) = -delta_/105.0;
            matrix_N_NN_[1](5,0) = -delta_/315.0;

            matrix_N_NN_[1](0,1) = matrix_N_NN_[1](1,0);
            matrix_N_NN_[1](1,1) = delta_/42.0;
            matrix_N_NN_[1](2,1) = -delta_/315.0;
            matrix_N_NN_[1](3,1) = delta_/105.0;
            matrix_N_NN_[1](4,1) = delta_/105.0;
            matrix_N_NN_[1](5,1) = -delta_/315.0;

            matrix_N_NN_[1](0,2) = matrix_N_NN_[1](2,0);
            matrix_N_NN_[1](1,2) = matrix_N_NN_[1](2,1);
            matrix_N_NN_[1](2,2) = delta_/210.0;
            matrix_N_NN_[1](3,2) = -delta_/105.0;
            matrix_N_NN_[1](4,2) = (-2.0*delta_)/315.0;
            matrix_N_NN_[1](5,2) = -delta_/315.0;

            matrix_N_NN_[1](0,3) = matrix_N_NN_[1](3,0);
            matrix_N_NN_[1](1,3) = matrix_N_NN_[1](3,1);
            matrix_N_NN_[1](2,3) = matrix_N_NN_[1](3,2);
            matrix_N_NN_[1](3,3) = (8.0*delta_)/105.0;
            matrix_N_NN_[1](4,3) = (4.0*delta_)/105.0;
            matrix_N_NN_[1](5,3) = (8.0*delta_)/315.0;

            matrix_N_NN_[1](0,4) = matrix_N_NN_[1](4,0);
            matrix_N_NN_[1](1,4) = matrix_N_NN_[1](4,1);
            matrix_N_NN_[1](2,4) = matrix_N_NN_[1](4,2);
            matrix_N_NN_[1](3,4) = matrix_N_NN_[1](4,3);
            matrix_N_NN_[1](4,4) = (8.0*delta_)/105.0;
            matrix_N_NN_[1](5,4) = (8.0*delta_)/315.0;

            matrix_N_NN_[1](0,5) = matrix_N_NN_[1](5,0);
            matrix_N_NN_[1](1,5) = matrix_N_NN_[1](5,1);
            matrix_N_NN_[1](2,5) = matrix_N_NN_[1](5,2);
            matrix_N_NN_[1](3,5) = matrix_N_NN_[1](5,3);
            matrix_N_NN_[1](4,5) = matrix_N_NN_[1](5,4);
            matrix_N_NN_[1](5,5) = (8.0*delta_)/315.0;


            // Fill third matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[2](0,0) = delta_/210.0;
            matrix_N_NN_[2](1,0) = delta_/1260.0;
            matrix_N_NN_[2](2,0) = -delta_/315.0;
            matrix_N_NN_[2](3,0) = -delta_/315.0;
            matrix_N_NN_[2](4,0) = -delta_/105.0;
            matrix_N_NN_[2](5,0) = (-2.0*delta_)/315.0;

            matrix_N_NN_[2](0,1) = matrix_N_NN_[2](1,0);
            matrix_N_NN_[2](1,1) = delta_/210.0;
            matrix_N_NN_[2](2,1) = -delta_/315.0;
            matrix_N_NN_[2](3,1) = -delta_/315.0;
            matrix_N_NN_[2](4,1) = (-2.0*delta_)/315.0;
            matrix_N_NN_[2](5,1) = -delta_/105.0;

            matrix_N_NN_[2](0,2) = matrix_N_NN_[2](2,0);
            matrix_N_NN_[2](1,2) = matrix_N_NN_[2](2,1);
            matrix_N_NN_[2](2,2) = delta_/42.0;
            matrix_N_NN_[2](3,2) = -delta_/315.0;
            matrix_N_NN_[2](4,2) = delta_/105.0;
            matrix_N_NN_[2](5,2) = delta_/105.0;

            matrix_N_NN_[2](0,3) = matrix_N_NN_[2](3,0);
            matrix_N_NN_[2](1,3) = matrix_N_NN_[2](3,1);
            matrix_N_NN_[2](2,3) = matrix_N_NN_[2](3,2);
            matrix_N_NN_[2](3,3) = (8.0*delta_)/315.0;
            matrix_N_NN_[2](4,3) = (8.0*delta_)/315.0;
            matrix_N_NN_[2](5,3) = (8.0*delta_)/315.0;

            matrix_N_NN_[2](0,4) = matrix_N_NN_[2](4,0);
            matrix_N_NN_[2](1,4) = matrix_N_NN_[2](4,1);
            matrix_N_NN_[2](2,4) = matrix_N_NN_[2](4,2);
            matrix_N_NN_[2](3,4) = matrix_N_NN_[2](4,3);
            matrix_N_NN_[2](4,4) = (8.0*delta_)/105.0;
            matrix_N_NN_[2](5,4) = (4.0*delta_)/105.0;

            matrix_N_NN_[2](0,5) = matrix_N_NN_[2](5,0);
            matrix_N_NN_[2](1,5) = matrix_N_NN_[2](5,1);
            matrix_N_NN_[2](2,5) = matrix_N_NN_[2](5,2);
            matrix_N_NN_[2](3,5) = matrix_N_NN_[2](5,3);
            matrix_N_NN_[2](4,5) = matrix_N_NN_[2](5,4);
            matrix_N_NN_[2](5,5) = (8.0*delta_)/105.0;
        }
        else if (basis_function_order_ == 3)
        {
            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[0](0,0) = delta_/112.;
            matrix_N_NN_[0](1,0) = delta_/1344.;
            matrix_N_NN_[0](2,0) = delta_/1344.;
            matrix_N_NN_[0](3,0) = (3*delta_)/560.;
            matrix_N_NN_[0](4,0) = (-3*delta_)/1120.;
            matrix_N_NN_[0](5,0) = delta_/2240.;
            matrix_N_NN_[0](6,0) = delta_/2240.;
            matrix_N_NN_[0](7,0) = (-3*delta_)/1120.;
            matrix_N_NN_[0](8,0) = (3*delta_)/560.;
            matrix_N_NN_[0](9,0) = 0.0;

            matrix_N_NN_[0](0,1) = matrix_N_NN_[0](1,0);
            matrix_N_NN_[0](1,1) = delta_/840.;
            matrix_N_NN_[0](2,1) = delta_/6720.;
            matrix_N_NN_[0](3,1) = delta_/448.;
            matrix_N_NN_[0](4,1) = -delta_/560.;
            matrix_N_NN_[0](5,1) = -delta_/1120.;
            matrix_N_NN_[0](6,1) = delta_/2240.;
            matrix_N_NN_[0](7,1) = delta_/2240.;
            matrix_N_NN_[0](8,1) = delta_/320.;
            matrix_N_NN_[0](9,1) = (3*delta_)/1120.;

            matrix_N_NN_[0](0,2) = matrix_N_NN_[0](2,0);
            matrix_N_NN_[0](1,2) = matrix_N_NN_[0](2,1);
            matrix_N_NN_[0](2,2) = delta_/840.;
            matrix_N_NN_[0](3,2) = delta_/320.;
            matrix_N_NN_[0](4,2) = delta_/2240.;
            matrix_N_NN_[0](5,2) = delta_/2240.;
            matrix_N_NN_[0](6,2) = -delta_/1120.;
            matrix_N_NN_[0](7,2) = -delta_/560.;
            matrix_N_NN_[0](8,2) = delta_/448.;
            matrix_N_NN_[0](9,2) = (3*delta_)/1120.;

            matrix_N_NN_[0](0,3) = matrix_N_NN_[0](3,0);
            matrix_N_NN_[0](1,3) = matrix_N_NN_[0](3,1);
            matrix_N_NN_[0](2,3) = matrix_N_NN_[0](3,2);
            matrix_N_NN_[0](3,3) = (27*delta_)/560.;
            matrix_N_NN_[0](4,3) = (-27*delta_)/2240.;
            matrix_N_NN_[0](5,3) = (-9*delta_)/2240.;
            matrix_N_NN_[0](6,3) = (-9*delta_)/2240.;
            matrix_N_NN_[0](7,3) = (-27*delta_)/2240.;
            matrix_N_NN_[0](8,3) = (27*delta_)/1120.;
            matrix_N_NN_[0](9,3) = (27*delta_)/1120.;

            matrix_N_NN_[0](0,4) = matrix_N_NN_[0](4,0);
            matrix_N_NN_[0](1,4) = matrix_N_NN_[0](4,1);
            matrix_N_NN_[0](2,4) = matrix_N_NN_[0](4,2);
            matrix_N_NN_[0](3,4) = matrix_N_NN_[0](4,3);
            matrix_N_NN_[0](4,4) = (27*delta_)/1120.;
            matrix_N_NN_[0](5,4) = (9*delta_)/1120.;
            matrix_N_NN_[0](6,4) = (-9*delta_)/2240.;
            matrix_N_NN_[0](7,4) = 0.0;
            matrix_N_NN_[0](8,4) = (-27*delta_)/2240.;
            matrix_N_NN_[0](9,4) = 0.0;

            matrix_N_NN_[0](0,5) = matrix_N_NN_[0](5,0);
            matrix_N_NN_[0](1,5) = matrix_N_NN_[0](5,1);
            matrix_N_NN_[0](2,5) = matrix_N_NN_[0](5,2);
            matrix_N_NN_[0](3,5) = matrix_N_NN_[0](5,3);
            matrix_N_NN_[0](4,5) = matrix_N_NN_[0](5,4);
            matrix_N_NN_[0](5,5) = (9*delta_)/1120.;
            matrix_N_NN_[0](6,5) = (-9*delta_)/2240.;
            matrix_N_NN_[0](7,5) = (-9*delta_)/2240.;
            matrix_N_NN_[0](8,5) = (-9*delta_)/2240.;
            matrix_N_NN_[0](9,5) = 0.0;

            matrix_N_NN_[0](0,6) = matrix_N_NN_[0](6,0);
            matrix_N_NN_[0](1,6) = matrix_N_NN_[0](6,1);
            matrix_N_NN_[0](2,6) = matrix_N_NN_[0](6,2);
            matrix_N_NN_[0](3,6) = matrix_N_NN_[0](6,3);
            matrix_N_NN_[0](4,6) = matrix_N_NN_[0](6,4);
            matrix_N_NN_[0](5,6) = matrix_N_NN_[0](6,5);
            matrix_N_NN_[0](6,6) = (9*delta_)/1120.;
            matrix_N_NN_[0](7,6) = (9*delta_)/1120.;
            matrix_N_NN_[0](8,6) = (-9*delta_)/2240.;
            matrix_N_NN_[0](9,6) = 0.0;

            matrix_N_NN_[0](0,7) = matrix_N_NN_[0](7,0);
            matrix_N_NN_[0](1,7) = matrix_N_NN_[0](7,1);
            matrix_N_NN_[0](2,7) = matrix_N_NN_[0](7,2);
            matrix_N_NN_[0](3,7) = matrix_N_NN_[0](7,3);
            matrix_N_NN_[0](4,7) = matrix_N_NN_[0](7,4);
            matrix_N_NN_[0](5,7) = matrix_N_NN_[0](7,5);
            matrix_N_NN_[0](6,7) = matrix_N_NN_[0](7,6);
            matrix_N_NN_[0](7,7) = (27*delta_)/1120.;
            matrix_N_NN_[0](8,7) = (-27*delta_)/2240.;
            matrix_N_NN_[0](9,7) = 0.0;

            matrix_N_NN_[0](0,8) = matrix_N_NN_[0](8,0);
            matrix_N_NN_[0](1,8) = matrix_N_NN_[0](8,1);
            matrix_N_NN_[0](2,8) = matrix_N_NN_[0](8,2);
            matrix_N_NN_[0](3,8) = matrix_N_NN_[0](8,3);
            matrix_N_NN_[0](4,8) = matrix_N_NN_[0](8,4);
            matrix_N_NN_[0](5,8) = matrix_N_NN_[0](8,5);
            matrix_N_NN_[0](6,8) = matrix_N_NN_[0](8,6);
            matrix_N_NN_[0](7,8) = matrix_N_NN_[0](8,7);
            matrix_N_NN_[0](8,8) = (27*delta_)/560.;
            matrix_N_NN_[0](9,8) = (27*delta_)/1120.;

            matrix_N_NN_[0](0,9) = matrix_N_NN_[0](9,0);
            matrix_N_NN_[0](1,9) = matrix_N_NN_[0](9,1);
            matrix_N_NN_[0](2,9) = matrix_N_NN_[0](9,2);
            matrix_N_NN_[0](3,9) = matrix_N_NN_[0](9,3);
            matrix_N_NN_[0](4,9) = matrix_N_NN_[0](9,4);
            matrix_N_NN_[0](5,9) = matrix_N_NN_[0](9,5);
            matrix_N_NN_[0](6,9) = matrix_N_NN_[0](9,6);
            matrix_N_NN_[0](7,9) = matrix_N_NN_[0](9,7);
            matrix_N_NN_[0](8,9) = matrix_N_NN_[0](9,8);
            matrix_N_NN_[0](9,9) = (27*delta_)/280.;

            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[1](0,0) = delta_/840.;
            matrix_N_NN_[1](1,0) = delta_/1344.;
            matrix_N_NN_[1](2,0) = delta_/6720.;
            matrix_N_NN_[1](3,0) = -delta_/560.;
            matrix_N_NN_[1](4,0) = delta_/448.;
            matrix_N_NN_[1](5,0) = delta_/320.;
            matrix_N_NN_[1](6,0) = delta_/2240.;
            matrix_N_NN_[1](7,0) = delta_/2240.;
            matrix_N_NN_[1](8,0) = -delta_/1120.;
            matrix_N_NN_[1](9,0) = (3*delta_)/1120.;

            matrix_N_NN_[1](0,1) = matrix_N_NN_[1](1,0);
            matrix_N_NN_[1](1,1) = delta_/112.;
            matrix_N_NN_[1](2,1) = delta_/1344.;
            matrix_N_NN_[1](3,1) = (-3*delta_)/1120.;
            matrix_N_NN_[1](4,1) = (3*delta_)/560.;
            matrix_N_NN_[1](5,1) = (3*delta_)/560.;
            matrix_N_NN_[1](6,1) = (-3*delta_)/1120.;
            matrix_N_NN_[1](7,1) = delta_/2240.;
            matrix_N_NN_[1](8,1) = delta_/2240.;
            matrix_N_NN_[1](9,1) = 0.0;

            matrix_N_NN_[1](0,2) = matrix_N_NN_[1](2,0);
            matrix_N_NN_[1](1,2) = matrix_N_NN_[1](2,1);
            matrix_N_NN_[1](2,2) = delta_/840.;
            matrix_N_NN_[1](3,2) = delta_/2240.;
            matrix_N_NN_[1](4,2) = delta_/320.;
            matrix_N_NN_[1](5,2) = delta_/448.;
            matrix_N_NN_[1](6,2) = -delta_/560.;
            matrix_N_NN_[1](7,2) = -delta_/1120.;
            matrix_N_NN_[1](8,2) = delta_/2240.;
            matrix_N_NN_[1](9,2) = (3*delta_)/1120.;

            matrix_N_NN_[1](0,3) = matrix_N_NN_[1](3,0);
            matrix_N_NN_[1](1,3) = matrix_N_NN_[1](3,1);
            matrix_N_NN_[1](2,3) = matrix_N_NN_[1](3,2);
            matrix_N_NN_[1](3,3) = (27*delta_)/1120.;
            matrix_N_NN_[1](4,3) = (-27*delta_)/2240.;
            matrix_N_NN_[1](5,3) = (-27*delta_)/2240.;
            matrix_N_NN_[1](6,3) = 0.0;
            matrix_N_NN_[1](7,3) = (-9*delta_)/2240.;
            matrix_N_NN_[1](8,3) = (9*delta_)/1120.;
            matrix_N_NN_[1](9,3) = 0.0;

            matrix_N_NN_[1](0,4) = matrix_N_NN_[1](4,0);
            matrix_N_NN_[1](1,4) = matrix_N_NN_[1](4,1);
            matrix_N_NN_[1](2,4) = matrix_N_NN_[1](4,2);
            matrix_N_NN_[1](3,4) = matrix_N_NN_[1](4,3);
            matrix_N_NN_[1](4,4) = (27*delta_)/560.;
            matrix_N_NN_[1](5,4) = (27*delta_)/1120.;
            matrix_N_NN_[1](6,4) = (-27*delta_)/2240.;
            matrix_N_NN_[1](7,4) = (-9*delta_)/2240.;
            matrix_N_NN_[1](8,4) = (-9*delta_)/2240.;
            matrix_N_NN_[1](9,4) = (27*delta_)/1120.;

            matrix_N_NN_[1](0,5) = matrix_N_NN_[1](5,0);
            matrix_N_NN_[1](1,5) = matrix_N_NN_[1](5,1);
            matrix_N_NN_[1](2,5) = matrix_N_NN_[1](5,2);
            matrix_N_NN_[1](3,5) = matrix_N_NN_[1](5,3);
            matrix_N_NN_[1](4,5) = matrix_N_NN_[1](5,4);
            matrix_N_NN_[1](5,5) = (27*delta_)/560.;
            matrix_N_NN_[1](6,5) = (-27*delta_)/2240.;
            matrix_N_NN_[1](7,5) = (-9*delta_)/2240.;
            matrix_N_NN_[1](8,5) = (-9*delta_)/2240.;
            matrix_N_NN_[1](9,5) = (27*delta_)/1120.;

            matrix_N_NN_[1](0,6) = matrix_N_NN_[1](6,0);
            matrix_N_NN_[1](1,6) = matrix_N_NN_[1](6,1);
            matrix_N_NN_[1](2,6) = matrix_N_NN_[1](6,2);
            matrix_N_NN_[1](3,6) = matrix_N_NN_[1](6,3);
            matrix_N_NN_[1](4,6) = matrix_N_NN_[1](6,4);
            matrix_N_NN_[1](5,6) = matrix_N_NN_[1](6,5);
            matrix_N_NN_[1](6,6) = (27*delta_)/1120.;
            matrix_N_NN_[1](7,6) = (9*delta_)/1120.;
            matrix_N_NN_[1](8,6) = (-9*delta_)/2240.;
            matrix_N_NN_[1](9,6) = 0.0;

            matrix_N_NN_[1](0,7) = matrix_N_NN_[1](7,0);
            matrix_N_NN_[1](1,7) = matrix_N_NN_[1](7,1);
            matrix_N_NN_[1](2,7) = matrix_N_NN_[1](7,2);
            matrix_N_NN_[1](3,7) = matrix_N_NN_[1](7,3);
            matrix_N_NN_[1](4,7) = matrix_N_NN_[1](7,4);
            matrix_N_NN_[1](5,7) = matrix_N_NN_[1](7,5);
            matrix_N_NN_[1](6,7) = matrix_N_NN_[1](7,6);
            matrix_N_NN_[1](7,7) = (9*delta_)/1120.;
            matrix_N_NN_[1](8,7) = (-9*delta_)/2240.;
            matrix_N_NN_[1](9,7) = 0.0;

            matrix_N_NN_[1](0,8) = matrix_N_NN_[1](8,0);
            matrix_N_NN_[1](1,8) = matrix_N_NN_[1](8,1);
            matrix_N_NN_[1](2,8) = matrix_N_NN_[1](8,2);
            matrix_N_NN_[1](3,8) = matrix_N_NN_[1](8,3);
            matrix_N_NN_[1](4,8) = matrix_N_NN_[1](8,4);
            matrix_N_NN_[1](5,8) = matrix_N_NN_[1](8,5);
            matrix_N_NN_[1](6,8) = matrix_N_NN_[1](8,6);
            matrix_N_NN_[1](7,8) = matrix_N_NN_[1](8,7);
            matrix_N_NN_[1](8,8) = (9*delta_)/1120.;
            matrix_N_NN_[1](9,8) = 0.0;

            matrix_N_NN_[1](0,9) = matrix_N_NN_[1](9,0);
            matrix_N_NN_[1](1,9) = matrix_N_NN_[1](9,1);
            matrix_N_NN_[1](2,9) = matrix_N_NN_[1](9,2);
            matrix_N_NN_[1](3,9) = matrix_N_NN_[1](9,3);
            matrix_N_NN_[1](4,9) = matrix_N_NN_[1](9,4);
            matrix_N_NN_[1](5,9) = matrix_N_NN_[1](9,5);
            matrix_N_NN_[1](6,9) = matrix_N_NN_[1](9,6);
            matrix_N_NN_[1](7,9) = matrix_N_NN_[1](9,7);
            matrix_N_NN_[1](8,9) = matrix_N_NN_[1](9,8);
            matrix_N_NN_[1](9,9) = (27*delta_)/280.;

            // Fill first matrix column-wise (Matrix is simmetric):
            matrix_N_NN_[2](0,0) = delta_/840.;
            matrix_N_NN_[2](1,0) = delta_/6720.;
            matrix_N_NN_[2](2,0) = delta_/1344.;
            matrix_N_NN_[2](3,0) = -delta_/1120.;
            matrix_N_NN_[2](4,0) = delta_/2240.;
            matrix_N_NN_[2](5,0) = delta_/2240.;
            matrix_N_NN_[2](6,0) = delta_/320.;
            matrix_N_NN_[2](7,0) = delta_/448.;
            matrix_N_NN_[2](8,0) = -delta_/560.;
            matrix_N_NN_[2](9,0) = (3*delta_)/1120.;

            matrix_N_NN_[2](0,1) = matrix_N_NN_[2](1,0);
            matrix_N_NN_[2](1,1) = delta_/840.;
            matrix_N_NN_[2](2,1) = delta_/1344.;
            matrix_N_NN_[2](3,1) = delta_/2240.;
            matrix_N_NN_[2](4,1) = -delta_/1120.;
            matrix_N_NN_[2](5,1) = -delta_/560.;
            matrix_N_NN_[2](6,1) = delta_/448.;
            matrix_N_NN_[2](7,1) = delta_/320.;
            matrix_N_NN_[2](8,1) = delta_/2240.;
            matrix_N_NN_[2](9,1) = (3*delta_)/1120.;

            matrix_N_NN_[2](0,2) = matrix_N_NN_[2](2,0);
            matrix_N_NN_[2](1,2) = matrix_N_NN_[2](2,1);
            matrix_N_NN_[2](2,2) = delta_/112.;
            matrix_N_NN_[2](3,2) = delta_/2240.;
            matrix_N_NN_[2](4,2) = delta_/2240.;
            matrix_N_NN_[2](5,2) = (-3*delta_)/1120.;
            matrix_N_NN_[2](6,2) = (3*delta_)/560.;
            matrix_N_NN_[2](7,2) = (3*delta_)/560.;
            matrix_N_NN_[2](8,2) = (-3*delta_)/1120.;
            matrix_N_NN_[2](9,2) = 0.0;

            matrix_N_NN_[2](0,3) = matrix_N_NN_[2](3,0);
            matrix_N_NN_[2](1,3) = matrix_N_NN_[2](3,1);
            matrix_N_NN_[2](2,3) = matrix_N_NN_[2](3,2);
            matrix_N_NN_[2](3,3) = (9*delta_)/1120.;
            matrix_N_NN_[2](4,3) = (-9*delta_)/2240.;
            matrix_N_NN_[2](5,3) = (-9*delta_)/2240.;
            matrix_N_NN_[2](6,3) = (-9*delta_)/2240.;
            matrix_N_NN_[2](7,3) = (-9*delta_)/2240.;
            matrix_N_NN_[2](8,3) = (9*delta_)/1120.;
            matrix_N_NN_[2](9,3) = 0.0;

            matrix_N_NN_[2](0,4) = matrix_N_NN_[2](4,0);
            matrix_N_NN_[2](1,4) = matrix_N_NN_[2](4,1);
            matrix_N_NN_[2](2,4) = matrix_N_NN_[2](4,2);
            matrix_N_NN_[2](3,4) = matrix_N_NN_[2](4,3);
            matrix_N_NN_[2](4,4) = (9*delta_)/1120.;
            matrix_N_NN_[2](5,4) = (9*delta_)/1120.;
            matrix_N_NN_[2](6,4) = (-9*delta_)/2240.;
            matrix_N_NN_[2](7,4) = (-9*delta_)/2240.;
            matrix_N_NN_[2](8,4) = (-9*delta_)/2240.;
            matrix_N_NN_[2](9,4) = 0.0;

            matrix_N_NN_[2](0,5) = matrix_N_NN_[2](5,0);
            matrix_N_NN_[2](1,5) = matrix_N_NN_[2](5,1);
            matrix_N_NN_[2](2,5) = matrix_N_NN_[2](5,2);
            matrix_N_NN_[2](3,5) = matrix_N_NN_[2](5,3);
            matrix_N_NN_[2](4,5) = matrix_N_NN_[2](5,4);
            matrix_N_NN_[2](5,5) = (27*delta_)/1120.;
            matrix_N_NN_[2](6,5) = (-27*delta_)/2240.;
            matrix_N_NN_[2](7,5) = (-27*delta_)/2240.;
            matrix_N_NN_[2](8,5) = 0.0;
            matrix_N_NN_[2](9,5) = 0.0;

            matrix_N_NN_[2](0,6) = matrix_N_NN_[2](6,0);
            matrix_N_NN_[2](1,6) = matrix_N_NN_[2](6,1);
            matrix_N_NN_[2](2,6) = matrix_N_NN_[2](6,2);
            matrix_N_NN_[2](3,6) = matrix_N_NN_[2](6,3);
            matrix_N_NN_[2](4,6) = matrix_N_NN_[2](6,4);
            matrix_N_NN_[2](5,6) = matrix_N_NN_[2](6,5);
            matrix_N_NN_[2](6,6) = (27*delta_)/560.;
            matrix_N_NN_[2](7,6) = (27*delta_)/1120.;
            matrix_N_NN_[2](8,6) = (-27*delta_)/2240.;
            matrix_N_NN_[2](9,6) = (27*delta_)/1120.;

            matrix_N_NN_[2](0,7) = matrix_N_NN_[2](7,0);
            matrix_N_NN_[2](1,7) = matrix_N_NN_[2](7,1);
            matrix_N_NN_[2](2,7) = matrix_N_NN_[2](7,2);
            matrix_N_NN_[2](3,7) = matrix_N_NN_[2](7,3);
            matrix_N_NN_[2](4,7) = matrix_N_NN_[2](7,4);
            matrix_N_NN_[2](5,7) = matrix_N_NN_[2](7,5);
            matrix_N_NN_[2](6,7) = matrix_N_NN_[2](7,6);
            matrix_N_NN_[2](7,7) = (27*delta_)/560.;
            matrix_N_NN_[2](8,7) = (-27*delta_)/2240.;
            matrix_N_NN_[2](9,7) = (27*delta_)/1120.;

            matrix_N_NN_[2](0,8) = matrix_N_NN_[2](8,0);
            matrix_N_NN_[2](1,8) = matrix_N_NN_[2](8,1);
            matrix_N_NN_[2](2,8) = matrix_N_NN_[2](8,2);
            matrix_N_NN_[2](3,8) = matrix_N_NN_[2](8,3);
            matrix_N_NN_[2](4,8) = matrix_N_NN_[2](8,4);
            matrix_N_NN_[2](5,8) = matrix_N_NN_[2](8,5);
            matrix_N_NN_[2](6,8) = matrix_N_NN_[2](8,6);
            matrix_N_NN_[2](7,8) = matrix_N_NN_[2](8,7);
            matrix_N_NN_[2](8,8) = (27*delta_)/1120.;
            matrix_N_NN_[2](9,8) = 0.0;

            matrix_N_NN_[2](0,9) = matrix_N_NN_[2](9,0);
            matrix_N_NN_[2](1,9) = matrix_N_NN_[2](9,1);
            matrix_N_NN_[2](2,9) = matrix_N_NN_[2](9,2);
            matrix_N_NN_[2](3,9) = matrix_N_NN_[2](9,3);
            matrix_N_NN_[2](4,9) = matrix_N_NN_[2](9,4);
            matrix_N_NN_[2](5,9) = matrix_N_NN_[2](9,5);
            matrix_N_NN_[2](6,9) = matrix_N_NN_[2](9,6);
            matrix_N_NN_[2](7,9) = matrix_N_NN_[2](9,7);
            matrix_N_NN_[2](8,9) = matrix_N_NN_[2](9,8);
            matrix_N_NN_[2](9,9) = (27*delta_)/280.;
        }
        else
            throw(Exception("FEATURE NOT INPLEMENTED","basis_function_order >= 4 not implemented"));
    }
    else
        throw(Exception("FEATURE NOT INPLEMENTED","coefficient_order_ > 1 not implemented"));
}


//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NxNx_matrix_numerically : Computes a single N_NxNx matrix
 * for the given coefficient function, using numerical integration.
 *
 * As far as this function concerns, there is no limit on the polynomial order of the basis
 * functions or the coefficient functions. There could be, however, a limit due to quadrature
 * rules or other functions used.
 * @param [in] coefficient_index : index of the coefficient function */
//************************************************************************************************//
void SolverTriangle::Compute_N_NxNx_matrix_numerically(const cemINT& coefficient_index)
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;
    cemINT matrix_index = 0;
    if (coefficient_order_ > 0)
        matrix_index = coefficient_index;

    matrix_N_NxNx_[matrix_index].resize(num_basis_functions,num_basis_functions);
    for (cemINT j=0; j<num_basis_functions; ++j)
    {
        for (cemINT i=0; i<num_basis_functions; ++i)
            matrix_N_NxNx_[matrix_index](i,j) = Compute_N_NxNx_matrix_entry(coefficient_index,i,j);
    }
}


//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NyNy_matrix_numerically :  Computes a single N_NyNy matrix
 * for the given coefficient function, using numerical integration.
 *
 * As far as this function concerns, there is no limit on the polynomial order of the basis
 * functions or the coefficient functions. There could be, however, a limit due to quadrature
 * rules or other functions used.
 * @param [in] coefficient_index : index of the coefficient function */
//************************************************************************************************//
void SolverTriangle::Compute_N_NyNy_matrix_numerically(const cemINT& coefficient_index)
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;
    cemINT matrix_index = 0;
    if (coefficient_order_ > 0)
        matrix_index = coefficient_index;

    matrix_N_NyNy_[matrix_index].resize(num_basis_functions,num_basis_functions);
    for (cemINT j=0; j<num_basis_functions; ++j)
    {
        for (cemINT i=0; i<num_basis_functions; ++i)
            matrix_N_NyNy_[matrix_index](i,j) = Compute_N_NyNy_matrix_entry(coefficient_index,i,j);
    }
}


//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NN_matrix_numerically :  Computes a single N_NN matrix
 * for the given coefficient function, using numerical integration.
 *
 * As far as this function concerns, there is no limit on the polynomial order of the basis
 * functions or the coefficient functions. There could be, however, a limit due to quadrature
 * rules or other functions used.
 * @param [in] coefficient_index : index of the coefficient function */
//************************************************************************************************//
void SolverTriangle::Compute_N_NN_matrix_numerically(const cemINT& coefficient_index)
{
    // Pre-compute common terms if they haven't been computed yet:
    setUpGeometry();

    cemINT num_basis_functions = (basis_function_order_+1)*(basis_function_order_+2)/2;
    cemINT matrix_index = 0;
    if (coefficient_order_ > 0)
        matrix_index = coefficient_index;

    matrix_N_NN_[matrix_index].resize(num_basis_functions,num_basis_functions);
    for (cemINT j=0; j<num_basis_functions; ++j)
    {
        for (cemINT i=0; i<num_basis_functions; ++i)
            matrix_N_NN_[matrix_index](i,j) = Compute_N_NN_matrix_entry(coefficient_index,i,j);
    }
}


//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NxNx_matrix_entry : Computes single matrix entry using
 * numerical integration.
 *
 * Computes \f[
 *  \iint\limits_{\Omega^{e}} \alpha_{k}^{e}\frac{\partial N_{i}^{e}}{\partial x}
 * \frac{\partial N_{j}^{e}}{\partial x}dxdy \f] using
 * quadrature rules. \f$ \beta_{k}^{e} \f$ is the \f$ k \f$-th coefficient function, and
 * \f$ N_{i}^{e} \f$ and \f$ N_{j}^{e} \f$ are the \f$ i \f$-th and \f$ j \f$-th basis functions
 * respectively.
 * @param [in] coefficient_index : index \f$ k \f$ of the coefficient function.
 * @param [in] test_function_index : index \f$ i \f$ of the test basis function.
 * @param [in] source_function_index : index \f$ j \f$ of the source basis function.
 * @return \f$ \iint\limits_{\Omega^{e}} \alpha_{k}^{e}\frac{\partial N_{i}^{e}}{\partial x}
 * \frac{\partial N_{j}^{e}}{\partial x}dxdy \f$ */
//************************************************************************************************//
cemDOUBLE SolverTriangle::Compute_N_NxNx_matrix_entry(const cemINT& coefficient_index,
                                                      const cemINT& test_function_index,
                                                      const cemINT& source_function_index) const
{
    // Get quadrature:
    cem_core::TriQuadrature quadrature;
    cemINT num_points = quadrature.getNumPointsForPolyOrder(coefficient_order_ + 2*basis_function_order_);

    const std::vector<cemDOUBLE>& ksi_points = quadrature.getKsiCoordinates(num_points);
    const std::vector<cemDOUBLE>& eta_points = quadrature.getEtaCoordinates(num_points);
    const std::vector<cemDOUBLE>& weights = quadrature.getWeights(num_points);

    // Prepare to evaluate:
    TriShapeFunction shape_function(basis_function_order_);
    std::vector<cemDOUBLE> test_ksi_deriv,test_eta_deriv;
    std::vector<cemDOUBLE> source_ksi_deriv,source_eta_deriv;
    std::vector<cemDOUBLE> coefficient_function;
    cemINT index_i,index_j,index_k;

    // Evaluate Test function:
    GetShapeFunctionIndices(basis_function_order_,test_function_index,index_i,index_j,index_k);
    test_ksi_deriv = shape_function.EvaluateKsiDeriv(index_i,index_j,index_k,ksi_points,eta_points);
    test_eta_deriv = shape_function.EvaluateEtaDeriv(index_i,index_j,index_k,ksi_points,eta_points);

    // Evaluate Source function:
    GetShapeFunctionIndices(basis_function_order_,source_function_index,index_i,index_j,index_k);
    source_ksi_deriv = shape_function.EvaluateKsiDeriv(index_i,index_j,index_k,ksi_points,eta_points);
    source_eta_deriv = shape_function.EvaluateEtaDeriv(index_i,index_j,index_k,ksi_points,eta_points);

    // Evaluate Coefficient function:
    shape_function.set_order(coefficient_order_);
    GetShapeFunctionIndices(coefficient_order_,coefficient_index,index_i,index_j,index_k);
    coefficient_function = shape_function.Evaluate(index_i,index_j,index_k,ksi_points,eta_points);

    // Add everything up:
    cemDOUBLE integral = 0;
    cemDOUBLE term = 0;
    cemDOUBLE dksi_dx = inverse_jacobian_matrix_(0,0);
    cemDOUBLE deta_dx = inverse_jacobian_matrix_(0,1);
    for (cemINT i=0; i<num_points; ++i)
    {
        term = coefficient_function[i];
        term *= (dksi_dx*test_ksi_deriv[i] + deta_dx*test_eta_deriv[i]);
        term *= (dksi_dx*source_ksi_deriv[i] + deta_dx*source_eta_deriv[i]);
        term *= weights[i];
        integral += term;
    }
    integral *= jacobian_matrix_.determinant();

    return integral;
}


//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NyNy_matrix_entry : Computes single matrix entry using
 * numerical integration.
 *
 * Computes \f[
 *  \iint\limits_{\Omega^{e}} \alpha_{k}^{e}\frac{\partial N_{i}^{e}}{\partial y}
 * \frac{\partial N_{j}^{e}}{\partial y}dxdy \f] using
 * quadrature rules. \f$ \beta_{k}^{e} \f$ is the \f$ k \f$-th coefficient function, and
 * \f$ N_{i}^{e} \f$ and \f$ N_{j}^{e} \f$ are the \f$ i \f$-th and \f$ j \f$-th basis functions
 * respectively.
 * @param [in] coefficient_index : index \f$ k \f$ of the coefficient function.
 * @param [in] test_function_index : index \f$ i \f$ of the test basis function.
 * @param [in] source_function_index : index \f$ j \f$ of the source basis function.
 * @return \f$ \iint\limits_{\Omega^{e}} \alpha_{k}^{e}\frac{\partial N_{i}^{e}}{\partial y}
 * \frac{\partial N_{j}^{e}}{\partial y}dxdy \f$ */
//************************************************************************************************//
cemDOUBLE SolverTriangle::Compute_N_NyNy_matrix_entry(const cemINT& coefficient_index,
                                                      const cemINT& test_function_index,
                                                      const cemINT& source_function_index) const
{
    // Get quadrature:
    cem_core::TriQuadrature quadrature;
    cemINT num_points = quadrature.getNumPointsForPolyOrder(coefficient_order_ + 2*basis_function_order_);

    const std::vector<cemDOUBLE>& ksi_points = quadrature.getKsiCoordinates(num_points);
    const std::vector<cemDOUBLE>& eta_points = quadrature.getEtaCoordinates(num_points);
    const std::vector<cemDOUBLE>& weights = quadrature.getWeights(num_points);

    // Prepare to evaluate:
    TriShapeFunction shape_function(basis_function_order_);
    std::vector<cemDOUBLE> test_ksi_deriv,test_eta_deriv;
    std::vector<cemDOUBLE> source_ksi_deriv,source_eta_deriv;
    std::vector<cemDOUBLE> coefficient_function;
    cemINT index_i,index_j,index_k;

    // Evaluate Test function:
    GetShapeFunctionIndices(basis_function_order_,test_function_index,index_i,index_j,index_k);
    test_ksi_deriv = shape_function.EvaluateKsiDeriv(index_i,index_j,index_k,ksi_points,eta_points);
    test_eta_deriv = shape_function.EvaluateEtaDeriv(index_i,index_j,index_k,ksi_points,eta_points);

    // Evaluate Source function:
    GetShapeFunctionIndices(basis_function_order_,source_function_index,index_i,index_j,index_k);
    source_ksi_deriv = shape_function.EvaluateKsiDeriv(index_i,index_j,index_k,ksi_points,eta_points);
    source_eta_deriv = shape_function.EvaluateEtaDeriv(index_i,index_j,index_k,ksi_points,eta_points);

    // Evaluate Coefficient function:
    shape_function.set_order(coefficient_order_);
    GetShapeFunctionIndices(coefficient_order_,coefficient_index,index_i,index_j,index_k);
    coefficient_function = shape_function.Evaluate(index_i,index_j,index_k,ksi_points,eta_points);

    // Add everything up:
    cemDOUBLE integral = 0;
    cemDOUBLE term = 0;
    cemDOUBLE dksi_dy = inverse_jacobian_matrix_(1,0);
    cemDOUBLE deta_dy = inverse_jacobian_matrix_(1,1);
    for (cemINT i=0; i<num_points; ++i)
    {
        term = coefficient_function[i];
        term *= (dksi_dy*test_ksi_deriv[i] + deta_dy*test_eta_deriv[i]);
        term *= (dksi_dy*source_ksi_deriv[i] + deta_dy*source_eta_deriv[i]);
        term *= weights[i];
        integral += term;
    }
    integral *= jacobian_matrix_.determinant();

    return integral;
}


//************************************************************************************************//
/** @brief SolverTriangle::Compute_N_NN_matrix_entry : Computes single matrix entry using
 * numerical integration.
 *
 * Computes \f[
 *  \iint\limits_{\Omega^{e}} \beta_{k}^{e}N_{i}^{e}N_{j}^{e}dxdy \f] using
 * quadrature rules. \f$ \beta_{k}^{e} \f$ is the \f$ k\f$-th coefficient function, and
 * \f$ N_{i}^{e} \f$ and \f$ N_{j}^{e} \f$ are the \f$ i \f$-th and \f$ j\f$-th basis functions
 * respectively.
 * @param [in] coefficient_index : index \f$ k \f$ of the coefficient function.
 * @param [in] test_function_index : index \f$ i \f$ of the test basis function.
 * @param [in] source_function_index : index \f$ j \f$ of the source basis function.
 * @return  \f$ \iint\limits_{\Omega^{e}} \beta_{k}^{e}N_{i}^{e}N_{j}^{e}dxdy \f$ */
//************************************************************************************************//
cemDOUBLE SolverTriangle::Compute_N_NN_matrix_entry(const cemINT& coefficient_index,
                                                    const cemINT& test_function_index,
                                                    const cemINT& source_function_index) const
{
    // Get quadrature:
    cem_core::TriQuadrature quadrature;
    cemINT num_points = quadrature.getNumPointsForPolyOrder(coefficient_order_ + 2*basis_function_order_);

    const std::vector<cemDOUBLE>& ksi_points = quadrature.getKsiCoordinates(num_points);
    const std::vector<cemDOUBLE>& eta_points = quadrature.getEtaCoordinates(num_points);
    const std::vector<cemDOUBLE>& weights = quadrature.getWeights(num_points);

    // Prepare to evaluate:
    TriShapeFunction shape_function(basis_function_order_);
    std::vector<cemDOUBLE> test_function,source_function,coefficient_function;
    cemINT index_i,index_j,index_k;

    // Evaluate Test function:
    GetShapeFunctionIndices(basis_function_order_,test_function_index,index_i,index_j,index_k);
    test_function = shape_function.Evaluate(index_i,index_j,index_k,ksi_points,eta_points);

    // Evaluate Source function:
    GetShapeFunctionIndices(basis_function_order_,source_function_index,index_i,index_j,index_k);
    source_function = shape_function.Evaluate(index_i,index_j,index_k,ksi_points,eta_points);

    // Evaluate Coefficient function:
    shape_function.set_order(coefficient_order_);
    GetShapeFunctionIndices(coefficient_order_,coefficient_index,index_i,index_j,index_k);
    coefficient_function = shape_function.Evaluate(index_i,index_j,index_k,ksi_points,eta_points);

    // Add everything up:
    cemDOUBLE integral = 0.0;
    for (cemINT i=0; i<num_points; ++i)
    {
        integral += coefficient_function[i]*test_function[i]*source_function[i]*weights[i];
    }
    integral *= jacobian_matrix_.determinant();

    return integral;
}


//************************************************************************************************//
/** @brief SolverTriangle::GetShapeFunctionIndices : Get three indices needed to evaluate ShapeFunction.
 *
 * Each basis function has an index in the triangle. Depending on which basis function has to be
 * evaluated, different indices are needed to evaluate the ShapeFunction that corresponds to that
 * particular basis function.
 * @param [in] shape_function_order : polynomial order of ShapeFunction
 * @param [in] basis_function_index : index of the basis function within the triangle
 * @param [out] index_i : index of the Silvester Polynomial in the \f$ \xi \f$ variable
 * @param [out] index_j : index of the Silvester Polynomial in the \f$ \eta \f$ variable
 * @param [out] index_k : index of the Silvester Polynomial in the \f$ 1-\xi-\eta \f$ variable */
//************************************************************************************************//
void SolverTriangle::GetShapeFunctionIndices(const cemINT& shape_function_order,
                                             const cemINT& basis_function_index,
                                             cemINT& index_i,
                                             cemINT& index_j,
                                             cemINT& index_k) const
{
    if (shape_function_order == 0)
    {
        index_i = 0;
        index_j = 0;
        index_k = 0;
    }
    if (shape_function_order == 1)
    {
        switch (basis_function_index)
        {
        case 0:
            index_i = 1;
            index_j = 0;
            index_k = 0;
            break;
        case 1:
            index_i = 0;
            index_j = 1;
            index_k = 0;
            break;
        case 2:
            index_i = 0;
            index_j = 0;
            index_k = 1;
            break;
        default:
            throw(Exception("INPUT ERROR","basisfunction_index must be from 1 to 3"));
            break;
        }
    }
    if (shape_function_order == 2)
    {
        switch (basis_function_index)
        {
        case 0:
            index_i = 2;
            index_j = 0;
            index_k = 0;
            break;
        case 1:
            index_i = 0;
            index_j = 2;
            index_k = 0;
            break;
        case 2:
            index_i = 0;
            index_j = 0;
            index_k = 2;
            break;
        case 3:
            index_i = 1;
            index_j = 1;
            index_k = 0;
            break;
        case 4:
            index_i = 0;
            index_j = 1;
            index_k = 1;
            break;
        case 5:
            index_i = 1;
            index_j = 0;
            index_k = 1;
            break;
        default:
            throw(Exception("INPUT ERROR","basisfunction_index must be from 1 to 6"));
            break;
        }
    }
    if (shape_function_order == 3)
    {
        switch (basis_function_index)
        {
        case 0:
            index_i = 3;
            index_j = 0;
            index_k = 0;
            break;
        case 1:
            index_i = 0;
            index_j = 3;
            index_k = 0;
            break;
        case 2:
            index_i = 0;
            index_j = 0;
            index_k = 3;
            break;
        case 3:
            index_i = 2;
            index_j = 1;
            index_k = 0;
            break;
        case 4:
            index_i = 1;
            index_j = 2;
            index_k = 0;
            break;
        case 5:
            index_i = 0;
            index_j = 2;
            index_k = 1;
            break;
        case 6:
            index_i = 0;
            index_j = 1;
            index_k = 2;
            break;
        case 7:
            index_i = 1;
            index_j = 0;
            index_k = 2;
            break;
        case 8:
            index_i = 2;
            index_j = 0;
            index_k = 1;
            break;
        case 9:
            index_i = 1;
            index_j = 1;
            index_k = 1;
            break;
        default:
            throw(Exception("INPUT ERROR","basisfunction_index must be from 1 to 10"));
            break;
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

        // Get XY coordinates of nodes:
        x1_ = element_ptr_->node(0)->operator [](0);
        x2_ = element_ptr_->node(1)->operator [](0);
        x3_ = element_ptr_->node(2)->operator [](0);
        y1_ = element_ptr_->node(0)->operator [](1);
        y2_ = element_ptr_->node(1)->operator [](1);
        y3_ = element_ptr_->node(2)->operator [](1);

        // Parameters for analytical integration of basis functions:
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

        // Jacobian Matrix of mapping from reference to actual triangle:
        jacobian_matrix_.resize(2,2);
        jacobian_matrix_(0,0) = x1_ - x3_;
        jacobian_matrix_(0,1) = y1_ - y3_;
        jacobian_matrix_(1,0) = x2_ - x3_;
        jacobian_matrix_(1,1) = y2_ - y3_;
        inverse_jacobian_matrix_ = jacobian_matrix_.inverse();

        geometry_is_Up_ = true;
    }
}
