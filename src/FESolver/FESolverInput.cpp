/*
 * FESolverInput.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "FESolverInput.h"

FESolverInput::FESolverInput() {
	dt = 0;
	t0 = 0;
}

FESolverInput::~FESolverInput() {}

void FESolverInput::set(Real t0, Real dt, RealVector& y0){
	this->dt=dt;
	this->t0=t0;
	this->y0=y0;
}

Real FESolverInput::getDt() const {
	return dt;
}


Real FESolverInput::getT0() const {
	return t0;
}

const RealVector& FESolverInput::getY0() const {
	return y0;
}
