#include "BlasLevel1.h"
#include <mkl.h>

using namespace cem_math;

//************************************************************************************************//
/** @brief MKL_VectorPlusEqualVector : Adds two double precision vectors.
 * Computes \f$ y = x + y \f$ or equivalently, y +=x
 * @param [in] N : Number of elements in vectors x and y
 * @param [in,out] y : double precision vector
 * @param [in] x : double precision vector */
//************************************************************************************************//
void MKL_VectorPlusEqualVector(const cemINT N, cemDOUBLE *y, const cemDOUBLE *x)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemDOUBLE alpha = 1.0;

    cblas_daxpy(N, alpha, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorPlusEqualVector : Adds two single precision vectors.
 * Computes \f$ y = x + y \f$ or equivalently, y +=x
 * @param [in] N : Number of elements in vectors x and y
 * @param [in,out] y : single precision vector
 * @param [in] x : single precision vector */
//************************************************************************************************//
void MKL_VectorPlusEqualVector(const cemINT N, cemFLOAT *y, const cemFLOAT *x)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemFLOAT alpha = 1.0;

    cblas_saxpy(N, alpha, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorPlusEqualVector : Adds two double precision complex vectors.
 * Computes \f$ y = x + y \f$ or equivalently, y +=x
 * @param [in] N : Number of elements in vectors x and y
 * @param [in,out] y : double precision complex vector
 * @param [in] x : double precision complex vector */
//************************************************************************************************//
void MKL_VectorPlusEqualVector(const cemINT N, cemDCOMPLEX *y, const cemDCOMPLEX *x)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemDCOMPLEX alpha = 1.0;

    cblas_zaxpy(N, &alpha, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorPlusEqualVector : Adds two single precision complex vectors.
 * Computes \f$ y = x + y \f$ or equivalently, y +=x
 * @param [in] N : Number of elements in vectors x and y
 * @param [in,out] y : single precision complex vector
 * @param [in] x : single precision complex vector */
//************************************************************************************************//
void MKL_VectorPlusEqualVector(const cemINT N, cemFCOMPLEX *y, const cemFCOMPLEX *x)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemFCOMPLEX alpha = 1.0;

    cblas_caxpy(N, &alpha, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorPlusEqualVector : Subtracts two double precision vectors.
 * Computes \f$ y = y - x \f$ or equivalently, y -= x
 * @param [in] N : Number of elements in vectors x and y
 * @param [in,out] y : double precision vector
 * @param [in] x : double precision vector */
//************************************************************************************************//
void MKL_VectorMinusEqualVector(const cemINT N, cemDOUBLE *y, const cemDOUBLE *x)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemDOUBLE alpha = -1.0;

    cblas_daxpy(N, alpha, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorPlusEqualVector : Subtracts two single precision vectors.
 * Computes \f$ y = y - x \f$ or equivalently, y -= x
 * @param [in] N : Number of elements in vectors x and y
 * @param [in,out] y : single precision vector
 * @param [in] x : single precision vector */
//************************************************************************************************//
void MKL_VectorMinusEqualVector(const cemINT N, cemFLOAT *y, const cemFLOAT *x)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemFLOAT alpha = -1.0;

    cblas_saxpy(N, alpha, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorPlusEqualVector : Subtracts two double precision complex vectors.
 * Computes \f$ y = y - x \f$ or equivalently, y -= x
 * @param [in] N : Number of elements in vectors x and y
 * @param [in,out] y : double precision complex vector
 * @param [in] x : double precision complex vector */
//************************************************************************************************//
void MKL_VectorMinusEqualVector(const cemINT N, cemDCOMPLEX *y, const cemDCOMPLEX *x)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemDCOMPLEX alpha = -1.0;

    cblas_zaxpy(N, &alpha, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorPlusEqualVector : Subtracts two single precision complex vectors.
 * Computes \f$ y = y - x \f$ or equivalently, y -= x
 * @param [in] N : Number of elements in vectors x and y
 * @param [in,out] y : single precision complex vector
 * @param [in] x : single precision complex vector */
//************************************************************************************************//
void MKL_VectorMinusEqualVector(const cemINT N, cemFCOMPLEX *y, const cemFCOMPLEX *x)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemFCOMPLEX alpha = -1.0;

    cblas_caxpy(N, &alpha, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_ScalarTimesEqualVector : Multiplies double precision vector with double precision scalar.
 * Computes \f$ x = \alpha x \f$ or equivalently x *= alpha
 * @param [in] N : Number of elements in vector x
 * @param [in,out] x : double precision vector
 * @param [in] alpha : double precision scalar */
//************************************************************************************************//
void MKL_ScalarTimesEqualVector(const cemINT N, cemDOUBLE *x, const cemDOUBLE alpha)
{
    cemINT incx = 1;
    cblas_dscal(N, alpha, x, incx);
}


//************************************************************************************************//
/** @brief MKL_ScalarTimesEqualVector : Multiplies single precision vector with single precision scalar.
 * Computes \f$ x = \alpha x \f$ or equivalently x *= alpha
 * @param [in] N : Number of elements in vector x
 * @param [in,out] x : single precision vector
 * @param [in] alpha : single precision scalar */
//************************************************************************************************//
void MKL_ScalarTimesEqualVector(const cemINT N, cemFLOAT *x, const cemFLOAT alpha)
{
    cemINT incx = 1;
    cblas_sscal(N, alpha, x, incx);
}


//************************************************************************************************//
/** @brief MKL_ScalarTimesEqualVector : Multiplies double precision complex vector with double precision complex scalar.
 * Computes \f$ x = \alpha x \f$ or equivalently x *= alpha
 * @param [in] N : Number of elements in vector x
 * @param [in,out] x : double precision complex vector
 * @param [in] alpha : double precision complex scalar */
//************************************************************************************************//
void MKL_ScalarTimesEqualVector(const cemINT N, cemDCOMPLEX *x, const cemDCOMPLEX alpha)
{
    cemINT incx = 1;
    cblas_zscal(N, &alpha, x, incx);
}


//************************************************************************************************//
/** @brief MKL_ScalarTimesEqualVector : Multiplies single precision complex vector with single precision complex scalar.
 * Computes \f$ x = \alpha x \f$ or equivalently x *= alpha
 * @param [in] N : Number of elements in vector x
 * @param [in,out] x : single precision complex vector
 * @param [in] alpha : single precision complex scalar */
//************************************************************************************************//
void MKL_ScalarTimesEqualVector(const cemINT N, cemFCOMPLEX *x, const cemFCOMPLEX alpha)
{
    cemINT incx = 1;
    cblas_cscal(N, &alpha, x, incx);
}


//************************************************************************************************//
/** @brief MKL_ScalarTimesEqualVector : Multiplies double precision complex vector with double precision scalar.
 * Computes \f$ x = \alpha x \f$ or equivalently x *= alpha
 * @param [in] N : Number of elements in vector x
 * @param [in,out] x : double precision complex vector
 * @param [in] alpha : double precision scalar */
//************************************************************************************************//
void MKL_ScalarTimesEqualVector(const cemINT N, cemDCOMPLEX *x, const cemDOUBLE alpha)
{
    cemINT incx = 1;
    cblas_zdscal(N, alpha, x, incx);
}


//************************************************************************************************//
/** @brief MKL_ScalarTimesEqualVector : Multiplies single precision complex vector with single precision scalar.
 * Computes \f$ x = \alpha x \f$ or equivalently x *= alpha
 * @param [in] N : Number of elements in vector x
 * @param [in,out] x : single precision complex vector
 * @param [in] alpha : single precision scalar */
//************************************************************************************************//
void MKL_ScalarTimesEqualVector(const cemINT N, cemFCOMPLEX *x, const cemFLOAT alpha)
{
    cemINT incx = 1;
    cblas_csscal(N, alpha, x, incx);
}


//************************************************************************************************//
/** @brief MKL_VectorCopy : Copies a double precision vector.
 * Computes \f$ y = x \f$
 * @param [in] N : Number of elements to be copied
 * @param [in] x : double precision vector to be copied
 * @param [in] incx : increment for the elements of x
 * @param [out] y : double precision vector where the copy is stored sixe >= (1 + (n-1)*abs(incy))
 * @param [in] incy : increments for the elements of y */
//************************************************************************************************//
void MKL_VectorCopy(const cemINT N,
                    const cemDOUBLE* x,
                    const cemINT incx,
                    cemDOUBLE* y,
                    const cemINT incy)
{
    cblas_dcopy(N, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorCopy : Copies a single precision vector.
 * Computes \f$ y = x \f$
 * @param [in] N : Number of elements to be copied
 * @param [in] x : single precision vector to be copied
 * @param [in] incx : increment for the elements of x
 * @param [out] y : single precision vector where the copy is stored sixe >= (1 + (n-1)*abs(incy))
 * @param [in] incy : increments for the elements of y */
//************************************************************************************************//
void MKL_VectorCopy(const cemINT N,
                    const cemFLOAT* x,
                    const cemINT incx,
                    cemFLOAT* y,
                    const cemINT incy)
{
    cblas_scopy(N, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorCopy : Copies a double precision complex vector.
 * Computes \f$ y = x \f$
 * @param [in] N : Number of elements to be copied
 * @param [in] x : double precision complex vector to be copied
 * @param [in] incx : increment for the elements of x
 * @param [out] y : double precision complex vector where the copy is stored sixe >= (1 + (n-1)*abs(incy))
 * @param [in] incy : increments for the elements of y */
//************************************************************************************************//
void MKL_VectorCopy(const cemINT N,
                    const cemDCOMPLEX* x,
                    const cemINT incx,
                    cemDCOMPLEX* y,
                    const cemINT incy)
{
    cblas_zcopy(N, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorCopy : Copies a single precision complex vector.
 * Computes \f$ y = x \f$
 * @param [in] N : Number of elements to be copied
 * @param [in] x : single precision complex vector to be copied
 * @param [in] incx : increment for the elements of x
 * @param [out] y : single precision complex vector where the copy is stored sixe >= (1 + (n-1)*abs(incy))
 * @param [in] incy : increments for the elements of y */
//************************************************************************************************//
void MKL_VectorCopy(const cemINT N,
                    const cemFCOMPLEX* x,
                    const cemINT incx,
                    cemFCOMPLEX* y,
                    const cemINT incy)
{
    cblas_ccopy(N, x, incx, y, incy);
}



//************************************************************************************************//
/** @brief MKL_VectorDotProduct : Dot product between two double precision vectors.
 * Computes \f$ x \cdot y \f$
 * @param [in] N : Number of elements in vectors
 * @param [in] x : double precision vector
 * @param [in] y : double precision vector
 * @return \f$ r = \sum_{i=1}^{N} x_i y_i \f$ */
//************************************************************************************************//
cemDOUBLE MKL_VectorDotProduct(const cemINT N, const cemDOUBLE *x, const cemDOUBLE *y)
{
    cemINT incx = 1;
    cemINT incy = 1;
    return cblas_ddot(N, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorDotProduct : Dot product between two single precision vectors.
 * Computes \f$ x \cdot y \f$
 * @param [in] N : Number of elements in vectors
 * @param [in] x : single precision vector
 * @param [in] y : single precision vector
 * @return \f$ r = \sum_{i=1}^{N} x_i y_i \f$ */
//************************************************************************************************//
cemFLOAT MKL_VectorDotProduct(const cemINT N, const cemFLOAT *x, const cemFLOAT *y)
{
    cemINT incx = 1;
    cemINT incy = 1;
    return cblas_sdot(N, x, incx, y, incy);
}


//************************************************************************************************//
/** @brief MKL_VectorDotProduct : Conjugated dot product between two double precision complex vectors.
 * Computes \f$ conjg(x) \cdot y \f$
 * @param [in] N : Number of elements in vectors
 * @param [in] x : double precision complex vector
 * @param [in] y : double precision complex vector
 * @return \f$ r = \sum_{i=1}^{N}conjg(x_i)y_i \f$ */
//************************************************************************************************//
cemDCOMPLEX MKL_VectorDotProductConjugated(const cemINT N, const cemDOUBLE *x, const cemDOUBLE *y)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemDCOMPLEX r = (0.0, 0.0);
    cblas_zdotc_sub(N, x, incx, y, incy, &r);

    return r;
}


//************************************************************************************************//
/** @brief MKL_VectorDotProduct : Conjugated dot product between two single precision complex vectors.
 * Computes \f$ conjg(x) \cdot y \f$
 * @param [in] N : Number of elements in vectors
 * @param [in] x : single precision complex vector
 * @param [in] y : single precision complex vector
 * @return \f$ r = \sum_{i=1}^{N}conjg(x_i)y_i \f$ */
//************************************************************************************************//
cemFCOMPLEX MKL_VectorDotProductConjugated(const cemINT N, const cemFCOMPLEX *x, const cemFCOMPLEX *y)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemFCOMPLEX r = (0.0, 0.0);
    cblas_cdotc_sub(N, x, incx, y, incy, &r);

    return r;
}


//************************************************************************************************//
/** @brief MKL_VectorDotProduct : Dot product between two double precision complex vectors.
 * Computes \f$ x \cdot y \f$
 * @param [in] N : Number of elements in vectors
 * @param [in] x : double precision complex vector
 * @param [in] y : double precision complex vector
 * @return \f$ r = \sum_{i=1}^{N} x_i y_i \f$ */
//************************************************************************************************//
cemDCOMPLEX MKL_VectorDotProduct(const cemINT N, const cemDCOMPLEX *x, const cemDCOMPLEX *y)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemDCOMPLEX r = (0.0, 0.0);
    cblas_zdotu_sub(N, x, incx, y, incy, &r);

    return r;
}


//************************************************************************************************//
/** @brief MKL_VectorDotProduct : Dot product between two single precision complex vectors.
 * Computes \f$ x \cdot y \f$
 * @param [in] N : Number of elements in vectors
 * @param [in] x : single precision complex vector
 * @param [in] y : single precision complex vector
 * @return \f$ r = \sum_{i=1}^{N} x_i y_i \f$ */
//************************************************************************************************//
cemFCOMPLEX MKL_VectorDotProduct(const cemINT N, const cemFCOMPLEX *x, const cemFCOMPLEX *y)
{
    cemINT incx = 1;
    cemINT incy = 1;
    cemFCOMPLEX r = (0.0, 0.0);
    cblas_cdotu_sub(N, x, incx, y, incy, &r);

    return r;
}


//************************************************************************************************//
/** @brief MKL_VectorNorm2 : Euclidean norm of double precision vector.
 * @param [in] N : Number of elements in vector x
 * @param [in] x : double precision vector
 * @return ||x|| */
//************************************************************************************************//
cemDOUBLE MKL_VectorNorm2(const cemINT N, const cemDOUBLE *x)
{
    cemINT incx = 1;
    return cblas_dnrm2(N, x, incx);
}


//************************************************************************************************//
/** @brief MKL_VectorNorm2 : Euclidean norm of single precision vector.
 * @param [in] N : Number of elements in vector x
 * @param [in] x : single precision vector
 * @return ||x|| */
//************************************************************************************************//
cemFLOAT MKL_VectorNorm2(const cemINT N, const cemFLOAT *x)
{
    cemINT incx = 1;
    return cblas_snrm2(N, x, incx);
}


//************************************************************************************************//
/** @brief MKL_VectorNorm2 : Euclidean norm of double precision complex vector.
 * @param [in] N : Number of elements in vector x
 * @param [in] x : double precision complex vector
 * @return ||x|| */
//************************************************************************************************//
cemDOUBLE MKL_VectorNorm2(const cemINT N, const cemDCOMPLEX *x)
{
    cemINT incx = 1;
    return cblas_dznrm2(N, x, incx);
}


//************************************************************************************************//
/** @brief MKL_VectorNorm2 : Euclidean norm of single precision complex vector.
 * @param [in] N : Number of elements in vector x
 * @param [in] x : single precision complex vector
 * @return ||x|| */
//************************************************************************************************//
cemFLOAT MKL_VectorNorm2(const cemINT N, const cemFCOMPLEX *x)
{
    cemINT incx = 1;
    return cblas_scnrm2(N, x, incx);
}











