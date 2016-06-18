/*
 * SingleRateBESolver.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "SingleRateBESolver.h"
#include "SingleRateBESolverData.h"

SingleRateBESolver::SingleRateBESolver() {
	Newton_tol_abs = 1.e-6;
	Newton_tol_rel = 1.e-4;
	Error_tol_abs = 1.e-6;
	Error_tol_rel = 1.e-4;
	tinitial = 0;
	dt = 0;
	tfinal = 0;
	this->fun = NULL;
	this->newt_solv = NULL;
}

SingleRateBESolver::~SingleRateBESolver() {}

void SingleRateBESolver::setFun(IRHSFunction* fun) {
	this->fun = fun;
}

void SingleRateBESolver::setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv) {
	newt_solv = std::move(newtSolv);
}

void SingleRateBESolver::setTfinal(Real tfinal) {
	this->tfinal = tfinal;
}

void SingleRateBESolver::setTinitial(Real tinitial) {
	this->tinitial = tinitial;
}

void SingleRateBESolver::setHinitial(Real dt) {
	this->dt = dt;
}

void SingleRateBESolver::setHz1initial(const RealVector& hz1) {}

void SingleRateBESolver::setInterpolator(std::unique_ptr<IInterpolationSolver> interp){}

void SingleRateBESolver::setYinitial(const RealVector& yinitial) {
	this->yinitial = yinitial;
}

vector<std::unique_ptr<ISolverData>>&& SingleRateBESolver::getSolution(){
	return std::move(vect_solution);
}

void SingleRateBESolver::setNewtonTolAbs(Real newtonTolAbs) {
	Newton_tol_abs = newtonTolAbs;
}

void SingleRateBESolver::setNewtonTolRel(Real newtonTolRel) {
	Newton_tol_rel = newtonTolRel;
}

void SingleRateBESolver::setErrorTolAbs(Real errorTolAbs){
	Error_tol_abs = errorTolAbs;
}

void SingleRateBESolver::setErrorTolRel(Real errorTolRel){
	Error_tol_rel = errorTolRel;
}

void SingleRateBESolver::compute(){

	Real time = tinitial;
	RealVector y_time = yinitial;

	RealVector error(y_time.size());
	error.fill(0.0);

	IntegerVector mesh(y_time.size());
	error.fill(1);

	//! First data output: initial conditions

	SingleRateBESolverData step_solution;

	step_solution.setTime(time);
	step_solution.setY(yinitial);
	step_solution.setH(dt);
	step_solution.setHasSucceded(true);
	step_solution.setRefining(false);
	step_solution.setError(error);
	step_solution.setMesh(mesh);
	step_solution.setNumbComponentsSolve(mesh);


	std::unique_ptr<SingleRateBESolverData> ptr_step_solution (new SingleRateBESolverData(step_solution));

	vect_solution.emplace_back( std::move(ptr_step_solution) );

	time_step_solver.setRHSFunction(fun);
	time_step_solver.setNewtSolv(std::move(newt_solv));


	while ( time < tfinal )
	{
		// Take into account t-final bound
		Real dt_step = dt;
		if (time + dt_step > tfinal)
			dt_step = tfinal-time;


		//! BE time step solver

		BESolverInput solv_input;
		solv_input.set(time,dt_step,y_time,Newton_tol_rel,Newton_tol_abs);


		info()<<"time = "<<time;
		time_step_solver.setInput(solv_input);


		time_step_solver.compute();

		BESolverOutput step_sol=time_step_solver.getOutputBE();

		//! update solution
		time = step_sol.getTFinal();
		y_time = step_sol.getYFinal();

		//! Store new solution

		SingleRateBESolverData step_solution;

		step_solution.setTime(time);
		step_solution.setY(y_time);
		step_solution.setH(dt_step);
		step_solution.setHasSucceded(true);
		step_solution.setRefining(false);
		step_solution.setError(error);
		step_solution.setMesh(mesh);
		step_solution.setNumbComponentsSolve(mesh);

		std::unique_ptr<SingleRateBESolverData> ptr_step_solution (new SingleRateBESolverData(step_solution));
		vect_solution.emplace_back( std::move(ptr_step_solution) );
	}

	info() << "Done !!";
	info()<<"time final = "<<time;



}
