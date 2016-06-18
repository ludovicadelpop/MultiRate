/*
 * TwoPhaseFlowFluxFunction.cpp
 *
 *  Created on: 6 janv. 2016
 *      Author: delpopol
 */

#include "TwoPhaseFlowFluxFunction.h"

TwoPhaseFlowFluxFunction::TwoPhaseFlowFluxFunction() {
	a = 0;
}

TwoPhaseFlowFluxFunction::~TwoPhaseFlowFluxFunction() {}

Real TwoPhaseFlowFluxFunction::getA() const {
	return a;
}

void TwoPhaseFlowFluxFunction::setA(Real a) {
	this->a = a;
}

Real TwoPhaseFlowFluxFunction::evalF(Real time, Real y_sol){

	Real val = (y_sol * y_sol)/( (y_sol*y_sol) + a*(1-y_sol)*(1-y_sol) );
	return val;

}

Real TwoPhaseFlowFluxFunction::evalFderivative(Real time, Real y_sol){
	
	Real val = (2 *y_sol *a *(1-y_sol))/(( (y_sol*y_sol) + a*(1-y_sol)*(1-y_sol))*((y_sol*y_sol) + a*(1-y_sol)*(1-y_sol)) );
	return val;
}
