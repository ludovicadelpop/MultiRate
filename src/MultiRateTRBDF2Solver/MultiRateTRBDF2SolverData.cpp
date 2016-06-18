/*
 * MultiRateTRBDF2SolverData.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: delpopol
 */

#include "MultiRateTRBDF2SolverData.h"

MultiRateTRBDF2SolverData::MultiRateTRBDF2SolverData() {
	time = 0.0;
	h = 0.0;
	has_succeded = false;
	refining = false;
}

MultiRateTRBDF2SolverData::~MultiRateTRBDF2SolverData() {}

const RealVector& MultiRateTRBDF2SolverData::getError() const {
	return error;
}

void MultiRateTRBDF2SolverData::setError(const RealVector& error) {
	this->error = error;
}

Real MultiRateTRBDF2SolverData::getH() const {
	return h;
}

void MultiRateTRBDF2SolverData::setH(Real h) {
	this->h = h;
}

Bool MultiRateTRBDF2SolverData::isHasSucceded() const {
	return has_succeded;
}

void MultiRateTRBDF2SolverData::setHasSucceded(Bool hasSucceded) {
	has_succeded = hasSucceded;
}


Real MultiRateTRBDF2SolverData::getTime() const {
	return time;
}

void MultiRateTRBDF2SolverData::setTime(Real time) {
	this->time = time;
}

const RealVector&  MultiRateTRBDF2SolverData::getY() const {
	return y;
}

void  MultiRateTRBDF2SolverData::setY(const RealVector& y) {
	this->y = y;
}

const IntegerVector& MultiRateTRBDF2SolverData::getMesh() const {
	return mesh;
}

void MultiRateTRBDF2SolverData::setMesh(const IntegerVector& mesh) {
	this->mesh = mesh;
}


Bool MultiRateTRBDF2SolverData::isRefining() const {
	return refining;
}

void MultiRateTRBDF2SolverData::setRefining(Bool refining) {
	this->refining = refining;
}

const IntegerVector& MultiRateTRBDF2SolverData::getNumbComponentsSolve() const {
	return numb_components_solve;
}

void MultiRateTRBDF2SolverData::setNumbComponentsSolve(const IntegerVector& numbComponentsSolve) {
	numb_components_solve = numbComponentsSolve;
}
