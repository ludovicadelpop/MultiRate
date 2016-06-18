/*
 * BurgersFluxFunction.h
 *
 *  Created on: 19/gen/2016
 *      Author: ludovicadelpopolo
 */

#ifndef BURGERSFLUXFUNCTION_H_
#define BURGERSFLUXFUNCTION_H_

#include "IFluxFunction.h"

//! Burgers Flux for Hyperbolic PDE
class BurgersFluxFunction : public IFluxFunction{
public:
	BurgersFluxFunction();
	virtual ~BurgersFluxFunction();

	Real evalF(Real time, Real y_sol);
	Real evalFderivative(Real time, Real y_sol);

};


#endif /* BURGERSFLUXFUNCTION_H_ */
