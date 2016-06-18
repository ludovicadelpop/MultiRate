/*
 * FESolver.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "FESolver.h"

FESolver::FESolver() {
	this->rhs_fun = NULL;
}

FESolver::~FESolver() {}

void FESolver::setInput(FESolverInput input){
	this->input=input;
}

FESolverOutput FESolver::getOutputFE(){
	return this->output;
}

void FESolver::setRHSFunction(IRHSFunction* fun){
		this->rhs_fun = fun;
}

void FESolver::compute(){

	Real t0 = input.getT0();
	Real dt = input.getDt();
	RealVector  y0 = input.getY0();


	if(rhs_fun == NULL)
		fatal()<< "RHS_Function is null";
	RealVector RHSvalue = rhs_fun->evalF(t0, y0);

	RealVector y_sol = y0 + RHSvalue * dt;
	Real t_sol = t0 + dt;

	output.setYFinal(y_sol);
	output.setTFinal(t_sol);
	output.setIsConverged(true);

}




