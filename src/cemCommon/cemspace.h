#ifndef CEMSPACE_H
#define CEMSPACE_H

#include "cemTypes.h"

namespace cem_space
{

/////////////////////////////////////////////////////////////////////
/// 3D Vector:
/////////////////////////////////////////////////////////////////////
template <class T> class V3
{
private:
    T coord_[3];

public:
    //====================================================
    // Constructors and Destructors:
    //====================================================
    // Default constructor:
    V3<T>() {coord_[0] = coord_[1] = coord_[2] = 0.0;}

    // Constructor from given coordinates:
    V3<T>(const T& x1, const T& x2, const T& x3)
    {coord_[0] = x1; coord_[1] = x2; coord_[2] = x3;}

    // Copy constructor:
    V3<T>(const V3<T>& V)
    {
        coord_[0] = V.coord_[0];
        coord_[1] = V.coord_[1];
        coord_[2] = V.coord_[2];
    }

    // Copy operator:
    V3<T>& operator=(const V3<T>& V)
    {
        coord_[0] = V.coord_[0];
        coord_[1] = V.coord_[1];
        coord_[2] = V.coord_[2];
        return *this;
    }

    // Destructor:
    ~V3<T>(void) {;}

    // Random access
    const T& operator[](const cem_def::cemINT& i) const {return coord_[i];}
    const T& operator[](const cem_def::cemUINT& i) const {return coord_[i];}

    // Random access assignment
    T& operator[](const cem_def::cemINT& i) {return coord_[i];}
    T& operator[](const cem_def::cemUINT& i) {return coord_[i];}

    //====================================================
    // Math Operations:
    //====================================================
    cem_def::cemBOOL operator == (const V3<T>& other) const
    {
        if (coord_[0] == other.coord_[0] &&
            coord_[1] == other.coord_[1] &&
            coord_[2] == other.coord_[2])
            return true;
        else
            return false;
    }

    // Multiply by scalar:
    V3<T> operator *= (const T& scalar)
    {
        coord_[0] *= scalar;
        coord_[1] *= scalar;
        coord_[2] *= scalar;
        return *this;
    }

    // Add 3D Vector:
    void Add(const V3<T>& V)
    {
        coord_[0] += V.coord_[0];
        coord_[1] += V.coord_[1];
        coord_[2] += V.coord_[2];
    }
    V3<T> operator + (const V3<T>& V)
    {
        this->Add(V);
        return *this;
    }

    // Substract 3D Vector:
    void Substract(const V3<T>& V)
    {
        coord_[0] -= V.coord_[0];
        coord_[1] -= V.coord_[1];
        coord_[2] -= V.coord_[2];
    }
    V3<T> operator - (const V3<T>& V)
    {
        this->Substract(V);
        return *this;
    }

    // Dot Product:
    T Dot (const V3<T>& V) const
    {
        return (coord_[0]*V.coord_[0] + coord_[1]*V.coord_[1] + coord_[2]*V.coord_[2]);
    }

    // Norm Squared:
    T NormSquared () const
    {
        return this->Dot(*this);
    }

    // Norm:
    T Norm () const
    {
        return sqrt(NormSquared());
    }

    // Cross Product:
    V3<T> Cross (const V3<T>& V) const
    {
        return V3<T>(
                coord_[1]*V.coord_[2] - coord_[2]*V.coord_[1],
                coord_[2]*V.coord_[0] - coord_[0]*V.coord_[2],
                coord_[0]*V.coord_[1] - coord_[1]*V.coord_[0]);
    }
};


/////////////////////////////////////////////////////////////////////
/// Double precision 3D Vector:
/////////////////////////////////////////////////////////////////////
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





/////////////////////////////////////////////////////////////////////
/// 2D Vector:
/////////////////////////////////////////////////////////////////////
template <class T> class V2
{
private:
    T coord_[2];

public:
    //====================================================
    // Constructors and Destructors:
    //====================================================
    // Default constructor:
    V2<T>() {coord_[0] = coord_[1] = 0.0;}

    // Constructor from given coordinates:
    V2<T>(const T& x1, const T& x2)
    {coord_[0] = x1; coord_[1] = x2;}

    // Copy constructor:
    V2<T>(const V2<T>& V)
    {coord_[0] = V.coord_[0]; coord_[1] = V.coord_[1];}

    // Copy operator:
    V2<T>& operator=(const V2<T>& V)
    {
        coord_[0] = V.coord_[0];
        coord_[1] = V.coord_[1];
        return *this;
    }

    // Destructor:
    ~V2<T>(void) {;}

    // Random access
    const T& operator[](const cem_def::cemINT& i) const {return coord_[i];}
    const T& operator[](const cem_def::cemUINT& i) const {return coord_[i];}

    // Random access assignment
    T& operator[](const cem_def::cemINT& i) {return coord_[i];}
    T& operator[](const cem_def::cemUINT& i) {return coord_[i];}

    //====================================================
    // Math Operations:
    //====================================================
    cem_def::cemBOOL operator == (const V2<T>& other) const
    {
        if (coord_[0] == other.coord_[0] &&
            coord_[1] == other.coord_[1])
            return true;
        else
            return false;
    }

    // Multiply by scalar:
    V2<T> operator *= (const T& scalar)
    {
        coord_[0] *= scalar;
        coord_[1] *= scalar;
        return *this;
    }

    // Add 2D Vector:
    void Add(const V2<T>& V)
    {
        coord_[0] += V.coord_[0];
        coord_[1] += V.coord_[1];
    }
    V2<T> operator + (const V2<T>& V)
    {
        this->Add(V);
        return *this;
    }

    // Substract 2D Vector:
    void Substract(const V2<T>& V)
    {
        coord_[0] -= V.coord_[0];
        coord_[1] -= V.coord_[1];
    }
    V2<T> operator - (const V2<T>& V)
    {
        this->Substract(V);
        return *this;
    }

    // Dot Product:
    T Dot (const V2<T>& V) const
    {
        return (coord_[0]*V.coord_[0] + coord_[1]*V.coord_[1]);
    }

    // Norm Squared:
    T NormSquared () const
    {
        return this->Dot(*this);
    }

    // Norm:
    T Norm () const
    {
        return sqrt(NormSquared());
    }

    // Cross Product:
    T Cross (const V2<T>& V) const
    {
        return coord_[0]*V.coord_[1] - coord_[1]*V.coord_[0];
    }
};

/////////////////////////////////////////////////////////////////////
/// Double precision 2D Vector:
/////////////////////////////////////////////////////////////////////
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

