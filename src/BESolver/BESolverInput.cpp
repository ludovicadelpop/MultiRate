/*
 * BESolverInput.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "BESolverInput.h"

BESolverInput::BESolverInput() {
	dt = 0;
	t0 = 0;
	Newton_tol_rel = 1.e-4;
	Newton_tol_abs = 1.e-6;
}

BESolverInput::~BESolverInput() {}

void BESolverInput::set(Real t0, Real dt, RealVector& y0, Real Newton_tol_rel, Real Newton_tol_abs){
	this->dt=dt;
	this->t0=t0;
	this->y0=y0;
	this->Newton_tol_abs = Newton_tol_abs;
	this->Newton_tol_rel = Newton_tol_rel;
}

Real BESolverInput::getDt() const {
	return dt;
}

Real BESolverInput::getT0() const {
	return t0;
}

RealVector& BESolverInput::getY0() {
	return y0;
}


Real BESolverInput::getNewtonTolAbs() const {
	return Newton_tol_abs;
}

Real BESolverInput::getNewtonTolRel() const {
	return Newton_tol_rel;
}

