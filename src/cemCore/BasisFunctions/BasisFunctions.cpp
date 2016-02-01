#include "BasisFunctions.h"
#include "cemError.h"
#include "SpecialFunctions/MiscFunctions.h"


using cem_core::ShapeFunction;
using cem_core::TriShapeFunction;
using cemcommon::Exception;


///***********************************************************************************************//
/// CLASS ShapeFunction:
///***********************************************************************************************//


//************************************************************************************************//
/** @brief ShapeFunction::ShapeFunction : Constructor with parameters.
 * @param [in] order : polynomial order of ShapeFunction */
//************************************************************************************************//
ShapeFunction::ShapeFunction(const cemINT& order)
{
    if (order < 1)
        throw(Exception("INPUT ERROR","ShapeFunction's order must be >= 1"));

    order_ = order;
}


//************************************************************************************************//
/** @brief ShapeFunction::order : Gets polynomial order of ShapeFunction.
 * @return order_ */
//************************************************************************************************//
cemINT ShapeFunction::order() const {return order_;}


//************************************************************************************************//
/** @brief ShapeFunction::set_order : Sets polynomial order of ShapeFunction.
 * @param [in] order : polynomial order */
//************************************************************************************************//
void ShapeFunction::set_order(const cemINT &order) {order_ = order;}



//************************************************************************************************//
/** @brief ShapeFunction::SilvesterPolynomial : Evaluates Silvester Polynomial with given arguments.
 *
 * Silverter Polynomial is defined as \f$ P_{m}^{N}(\xi) \f$:
 * \f$ P_{m}^{N}(\xi) = 1 \f$, if \f$ m = 0 \f$;
 * \f$ P_{m}^{N}(\xi) = \frac{1}{m!}\prod\limits_{p=0}^{m-1}(N\xi - p) \f$, if \f$ m > 0 \f$;
 * where \f$ m \f$ is the index, and \f$ N \f$ is the order. the Silvester polynomial exhibits
 * \f$ m \f$ equally spaced zeros located at \f$ \xi = 0,1/N,\ldots,(m-1)/N \f$ and has unity value
 * at \f$ \xi = m/N \f$.
 * @param [in] order : order \f$N\f$ of the polynomial to evaluate (order >= 1)
 * @param [in] index : index \f$m\f$ of the polynomial to evaluate (0 <= index <= order)
 * @param [in] ksi : point in real line \f$\xi\f$ in which to evaluate the polynomial
 * @return : \f$ P_{m}^{N}(\xi) \f$ */
//************************************************************************************************//
cemDOUBLE ShapeFunction::SilvesterPolynomial(const cemINT& index,
                                             const cemDOUBLE& ksi) const
{
    if (index > order_)
        throw(Exception("INPUT ERROR","index must be <= order_"));

    cemDOUBLE poly = 1.0;

    if (index > 0)
    {
        for (cemINT p=0; p<index; ++p)
        {
            poly *= order_*ksi - p;
        }
        poly /= cem_math::Factorial(index);
    }

    return poly;
}


//************************************************************************************************//
/** @brief ShapeFunction::SilvesterPolynomialDeriv : Evaluates derivative of Silvester Polynomial.
 *
 * The derivative of the Silvester polynomial is computed as follows:
 * \f$ \frac{d}{d\xi}P_{m}^{N}(\xi) = \frac{N}{m!}\sum\limits_{j=0}^{m-1}
 * \prod\limits_{p=0,p\neq j}^{m-1}(N\xi - p) \f$
 * @param [in] order : order \f$N\f$ of the polynomial to evaluate (order >= 1)
 * @param [in] index : index \f$m\f$ of the polynomial to evaluate (0 <= index <= order)
 * @param [in] ksi : point in real line \f$\xi\f$ in which to evaluate the polynomial
 * @return : \f$ \frac{d}{d\xi}P_{m}^{N}(\xi) \f$ */
//************************************************************************************************//
cemDOUBLE ShapeFunction::SilvesterPolynomialDeriv(const cemINT &index,
                                                  const cemDOUBLE &ksi) const
{
    if (index > order_)
        throw(Exception("INPUT ERROR","index must be <= order_"));

    cemDOUBLE deriv = 0.0;

    if (index > 0)
    {
        for (cemINT j=0; j<index; ++j)
        {
            cemDOUBLE poly = 1.0;
            for (cemINT p=0; p<index; ++p)
            {
                if (p != j)
                    poly *= order_*ksi - p;
            }
            deriv += poly;
        }
        deriv *= order_;
        deriv /= cem_math::Factorial(index);
    }

    return deriv;
}



///***********************************************************************************************//
/// CLASS TriShapeFunction:
///***********************************************************************************************//

//************************************************************************************************//
/** @brief TriShapeFunction::Evaluate : Evaluates shape function at a single point in unit-triangle.
 *
 * Shape Function is defined as the product of three Silverter Polynomials:
 * \f$ N_{i}(\xi,\eta) = P_{I}^{N}(\xi)P_{J}^{N}(\eta)P_{K}^{N}(1-\xi-\eta) \f$.
 * For each value of \f$ i=1,2,\ldots,(N+1)(N+2)/2 \f$ there is a permutation of values for the
 * indices \f$ I,J,K \f$ such that \f$ I+J+K = N \f$.
 * @param [in] order : order \f$N\f$ of the shape function to evaluate (order >= 1)
 * @param [in] index_i : index \f$I\f$ for the Silvester Polynomial in \f$\xi\f$
 * @param [in] index_j : index \f$J\f$ for the Silvester Polynomial in \f$\eta\f$
 * @param [in] index_k : index \f$K\f$ for the Silvester Polynomial in \f$1-\xi-\eta\f$
 * @param [in] ksi : point in the \f$\xi\f$ axis in which to evaluate (\f$ 0\leq \xi \leq 1 \f$)
 * @param [in] eta : point in the \f$\eta\f$ axis in which to evaluate (\f$ 0\leq \eta \leq \xi \f$)
 * @return : \f$ N_{i}(\xi,\eta) = P_{I}^{N}(\xi)P_{J}^{N}(\eta)P_{K}^{N}(1-\xi-\eta) \f$. */
//************************************************************************************************//
cemDOUBLE TriShapeFunction::Evaluate(const cemINT& index_i,
                                     const cemINT& index_j,
                                     const cemINT& index_k,
                                     const cemDOUBLE& ksi,
                                     const cemDOUBLE& eta) const
{
    if (index_i + index_j + index_k > order_)
        throw(Exception("INPUT ERROR","Sum of indices must be <= order"));

    cemDOUBLE result = SilvesterPolynomial(index_i,ksi);
    result *= SilvesterPolynomial(index_j,eta);
    result *= SilvesterPolynomial(index_k,1-ksi-eta);

    return result;
}


//************************************************************************************************//
/** @brief TriShapeFunction::EvaluateKsiDeriv : Evaluates the ksi derivative of shape function at
 * a single point in the unit-triangle.
 *
 * The derivative with respect to \f$ \xi \f$ is evaluated as follows: \f$ \frac{\partial N_{i}}
 * {\partial\xi} = \frac{d}{d\xi}P_{I}^{N}(\xi)P_{J}^{N}(\eta)
 * P_{K}^{N}(1-\xi-\eta) - P_{I}^{N}(\xi)P_{J}^{N}(\eta)\frac{d}{d\alpha}P_{K}^{N}(\alpha) \f$
 * @param [in] order : order \f$N\f$ of the shape function to evaluate (order >= 1)
 * @param [in] index_i : index \f$I\f$ for the Silvester Polynomial in \f$\xi\f$
 * @param [in] index_j : index \f$J\f$ for the Silvester Polynomial in \f$\eta\f$
 * @param [in] index_k : index \f$K\f$ for the Silvester Polynomial in \f$1-\xi-\eta\f$
 * @param [in] ksi : point in the \f$\xi\f$ axis in which to evaluate (\f$ 0\leq \xi \leq 1 \f$)
 * @param [in] eta : point in the \f$\eta\f$ axis in which to evaluate (\f$ 0\leq \eta \leq \xi \f$)
 * @return : \f$ \frac{\partial}{\partial\xi}N_{i}(\xi,\eta) \f$. */
//************************************************************************************************//
cemDOUBLE TriShapeFunction::EvaluateKsiDeriv(const cemINT &index_i,
                                             const cemINT &index_j,
                                             const cemINT &index_k,
                                             const cemDOUBLE &ksi,
                                             const cemDOUBLE &eta) const
{
    cemDOUBLE first_term = SilvesterPolynomialDeriv(index_i,ksi);
    first_term *= SilvesterPolynomial(index_j,eta);
    first_term *= SilvesterPolynomial(index_k,1-ksi-eta);

    cemDOUBLE second_term = SilvesterPolynomial(index_i,ksi);
    second_term *= SilvesterPolynomial(index_j,eta);
    second_term *= SilvesterPolynomialDeriv(index_k,1-ksi-eta);

    return first_term-second_term;
}


//************************************************************************************************//
/** @brief TriShapeFunction::EvaluateEtaDeriv : Evaluates the eta derivative of shape function at
 * a single point in the unit-triangle.
 *
 * The derivative with respect to \f$ \eta \f$ is evaluated as follows: \f$ \frac{\partial N_{i}}
 * {\partial\eta} = P_{I}^{N}(\xi)\frac{d}{d\eta}P_{J}^{N}(\eta)P_{K}^{N}(1-\xi-\eta)
 * - P_{I}^{N}(\xi)P_{J}^{N}(\eta)\frac{d}{d\alpha}P_{K}^{N}(\alpha) \f$
 * @param [in] order : order \f$N\f$ of the shape function to evaluate (order >= 1)
 * @param [in] index_i : index \f$I\f$ for the Silvester Polynomial in \f$\xi\f$
 * @param [in] index_j : index \f$J\f$ for the Silvester Polynomial in \f$\eta\f$
 * @param [in] index_k : index \f$K\f$ for the Silvester Polynomial in \f$1-\xi-\eta\f$
 * @param [in] ksi : point in the \f$\xi\f$ axis in which to evaluate (\f$ 0\leq \xi \leq 1 \f$)
 * @param [in] eta : point in the \f$\eta\f$ axis in which to evaluate (\f$ 0\leq \eta \leq \xi \f$)
 * @return : \f$ \frac{\partial}{\partial\eta}N_{i}(\xi,\eta) \f$. */
//************************************************************************************************//
cemDOUBLE TriShapeFunction::EvaluateEtaDeriv(const cemINT &index_i,
                                             const cemINT &index_j,
                                             const cemINT &index_k,
                                             const cemDOUBLE &ksi,
                                             const cemDOUBLE &eta) const
{
    cemDOUBLE first_term = SilvesterPolynomial(index_i,ksi);
    first_term *= SilvesterPolynomialDeriv(index_j,eta);
    first_term *= SilvesterPolynomial(index_k,1-ksi-eta);

    cemDOUBLE second_term = SilvesterPolynomial(index_i,ksi);
    second_term *= SilvesterPolynomial(index_j,eta);
    second_term *= SilvesterPolynomialDeriv(index_k,1-ksi-eta);

    return first_term-second_term;
}



//************************************************************************************************//
/** @brief TriShapeFunction::Evaluate : Evaluates shape function at several points in unit-triangle.
 *
 * Shape Function is defined as the product of three Silverter Polynomials:
 * \f$ N_{i}(\xi,\eta) = P_{I}^{N}(\xi)P_{J}^{N}(\eta)P_{K}^{N}(1-\xi-\eta) \f$.
 * For each value of \f$ i=1,2,\ldots,(N+1)(N+2)/2 \f$ there is a permutation of values for the
 * indices \f$ I,J,K \f$ such that \f$ I+J+K = N \f$.
 * @param [in] order : order \f$N\f$ of the shape function to evaluate (order >= 1)
 * @param [in] index_i : index \f$I\f$ for the Silvester Polynomial in \f$\xi\f$
 * @param [in] index_j : index \f$J\f$ for the Silvester Polynomial in \f$\eta\f$
 * @param [in] index_k : index \f$K\f$ for the Silvester Polynomial in \f$1-\xi-\eta\f$
 * @param [in] ksi : points in the \f$\xi\f$ axis in which to evaluate (\f$ 0\leq \xi \leq 1 \f$)
 * @param [in] eta : points in the \f$\eta\f$ axis in which to evaluate (\f$ 0\leq \eta \leq \xi \f$)
 * @return : \f$ N_{i}(\xi,\eta) = P_{I}^{N}(\xi)P_{J}^{N}(\eta)P_{K}^{N}(1-\xi-\eta) \f$. */
//************************************************************************************************//
std::vector<cemDOUBLE> TriShapeFunction::Evaluate(const cemINT& index_i,
                                                  const cemINT& index_j,
                                                  const cemINT& index_k,
                                                  const std::vector<cemDOUBLE>& ksi,
                                                  const std::vector<cemDOUBLE>& eta) const
{
    if (index_i + index_j + index_k > order_)
        throw(Exception("INPUT ERROR","Sum of indices must be <= order"));

    cemINT N = ksi.size();
    if (eta.size() != N)
        throw(Exception("INPUT ERROR","Vectors ksi and eta have different dimensions"));

    std::vector<cemDOUBLE> result;
    result.resize(N);

    for (cemINT i=0; i<N; ++i)
        result[i] = Evaluate(index_i,index_j,index_k,ksi[i],eta[i]);

    return result;
}


//************************************************************************************************//
/** @brief TriShapeFunction::EvaluateKsiDeriv : Evaluates the ksi derivative of shape function at
 * multiple points in the unit-triangle.
 *
 * The derivative with respect to \f$ \xi \f$ is evaluated as follows: \f$ \frac{\partial N_{i}}
 * {\partial\xi} = \frac{d}{d\xi}P_{I}^{N}(\xi)P_{J}^{N}(\eta)
 * P_{K}^{N}(1-\xi-\eta) - P_{I}^{N}(\xi)P_{J}^{N}(\eta)\frac{d}{d\alpha}P_{K}^{N}(\alpha) \f$
 * @param [in] order : order \f$N\f$ of the shape function to evaluate (order >= 1)
 * @param [in] index_i : index \f$I\f$ for the Silvester Polynomial in \f$\xi\f$
 * @param [in] index_j : index \f$J\f$ for the Silvester Polynomial in \f$\eta\f$
 * @param [in] index_k : index \f$K\f$ for the Silvester Polynomial in \f$1-\xi-\eta\f$
 * @param [in] ksi : points in the \f$\xi\f$ axis in which to evaluate (\f$ 0\leq \xi \leq 1 \f$)
 * @param [in] eta : points in the \f$\eta\f$ axis in which to evaluate (\f$ 0\leq \eta \leq \xi \f$)
 * @return : \f$ \frac{\partial}{\partial\xi}N_{i}(\xi,\eta) \f$. */
//************************************************************************************************//
std::vector<cemDOUBLE> TriShapeFunction::EvaluateKsiDeriv(const cemINT &index_i,
                                                          const cemINT &index_j,
                                                          const cemINT &index_k,
                                                          const std::vector<cemDOUBLE> &ksi,
                                                          const std::vector<cemDOUBLE> &eta) const
{
    if (index_i + index_j + index_k > order_)
        throw(Exception("INPUT ERROR","Sum of indices must be <= order"));

    cemINT N = ksi.size();
    if (eta.size() != N)
        throw(Exception("INPUT ERROR","Vectors ksi and eta have different dimensions"));

    std::vector<cemDOUBLE> result;
    result.resize(N);

    for (cemINT i=0; i<N; ++i)
        result[i] = EvaluateKsiDeriv(index_i,index_j,index_k,ksi[i],eta[i]);

    return result;
}


//************************************************************************************************//
/** @brief TriShapeFunction::EvaluateEtaDeriv : Evaluates the eta derivative of shape function at
 * multiple points in the unit-triangle.
 *
 * The derivative with respect to \f$ \eta \f$ is evaluated as follows: \f$ \frac{\partial N_{i}}
 * {\partial\eta} = P_{I}^{N}(\xi)\frac{d}{d\eta}P_{J}^{N}(\eta)P_{K}^{N}(1-\xi-\eta)
 * - P_{I}^{N}(\xi)P_{J}^{N}(\eta)\frac{d}{d\alpha}P_{K}^{N}(\alpha) \f$
 * @param [in] order : order \f$N\f$ of the shape function to evaluate (order >= 1)
 * @param [in] index_i : index \f$I\f$ for the Silvester Polynomial in \f$\xi\f$
 * @param [in] index_j : index \f$J\f$ for the Silvester Polynomial in \f$\eta\f$
 * @param [in] index_k : index \f$K\f$ for the Silvester Polynomial in \f$1-\xi-\eta\f$
 * @param [in] ksi : points in the \f$\xi\f$ axis in which to evaluate (\f$ 0\leq \xi \leq 1 \f$)
 * @param [in] eta : points in the \f$\eta\f$ axis in which to evaluate (\f$ 0\leq \eta \leq \xi \f$)
 * @return : \f$ \frac{\partial}{\partial\eta}N_{i}(\xi,\eta) \f$. */
//************************************************************************************************//
std::vector<cemDOUBLE> TriShapeFunction::EvaluateEtaDeriv(const cemINT &index_i,
                                                          const cemINT &index_j,
                                                          const cemINT &index_k,
                                                          const std::vector<cemDOUBLE> &ksi,
                                                          const std::vector<cemDOUBLE> &eta) const
{
    if (index_i + index_j + index_k > order_)
        throw(Exception("INPUT ERROR","Sum of indices must be <= order"));

    cemINT N = ksi.size();
    if (eta.size() != N)
        throw(Exception("INPUT ERROR","Vectors ksi and eta have different dimensions"));

    std::vector<cemDOUBLE> result;
    result.resize(N);

    for (cemINT i=0; i<N; ++i)
        result[i] = EvaluateEtaDeriv(index_i,index_j,index_k,ksi[i],eta[i]);

    return result;
}







