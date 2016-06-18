/*
 * TRBDF2SolverParameters.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#include "TRBDF2SolverParameters.h"

TRBDF2SolverParameters::TRBDF2SolverParameters() {
	pd0 = 1.5+sqrt(2.0);
	pd1 = 2.5+2.0*sqrt(2.0);
	pd2 = -(6+4.5*sqrt(2.0));
	gm = 2.0-sqrt(2.0);
	d =  gm/2.0;
	w = sqrt(2.0)/4.0;
	e0 = (1.0-w)/3.0;
	e1 = w+1.0/3.0;
	e2 = d/3.0;

}

TRBDF2SolverParameters::~TRBDF2SolverParameters() {}

Real TRBDF2SolverParameters::getD() const {
	return d;
}

Real TRBDF2SolverParameters::getE0() const {
	return e0;
}

Real TRBDF2SolverParameters::getE1() const {
	return e1;
}

Real TRBDF2SolverParameters::getE2() const {
	return e2;
}

Real TRBDF2SolverParameters::getGm() const {
	return gm;
}

Real TRBDF2SolverParameters::getPd0() const {
	return pd0;
}

Real TRBDF2SolverParameters::getPd1() const {
	return pd1;
}

Real TRBDF2SolverParameters::getPd2() const {
	return pd2;
}

Real TRBDF2SolverParameters::getW() const {
	return w;
}

void TRBDF2SolverParameters::setParam(Real pd0,Real pd1, Real pd2, Real e0, Real e1, Real e2, Real gm, Real d, Real w){
	this->pd0 = pd0;
	this->pd1 = pd1;
	this->pd2 = pd2;
	this->gm = gm;
	this->d =  d;
	this->w = w;
	this->e0 = e0;
	this->e1 = e1;
	this->e2 = e2;
}
