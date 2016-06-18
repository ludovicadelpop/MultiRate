/*
 * SingleRateTRBDF2Solver.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: delpopol
 */

#include <SingleRateTRBDF2Solver/SingleRateTRBDF2Solver.h>
#include <algorithm>
#include <math.h>

SingleRateTRBDF2Solver::SingleRateTRBDF2Solver() {
	Newton_tol_abs = 1.e-6;
	Newton_tol_rel = 1.e-4;
	Error_tol_abs = 1.e-6;
	Error_tol_rel = 1.e-4;
	hinitial = 1.e-4;
	tfinal = 0;
	tinitial = 0;
	this->fun = NULL;
	this->newt_solv = NULL;
}

SingleRateTRBDF2Solver::~SingleRateTRBDF2Solver() {}

void SingleRateTRBDF2Solver::setFun(IRHSFunction* fun) {
	this->fun = fun;
}

void SingleRateTRBDF2Solver::setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv) {
	newt_solv = std::move(newtSolv);
}

void SingleRateTRBDF2Solver::setInterpolator(std::unique_ptr<IInterpolationSolver> interp){}

void SingleRateTRBDF2Solver::setHinitial(Real hinitial) {
	this->hinitial = hinitial;
}

void SingleRateTRBDF2Solver::setHz1initial(const RealVector& hz1initial) {
	this->hz_1initial = hz1initial;
}

void SingleRateTRBDF2Solver::setYinitial(const RealVector& yinitial) {
	this->yinitial = yinitial;
}

void SingleRateTRBDF2Solver::setTinitial(Real tinitial) {
	this->tinitial = tinitial;
}

void SingleRateTRBDF2Solver::setErrorTolAbs(Real errorTolAbs) {
	Error_tol_abs = errorTolAbs;
}

void SingleRateTRBDF2Solver::setErrorTolRel(Real errorTolRel) {
	Error_tol_rel = errorTolRel;
}

void SingleRateTRBDF2Solver::setNewtonTolAbs(Real newtonTolAbs) {
	Newton_tol_abs = newtonTolAbs;
}

void SingleRateTRBDF2Solver::setNewtonTolRel(Real newtonTolRel) {
	Newton_tol_rel = newtonTolRel;
}

void SingleRateTRBDF2Solver::setTfinal(Real tfinal) {
	this->tfinal = tfinal;
}

std::vector<std::unique_ptr<ISolverData>>&& SingleRateTRBDF2Solver::getSolution(){
	return (std::move(outputDataVector));
}


void SingleRateTRBDF2Solver::compute(){

	// Parameters time step size
	Real hmax = 1.e+4;
	Real v_ref_ext = 0.7;
	Real smoothInt = 0.002;
	Real smoothExt = 4.0;
	Real v_new_nref_ext = 0.9;


	Real t0 = tinitial;
	Real h = hinitial;
	RealVector y0 = yinitial;
	RealVector hz_1 = hz_1initial;

	RealVector del_max_err(y0.size());
	del_max_err.fill(1.0);

	TRBDF2SolverInput internal_input;
	Real pd0 = 1.5+sqrt(2.0);
	Real pd1 = 2.5+2.0*sqrt(2.0);
	Real pd2 = -(6+4.5*sqrt(2.0));
	Real gm = 2.0-sqrt(2.0);
	Real d =  gm/2.0;
	Real w = sqrt(2.0)/4.0;
	Real e0 = (1.0-w)/3.0;
	Real e1 = w+1.0/3.0;
	Real e2 = d/3.0;

	TRBDF2SolverParameters internal_param;
	internal_param.setParam(pd0,pd1,pd2,e0,e1,e2,gm,d,w);


	RealVector E(y0.size());
	E.fill(0.0);

	IntegerVector mesh(y0.size());
	mesh.fill(1);

	// First data output: initial conditions

	SingleRateTRBDF2SolverData outputData;

	outputData.setTime(t0);
	outputData.setH(0.0);
	outputData.setError(E);
	outputData.setY(y0);
	outputData.setHasSucceded(true);
	outputData.setRefining(false);
	outputData.setNumbComponentsSolve(mesh);
	outputData.setMesh(mesh);

	std::unique_ptr<SingleRateTRBDF2SolverData> ptr_step_solution( new SingleRateTRBDF2SolverData(outputData));
	outputDataVector.emplace_back(std::move(ptr_step_solution));

	Integer y0_size = y0.size();
	RealMatrixSparse jac(y0_size,y0_size);

	RealMatrixSparse I;
	I.resize(y0_size,y0_size);
	I.setIdentity();

	RealMatrixSparse matrix_iter(y0_size,y0_size);

	RealVector tol_c(y0_size);
	RealVector est(y0_size);
	RealVector Est(y0_size);
	RealVector err_tol(y0_size);
	BoolVector components_ref(y0_size);

	RealVector y1(y0_size);
	RealVector y2(y0_size);

	IntegerVector ref(y0_size);
	ref.fill(1);

	internal_solver.setRhsFun(fun);
	internal_solver.setNewtSolv(std::move(newt_solv));


	while (t0 < tfinal){

		Integer NF = 0; // number of consecutive Newton divergence

		std::cout <<std::endl;
		std::cout<<" ==================== current time = " << t0;
		std::cout<<std::endl;

		// Calculate the Jacobian and the mixed tolerance

		jac = fun->evaldFdY(t0,y0);

		tol_c = Error_tol_rel * y0.array().abs() + Error_tol_abs;
		Bool errmax = true;


		while( errmax == true ){


			matrix_iter = I - d * h * jac;

			std::cout <<std::endl;
			std::cout <<" ==================== Solve time, h = " << t0 << " " << h;
			std::cout <<std::endl;

			// Calculate the solution with TRBDF2 Method


			internal_input.setInput(t0,h,hz_1,y0,y1,y2,matrix_iter,Newton_tol_rel,Newton_tol_abs,ref);
			internal_solver.setInput(internal_input);
			internal_solver.setParam(internal_param);

			internal_solver.compute();

			Bool newton_converge = ( internal_solver.getOutput().isNewtonDiverge() == false );

			if ( newton_converge == true ){

				// Newton converge

				est = internal_solver.getOutput().getEst();

				// Compute Standard Stiff Problem Estimator

				Eigen::SparseLU<RealMatrixSparse> solver;
				solver.analyzePattern(matrix_iter);
				solver.factorize(matrix_iter);
				Est = solver.solve(est);
				Est = Est.array().abs();

				err_tol = Est.array() / tol_c.array();
				components_ref = (err_tol.array() > del_max_err.array());

				Bool hasSucceded = (components_ref.array().any() == false);


				info() << "hasSucceded= " << hasSucceded ;

				// Store the numerical Solution

				SingleRateTRBDF2SolverData outputData;

				outputData.setTime(internal_solver.getOutput().getT2());
				outputData.setH(h);
				outputData.setError(Est);
				outputData.setY(internal_solver.getOutput().getY2());
				outputData.setHasSucceded(hasSucceded);
				outputData.setRefining(false);
				outputData.setNumbComponentsSolve(mesh);
				outputData.setMesh(mesh);

				std::unique_ptr<SingleRateTRBDF2SolverData> ptr_step_solution( new SingleRateTRBDF2SolverData(outputData));
				outputDataVector.emplace_back(std::move(ptr_step_solution));



				if (  hasSucceded == false ){

					// Newton is OK But some components estimator > Tol

					// Control restart timestep

					RealVector eta = tol_c.array() / Est.array();
					Real eta_min = eta.minCoeff();
					h = h*std::max( smoothInt,(v_ref_ext*(pow(eta_min,0.33))));
				}

				else{
					// Newton is OK But and ALL components estimator < Tol


					t0 = internal_solver.getOutput().getT2();
					hz_1 = (internal_solver.getOutput().getZ2() / h);
					y0 = internal_solver.getOutput().getY2();

					errmax = false;

					// Propose next timestep

					RealVector abs_Est = Est.array().abs();
					RealVector eta = tol_c.cwiseQuotient(abs_Est);
					Real eta_min = eta.minCoeff();
					Real minimum = std::min(smoothExt,(v_new_nref_ext*pow(eta_min,0.33)));
					h = std::min(hmax ,( h * minimum));

					// Take into account tfinal bound
					if ( (t0 + h) > tfinal )
						h = tfinal - t0;
				}
			}

			else{

				// Newton divergence

				NF += 1;
				if ( NF == 1)
					h = 0.2 * h;
				else {
					if( NF < 3 )
						h = 0.5 * h;
					else
						h = 0.8 * h;
				}
			}
		}
	}
}
