/*
 * SingleRateFESolver.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "SingleRateFESolver.h"
#include "SingleRateFESolverData.h"

SingleRateFESolver::SingleRateFESolver() {
	tinitial = 0;
	dt = 0;
	tfinal = 0;
	this->fun = NULL;
}

SingleRateFESolver::~SingleRateFESolver() {}

void SingleRateFESolver::setFun(IRHSFunction* fun) {
	this->fun = fun;
}

void SingleRateFESolver::setTfinal(Real tfinal) {
	this->tfinal = tfinal;
}

void SingleRateFESolver::setTinitial(Real tinitial) {
	this->tinitial = tinitial;
}

void SingleRateFESolver::setYinitial(const RealVector& yinitial) {
	this->yinitial = yinitial;
}

std::vector<std::unique_ptr<ISolverData>>&& SingleRateFESolver::getSolution(){
	return (std::move(vect_solution));
}

void SingleRateFESolver::setHinitial(Real hinitial){
	this->dt=hinitial;
}
void SingleRateFESolver::setNewtSolv(std::unique_ptr<INewtonSolver> newt_solv){}

void SingleRateFESolver::setHz1initial(const RealVector& hz1initial){}

void SingleRateFESolver::setNewtonTolAbs(Real newtonTolAbs){}

void SingleRateFESolver::setNewtonTolRel(Real newtonTolRel){}

void SingleRateFESolver::setErrorTolAbs(Real errorTolAbs){}

void SingleRateFESolver::setInterpolator(std::unique_ptr<IInterpolationSolver> interp){}

void SingleRateFESolver::setErrorTolRel(Real errorTolRel){}

void SingleRateFESolver::compute(){

	FESolverUtils util_be;

	Real tol = 1.e-4;

	Real time = tinitial;
	RealVector y_time = yinitial;

	RealVector error(y_time.size());
	error.fill(0.0);

	IntegerVector mesh(y_time.size());
	error.fill(1);


	//! First data output: initial conditions

	SingleRateFESolverData step_solution;

	step_solution.setTime(time);
	step_solution.setY(yinitial);
	step_solution.setH(dt);
	step_solution.setHasSucceded(true);
	step_solution.setRefining(false);
	step_solution.setError(error);
	step_solution.setMesh(mesh);
	step_solution.setNumbComponentsSolve(mesh);


	std::unique_ptr<SingleRateFESolverData> ptr_step_solution (new SingleRateFESolverData(step_solution));

	vect_solution.emplace_back( std::move(ptr_step_solution) );

	time_step_solver.setRHSFunction(fun);

	while ( time < tfinal )
	{
		// Take into account t-final bound
		Real dt_step = dt;
		if (time + dt_step > tfinal)
			dt_step = tfinal-time;

		FESolverInput solv_input;
		solv_input.set(time,dt_step,y_time);

		info()<<"time = "<<time;

		//FESolver time_step_solver;

		time_step_solver.setInput(solv_input);

		time_step_solver.compute();

		FESolverOutput solution=time_step_solver.getOutputFE();


		util_be.printInfo(solution);

		//! update solution
		time = solution.getTFinal();
		y_time = solution.getYFinal();

		//! Store new solution

		SingleRateFESolverData step_solution;

		step_solution.setTime(time);
		step_solution.setY(y_time);
		step_solution.setH(dt_step);
		step_solution.setHasSucceded(true);
		step_solution.setRefining(false);
		step_solution.setError(error);
		step_solution.setMesh(mesh);
		step_solution.setNumbComponentsSolve(mesh);

		std::unique_ptr<SingleRateFESolverData> ptr_step_solution (new SingleRateFESolverData(step_solution));

		vect_solution.emplace_back( std::move(ptr_step_solution) );

	}

	info() << "Done !!";
	info()<<"time final = "<<time;



}
