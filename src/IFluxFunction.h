/*
 * IFluxFunction.h
 *
 *  Created on: 5 janv. 2016
 *      Author: delpopol
 */

#ifndef IFLUXFUNCTION_H_
#define IFLUXFUNCTION_H_

#include "StandardTypes.h"

using namespace Utils;

//! Base class for the flux function of the Hyperbolic equation
class IFluxFunction {
public:
	IFluxFunction(){}
	virtual ~IFluxFunction(){}

	virtual Real evalF(Real time, Real y_sol) = 0;
	virtual Real evalFderivative(Real time, Real y_sol) = 0;

};

#endif /* IFLUXFUNCTION_H_ */
