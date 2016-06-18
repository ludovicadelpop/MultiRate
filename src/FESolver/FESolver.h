/*
 * FESolver.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef FESOLVER_H_
#define FESOLVER_H_

#include "IRHSFunction.h"
#include "FESolverInput.h"
#include "FESolverOutput.h"
#include "TraceMng.h"


//! Single step solver with Forward Euler method
class FESolver:public TraceMng {
public:
	FESolver();
	virtual ~FESolver();

	void setRHSFunction(IRHSFunction* fun);
	void compute();

	void setInput(FESolverInput input);
	FESolverOutput getOutputFE();



private:
	FESolverInput input;			/*!< Input parameters */
	FESolverOutput output;			/*!< Output parameters */
	IRHSFunction* rhs_fun;			/*!< RHS Function */

};

#endif /* FESOLVER_H_ */
