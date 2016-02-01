#ifndef QUADRATURE_H
#define QUADRATURE_H

#include <map>
#include <vector>
#include "cemTypes.h"

using namespace cem_def;

namespace cem_core {

//************************************************************************************************//
/** @brief The Quadrature class : Generic Quadrature rule. */
//************************************************************************************************//
class Quadrature
{
public:
    Quadrature()
    {
        using_ksi_ = false;
        using_eta_ = false;
        using_zeta_ = false;
    }

    cemINT getNumPointsForPolyOrder(const cemINT& order) const;
    cemINT getNumPointsAbove(const cemINT& number) const ;
    cemINT getNumPointsBelow(const cemINT& number) const;
    cemINT getNumberOfRules() const;

    const std::vector<cemDOUBLE>& getKsiCoordinates(const cemINT& num_points) const;
    const std::vector<cemDOUBLE>& getEtaCoordinates(const cemINT& num_points) const;
    const std::vector<cemDOUBLE>& getZetaCoordinates(const cemINT& num_points) const;
    const std::vector<cemDOUBLE>& getWeights(const cemINT& num_points) const;


protected:
    cemBOOL using_ksi_;     //!< True if the quadrature rule has ksi coordinates.
    cemBOOL using_eta_;     //!< True if the quadrature rule has eta coordinates.
    cemBOOL using_zeta_;    //!< True if the quadrature rule has zeta coordinates.
    std::map< cemINT,std::vector<cemDOUBLE> > ksi_;     //!< ksi coordinates for several rules.
    std::map< cemINT,std::vector<cemDOUBLE> > eta_;     //!< eta coordinates for several rules.
    std::map< cemINT,std::vector<cemDOUBLE> > zeta_;    //!< zeta coordinates for several rules.
    std::map< cemINT,std::vector<cemDOUBLE> > weight_;  //!< weights coordinates for several rules.
    std::map< cemINT,cemINT > order_to_num_points_;     //!< map from order to number of points.
};


//************************************************************************************************//
/** @brief The LineQuadrature class : Quadrature rules for Lines.
 *
 * Quadrature rules are designed to integrate functions defined on the interval [-1,1]. */
//************************************************************************************************//
class LineQuadrature : public Quadrature
{
public:
    LineQuadrature() : Quadrature() {initialize();}

private:
    void initialize();
};


//************************************************************************************************//
/** @brief The TriQuadrature class : Quadrature rules for Triangles.
 *
 * Quadrature rules are designed to integrate functions defined on the unit triangle, i.e.
 * right-angled triangle with 2 sides of length 1 (Area = 1/2). */
//************************************************************************************************//
class TriQuadrature : public Quadrature
{
public:
    TriQuadrature() : Quadrature() {initialize();}

private:
    void initialize();
};


//************************************************************************************************//
/** @brief The QuadQuadrature class : Quadrature rules for Quadrangles. */
//************************************************************************************************//
class QuadQuadrature : public Quadrature
{
public:
    QuadQuadrature() : Quadrature() {initialize();}

private:
    void initialize();
};


//************************************************************************************************//
/** @brief The TetraQuadrature class : Quadrature rules for Tetrahedra. */
//************************************************************************************************//
class TetraQuadrature : public Quadrature
{
public:
    TetraQuadrature() : Quadrature() {initialize();}

private:
    void initialize();
};


//************************************************************************************************//
/** @brief The HexaQuadrature class : Quadrature rules for Hexahedra. */
//************************************************************************************************//
class HexaQuadrature : public Quadrature
{
public:
    HexaQuadrature() : Quadrature() {initialize();}

private:
    void initialize();
};


//************************************************************************************************//
/** @brief The PrismQuadrature class : Quadrature rules for Prisms. */
//************************************************************************************************//
class PrismQuadrature : public Quadrature
{
public:
    PrismQuadrature() : Quadrature() {initialize();}

private:
    void initialize();
};


//************************************************************************************************//
/** @brief The PyraQuadrature class : Quadrature rules for Pyramids. */
//************************************************************************************************//
class PyraQuadrature : public Quadrature
{
public:
    PyraQuadrature() : Quadrature() {initialize();}

private:
    void initialize();
};



}


#endif // QUADRATURE_H
