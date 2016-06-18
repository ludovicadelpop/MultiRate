/*
 * SingleRateTRBDF2SolverData.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: delpopol
 */

#include "SingleRateTRBDF2SolverData.h"

SingleRateTRBDF2SolverData::SingleRateTRBDF2SolverData() {
	refining = false;
	has_succeded = false;
	h = 0;
	time = 0;
}

SingleRateTRBDF2SolverData::~SingleRateTRBDF2SolverData() {}

const RealVector& SingleRateTRBDF2SolverData::getError() const {
	return error;
}

void SingleRateTRBDF2SolverData::setError(const RealVector& err) {
	error = err;
}

Real SingleRateTRBDF2SolverData::getH() const {
	return h;
}

void SingleRateTRBDF2SolverData::setH(Real vec) {
	h = vec;
}

Bool SingleRateTRBDF2SolverData::isHasSucceded() const {
	return has_succeded;
}

void SingleRateTRBDF2SolverData::setHasSucceded(Bool hasSucceded) {
	has_succeded = hasSucceded;
}

Real SingleRateTRBDF2SolverData::getTime() const {
	return time;
}

void SingleRateTRBDF2SolverData::setTime(Real t) {
	time = t;
}

const RealVector& SingleRateTRBDF2SolverData::getY() const {
	return y;
}

void SingleRateTRBDF2SolverData::setY(const RealVector& yn) {
	y = yn;
}


const IntegerVector& SingleRateTRBDF2SolverData::getMesh() const {
	return mesh;
}

void SingleRateTRBDF2SolverData::setMesh(const IntegerVector& mesh) {
	this->mesh = mesh;
}

const IntegerVector& SingleRateTRBDF2SolverData::getNumbComponentsSolve() const {
	return numb_components_solve;
}

void SingleRateTRBDF2SolverData::setNumbComponentsSolve(const IntegerVector& numbComponentsSolve) {
	numb_components_solve = numbComponentsSolve;
}

Bool SingleRateTRBDF2SolverData::isRefining() const {
	return refining;
}

void SingleRateTRBDF2SolverData::setRefining(Bool refining) {
	this->refining = refining;
}
