/*
 * SingleRateBESolver.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef SINGLERATEBESOLVER_H_
#define SINGLERATEBESOLVER_H_

#include "BESolver/BESolver.h"
#include "IMasterSolver.h"
#include "IRHSFunction.h"
#include "ISolverData.h"
#include "StandardTypes.h"
#include "INewtonFunction.h"
#include "INewtonSolver.h"
#include "SingleRateBESolverData.h"

using namespace Utils;
using namespace std;

//! Class to define the Singlerate Backward Euler Solver with a fixed time step.

class SingleRateBESolver: public TraceMng, public IMasterSolver {
public:
	SingleRateBESolver();
	virtual ~SingleRateBESolver();

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

	IRHSFunction* fun;											/*!< RHS Function */
	std::unique_ptr<INewtonSolver> newt_solv;									/*!< Newton solver */
	Real tinitial;												/*!< Initial time */
	Real tfinal;												/*!< Final time*/
	Real dt;													/*!< Time step */
	Real Newton_tol_rel;										/*!< Relative tolerance for Newton solver */
	Real Newton_tol_abs;										/*!< Absolute tolerance for Newton solver */
	Real Error_tol_rel;											/*!< Relative tolerance for the estimate error */
	Real Error_tol_abs;											/*!< Absolute tolerance for the estimate error */
	RealVector yinitial;										/*!< Initial condition */
	BESolver time_step_solver;									/*!< Time step solver */
	vector<std::unique_ptr<ISolverData>> vect_solution;			/*!< Solution's vector */

};

#endif /* SINGLERATEBESOLVER_H_ */
