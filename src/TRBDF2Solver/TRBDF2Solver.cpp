/*
 * TRBDF2Solver.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#include "TRBDF2Solver.h"
#include "TRBDF2SolverNewtonFunction/TRBDF2SolverNewtonFunction.h"
#include "VectorUtility/VectorUtility.h"

TRBDF2Solver::TRBDF2Solver() {
	this->newt_solv = NULL;
	this->rhs_fun = NULL;
}

TRBDF2Solver::~TRBDF2Solver() {}

void TRBDF2Solver::setInput(const TRBDF2SolverInput& input) {
	this->input = input;
}

const TRBDF2SolverOutput& TRBDF2Solver::getOutput() const {
	return output;
}

void TRBDF2Solver::setOutput(const TRBDF2SolverOutput& output) {
	this->output = output;
}

void TRBDF2Solver::setRhsFun( IRHSFunction* rhsFun) {
	this->rhs_fun = rhsFun;
}

void TRBDF2Solver::setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv) {
		newt_solv = std::move(newtSolv);
	}

const TRBDF2SolverParameters& TRBDF2Solver::getParam() const {
	return param;
}

void TRBDF2Solver::setParam(TRBDF2SolverParameters& param) {
	this->param = param;
}

void TRBDF2Solver::compute(){

	// Store the input values

	Real t0 = input.getT0();
	Real h = input.getH();
	RealVector hz_1 = input.getHz1();
	Real tol_rel = input.getTolRel();
	Real tol_abs = input.getTolAbs();
	RealVector y0 = input.getY0();
	RealVector y1 = input.getY1();
	RealVector y2 = input.getY2();
	IntegerVector ref = input.getRef();
	RealMatrixSparse matrix_iter = input.getMatrixIter();

	// Store the parameters that are necessary for TRBDF2 method

	Real pd0 = param.getPd0();
	Real pd1 = param.getPd1();
	Real pd2 = param.getPd2();

	Real e0 = param.getE0();
	Real e1 = param.getE1();
	Real e2 = param.getE2();

	Real w = param.getW();
	Real d = param.getD();
	Real gm = param.getGm();

	Real t1 = t0 + h * gm;
	Real t2 = t0 + h;
	RealVector z0 = h * hz_1;

	IntegerVector no_ref(ref.cast<Real>().size());
	no_ref.fill(1);
	no_ref = no_ref - ref;
	Bool Newton_diverge = false;
	RealVector z1 = z0;


	Bool refining = (ref.all() == false);

	// 	We split the code in two cases:
	//  the case that we have to compute the solution for all the components,
	//  the case where we have to compute the solution only for some components.


	if ( refining == false ){

		// We compute the solution for all the components

		// Set the Newton function for the z variables and not for y
		//  z variables represent   \f$ z(x,t) = h y'(x,t)  \f$ where h is the time step.


		RealVector yTR = y0 + d * z0;
		TRBDF2SolverNewtonFunction fTR;
		fTR.setDt(h);
		fTR.setFun(rhs_fun);
		fTR.setTnp(t1);
		fTR.setYn(yTR);
		fTR.setRef(ref);

		Integer size = z1.size();
		Integer maxNumberIteration =std::min(10,size);


		newt_solv->compute(fTR,matrix_iter,z1,tol_rel,tol_abs,Newton_diverge,maxNumberIteration);

		y1 = y0 +d*z0 + d*z1;

	}else{

		// We compute the solution for some components

		RealVector dz0 = d* z0;


		 // We create the vector for the evaluation of the rhs with the interpolated values for that
		 // componets that are not computed.


		RealVector yTR = y1.cwiseProduct(no_ref.cast<Real>());
		yTR += y0.cwiseProduct(ref.cast<Real>());
		yTR += VectorUtility::vectorProlong(dz0,ref);

		TRBDF2SolverNewtonFunction fTR;

		fTR.setDt(h);
		fTR.setFun(rhs_fun);
		fTR.setTnp(t1);
		fTR.setYn(yTR);
		fTR.setRef(ref);
		fTR.setD(d);

		Integer size = z1.size();
		Integer maxNumberIteration =std::min(100,5*size);


		newt_solv->compute(fTR,matrix_iter,z1,tol_rel,tol_abs,Newton_diverge,maxNumberIteration);

		// From z1 we calculate the y1 vector
		RealVector y_partial = dz0 + d*z1;
		y_partial = VectorUtility::vectorProlong(y_partial,ref);
		y1 = y1.cwiseProduct(no_ref.cast<Real>());
		y1 += y0.cwiseProduct(ref.cast<Real>());
		y1 += y_partial.cwiseProduct(ref.cast<Real>());



	}
	if( Newton_diverge == false  ){

		RealVector z2 = z0;

		if ( refining == false ){
			z2 = pd0*z0 + pd1*z1 + pd2*(y1-y0);

			RealVector yBDF = y0 + w*z0 + w*z1;

			TRBDF2SolverNewtonFunction fBDF;

			fBDF.setDt(h);
			fBDF.setFun(rhs_fun);
			fBDF.setTnp(t2);
			fBDF.setYn(yBDF);
			fBDF.setRef(ref);
			fBDF.setD(d);

			Integer size = z2.size();
			Integer maxNumberIteration =std::min(10,size);

			newt_solv->compute(fBDF,matrix_iter,z2,tol_rel,tol_abs,Newton_diverge,maxNumberIteration);


			y2 = y0 + w*z0 + w*z1 + d*z2;
		}
		else{

			RealVector diff_solution = y1-y0;
			z2 = pd0*z0 + pd1*z1 + pd2*VectorUtility::vectorReduce(diff_solution,ref);

			// We add at the vector the interpolated values.

			RealVector y_partial = w*z0 + w*z1;
			RealVector yBDF = y2.cwiseProduct(no_ref.cast<Real>());
			yBDF += y0.cwiseProduct(ref.cast<Real>());
			yBDF += VectorUtility::vectorProlong(y_partial,ref);

			TRBDF2SolverNewtonFunction fBDF;

			fBDF.setDt(h);
			fBDF.setFun(rhs_fun);
			fBDF.setTnp(t2);
			fBDF.setYn(yBDF);
			fBDF.setRef(ref);

			Integer size = z2.size();
			Integer maxNumberIteration =std::min(10,5*size);

			newt_solv->compute(fBDF,matrix_iter,z2,tol_rel,tol_abs,Newton_diverge,maxNumberIteration);

			// We convert the z values into y values.

			RealVector delta_y2 = w*z0 + w*z1 + d*z2;
			y2 = y2.cwiseProduct(no_ref.cast<Real>());
			y2 +=  y0.cwiseProduct(ref.cast<Real>());
			y2 += VectorUtility::vectorProlong(delta_y2,ref);


		}
		if ( Newton_diverge == false  ){
			RealVector est = (z0*(e0-w) + z1*(e1-w) +z2*(e2-d));
			est = est.array().abs();

			// Set the output

			output.setEst(est);
			output.setT2(t2);
			output.setY2(y2);
			output.setZ2(z2);
			output.setT1(t1);
			output.setY1(y1);
			output.setZ0(z0);
			output.setZ1(z1);
			output.setZ2(z2);

			//std::cout<<y2<<std::endl;

			std::cout<<std::endl<<"time "<<t2<<std::endl;

		}

	}
	output.setNewtonDiverge(Newton_diverge);
}




