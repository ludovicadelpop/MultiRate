/*
 * MasterSolution.cpp
 *
 *  Created on: 15 déc. 2015
 *      Author: delpopol
 */

#include "MasterSolution.h"

MasterSolution::MasterSolution() {
	t = 0;
}

MasterSolution::~MasterSolution() {}


Real MasterSolution::getT() const {
	return t;
}

void MasterSolution::setT(Real t) {
	this->t = t;
}

const RealVector& MasterSolution::getY() const {
	return y;
}

void MasterSolution::setY(const RealVector& y) {
	this->y = y;
}


