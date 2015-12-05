#include "DenseMatrix.h"
#include "cemError.h"
#include "cemUtils.h"
#include "MKL/BlasLevel1.h"
#include <cstring>

using namespace cem_math;
using namespace cem_def;



//************************************************************************************************//
/** @brief DenseMatrix::DenseMatrix : Default constructor. */
//************************************************************************************************//
template <class T>
DenseMatrix<T>::DenseMatrix()
{
    num_rows_ = 0 ;
    num_columns_ = 0;
    matrix_entries_ = NULL;
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::~DenseMatrix : Destructor. */
//************************************************************************************************//
template <class T>
DenseMatrix<T>::~DenseMatrix()
{
    CLEAN_ARRAY(matrix_entries_);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::DenseMatrix : Constructor with matrix size.
 * @param n_rows : Number of rows
 * @param n_columns : Number of columns */
//************************************************************************************************//
template <class T>
DenseMatrix<T>::DenseMatrix(cemUINT n_rows, cemUINT n_columns)
{
    resize(n_rows,n_columns);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::copy : Copies all data from another matrix.
 * @param other : Matrix to be copied */
//************************************************************************************************//
template <class T>
void DenseMatrix<T>::copy(const DenseMatrix<T>& other)
{
    resize(other.num_rows_,other.num_columns_);

    cemUINT8 size = num_rows_;
    size *= num_columns_;
    for (cemUINT8 ii=0; ii<size; ++ii)
        this->matrix_entries_[ii] = other.matrix_entries_[ii];
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::DenseMatrix : Copy constructor.
 * @param other : Matrix to be copied. */
//************************************************************************************************//
template <class T>
DenseMatrix<T>::DenseMatrix(const DenseMatrix<T>& other)
{
    copy(other);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::operator = : Copy operator.
 * @param other : Matrix to be copied
 * @return : A new matrix, equal to the one given */
//************************************************************************************************//
template <class T>
DenseMatrix<T>& DenseMatrix<T>::operator = (const DenseMatrix<T>& other)
{
    copy(other);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::num_rows : Gets number of rows in matrix.
 * @return : num_rows_ */
//************************************************************************************************//
template <class T>
cemUINT DenseMatrix<T>::num_rows() const {return num_rows_;}


//************************************************************************************************//
/** @brief DenseMatrix<T>::num_columns : Gets number of columns in matrix.
 * @return : num_columns_ */
//************************************************************************************************//
template <class T>
cemUINT DenseMatrix<T>::num_columns() const {return num_columns_;}


//************************************************************************************************//
/** @brief DenseMatrix<T>::operator () : Random access operator for read only purposes.
 * @param row : row of matrix entry to get, from 1 to num_rows_
 * @param col : column of matrix entry to get, from 1 to num_columns_
 * @return : Matrix(row,col) */
//************************************************************************************************//
template <class T>
const T& DenseMatrix<T>::operator () (cemUINT row, cemUINT col) const
{
    cemUINT8 location = num_rows_;
    location *= col - 1;
    location += row - 1;
    return(matrix_entries_[location]);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::operator () : Random access operator for read-write purposes.
 * @param row : row of matrix entry to get, from 1 to num_rows_
 * @param col : column of matrix entry to get, from 1 to num_columns_
 * @return : Matrix(row,col) */
//************************************************************************************************//
template <class T>
T& DenseMatrix<T>::operator () (cemUINT row, cemUINT col)
{
    cemUINT8 location = num_rows_;
    location *= col - 1;
    location += row - 1;
    return(matrix_entries_[location]);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::initialize : Sets all matrix entries to zero. */
//************************************************************************************************//
template <class T>
void DenseMatrix<T>::initialize()
{
    cemUINT8 size = num_rows_;
    size *= num_columns_;
    std::memset(&matrix_entries_[0], 0, sizeof(T)*size);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::resize : Resize matrix to given numbers of rows and columns.
 * @param n_rows : Number of rows >= 1
 * @param n_columns : Number of columns >= 1 */
//************************************************************************************************//
template <class T>
void DenseMatrix<T>::resize(cemUINT n_rows, cemUINT n_columns)
{
    if (!matrix_entries_)
        CLEAN_ARRAY(matrix_entries_);
    num_rows_ = n_rows;
    num_columns_ = n_columns;

    cemUINT8 size = num_rows_;
    size *= num_columns_;
    try
    {
        matrix_entries_ = new T[size];
    }
    catch (std::bad_alloc)
    {
        cemUINT memory = size*sizeof(T)/1024/1024;
        std::string temp = cem_utils::NumberToString<cemUINT>(memory);
        throw("MEMORY OVERFLOW", "Requested memory=" + temp + "Mb");
    }
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::add : Adds two matrices of the same size.
 * Computes \f$ A = A + B \f$ or equivalently, A += B
 * @param [in] B : Matrix that is added to 'this' */
//************************************************************************************************//
template <class T>
void DenseMatrix<T>::add(const DenseMatrix<T>& B)
{
    if (num_columns_ != B.num_columns_ || num_rows_ != B.num_rows_ )
        throw("INVALID MATRIX OPERATION","Matrix size mismatch");

    cemUINT8 size = num_rows_;
    size *= num_columns_;
    MKL_VectorPlusEqualVector(size, matrix_entries_, B.matrix_entries_);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::operator += : Adds two matrices of the same size.
 * @param [in] B : Matrix that is added to 'this'
 * @return A = A + B */
//************************************************************************************************//
template <class T>
const DenseMatrix<T>& DenseMatrix<T>::operator += (const DenseMatrix<T>& B)
{
    this->add(B);
    return *this;
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::substract : Subtracts two matrices of the same size.
 * Computes \f$ A = A - B \f$ or equivalently, A -= B
 * @param [in] B : Matrix that is substracted to 'this' */
//************************************************************************************************//
template <class T>
void DenseMatrix<T>::substract(const DenseMatrix<T>& B)
{
    if (num_columns_ != B.num_columns_ || num_rows_ != B.num_rows_ )
        throw("INVALID MATRIX OPERATION","Matrix size mismatch");

    cemUINT8 size = num_rows_;
    size *= num_columns_;
    MKL_VectorMinusEqualVector(size, matrix_entries_, B.matrix_entries_);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::operator -= : Subtracts two matrices of the same size.
 * @param [in] B : Matrix that is substracted to 'this'
 * @return A = A - B */
//************************************************************************************************//
template <class T>
const DenseMatrix<T>& DenseMatrix<T>::operator -= (const DenseMatrix<T>& B)
{
    this->substract(B);
    return *this;
}



//************************************************************************************************//
// Class Instantiations:
//************************************************************************************************//
template class DenseMatrix<cemFLOAT>;
template class DenseMatrix<cemDOUBLE>;
template class DenseMatrix<cemFCOMPLEX>;
template class DenseMatrix<cemDCOMPLEX>;

