/*
 * LinearFluxFunction.cpp
 *
 *  Created on: 5 janv. 2016
 *      Author: delpopol
 */

#include "../HyperbolicEquationUpwindRHSFunction/LinearFluxFunction.h"

LinearFluxFunction::LinearFluxFunction() {
	a = 0;
}

LinearFluxFunction::~LinearFluxFunction() {}

Real LinearFluxFunction::getA() const {
	return a;
}

void LinearFluxFunction::setA(Real a) {
	this->a = a;
}

Real LinearFluxFunction::evalF(Real time, Real y_sol){

	Real val = (a * y_sol);
	return val;

}

Real LinearFluxFunction::evalFderivative(Real time, Real y_sol){
	
	return a;
}
