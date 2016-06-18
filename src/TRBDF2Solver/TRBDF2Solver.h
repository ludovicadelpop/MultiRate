/*
 * TRBDF2Solver.h
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#ifndef TRBDF2SOLVER_H_
#define TRBDF2SOLVER_H_

#include "TRBDF2SolverInput.h"
#include "TRBDF2SolverOutput.h"
#include "TRBDF2SolverParameters.h"
#include "StandardTypes.h"
#include "IRHSFunction.h"
#include "INewtonSolver.h"
#include "TraceMng.h"

using namespace Utils;

//! A single time step solver with the TR-BDF2 method
class TRBDF2Solver {
public:
	TRBDF2Solver();
	virtual ~TRBDF2Solver();

	void setInput(const TRBDF2SolverInput& input);

	const TRBDF2SolverOutput& getOutput() const;

	void setOutput(const TRBDF2SolverOutput& output);

	void setRhsFun(IRHSFunction* rhsFun);

	void setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv);

	void compute();

	const TRBDF2SolverParameters& getParam() const;

	void setParam(TRBDF2SolverParameters& param);


private:
	TRBDF2SolverParameters param;					/*!< Method Parameters */
	TRBDF2SolverInput input;						/*!< Input parameters to compute the solution */
	TRBDF2SolverOutput output;						/*!< Output values */
	IRHSFunction* rhs_fun;							/*!< RHS Function */
	std::unique_ptr<INewtonSolver> newt_solv;		/*!< Newton Solver */
};

#endif /* TRBDF2SOLVER_H_ */
