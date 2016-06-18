/*
 * SingleRateTRBDF2Solver.h
 *
 *  Created on: Nov 9, 2015
 *      Author: delpopol
 */

#ifndef SINGLERATETRBDF2SOLVER_H_
#define SINGLERATETRBDF2SOLVER_H_


#include "IMasterSolver.h"
#include "IRHSFunction.h"
#include "TRBDF2Solver/TRBDF2Solver.h"
#include "TraceMng.h"
#include "INewtonSolver.h"
#include "SingleRateTRBDF2Solver/SingleRateTRBDF2SolverData.h"

//! Derived Class of IMasterSolver computes the solution with the singlerate TRBDF2 method.

class SingleRateTRBDF2Solver : public TraceMng, public IMasterSolver {
public:
	SingleRateTRBDF2Solver();
	virtual ~SingleRateTRBDF2Solver();

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

	void setInterpolator(std::unique_ptr<IInterpolationSolver> interp);

	void compute();

private:
	Real tinitial;													/*!< Initial time*/
	Real hinitial;													/*!< Initial time step */
	Real Newton_tol_rel;											/*!< Relative tolerance for Newton solver */
	Real Newton_tol_abs;											/*!< Absolute tolerance for Newton solver */
	Real Error_tol_rel;												/*!< Relative tolerance for the estimate error */
	Real Error_tol_abs;												/*!< Absolute tolerance for the estimate error */
	RealVector hz_1initial;											/*!< Initial guess y0' */
	RealVector yinitial;											/*!< Initial condition */
	Real tfinal;													/*!< Final time */
	IRHSFunction *fun;												/*!< RHS Function */
	std::unique_ptr<INewtonSolver> newt_solv;										/*!< Newton solver */
	TRBDF2Solver internal_solver;									/*!< Time step solver */
	std::vector<std::unique_ptr<ISolverData>> outputDataVector;		/*!< Solution's vector */
};

#endif /* SINGLERATETRBDF2SOLVER_H_ */
