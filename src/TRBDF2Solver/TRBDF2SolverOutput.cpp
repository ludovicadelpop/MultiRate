/*
 * TRBDF2SolverOutput.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#include "TRBDF2SolverOutput.h"

TRBDF2SolverOutput::TRBDF2SolverOutput() {
	t1 = 0;
	t2 = 0;
	newton_diverge = true;
}

TRBDF2SolverOutput::~TRBDF2SolverOutput() {}

const RealVector& TRBDF2SolverOutput::getEst() const {
	return est;
}

void TRBDF2SolverOutput::setEst(const RealVector& est) {
	this->est = est;
}

Bool TRBDF2SolverOutput::isNewtonDiverge() const {
	return newton_diverge;
}

void TRBDF2SolverOutput::setNewtonDiverge(Bool newtonDiverge) {
	newton_diverge = newtonDiverge;
}

Real TRBDF2SolverOutput::getT2() const {
	return t2;
}

void TRBDF2SolverOutput::setT2(Real t2) {
	this->t2 = t2;
}

const RealVector& TRBDF2SolverOutput::getY2() const {
	return y2;
}

void TRBDF2SolverOutput::setY2(const RealVector& y2) {
	this->y2 = y2;
}

const RealVector& TRBDF2SolverOutput::getZ2() const {
	return z2;
}

void TRBDF2SolverOutput::setZ2(const RealVector& z2) {
	this->z2 = z2;
}

Real TRBDF2SolverOutput::getT1() const {
	return t1;
}

void TRBDF2SolverOutput::setT1(Real t1) {
	this->t1 = t1;
}

const RealVector& TRBDF2SolverOutput::getY1() const {
	return y1;
}

void TRBDF2SolverOutput::setY1(const RealVector& y1) {
	this->y1 = y1;
}

const RealVector& TRBDF2SolverOutput::getZ0() const {
	return z0;
}

void TRBDF2SolverOutput::setZ0(const RealVector& z0) {
	this->z0 = z0;
}

const RealVector& TRBDF2SolverOutput::getZ1() const {
	return z1;
}

void TRBDF2SolverOutput::setZ1(const RealVector& z1) {
	this->z1 = z1;
}
