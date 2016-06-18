/*
 * AllenCahnRHSFunction.cpp
 *
 *  Created on: Nov 16, 2015
 *      Author: delpopol
 */

#include "AllenCahnRHSFunction.h"

AllenCahnRHSFunction::AllenCahnRHSFunction() {
	x0 = 0;
	xL = 1;
	Nx = 0;
	sigma = 0;
}

AllenCahnRHSFunction::~AllenCahnRHSFunction() {}

void AllenCahnRHSFunction::setSigma(const Real sigma){
	this->sigma = sigma;
}

void AllenCahnRHSFunction::setNx(const Integer nx){
	this->Nx = nx;
}

Real AllenCahnRHSFunction::getX0() const {
	return x0;
}

void AllenCahnRHSFunction::setX0(Real x0) {
	this->x0 = x0;
}

Real AllenCahnRHSFunction::getXL() const {
	return xL;
}

void AllenCahnRHSFunction::setXL(Real l) {
	xL = l;
}

RealVector AllenCahnRHSFunction::evalF(Real time, RealVector& y){

	Integer y_size = y.size();
	RealVector F(y_size);
	F.fill(0.0);

	/*!
	 * I create a uniform grid with Nx nodes.
	 */

	Real dx = (xL - x0) / Nx;

	/*! For the first and the last node we have to use the Neumann boundary conditions!
	 *	For the other nodes we use centered finite  differences.
	 */

	Real y0 = y(0);
	F(0) = sigma * (y(1) - 2.0*y(0) + y(1) )/(pow(dx,2.0)) + y(0)*(1 - (y0*y0));

	for (Integer i = 1; i < (Nx-1); ++i){
		Real yi = y(i);
		F(i) = sigma * ( y(i+1) - 2.0*y(i) + y(i-1))/(pow(dx,2.0)) + y(i)*(1 - (yi*yi));
	}

	Real ynx = y(Nx-1);
	F(Nx-1) = sigma * (+y(Nx-2) -2.0*y(Nx-1) + y(Nx-2))/(pow(dx,2.0)) + y(Nx-1)*(1 - (ynx*ynx));

	return F;
}

RealVector AllenCahnRHSFunction::evalF(Real time, RealVector& y, IntegerVector& ref){

	Integer elem_ref = ref.sum();
	RealVector F(elem_ref);
	F.fill(0.0);

	Real dx = (xL - x0) / Nx;

	Integer idx = 0;

	/*! For the first and the last node we have to use the Neumann boundary conditions!
	 *	For the other nodes we use centered finite  differences.
	 *	Only for the components that we have to compute the solution and are not interpolated.
	 */

	if (ref(0) == 1){
		Real y0 = y(0);
		F(idx) =  sigma * (y(1) - 2.0*y(0) + y(1) )/(pow(dx,2.0)) + y(0)*(1 - (y0*y0));;
		idx += 1;
	}
	for (Integer i = 1; i < (Nx-1); ++i){
		if (ref(i) == 1){
			Real yi = y(i);
			F(idx) = sigma * ( y(i+1) - 2.0*y(i) + y(i-1))/((dx*dx)) + y(i)*(1 - (yi*yi));
			idx += 1;
		}
	}

	if(ref(Nx-1) == 1){
		Real ynx = y(Nx-1);
		F(idx) = sigma * (+y(Nx-2) -2.0*y(Nx-1) + y(Nx-2))/(pow(dx,2.0)) + y(Nx-1)*(1 - (ynx*ynx));
	}
	return F;
}

RealMatrixSparse AllenCahnRHSFunction::evaldFdY(Real time,RealVector& y){

	// this is not the analytical Jacobian! It is compute with finite differences.

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

RealMatrixSparse AllenCahnRHSFunction::evaldFdY(Real time, RealVector& y, IntegerVector& ref){

	// this is not the analytical Jacobian! It is compute with finite differences.

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
Real AllenCahnRHSFunction::getSigma(){
	return sigma;
}
Integer AllenCahnRHSFunction::getNx(){
	return Nx;
}
