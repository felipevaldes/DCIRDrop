#ifndef CEMSPACE_H
#define CEMSPACE_H

#include "cemTypes.h"

namespace cem_space
{

///***********************************************************************************************//
/// CLASS: V3
///***********************************************************************************************//
template <class T> class V3
{
public:
    /** @brief V3<T> : Default constructor */
    V3<T>() {coord_[0] = coord_[1] = coord_[2] = 0.0;}

    /** @brief V3<T> : Constructor with parameters. */
    V3<T>(const T& x1, const T& x2, const T& x3)
    {coord_[0] = x1; coord_[1] = x2; coord_[2] = x3;}

    /** @brief V3<T> : Copy constructor. */
    V3<T>(const V3<T>& V) {copy(V);}

    /** @brief operator = : Copy operator. */
    V3<T>& operator=(const V3<T>& V) {copy(V);}

    /** @brief operator [] : Random access operator. */
    const T& operator[](const cem_def::cemINT& i) const {return coord_[i];}
    const T& operator[](const cem_def::cemUINT& i) const {return coord_[i];}

    /** @brief operator [] : Random access asignment. */
    T& operator[](const cem_def::cemINT& i) {return coord_[i];}
    T& operator[](const cem_def::cemUINT& i) {return coord_[i];}

    /** @brief operator == : Equal operator: TRUE if all coordinates are equal. */
    cem_def::cemBOOL operator == (const V3<T>& other) const
    {
        if (coord_[0] == other.coord_[0] &&
            coord_[1] == other.coord_[1] &&
            coord_[2] == other.coord_[2])
            return true;
        else
            return false;
    }

    /** @brief operator *= : Multiply vector by scalar. */
    V3<T> operator *= (const T& scalar)
    {
        coord_[0] *= scalar;
        coord_[1] *= scalar;
        coord_[2] *= scalar;
        return *this;
    }

    /** @brief Add : Vector addition. */
    void Add(const V3<T>& V)
    {
        coord_[0] += V.coord_[0];
        coord_[1] += V.coord_[1];
        coord_[2] += V.coord_[2];
    }

    /** @brief operator + : Vector addition operator. */
    V3<T> operator + (const V3<T>& V)
    {
        this->Add(V);
        return *this;
    }

    /** @brief Substract : Vector substraction. */
    void Substract(const V3<T>& V)
    {
        coord_[0] -= V.coord_[0];
        coord_[1] -= V.coord_[1];
        coord_[2] -= V.coord_[2];
    }

    /** @brief operator - : Vector substraction operator. */
    V3<T> operator - (const V3<T>& V)
    {
        this->Substract(V);
        return *this;
    }

    /** @brief Dot : Vector dot (scalar) product. */
    T Dot (const V3<T>& V) const
    {
        return (coord_[0]*V.coord_[0] + coord_[1]*V.coord_[1] + coord_[2]*V.coord_[2]);
    }

    /** @brief NormSquared : Computes Norm-2 squared of vector. */
    T NormSquared () const
    {
        return this->Dot(*this);
    }

    /** @brief Norm : Computes Norm-2 of vector. */
    T Norm () const
    {
        return sqrt(NormSquared());
    }

    /** @brief Cross : Computes Vector Cross Product. */
    V3<T> Cross (const V3<T>& V) const
    {
        return V3<T>(
                coord_[1]*V.coord_[2] - coord_[2]*V.coord_[1],
                coord_[2]*V.coord_[0] - coord_[0]*V.coord_[2],
                coord_[0]*V.coord_[1] - coord_[1]*V.coord_[0]);
    }

protected:
    /** @brief copy: Deep copy of V3. */
    void copy(const V3<T>& V)
    {
        coord_[0] = V.coord_[0];
        coord_[1] = V.coord_[1];
        coord_[2] = V.coord_[2];
    }

private:
    T coord_[3];        /**< 3 coordinates vector */
};




///***********************************************************************************************//
/// TYPEDEF: V3D
///***********************************************************************************************//
typedef V3<cem_def::cemDOUBLE> V3D;

inline std::ostream& operator << (std::ostream& out_stream, const V3D& V)
{
    // Set precision to 5 and display type to scientific
    // Store old values to leave out_stream unaltered
    std::ios::fmtflags	flags = out_stream.setf(std::ios::scientific);
    int precision = static_cast<int>(out_stream.precision(5));

    out_stream <<  V[0] << "\t" << V[1] << "\t" << V[2];

    out_stream.flags(flags);
    out_stream.precision(precision);
    return out_stream;
}




///***********************************************************************************************//
/// CLASS: V2
///***********************************************************************************************//
template <class T> class V2
{
public:
    /** @brief V2<T> : Default constructor */
    V2<T>() {coord_[0] = coord_[1] = 0.0;}

    /** @brief V2<T> : Constructor with parameters. */
    V2<T>(const T& x1, const T& x2)
    {coord_[0] = x1; coord_[1] = x2;}

    /** @brief V2<T> : Copy constructor. */
    V2<T>(const V2<T>& V) {copy(V);}

    /** @brief operator = : Copy operator. */
    V2<T>& operator=(const V2<T>& V)
    {
        copy(V);
        return *this;
    }

    /** @brief operator [] : Random access operator. */
    const T& operator[](const cem_def::cemINT& i) const {return coord_[i];}
    const T& operator[](const cem_def::cemUINT& i) const {return coord_[i];}

    /** @brief operator [] : Random access asignment. */
    T& operator[](const cem_def::cemINT& i) {return coord_[i];}
    T& operator[](const cem_def::cemUINT& i) {return coord_[i];}

    /** @brief operator == : Equal operator: TRUE if all coordinates are equal. */
    cem_def::cemBOOL operator == (const V2<T>& other) const
    {
        if (coord_[0] == other.coord_[0] &&
            coord_[1] == other.coord_[1])
            return true;
        else
            return false;
    }

    /** @brief operator *= : Multiply vector by scalar. */
    V2<T> operator *= (const T& scalar)
    {
        coord_[0] *= scalar;
        coord_[1] *= scalar;
        return *this;
    }

    /** @brief Add : Vector addition. */
    void Add(const V2<T>& V)
    {
        coord_[0] += V.coord_[0];
        coord_[1] += V.coord_[1];
    }

    /** @brief operator + : Vector addition operator. */
    V2<T> operator + (const V2<T>& V)
    {
        this->Add(V);
        return *this;
    }

    /** @brief Substract : Vector substraction. */
    void Substract(const V2<T>& V)
    {
        coord_[0] -= V.coord_[0];
        coord_[1] -= V.coord_[1];
    }

    /** @brief operator - : Vector substraction operator. */
    V2<T> operator - (const V2<T>& V)
    {
        this->Substract(V);
        return *this;
    }

    /** @brief Dot : Vector dot (scalar) product. */
    T Dot (const V2<T>& V) const
    {
        return (coord_[0]*V.coord_[0] + coord_[1]*V.coord_[1]);
    }

    /** @brief NormSquared : Computes Norm-2 squared of vector. */
    T NormSquared () const
    {
        return this->Dot(*this);
    }

    /** @brief Norm : Computes Norm-2 of vector. */
    T Norm () const
    {
        return sqrt(NormSquared());
    }

    /** @brief Cross : Computes Vector Cross Product. */
    T Cross (const V2<T>& V) const
    {
        return coord_[0]*V.coord_[1] - coord_[1]*V.coord_[0];
    }

protected:
    void copy(const V2<T>& V)
    {coord_[0] = V.coord_[0]; coord_[1] = V.coord_[1];}

private:
    T coord_[2];
};

///***********************************************************************************************//
/// TYPEDEF: V2D
///***********************************************************************************************//
typedef V2<cem_def::cemDOUBLE> V2D;

inline std::ostream& operator << (std::ostream& out_stream, const V2D& V)
{
    // Set precision to 5 and display type to scientific
    // Store old values to leave out_stream unaltered
    std::ios::fmtflags	flags = out_stream.setf(std::ios::scientific);
    int precision = static_cast<int>(out_stream.precision(5));

    out_stream <<  V[0] << "\t" << V[1];

    out_stream.flags(flags);
    out_stream.precision(precision);
    return out_stream;
}


}

#endif // CEMSPACE_H

