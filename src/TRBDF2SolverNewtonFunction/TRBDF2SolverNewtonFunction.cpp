/*
 * TRBDF2SolverNewtonFunction.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: delpopol
 */

#include "TRBDF2SolverNewtonFunction.h"
#include "VectorUtility/VectorUtility.h"

TRBDF2SolverNewtonFunction::TRBDF2SolverNewtonFunction() {
	tnp = 0;
	dt = 0;
	this->fun = NULL;
	d = (2-sqrt(2))/2;
}

TRBDF2SolverNewtonFunction::~TRBDF2SolverNewtonFunction() {}

void TRBDF2SolverNewtonFunction::setDt(Real dt) {
	this->dt = dt;
}

void TRBDF2SolverNewtonFunction::setFun(IRHSFunction* fun) {
	this->fun = fun;
}

void TRBDF2SolverNewtonFunction::setYn(RealVector& ya) {
	this->ya = ya;
}

void TRBDF2SolverNewtonFunction::setTnp(Real tnp) {
	this->tnp = tnp;
}

void TRBDF2SolverNewtonFunction::setRef(IntegerVector& ref) {
	this->ref = ref;
}

void TRBDF2SolverNewtonFunction::setD(Real d) {
	this->d = d;
}

void TRBDF2SolverNewtonFunction::evalFJ(RealVector& Z, RealVector& F, RealMatrixSparse& J){

	Bool refining = (ref.all() == false);

	if(refining == false){

		Integer n = Z.size();
		RealVector Y(n);
		Y.fill(0.0);
		F.fill(0.0);

		RealMatrixSparse DZ_DZ(n,n);  //Identity matrix
		DZ_DZ.setIdentity();

		Y = ya + d * Z;

		RealVector f  = fun->evalF(tnp,Y);
		RealMatrixSparse Df_DY = fun->evaldFdY(tnp,Y);


		F = Z     - dt *     f;
		J = DZ_DZ - dt * d * Df_DY;    //J = DF_DZ

	}
	else{

		Real d = (2 - sqrt(2))/2;

		Integer n = ref.cast<Real>().size();
		RealVector Y(n);
		Y.fill(0);
		F.fill(0);

		Integer elem_ref = ref.sum();
		RealMatrixSparse DZ_DZ;
		DZ_DZ.resize(elem_ref,elem_ref);
		DZ_DZ.setIdentity();


		RealVector Z_long = VectorUtility::vectorProlong(Z,ref);

		Y = ya + d * Z_long;

		RealVector f  = fun->evalF(tnp,Y,ref);
		RealMatrixSparse Df_DY = fun->evaldFdY(tnp,Y,ref);

		F = Z     - dt *     f;
		J = DZ_DZ - dt * d * Df_DY;  //J = DF_DZ
	}
}

void TRBDF2SolverNewtonFunction::evalF(RealVector& Z, RealVector& F){

	Bool refining = (ref.all() == false);

	if(refining == false){
		Integer n = Z.size();
		RealVector Y(n);
		Y.fill(0.0);
		F.fill(0.0);

		Y = ya + d * Z;

		RealVector f  = fun->evalF(tnp,Y);

		F = Z  - dt * f;
	}
	else{

		Integer n = ref.cast<Real>().size();
		RealVector Y(n);
		Y.fill(0.0);
		F.fill(0.0);

		RealVector Z_long = VectorUtility::vectorProlong(Z,ref);

		Y = ya + d * Z_long;

		RealVector f  = fun->evalF(tnp,Y,ref);

		F = Z  - dt * f;
	}
}

