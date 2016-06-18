/*
 * HyperbolicEquationRusanovFlux.cpp
 *
 *  Created on: 19/gen/2016
 *      Author: ludovicadelpopolo
 */

#include "HyperbolicEquationRusanovFlux.h"

HyperbolicEquationRusanovFlux::HyperbolicEquationRusanovFlux() {
	this->flux_func = NULL;
	this->bc_func = NULL;
	Nx = 200;
	x0 = 0;
	xL = 1;

}

HyperbolicEquationRusanovFlux::~HyperbolicEquationRusanovFlux() {}

Integer HyperbolicEquationRusanovFlux::getNx() const {
	return Nx;
}

void HyperbolicEquationRusanovFlux::setNx(Integer nx) {
	Nx = nx;
}

Real HyperbolicEquationRusanovFlux::getX0() const {
	return x0;
}

void HyperbolicEquationRusanovFlux::setX0(Real x0) {
	this->x0 = x0;
}

Real HyperbolicEquationRusanovFlux::getXL() const {
	return xL;
}

void HyperbolicEquationRusanovFlux::setXL(Real l) {
	xL = l;
}

void HyperbolicEquationRusanovFlux::setBcFunc(IBCFunction* bcFunc) {
	bc_func = bcFunc;
}

void HyperbolicEquationRusanovFlux::setFluxFunc(IFluxFunction* fl_func){
	flux_func = fl_func;
}

RealVector HyperbolicEquationRusanovFlux::evalF(Real time, RealVector& y){

	//! I use a uniform space grid
	Real dx = (xL - x0) / Nx;
	Integer y_size = y.size();
	RealVector F(y_size);
	F.fill(0.0);



	//! For the first node we impose that the value is equal to the BC value.

		Integer i=0;
		Real y0 = bc_func->getValue(time); 
		Real yi_succ = y(i+1);

		Real f_deriv_i = fabs(flux_func-> evalFderivative(time,y0));
		Real f_deriv_isucc = fabs(flux_func-> evalFderivative(time,yi_succ));

		Real f_prev =  flux_func->evalF(time,y0);
		Real f_succ =  0.5*(flux_func->evalF(time,y0) + flux_func->evalF(time,yi_succ) - ( std::max( f_deriv_i, f_deriv_isucc))*(yi_succ-y0));

		F(0) = - 1.0/dx  * (f_succ - f_prev );

	for (Integer i = 1; i < Nx-1; ++i){

		//! We use a finite volume method with Rusanov flux

		Real yi = y(i);
		Real yi_succ = y(i+1);
		Real yi_prev = y(i-1);

		Real f_deriv_i = fabs(flux_func-> evalFderivative(time,yi));
		Real f_deriv_isucc = fabs(flux_func-> evalFderivative(time,yi_succ));
		Real f_deriv_iprev = fabs(flux_func-> evalFderivative(time,yi_prev));

		Real f_prev =  0.5*(flux_func->evalF(time,yi_prev) + flux_func->evalF(time,yi) - (std::max( f_deriv_i, f_deriv_iprev))*(yi-yi_prev));
		Real f_succ =  0.5*(flux_func->evalF(time,yi) + flux_func->evalF(time,yi_succ) - ( std::max( f_deriv_i, f_deriv_isucc))*(yi_succ-yi));

		F(i) = - 1.0/dx  * (f_succ - f_prev );
	}

	Real yn = y(Nx-1);
	Real yi_prev = y(Nx-2);

	f_deriv_i = fabs(flux_func-> evalFderivative(time,yn));
	Real f_deriv_iprev = fabs(flux_func-> evalFderivative(time,yi_prev));

	f_prev =  0.5*(flux_func->evalF(time,yi_prev) + flux_func->evalF(time,yn) - (std::max( f_deriv_i, f_deriv_iprev))*(yn-yi_prev));
	f_succ =  flux_func->evalF(time,yn);

	F(Nx-1) = - 1.0/dx  * (f_succ - f_prev );

	return F;

}

RealVector HyperbolicEquationRusanovFlux::evalF(Real time, RealVector& y, IntegerVector& ref){

	Real dx = (xL - x0) / Nx;
	Integer elem_ref = ref.sum();
	RealVector F(elem_ref);
	F.fill(0.0);

	Integer idx = 0;

	if (ref(0) == 1){
		Integer i=0;
		Real y0 = bc_func->getValue(time); 
		Real yi_succ = y(i+1);

		Real f_deriv_i = fabs(flux_func-> evalFderivative(time,y0));
		Real f_deriv_isucc = fabs(flux_func-> evalFderivative(time,yi_succ));

		Real f_prev =  flux_func->evalF(time,y0);
		Real f_succ =  0.5*(flux_func->evalF(time,y0) + flux_func->evalF(time,yi_succ) - ( std::max( f_deriv_i, f_deriv_isucc))*(yi_succ-y0));

		F(0) = - 1.0/dx  * (f_succ - f_prev );
		idx += 1;
	}
	for (Integer i = 1; i < Nx-1; ++i){
		if (ref(i) == 1){

			//! We use a finite volume method with Rusanov flux

			Real yi = y(i);
			Real yi_succ = y(i+1);
			Real yi_prev = y(i-1);

			Real f_deriv_i = fabs(flux_func-> evalFderivative(time,yi));
			Real f_deriv_isucc = fabs(flux_func-> evalFderivative(time,yi_succ));
			Real f_deriv_iprev = fabs(flux_func-> evalFderivative(time,yi_prev));

			Real f_prev =  0.5*(flux_func->evalF(time,yi_prev) + flux_func->evalF(time,yi) - (std::max( f_deriv_i, f_deriv_iprev))*(yi-yi_prev));
			Real f_succ =  0.5*(flux_func->evalF(time,yi) + flux_func->evalF(time,yi_succ) - ( std::max( f_deriv_i, f_deriv_isucc))*(yi_succ-yi));

			F(idx) = - 1.0/dx  * (f_succ - f_prev );
			idx += 1;
		}
	}

	if(ref(Nx-1)==1){
		Real yn = y(Nx-1);
		Real yi_prev = y(Nx-2);

		Real f_deriv_i = fabs(flux_func-> evalFderivative(time,yn));
		Real f_deriv_iprev = fabs(flux_func-> evalFderivative(time,yi_prev));

		Real f_prev =  0.5*(flux_func->evalF(time,yi_prev) + flux_func->evalF(time,yn) - (std::max( f_deriv_i, f_deriv_iprev))*(yn-yi_prev));
		Real f_succ =  flux_func->evalF(time,yn);

		F(idx) = - 1.0/dx  * (f_succ - f_prev );
	}
	return F;
}

RealMatrixSparse HyperbolicEquationRusanovFlux::evaldFdY(Real time, RealVector& y){
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

RealMatrixSparse HyperbolicEquationRusanovFlux::evaldFdY(Real time, RealVector& y,IntegerVector& ref){
	///
	/// this is not the exact Jacobian!
	///
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
