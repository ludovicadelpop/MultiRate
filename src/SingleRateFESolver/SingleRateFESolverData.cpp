/*
 * SingleRateFESolverData.cpp
 *
 *  Created on: 14 janv. 2016
 *      Author: delpopol
 */

#include <SingleRateFESolver/SingleRateFESolverData.h>

SingleRateFESolverData::SingleRateFESolverData() {
	time = 0.0;
	h = 0.0;
	has_succeded = false;
	refining = false;
}

SingleRateFESolverData::~SingleRateFESolverData() {}

const RealVector& SingleRateFESolverData::getError() const {
	return error;
}

void SingleRateFESolverData::setError(const RealVector& error) {
	this->error = error;
}

Real SingleRateFESolverData::getH() const {
	return h;
}

void SingleRateFESolverData::setH(Real h) {
	this->h = h;
}

Bool SingleRateFESolverData::isHasSucceded() const {
	return has_succeded;
}

void SingleRateFESolverData::setHasSucceded(Bool hasSucceded) {
	has_succeded = hasSucceded;
}


Real SingleRateFESolverData::getTime() const {
	return time;
}

void SingleRateFESolverData::setTime(Real time) {
	this->time = time;
}

const RealVector&  SingleRateFESolverData::getY() const {
	return y;
}

void  SingleRateFESolverData::setY(const RealVector& y) {
	this->y = y;
}

const IntegerVector& SingleRateFESolverData::getMesh() const {
	return mesh;
}

Bool SingleRateFESolverData::isRefining() const {
	return refining;
}

void SingleRateFESolverData::setRefining(Bool refining) {
	this->refining = refining;
}

const IntegerVector& SingleRateFESolverData::getNumbComponentsSolve() const {
	return numb_components_solve;
}

void SingleRateFESolverData::setNumbComponentsSolve(const IntegerVector& numbComponentsSolve) {
	numb_components_solve = numbComponentsSolve;
}

void SingleRateFESolverData::setMesh(const IntegerVector& mesh) {
	this->mesh = mesh;
}
