/*
 * SetProblemLinearHyperbolicEquation.h
 *
 *  Created on: 22 déc. 2015
 *      Author: delpopol
 */

#ifndef SETPROBLEMLINEARHYPERBOLICEQUATION_H_
#define SETPROBLEMLINEARHYPERBOLICEQUATION_H_

#include "StandardTypes.h"
using namespace Utils;

namespace SetProblemLinearHyperbolicEquation{
//! initial condition gaussian function
void InitialConditionFunction(RealVector& y0, Real& x0, Integer& Nx, Real& xL){

	RealVector x(Nx);
	x.setLinSpaced(Nx,x0,xL);

	y0.resize(Nx);

	for(Integer i=0; i < Nx; ++i){
		Real xi = x[i];
		y0[i] = exp(-xi*xi);
	}
}
//! initial condition constant function
void InitialConditionCostant(RealVector& y0, Real& x0, Integer& Nx, Real& xL,Real constant_value){

	RealVector x(Nx);
	x.setLinSpaced(Nx,x0,xL);

	Integer size = x.size();
	y0.resize(size);
	y0.fill(constant_value);

}

}


#endif /* SETPROBLEMLINEARHYPERBOLICEQUATION_H_ */
