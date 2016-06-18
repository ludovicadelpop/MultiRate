/*
 * FESolverOutput.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "FESolverOutput.h"

FESolverOutput::FESolverOutput() {
	is_converged = false;
	t_final = 0;
}

FESolverOutput::~FESolverOutput() {}

void FESolverOutput::setYFinal(const RealVector& final) {
	y_final = final;
}

const RealVector& FESolverOutput::getYFinal() const {
	return y_final;
}

Real FESolverOutput::getTFinal() const {
	return t_final;
}

Bool FESolverOutput::getIsConverged() const {
	return is_converged;
}

void FESolverOutput::setIsConverged(Bool isConverged) {
	is_converged = isConverged;
}

void FESolverOutput::setTFinal(const Real  final) {
	t_final = final;
}
