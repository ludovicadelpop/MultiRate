/*
 * InterpolationInputSolver.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: pacs_student
 */

#include "InterpolationInputSolver.h"

InterpolationInputSolver::InterpolationInputSolver() {}

InterpolationInputSolver::~InterpolationInputSolver(){}

void InterpolationInputSolver::setRef(const IntegerVector& ref) {
	this->ref = ref;
}

void InterpolationInputSolver::setT0Int(const RealVector& t0Int) {
	t0_int = t0Int;
}

void InterpolationInputSolver::setT1Int(const RealVector& t1Int) {
	t1_int = t1Int;
}

void InterpolationInputSolver::setT2Int(const RealVector& t2Int) {
	t2_int = t2Int;
}

void InterpolationInputSolver::setY0Int(const RealVector& y0Int) {
	y0_int = y0Int;
}

void InterpolationInputSolver::setY1Int(const RealVector& y1Int) {
	y1_int = y1Int;
}

void InterpolationInputSolver::setY2Int(const RealVector& y2Int) {
	y2_int = y2Int;
}

void InterpolationInputSolver::setZ0Int(const RealVector& z0Int) {
	z0_int = z0Int;
}

void InterpolationInputSolver::setZ1Int(const RealVector& z1Int) {
	z1_int = z1Int;
}

void InterpolationInputSolver::setZ2Int(const RealVector& z2Int) {
	z2_int = z2Int;
}

const IntegerVector& InterpolationInputSolver::getRef() const {
	return ref;
}

const RealVector& InterpolationInputSolver::getT0Int() const {
	return t0_int;
}

const RealVector& InterpolationInputSolver::getT1Int() const {
	return t1_int;
}

const RealVector& InterpolationInputSolver::getT2Int() const {
	return t2_int;
}

const RealVector& InterpolationInputSolver::getY0Int() const {
	return y0_int;
}

const RealVector& InterpolationInputSolver::getY1Int() const {
	return y1_int;
}

const RealVector& InterpolationInputSolver::getY2Int() const {
	return y2_int;
}

const RealVector& InterpolationInputSolver::getZ0Int() const {
	return z0_int;
}

const RealVector& InterpolationInputSolver::getZ1Int() const {
	return z1_int;
}

const RealVector& InterpolationInputSolver::getZ2Int() const {
	return z2_int;
}
