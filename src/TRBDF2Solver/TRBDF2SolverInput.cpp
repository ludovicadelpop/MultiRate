/*
 * TRBDF2SolverInput.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#include "TRBDF2SolverInput.h"

TRBDF2SolverInput::TRBDF2SolverInput() {
	tol_abs = 1.e-6;
	tol_rel = 1.e-4;
	h = 0;
	t0 = 0;
}

TRBDF2SolverInput::~TRBDF2SolverInput() {}

void TRBDF2SolverInput::setInput(Real t0,Real h,RealVector& hz1,RealVector& y0,RealVector& y1,RealVector& y2,RealMatrixSparse& matrixiter,
				Real tolAbsolute, Real tolRelative, IntegerVector& ref){
	this->h = h;
	this->hz_1 = hz1;
	this->t0 = t0;
	this->tol_abs = tolAbsolute;
	this->tol_rel = tolRelative;
	this->y0 = y0;
	this->y1 = y1;
	this->y2 = y2;
	this->matrix_iter = matrixiter;
	this->ref = ref;
}

Real TRBDF2SolverInput::getH() const {
	return h;
}

RealVector& TRBDF2SolverInput::getHz1() {
	return hz_1;
}

Real TRBDF2SolverInput::getT0() const {
	return t0;
}

Real TRBDF2SolverInput::getTolAbs() const {
	return tol_abs;
}

Real TRBDF2SolverInput::getTolRel() const {
	return tol_rel;
}

RealVector& TRBDF2SolverInput::getY0(){
	return y0;
}

RealMatrixSparse& TRBDF2SolverInput::getMatrixIter() {
	return matrix_iter;
}

const IntegerVector& TRBDF2SolverInput::getRef() const {
	return ref;
}

const RealVector& TRBDF2SolverInput::getY1() const {
	return y1;
}

const RealVector& TRBDF2SolverInput::getY2() const {
	return y2;
}
