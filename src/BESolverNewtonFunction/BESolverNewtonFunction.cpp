/*
 * BESolverNewtonFunction.cpp
 *
 *  Created on: Nov 6, 2015
 *      Author: delpopol
 */

#include "BESolverNewtonFunction.h"

BESolverNewtonFunction::BESolverNewtonFunction() {
	tnp = 0;
	dt = 0;
	this->fun = NULL;
}

BESolverNewtonFunction::~BESolverNewtonFunction() {}

void BESolverNewtonFunction::setDt(Real dt) {
	this->dt = dt;
}


void BESolverNewtonFunction::setFun(IRHSFunction* fun) {
	this->fun = fun;
}

void BESolverNewtonFunction::setYn(const RealVector& yn) {
	this->yn = yn;
}

void BESolverNewtonFunction::setTnp(Real tnp) {
	this->tnp = tnp;
}

void BESolverNewtonFunction::evalFJ(RealVector& Y, RealVector& F, RealMatrixSparse& J){

	Integer n = Y.size();
	F.fill(0.0);

	RealMatrixSparse DY_DY(n,n);
	DY_DY.setIdentity();

	RealVector f     = fun->evalF(tnp,Y);
	RealMatrixSparse Df_DY = fun->evaldFdY(tnp,Y);

	F = Y     - yn - dt * f    ;
	J = DY_DY      - dt * Df_DY;

}


void BESolverNewtonFunction::evalF( RealVector& Y, RealVector& F){

	//Integer n = Y.size();
	F.fill(0.0);

	RealVector f  = fun->evalF(tnp,Y);

	F = Y  - yn - dt * f    ;

}




