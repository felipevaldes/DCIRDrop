#ifndef CEMCONSTS_H
#define CEMCONSTS_H

#include "cemTypes.h"

namespace cem_const
{
// Versions of Pi:
const cem_def::cemDOUBLE PI =     3.1415926535897932384626433832795;
const cem_def::cemDOUBLE PI2 =    6.283185307179586476925286766559;
const cem_def::cemDOUBLE PI4 =    12.566370614359172953850573533118;
const cem_def::cemDOUBLE PI8 =    25.132741228718355907701147066236;
const cem_def::cemDOUBLE PI_2 =   1.5707963267948966192313216916398;
const cem_def::cemDOUBLE PI_4 =   0.78539816339744830961566084581988;
const cem_def::cemDOUBLE PI_8 =   0.39269908169872415480783042290994;
const cem_def::cemDOUBLE SqrtPi = 1.7724538509055160272981674833411;

// Square Root of 2:
const cem_def::cemDOUBLE Sqrt2 =     1.4142135623730950488016887242097;
const cem_def::cemDOUBLE Sqrt_2	=   0.70710678118654752440084436210485;

// Physical Constants:
const cem_def::cemDOUBLE C_0 = 2.99792458e+8;
const cem_def::cemDOUBLE MU_0 =  PI*4.0e-07;
const cem_def::cemDOUBLE EPSILON_0 = 1.0/(C_0*C_0*MU_0);
const cem_def::cemDOUBLE ETA_0 = sqrt(MU_0/EPSILON_0);

// Unit Conversions:
const cem_def::cemDOUBLE	DEG_TO_RAD = PI/180.0;
const cem_def::cemDOUBLE	RAD_TO_DEG = 180.0/PI;
const cem_def::cemDOUBLE	INCHES_TO_METERS = 0.0254;
const cem_def::cemDOUBLE METERS_TO_MICRONS = 1000000;

// Unit Complex:
const cem_def::cemDCOMPLEX CMPLX_ZERO = (0.0, 0.0);
const cem_def::cemDCOMPLEX CMPLX_ONE = (1.0, 0.0);
const cem_def::cemDCOMPLEX CMPLX_J = (0.0, 1.0);
}


#endif // CEMCONSTS_H
