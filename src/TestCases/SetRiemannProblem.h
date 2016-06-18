/*
 * SetRiemannProblem.h
 *
 *  Created on: 19/gen/2016
 *      Author: ludovicadelpopolo
 */

#ifndef SETRIEMANNPROBLEM_H_
#define SETRIEMANNPROBLEM_H_

#include "StandardTypes.h"
using namespace Utils;

namespace SetRiemannProblem{
void InitialConditionFunction(RealVector& y0, Real& x0, Integer& Nx, Real& xL){

	RealVector x(Nx);
	x.setLinSpaced(Nx,x0,xL);

	Integer size = x.size();
	y0.resize(size);

	for(Integer i=0; i < size; ++i){
		Real xi = x[i];
		if (xi <= 0.0)
			y0[i] = 0.0;
		else
			y0[i] = 1.0;
	}
}



}



#endif /* SETRIEMANNPROBLEM_H_ */
