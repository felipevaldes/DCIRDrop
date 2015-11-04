#include "DenseMatrix.h"
#include "cemError.h"
#include "cemUtils.h"

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
 * @param row : row of matrix entry to get
 * @param col : column of matrix entry to get
 * @return : Matrix(row,col) */
//************************************************************************************************//
template <class T>
const T& DenseMatrix<T>::operator () (cemUINT row, cemUINT col) const
{
    cemUINT8 location = num_rows_;
    location *= col;
    location += row;
    return(matrix_entries_[location]);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::operator () : Random access operator for read-write purposes.
 * @param row : row of matrix entry to get
 * @param col : column of matrix entry to get
 * @return : Matrix(row,col) */
//************************************************************************************************//
template <class T>
T& DenseMatrix<T>::operator () (cemUINT row, cemUINT col)
{
    cemUINT8 location = num_rows_;
    location *= col;
    location += row;
    return(matrix_entries_[location]);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::initialize : Sets all matrix entries to a single value.
 * @param value : Value to set in all entries */
//************************************************************************************************//
template <class T>
void DenseMatrix<T>::initialize(T value)
{
    cemUINT8 size = num_rows_;
    size *= num_columns_;
    memset(&matrix_entries_[0], value, sizeof(T)*size);
}


//************************************************************************************************//
/** @brief DenseMatrix<T>::resize : Resize matrix to given numbers of rows and columns. */
//************************************************************************************************//
template <class T>
void DenseMatrix<T>::resize(cemUINT n_rows, cemUINT n_columns)
{
    CLEAN_ARRAY(matrix_entries_);
    num_rows_ = n_rows;
    num_columns_ = n_columns;

    cemUINT8 size = num_rows_;
    size *= num_rows_;
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



template <class T>
void DenseMatrix<T>::add(const DenseMatrix<T>& other)
{

}


template <class T>
const DenseMatrix<T>& DenseMatrix<T>::operator += (const DenseMatrix<T>& other)
{

}



template <class T>
void DenseMatrix<T>::substract(const DenseMatrix<T>& other)
{

}



template <class T>
const DenseMatrix<T>& DenseMatrix<T>::operator -= (const DenseMatrix<T>& other)
{

}




