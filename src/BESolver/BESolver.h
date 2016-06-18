/*
 * BESolver.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef BESOLVER_H_
#define BESOLVER_H_

#include "BESolverInput.h"
#include "BESolverOutput.h"
#include "INewtonFunction.h"
#include "TraceMng.h"
#include "IRHSFunction.h"
#include "INewtonSolver.h"

//! Class to solve a single time step with backward Euler method
class BESolver:public TraceMng {
public:
	BESolver();
	virtual ~BESolver();

	void setRHSFunction(IRHSFunction* fun);
	void setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv);

	//!This method advances by one time step the solution.
	void compute();

	void setInput(BESolverInput input);
	BESolverOutput getOutputBE();



private:
	BESolverInput input;						/*!< Input */
	BESolverOutput output;  					/*!< Output */
	IRHSFunction* rhs_fun;      				/*!< RHS Function */
	std::unique_ptr<INewtonSolver> newt_solv;   /*!< Newton solver */

};

#endif /* BESOLVER_H_ */
