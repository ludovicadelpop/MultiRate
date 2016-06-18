/*
 * MultiRateTRBDF2Solver.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: delpopol
 */

#include "MultiRateTRBDF2Solver.h"
#include "VectorUtility/VectorUtility.h"
#include <limits>
#include <Eigen/Sparse>
#include "InterpolationSolver/InterpolationInputSolver.h"
#include "InterpolationSolver/InterpolationOutputSolver.h"

MultiRateTRBDF2Solver::MultiRateTRBDF2Solver() {
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

MultiRateTRBDF2Solver::~MultiRateTRBDF2Solver() {}

void MultiRateTRBDF2Solver::setFun(IRHSFunction* fun) {
	this->fun = fun;
}

void MultiRateTRBDF2Solver::setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv) {
	newt_solv = std::move(newtSolv);
}

void MultiRateTRBDF2Solver::setInterpolator(std::unique_ptr<IInterpolationSolver> interp) {
	interpolation = std::move(interp);
}

void MultiRateTRBDF2Solver::setHinitial(Real hinitial) {
	this->hinitial = hinitial;
}

void MultiRateTRBDF2Solver::setHz1initial(const RealVector& hz1initial) {
	hz_1initial = hz1initial;
}

void MultiRateTRBDF2Solver::setTfinal(Real tfinal) {
	this->tfinal = tfinal;
}

void MultiRateTRBDF2Solver::setTinitial(Real tinitial) {
	this->tinitial = tinitial;
}

void MultiRateTRBDF2Solver::setErrorTolAbs(Real errorTolAbs) {
	Error_tol_abs = errorTolAbs;
}

void MultiRateTRBDF2Solver::setErrorTolRel(Real errorTolRel) {
	Error_tol_rel = errorTolRel;
}

void MultiRateTRBDF2Solver::setNewtonTolAbs(Real newtonTolAbs) {
	Newton_tol_abs = newtonTolAbs;
}

void MultiRateTRBDF2Solver::setNewtonTolRel(Real newtonTolRel) {
	Newton_tol_rel = newtonTolRel;
}

void MultiRateTRBDF2Solver::setYinitial(const RealVector& yinitial) {
	this->yinitial = yinitial;
}

std::vector<std::unique_ptr<ISolverData>>&& MultiRateTRBDF2Solver::getSolution(){
	return (std::move(outputDataVector));
}

void MultiRateTRBDF2Solver::compute(){

	// Parameters used to calculate the time step size

	Real hmax = 1.e+4;
	Real v_ref_ext = 0.7;
	Real v_ref_int = 0.7;
	Real smooth = 6.0;
	Real smoothL = 0.02;
	Real smoothInt = 0.002;
	Real smoothExt = 4.0;
	Real v_new_nref_ext = 0.9;
	Real v_new_nref_int = 0.7;
	Real v_new_ref_ext = 0.9;
	Real v_new_ref_int = 0.7;
	Real v_global_fail_int = 0.7;
	Real v_global_fail_ext = 0.7;


	// Intial values
	Real t0 = tinitial;
	Real h = hinitial;
	RealVector y0 = yinitial;
	RealVector hz_1 = hz_1initial;

	Integer y0_size = y0.size();

	IntegerVector ref(y0_size);
	ref.fill(1);

	RealVector del_max_err(y0_size);
	del_max_err.fill(0.7);

	TRBDF2SolverInput internal_input;

	//Parameters TR-BDF2 Interpolation

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


	RealVector E(y0_size);
	E.fill(0.0);

	//First data output: initial condition

	MultiRateTRBDF2SolverData outputData;

	outputData.setTime(t0);
	outputData.setH(0.0);
	outputData.setError(E);
	outputData.setY(y0);
	outputData.setHasSucceded(true);
	outputData.setNumbComponentsSolve(ref);
	outputData.setMesh(ref);
	outputData.setRefining(false);

	std::unique_ptr<MultiRateTRBDF2SolverData> ptr_step_solution (new MultiRateTRBDF2SolverData(outputData));
	outputDataVector.emplace_back(std::move(ptr_step_solution));

	Real t1;
	Real t2;
	RealVector z0(y0_size);
	RealVector z1(y0_size);
	RealVector z2(y0_size);
	RealVector y1(y0_size);
	RealVector y2(y0_size);

	RealVector tol_c(y0_size); // mixed tolerance

	RealVector est;        					// estimator
	RealVector Est;							// modified estimator
	RealVector err_tol(y0_size);
	BoolVector components_ref(y0_size);		//components set to refine

	// Initialize vector useful to compute the solution in a sub-level

	std::vector<Real> t_fin_vec;       //vector of final times
	t_fin_vec.emplace_back(tfinal);
	std::vector<IntegerVector> ref_vec;		//vector of the refined components
	ref_vec.emplace_back(ref);
	std::vector<IntegerVector> ref_prev_vec;	// vector of the refined components at the previos iteration
	ref_prev_vec.emplace_back(ref);
	std::vector<RealVector> tol_vec;		//mixed tolerance vector
	tol_vec.emplace_back(E);
	std::vector<Real> h_vec;				//time step size vector
	h_vec.emplace_back(h);
	std::vector<RealVector> Est_vec;		//estimator vector
	Est_vec.emplace_back(E);
	std::vector<RealVector> z2_vec;			//vector of solution for the z variable
	z2_vec.emplace_back(E);
	std::vector<RealVector> hz_vec;			//vector of initial conditions for z variable
	hz_vec.emplace_back(hz_1);

	RealVector tol_red; 		// mixed tolerance reduced

	RealMatrixSparse jac;			//jacobian matrix
	RealMatrixSparse I;				//identity matrix
	RealMatrixSparse matrix_iter;	//jacobian matrix for z variable

	InterpolationInputSolver interp_input;	//input for the interpolator

	std::vector<InterpolationInputSolver> interp_input_vec;

	Bool newton_converge;

	unsigned int n_sub = 0;             // sub-levels index

	internal_solver.setRhsFun(fun);                    //set the RHSfunction
	internal_solver.setNewtSolv(std::move(newt_solv)); // set the Newton solver
	internal_solver.setParam(internal_param);		   // set the parameters

	while (t0 < t_fin_vec[n_sub]){

		Integer NF = 0; // how many consecutive times Newton solver has diverged

		std::cout <<endl;
		cout<<" ==================== current time = " << t0;
		std::cout<<endl;

		//Calculate the Jacobian and the mixed tolerance

		if( n_sub == 0){

			cout<<"level= "<<n_sub<<endl;

			jac.resize(y0_size,y0_size);
			matrix_iter.resize(y0_size,y0_size);
			jac = fun->evaldFdY(t0,y0);
			I.resize(y0_size,y0_size);
			I.setIdentity();

			tol_c = Error_tol_rel * y0.array().abs() + Error_tol_abs;
			tol_vec[n_sub] = tol_c;
		}
		else{

			cout<<"level= "<<n_sub<<" numb components "<<ref_vec[n_sub-1].sum()<<endl;

			Integer ref_elem = ref_vec[n_sub-1].sum();
			jac.resize(ref_elem,ref_elem);
			jac = fun->evaldFdY(t0,y0,ref_vec[n_sub-1]);

			matrix_iter.resize(ref_elem,ref_elem);
			I.resize(ref_elem,ref_elem);
			I.setIdentity();

			tol_c = Error_tol_rel * y0.array().abs() + Error_tol_abs;
			tol_vec[n_sub] = tol_c;
		}


		Bool errmax = true;

		while( errmax == true ){  // has_succeded == false!! We don't reject the time step

			matrix_iter = I - d * h * jac; //we solve the problem in function of z.

			std::cout <<std::endl;
			cout <<" ==================== Solve time, h = " << t0 << " " << h;
			std::cout <<std::endl;

			//! Calculate the solution with TRBDF2 Method

			if (n_sub == 0){
				t1 = t0 + h*gm;
				t2 = t0 + h;
				internal_input.setInput(t0,h,hz_vec[n_sub],y0,y1,y2,matrix_iter,Newton_tol_rel,Newton_tol_abs,ref);
				internal_solver.setInput(internal_input);
				internal_solver.compute();

				newton_converge = ( internal_solver.getOutput().isNewtonDiverge() == false );

			}
			else{

				//! we are in a sub-level we have to do the interpolation
				t1 = t0 + h*gm;
				t2 = t0 + h;
				interpolation->setInput(interp_input_vec[n_sub-1]);
				interpolation->compute(t1,t2,gm);

				RealVector y1 = interpolation->getOutput().getY1();
				RealVector y2 = interpolation->getOutput().getY2();

				tol_red.resize(ref_vec[n_sub-1].sum());
				tol_red	= VectorUtility::vectorReduce(tol_vec[n_sub],ref_vec[n_sub-1]);
				RealVector hz_red = VectorUtility::vectorReduce(hz_vec[n_sub],ref_vec[n_sub-1]);

				internal_input.setInput(t0,h,hz_red,y0,y1,y2,matrix_iter,Newton_tol_rel,Newton_tol_abs,ref_vec[n_sub-1]);
				internal_solver.setInput(internal_input);

				internal_solver.compute();
				newton_converge = ( internal_solver.getOutput().isNewtonDiverge() == false );
			}

			if ( newton_converge == true ){
				// Newton converge

				//! Compute Standard Stiff Problem Estimator
				if (n_sub == 0){
					est.resize(y0_size);
					est = internal_solver.getOutput().getEst();

					Est.resize(y0_size);
					Eigen::SparseLU<RealMatrixSparse> solver;
					solver.analyzePattern(matrix_iter);
					solver.factorize(matrix_iter);
					Est = solver.solve(est);
					Est = Est.array().abs();

					Est_vec[n_sub] = Est;

					err_tol = Est.array() / tol_vec[n_sub].array();
					components_ref = (err_tol.array() > del_max_err.array());
					ref_vec[n_sub] = components_ref.cast<Integer>();
					ref_prev_vec[n_sub] = ref;

					z0.resize(y0_size);
					z1.resize(y0_size);
					z2.resize(y0_size);

				}
				else{

					Integer ref_elem = ref_vec[n_sub-1].sum();
					est.resize(ref_elem);
					est = internal_solver.getOutput().getEst();

					Est.resize(ref_elem);
					Eigen::SparseLU<RealMatrixSparse> solver;
					solver.analyzePattern(matrix_iter);
					solver.factorize(matrix_iter);
					Est = solver.solve(est);
					Est = Est.array().abs();

					Est_vec[n_sub]=VectorUtility::vectorProlong(Est,ref_vec[n_sub-1]);

					ref_prev_vec[n_sub] = ref_vec[n_sub-1];
					err_tol = Est_vec[n_sub].array() / tol_vec[n_sub].array();

					components_ref = (err_tol.array() > del_max_err.array());
					ref_vec[n_sub] = components_ref.cast<Integer>();

					z0.resize(ref_elem);
					z1.resize(ref_elem);
					z2.resize(ref_elem);
				}

				//! Calculate if the time step has succeded and if we have some components that should be refine


				IntegerVector diff_ref =  (ref_prev_vec[n_sub] - ref_vec[n_sub]);
				Bool refining = (ref_vec[n_sub].any() &&  diff_ref.any());
				Bool has_succeded = (refining == false && ref_vec[n_sub].any() == false);
				info() << "hasSucceded= " << has_succeded ;
				cout<<endl;
				info() << "refining= " << refining ;

				//! Store the numerical Solution and update values

				y2 = internal_solver.getOutput().getY2();
				y1 = internal_solver.getOutput().getY1();
				z0 = internal_solver.getOutput().getZ0();
				z1 = internal_solver.getOutput().getZ1();
				z2 = internal_solver.getOutput().getZ2();

				MultiRateTRBDF2SolverData outputData;

				outputData.setTime(internal_solver.getOutput().getT2());
				outputData.setH(h);
				outputData.setError(Est_vec[n_sub]);
				outputData.setY(y2);
				outputData.setHasSucceded(has_succeded);
				outputData.setNumbComponentsSolve(ref_prev_vec[n_sub]);
				outputData.setMesh(ref_prev_vec[n_sub]);
				outputData.setRefining(refining);

				std::unique_ptr<MultiRateTRBDF2SolverData> ptr_step_solution (new MultiRateTRBDF2SolverData(outputData));
				outputDataVector.emplace_back(std::move(ptr_step_solution));
				

				if( refining == true ){

					// we have to refined
					if(n_sub == 0){

						// store the values that we need for the interpolation

						interp_input.setRef(ref_vec[n_sub]);

						//we create the time vectors because for each component, if the sublevels
						//become more than one, we could have different time slabs where the solution
						//is knowed.

						RealVector t0_vec(y0_size);
						t0_vec.fill(t0);
						interp_input.setT0Int(t0_vec);
						RealVector t1_vec(y0_size);
						t1_vec.fill(t1);
						interp_input.setT1Int(t1_vec);
						RealVector t2_vec(y0_size);
						t2_vec.fill(t2);
						interp_input.setT2Int(t2_vec);
						interp_input.setY0Int(y0);
						interp_input.setY1Int(y1);
						interp_input.setY2Int(y2);
						interp_input.setZ0Int(z0);
						interp_input.setZ1Int(z1);
						interp_input.setZ2Int(z2);
						interp_input_vec.emplace_back(interp_input);
					}
					else{
						
						// update the values that we need for the interpolation
						// we set the new values only for the components that at the previous time step
						// were not good but now they will have to be interpolated.
						IntegerVector no_ref(y0_size);
						no_ref.fill(1);
						no_ref -= ref_vec[n_sub-1];

						interp_input.setRef(ref_vec[n_sub]);

						RealVector z0_temp = interp_input_vec[n_sub-1].getZ0Int();
						z0_temp = z0_temp.cwiseProduct(no_ref.cast<Real>());
						z0_temp += VectorUtility::vectorProlong(z0,ref_prev_vec[n_sub]);
						interp_input.setZ0Int(z0_temp);

						RealVector z1_temp = interp_input_vec[n_sub-1].getZ1Int();
						z1_temp = z1_temp.cwiseProduct(no_ref.cast<Real>());
						z1_temp += VectorUtility::vectorProlong(z1,ref_prev_vec[n_sub]);
						interp_input.setZ1Int(z1_temp);

						RealVector z2_temp = interp_input_vec[n_sub-1].getZ0Int();
						z2_temp = z2_temp.cwiseProduct(no_ref.cast<Real>());
						z2_temp += VectorUtility::vectorProlong(z2,ref_prev_vec[n_sub]);
						interp_input.setZ2Int(z2_temp);

						RealVector y0_temp = interp_input_vec[n_sub-1].getY0Int();
						y0_temp = y0_temp.cwiseProduct(no_ref.cast<Real>());
						y0_temp += y0.cwiseProduct(ref_prev_vec[n_sub].cast<Real>());
						interp_input.setY0Int(y0_temp);

						RealVector y1_temp = interp_input_vec[n_sub-1].getY1Int();
						y1_temp = y1_temp.cwiseProduct(no_ref.cast<Real>());
						y1_temp += y1.cwiseProduct(ref_prev_vec[n_sub].cast<Real>());
						interp_input.setY1Int(y1_temp);

						RealVector y2_temp = interp_input_vec[n_sub-1].getY2Int();
						y2_temp = y2_temp.cwiseProduct(no_ref.cast<Real>());
						y2_temp += y2.cwiseProduct(ref_prev_vec[n_sub].cast<Real>());
						interp_input.setY2Int(y2_temp);

						RealVector t0_temp = interp_input_vec[n_sub-1].getT0Int();
						t0_temp = t0_temp.cwiseProduct(no_ref.cast<Real>());
						t0_temp += t0*((ref_prev_vec[n_sub]).cast<Real>());
						interp_input.setT0Int(t0_temp);

						RealVector t1_temp = interp_input_vec[n_sub-1].getT1Int();
						t1_temp = t1_temp.cwiseProduct(no_ref.cast<Real>());
						t1_temp += t1*((ref_prev_vec[n_sub]).cast<Real>());
						interp_input.setT1Int(t1_temp);

						RealVector t2_temp = interp_input_vec[n_sub-1].getT2Int();
						t2_temp = t2_temp.cwiseProduct(no_ref.cast<Real>());
						t2_temp += t2*((ref_prev_vec[n_sub]).cast<Real>());
						interp_input.setT2Int(t2_temp);

						interp_input_vec.emplace_back(interp_input);
					}


					ref_vec.emplace_back(ref);
					ref_prev_vec.emplace_back(ref);
					tol_vec.emplace_back(E);
					Est_vec.emplace_back(E);
					z2_vec.emplace_back(E);
					hz_vec.emplace_back(E);
					h_vec.emplace_back(0.0);


					h_vec[n_sub] = h;
					z2_vec[n_sub] = VectorUtility::vectorProlong(z2,ref_prev_vec[n_sub]);


					//! Propose next time step

					if (n_sub >= 1){
						RealVector eta = tol_red.cwiseQuotient(Est);
						Real eta_min = eta.minCoeff();
						eta_min = pow(eta_min,0.33);
						h = h*max(smoothInt,v_ref_int*eta_min);
					}
					else{
						RealVector eta = tol_vec[n_sub].cwiseQuotient(Est);
						Real eta_min = eta.minCoeff();
						eta_min = pow(eta_min,0.33);
						h = h*max(smoothInt,v_ref_ext*eta_min);
					}

					n_sub = n_sub + 1;
					hz_vec[n_sub] =hz_vec[n_sub-1].cwiseProduct(ref_prev_vec[n_sub].cast<Real>());

					t_fin_vec.emplace_back(t0 + h_vec[n_sub-1]);
					errmax = false;
				}
				else{
					if (has_succeded == false){

						//! if we don't accept the time step we calculate a small one

						if (n_sub >= 1){
							Est = Est.array().abs();
							RealVector eta = tol_red.cwiseQuotient(Est);
							Real eta_min = eta.minCoeff();
							eta_min = pow(eta_min,0.33);
							h = v_global_fail_int * h * max(smoothL,eta_min);
						}
						else{
							Est= Est.array().abs();
							RealVector eta = tol_vec[n_sub].cwiseQuotient(Est);
							Real eta_min = eta.minCoeff();
							eta_min = pow(eta_min,0.33);
							h = v_global_fail_ext * h * max(smoothL,eta_min);
						}
					}
					else{

						//! we accept the time step and it is not necessary to refine

						t0 = internal_solver.getOutput().getT2();
						y0 = internal_solver.getOutput().getY2();

						if( n_sub == 0){
							hz_vec[n_sub] = (z2 / h);
						}
						else{
							RealVector z2_long = VectorUtility::vectorProlong(z2,ref_prev_vec[n_sub]);
							hz_vec[n_sub] = (z2_long / h);
						}
						ref_vec[n_sub] = ref_prev_vec[n_sub];
						errmax = false;

						//! Propose next time step

						if( n_sub == 0 ){
							Est = Est.array().abs();
							RealVector eta = tol_vec[n_sub].cwiseQuotient(Est);
							Real eta_min = eta.minCoeff();
							Real minimum = min(smoothExt,(v_new_nref_ext*pow(eta_min,0.33)));
							h = min(hmax ,( h * minimum));
						}
						else{
							Est = Est.array().abs();
							RealVector eta = tol_red.cwiseQuotient(Est);
							Real eta_min = eta.minCoeff();
							Real minimum = min(smooth,(v_new_nref_int*pow(eta_min,0.33)));
							h = min(hmax ,( h * minimum));
						}
						// Take into account t-final bound
						if ( (t0 + h) > t_fin_vec[n_sub] )
							h = t_fin_vec[n_sub] - t0;


					}
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

		if (abs(t_fin_vec[n_sub]-t0) <	std::numeric_limits<Real>::epsilon() && n_sub != 0){

			/*!
			 * Special case: we exit from a sub-level that has the same t-final of the previous one or more than one.
			 * we have to update the initial condition (hz) and we have to eliminate the variables of the forward sub-levels.
			*/

			interp_input_vec.erase(interp_input_vec.end()-1);
			t_fin_vec.erase(t_fin_vec.end()-1);
			n_sub = n_sub-1;

			RealVector hz_temp(y0_size);
			hz_temp.fill(0.0);

			IntegerVector no_ref(y0_size);
			no_ref.fill(1);
			no_ref -= ref_vec[n_sub];

			hz_1 = hz_vec[n_sub+1].cwiseProduct(ref_vec[n_sub].cast<Real>());
			RealVector z_temp = z2_vec[n_sub]/h_vec[n_sub];
			hz_1 += z_temp.cwiseProduct(no_ref.cast<Real>());

			h_vec.erase(h_vec.end()-1);
			hz_vec.erase(hz_vec.end()-1);
			z2_vec.erase(z2_vec.end()-1);
			ref_vec.erase(ref_vec.end()-1);
			ref_prev_vec.erase(ref_prev_vec.end()-1);
			tol_vec.erase(tol_vec.end()-1);
			Est_vec.erase(Est_vec.end()-1);


			
			while(abs(t_fin_vec[n_sub]-t0) <	std::numeric_limits<Real>::epsilon() && n_sub != 0){
				 n_sub -= 1;
				 interp_input_vec.erase(interp_input_vec.end()-1);
				 t_fin_vec.erase(t_fin_vec.end()-1);
				 no_ref.fill(1);
				 no_ref -= ref_prev_vec[n_sub];

				 RealVector z_temp = z2_vec[n_sub]/h_vec[n_sub];
				 hz_temp += z_temp.cwiseProduct(no_ref.cast<Real>());

				h_vec.erase(h_vec.end()-1);
				hz_vec.erase(hz_vec.end()-1);
				z2_vec.erase(z2_vec.end()-1);
				ref_vec.erase(ref_vec.end()-1);
				ref_prev_vec.erase(ref_prev_vec.end()-1);
				tol_vec.erase(tol_vec.end()-1);
				Est_vec.erase(Est_vec.end()-1);
			}

			hz_1 += hz_temp;
			//! Propose next time step

			if( n_sub == 0 ){
				RealVector eta = tol_vec[n_sub].cwiseQuotient(Est_vec[n_sub]);
				IntegerVector diff = ref_prev_vec[n_sub] - ref_vec[n_sub];
				RealVector eta_red = VectorUtility::vectorReduce(eta,diff);
				Real eta_min = eta_red.minCoeff();
				Real minimum = min(smoothExt,(v_new_ref_ext*eta_min));
				Real h_tmp = h_vec[n_sub];
				h = min(hmax ,( h_tmp * minimum));
			}
			else{
				RealVector eta = tol_vec[n_sub].cwiseQuotient(Est_vec[n_sub]);
				IntegerVector diff = ref_prev_vec[n_sub] - ref_vec[n_sub];
				RealVector eta_red = VectorUtility::vectorReduce(eta,diff);
				Real eta_min = eta_red.minCoeff();
				Real minimum = min(smooth,(v_new_ref_int*eta_min));
				Real h_tmp = h_vec[n_sub];
				h = min(hmax ,( h_tmp * minimum));
			}
			// Take into account tfinal bound
			if ( (t0 + h) > t_fin_vec[n_sub] )
				h = t_fin_vec[n_sub] - t0;

			hz_vec[n_sub] = hz_1;
			ref_vec[n_sub] = ref_prev_vec[n_sub];
			outputDataVector[outputDataVector.size()-1]->setMesh(ref_prev_vec[n_sub]);
		}
	}
}



