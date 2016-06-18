/*
 * SingleRateFESolver.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef SINGLERATEFESOLVER_H_
#define SINGLERATEFESOLVER_H_

#include "FESolver/FESolver.h"
#include "FESolver/FESolverUtils.h"
#include "IMasterSolver.h"
#include "IRHSFunction.h"
#include "StandardTypes.h"
#include "ISolverData.h"

using namespace Utils;

//! Class to define the Singlerate Forward Euler Solver with a fixed time step.

class SingleRateFESolver: public TraceMng, public IMasterSolver {
public:
	SingleRateFESolver();
	virtual ~SingleRateFESolver();

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
	Real tinitial;												/*!< Initial time */
	Real tfinal;												/*!< Final time */
	Real dt;													/*!< Time step */
	RealVector yinitial;										/*!< Initial condition */
	FESolver time_step_solver;									/*!< Time step solver */
	std::vector<std::unique_ptr<ISolverData>> vect_solution;			/*!< Solution's vector */
};

#endif /* SINGLERATEFESOLVER_HPP_ */
