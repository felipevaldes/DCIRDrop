#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include "Matrix.h"


namespace cem_math
{

template <class T>
class DenseMatrix : public Matrix<T>
{
public:
    // Default constructor:
    DenseMatrix();

    // Destructor:
    ~DenseMatrix();

    // Constructor with parameters:
    DenseMatrix(cemUINT n_rows, cemUINT n_columns);

    // Copy constructor:
    DenseMatrix(const DenseMatrix<T>& other);
    DenseMatrix& operator = (const DenseMatrix<T>& other);

    // Get data members:
    cemUINT num_rows() const;
    cemUINT num_columns() const;
    const T& operator () (cemUINT row, cemUINT col) const;

    // Set data members:
    T& operator () (cemUINT row, cemUINT col);
    void initialize();
    void resize(cemUINT n_rows, cemUINT n_columns);

    // Math operations:
    void add(const DenseMatrix<T>& B);
    const DenseMatrix& operator += (const DenseMatrix<T>& B);
    void substract(const DenseMatrix<T>& B);
    const DenseMatrix& operator -= (const DenseMatrix<T>& B);

private:
    cemINT  num_rows_;          /**< Number of rows of the matrix */
    cemINT  num_columns_;       /**< Number of columns of the matrix */
    T*      matrix_entries_;    /**< Matrix entries, stored column-wise */

    void copy(const DenseMatrix<T>& matrix);
};


}



#endif // DENSEMATRIX_H

