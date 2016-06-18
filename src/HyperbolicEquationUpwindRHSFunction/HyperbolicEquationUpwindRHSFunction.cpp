/*
 * HyperbolicEquationUpwindRHSFunction.cpp
 *
 *  Created on: 22 déc. 2015
 *      Author: delpopol
 */

#include "HyperbolicEquationUpwindRHSFunction.h"

HyperbolicEquationUpwindRHSFunction::HyperbolicEquationUpwindRHSFunction() {
	this->flux_func = NULL;
	this->bc_func = NULL;
	Nx = 200;
	x0 = 0;
	xL = 1;

}

HyperbolicEquationUpwindRHSFunction::~HyperbolicEquationUpwindRHSFunction() {}


Integer HyperbolicEquationUpwindRHSFunction::getNx() const {
	return Nx;
}

void HyperbolicEquationUpwindRHSFunction::setNx(Integer nx) {
	Nx = nx;
}

Real HyperbolicEquationUpwindRHSFunction::getX0() const {
	return x0;
}

void HyperbolicEquationUpwindRHSFunction::setX0(Real x0) {
	this->x0 = x0;
}

Real HyperbolicEquationUpwindRHSFunction::getXL() const {
	return xL;
}

void HyperbolicEquationUpwindRHSFunction::setXL(Real l) {
	xL = l;
}

void HyperbolicEquationUpwindRHSFunction::setBcFunc(IBCFunction* bcFunc) {
	bc_func = bcFunc;
}

void HyperbolicEquationUpwindRHSFunction::setFluxFunc(IFluxFunction* fl_func){
	flux_func = fl_func;
}

RealVector HyperbolicEquationUpwindRHSFunction::evalF(Real time, RealVector& y){

	// I use a uniform space grid
	Real dx = (xL - x0) / Nx;
	Integer y_size = y.size();
	RealVector F(y_size);
	F.fill(0.0);



	//! For the first node we impose that the value is equal to the BC value.
	F(0) = bc_func->getValue(time);
	for (Integer i = 1; i <= Nx-2; ++i){
		Real yi = y(i);
		Real a = flux_func->evalFderivative(time,yi);
		if ( a > 0.0 ){
			Real yi_prec = y(i-1);
			F(i) = 1.0/dx  * ( flux_func->evalF(time,yi_prec) - flux_func->evalF(time,yi) );
		}
		else{
			Real yi_succ = y(i+1);
			F(i) = 1.0/dx  * ( flux_func->evalF(time,yi) - flux_func->evalF(time,yi_succ) );
		}
	}

	return F;

}

RealVector HyperbolicEquationUpwindRHSFunction::evalF(Real time, RealVector& y, IntegerVector& ref){

	Real dx = (xL - x0) / Nx;
	Integer elem_ref = ref.sum();
	RealVector F(elem_ref);
	F.fill(0.0);

	Integer idx = 0;

	if (ref(0) == 1){
		F(idx) = bc_func->getValue(time);
		idx += 1;
	}
	for (Integer i = 1; i <= Nx-2; ++i){
		if (ref(i) == 1){
			Real yi = y(i);
			Real a = flux_func->evalFderivative(time,yi);
			if ( a > 0.0 ){
				Real yi_prec = y(i-1);
				F(idx) = 1.0/dx  * ( flux_func->evalF(time,yi_prec) - flux_func->evalF(time,yi) );
			}
			else{
				Real yi_succ = y(i+1);
				F(idx) = 1.0/dx  * ( flux_func->evalF(time,yi) - flux_func->evalF(time,yi_succ) );
			}
			idx += 1;
		}
	}

	return F;
}

RealMatrixSparse HyperbolicEquationUpwindRHSFunction::evaldFdY(Real time, RealVector& y){
	///
	/// this is not the exact Jacobian!
	///

	Integer y_size = y.size();
	RealMatrixSparse J(y_size,y_size);

	Integer col = 0;
	Real epsi = 1.e-3;
	Real iepsi = 1.0 / 1.e-3;
	RealVector F = evalF(time,y);

	for (Integer j = 0; j < y_size; ++j){

		RealVector yd = y;
		yd(j) = yd(j) + epsi;

		RealVector Fd = evalF(time,yd);

		for(Integer i=0; i< Fd.size(); i++){
			J.insert(i,col) = (Fd[i] - F[i]) * iepsi;
		}
		col = col + 1;
	}

	return J;
}

RealMatrixSparse HyperbolicEquationUpwindRHSFunction::evaldFdY(Real time, RealVector& y,IntegerVector& ref){

	// this is not the exact Jacobian!

		Integer y_size = y.size();
		Integer elem_ref = ref.sum();
		RealMatrixSparse J(elem_ref,elem_ref);


		Integer col = 0;
		Real epsi = 1.e-3;
		Real iepsi = 1.0 / 1.e-3;
		RealVector F = evalF(time,y,ref);

		for (Integer j = 0; j < y_size; ++j){
			if(ref(j) == 1){
				RealVector yd = y;
				yd(j) = yd(j) + epsi;

				RealVector Fd = evalF(time,yd,ref);

				for(Integer i=0; i< Fd.size(); i++){
					J.insert(i,col) = (Fd[i] - F[i]) * iepsi;
				}
				col = col + 1;
			}
		}

		return J;
}
