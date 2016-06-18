/*
 * InterpolationOutputSolver.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: delpopol
 */

#include "InterpolationOutputSolver.h"

InterpolationOutputSolver::InterpolationOutputSolver() {}

InterpolationOutputSolver::~InterpolationOutputSolver() {}

const RealVector& InterpolationOutputSolver::getY1() const {
	return y1;
}

void InterpolationOutputSolver::setY1(const RealVector& y1) {
	this->y1 = y1;
}

const RealVector& InterpolationOutputSolver::getY2() const {
	return y2;
}

void InterpolationOutputSolver::setY2(const RealVector& y2) {
	this->y2 = y2;
}
