/*
 * MultiRateTRBDF2Solver.h
 *
 *  Created on: Nov 23, 2015
 *      Author: delpopol
 */

#ifndef MULTIRATETRBDF2SOLVER_H_
#define MULTIRATETRBDF2SOLVER_H_

#include "IMasterSolver.h"
#include "IRHSFunction.h"
#include "TRBDF2Solver/TRBDF2Solver.h"
#include <vector>

#include "MultiRateTRBDF2SolverData.h"
#include "IInterpolationSolver.h"

#include "INewtonSolver.h"
#include "TraceMng.h"

#include "StandardTypes.h"
using namespace Utils;
using namespace std;

//! Multirate TRBDF2 method with time-adjusting strategy

class MultiRateTRBDF2Solver: public TraceMng, public IMasterSolver {
public:
	MultiRateTRBDF2Solver();
	virtual ~MultiRateTRBDF2Solver();
	//! Sets the RHS Function
	void setFun(IRHSFunction* fun);
	//! Sets the Newton SOlver
	void setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv);
	//! Sets the time step for the first time slab
	void setHinitial(Real hinitial);
	//! Sets the initial guess for the variable z
	void setHz1initial(const RealVector& hz1initial);
	//! Sets the final time
	void setTfinal(Real tfinal);
	//! Sets the initial time
	void setTinitial(Real tinitial);
	//! Sets the initial condition
	void setYinitial(const RealVector& yinitial);
	//! Gets the solution vector
	std::vector<std::unique_ptr<ISolverData>>&& getSolution();
	//! Sets the absolute Newton tolerance
	void setNewtonTolAbs(Real newtonTolAbs);
	//! Sets the relative Newton tolerance
	void setNewtonTolRel(Real newtonTolRel);
	//! Sets the absolute Error tolerance
	void setErrorTolAbs(Real errorTolAbs);
	//! Sets the relative Error tolerance
	void setErrorTolRel(Real errorTolRel);
	//! Sets interpolator
	void setInterpolator(std::unique_ptr<IInterpolationSolver> interp);

	void compute();

private:
	Real tinitial;														 /*!< Initial time*/
	Real hinitial;										 				 /*!< Initial size time step */
	Real Newton_tol_rel;												 /*!< Relative tolerance for the Newton solver */
	Real Newton_tol_abs;												 /*!< Absolute tolerance for the Newton solver */
	Real Error_tol_rel;													 /*!< Relative tolerance for the estimate error */
	Real Error_tol_abs;													 /*!< Absolute tolerance for the estimate error */
	RealVector hz_1initial;												 /*!< Initial guess y0' */
	RealVector yinitial;												 /*!< Initial solution */
	Real tfinal;										 				 /*!< Final time */
	IRHSFunction *fun;													 /*!< RHS Function */
	std::unique_ptr<INewtonSolver> newt_solv;    						 /*!< Newton solver */
	std::unique_ptr<IInterpolationSolver> interpolation; 				 /*!< Interpolation */
	TRBDF2Solver internal_solver;										 /*!< Internal time step solver */
	std::vector<std::unique_ptr<ISolverData>> outputDataVector;			 /*!< Output data */
};

#endif /*MULTIRATETRBDF2SOLVER_H_ */
