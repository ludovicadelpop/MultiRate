/*
 * BESolver.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "BESolver.h"
#include "BESolverNewtonFunction/BESolverNewtonFunction.h"

BESolver::BESolver() {
	this->rhs_fun = NULL;
	this->newt_solv = NULL;
}

BESolver::~BESolver() {}


void BESolver::setInput(BESolverInput input){
	this->input=input;
}

BESolverOutput BESolver::getOutputBE(){
	return this->output;
}

void BESolver::setRHSFunction(IRHSFunction* fun){
	this->rhs_fun = fun;
}

void  BESolver::setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv) {
	newt_solv = std::move( newtSolv);
}

void BESolver::compute(){

	Real t0 = input.getT0();
	Real dt = input.getDt();
	RealVector y0 = input.getY0();


	Real tol_rel = input.getNewtonTolRel();
	Real tol_abs = input.getNewtonTolAbs();

	if(rhs_fun == NULL)
		fatal()<< "RHS_Function is null";

	RealVector y_sol(y0.size());
	y_sol = y0;

	// I create the Newton function for BE solver.
	BESolverNewtonFunction newt_solv_function;

	newt_solv_function.setDt(dt);
	newt_solv_function.setFun(rhs_fun);
	newt_solv_function.setYn(y0);
	newt_solv_function.setTnp(t0 + dt);


	RealMatrixSparse J(y0.size(),y0.size());
	RealMatrixSparse I(y0.size(),y0.size());
	I.setIdentity();
	J = rhs_fun->evaldFdY(t0+dt,y0);

	J = I - dt * J;

	Bool diverge_Newton;

	//Calls Newton solver
	newt_solv->compute(newt_solv_function,J,y_sol,tol_rel,tol_abs,diverge_Newton,50);

	Real t_sol = t0 + dt;

	//Set the output

	output.setYFinal(y_sol);
	output.setTFinal(t_sol);
	output.setDt(dt);
	output.setIsConverged(true);

}



