/*
 * SingleRateBESolverData.cpp
 *
 *  Created on: 8 janv. 2016
 *      Author: delpopol
 */

#include "SingleRateBESolverData.h"

SingleRateBESolverData::SingleRateBESolverData() {
	time = 0.0;
	h = 0.0;
	has_succeded = false;
	refining = false;
}

SingleRateBESolverData::~SingleRateBESolverData() {}

const RealVector& SingleRateBESolverData::getError() const {
	return error;
}

void SingleRateBESolverData::setError(const RealVector& error) {
	this->error = error;
}

Real SingleRateBESolverData::getH() const {
	return h;
}

void SingleRateBESolverData::setH(Real h) {
	this->h = h;
}

Bool SingleRateBESolverData::isHasSucceded() const {
	return has_succeded;
}

void SingleRateBESolverData::setHasSucceded(Bool hasSucceded) {
	has_succeded = hasSucceded;
}


Real SingleRateBESolverData::getTime() const {
	return time;
}

void SingleRateBESolverData::setTime(Real time) {
	this->time = time;
}

const RealVector&  SingleRateBESolverData::getY() const {
	return y;
}

void  SingleRateBESolverData::setY(const RealVector& y) {
	this->y = y;
}

const IntegerVector& SingleRateBESolverData::getMesh() const {
	return mesh;
}

Bool SingleRateBESolverData::isRefining() const {
	return refining;
}

void SingleRateBESolverData::setRefining(Bool refining) {
	this->refining = refining;
}

const IntegerVector& SingleRateBESolverData::getNumbComponentsSolve() const {
	return numb_components_solve;
}

void SingleRateBESolverData::setNumbComponentsSolve(const IntegerVector& numbComponentsSolve) {
	numb_components_solve = numbComponentsSolve;
}

void SingleRateBESolverData::setMesh(const IntegerVector& mesh) {
	this->mesh = mesh;
}
