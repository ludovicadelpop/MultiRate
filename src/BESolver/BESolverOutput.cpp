/*
 * BESolverOutput.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "BESolverOutput.h"

BESolverOutput::BESolverOutput() {
	t_final = 0;
	dt = 0;
	is_converged = false;
}

BESolverOutput::~BESolverOutput() {}

void BESolverOutput::setYFinal(const RealVector& final) {
	y_final = final;
}

const RealVector& BESolverOutput::getYFinal() const {
	return y_final;
}

Real BESolverOutput::getTFinal() const {
	return t_final;
}

Bool BESolverOutput::getIsConverged() const {
	return is_converged;
}

void BESolverOutput::setIsConverged(Bool isConverged) {
	is_converged = isConverged;
}

void BESolverOutput::setTFinal(const Real  final) {
	t_final = final;
}

Real BESolverOutput::getDt() const {
	return dt;
}

void BESolverOutput::setDt(Real dt) {
	this->dt = dt;
}
