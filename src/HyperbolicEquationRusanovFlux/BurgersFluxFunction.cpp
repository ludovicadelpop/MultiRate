/*
 * BurgersFluxFunction.cpp
 *
 *  Created on: 19/gen/2016
 *      Author: ludovicadelpopolo
 */

#include "BurgersFluxFunction.h"

BurgersFluxFunction::BurgersFluxFunction() {}

BurgersFluxFunction::~BurgersFluxFunction() {}

Real BurgersFluxFunction::evalF(Real time, Real y_sol){

	Real val = 0.5 * y_sol * y_sol;
	return val;

}

Real BurgersFluxFunction::evalFderivative(Real time, Real y_sol){

	Real val = y_sol;
	return val;
}
