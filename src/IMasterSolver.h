/*
 * IMasterSolver.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef IMASTERSOLVER_H_
#define IMASTERSOLVER_H_

#include <vector>
#include <memory>
#include "IRHSFunction.h"
#include "ISolverData.h"
#include "INewtonSolver.h"
#include "IInterpolationSolver.h"

//! Base class for the Master solver
class IMasterSolver {
public:
	IMasterSolver() {}
	virtual ~IMasterSolver() {}

	virtual void setNewtSolv(std::unique_ptr<INewtonSolver> newtSolv)=0;
	virtual void setInterpolator(std::unique_ptr<IInterpolationSolver> interp)=0;
	virtual void setHinitial(Real hinitial)=0;
	virtual void setHz1initial(const RealVector& hz1initial)=0;
	virtual void setTfinal(Real tfinal)=0;
	virtual void setTinitial(Real tinitial)=0;
	virtual void setYinitial(const RealVector& yinitial)=0;
	virtual void setNewtonTolAbs(Real newtonTolAbs)=0;
	virtual void setNewtonTolRel(Real newtonTolRel)=0;
	virtual void setErrorTolAbs(Real errorTolAbs)=0;
	virtual void setErrorTolRel(Real errorTolRel)=0;
	virtual void compute() = 0;
	virtual void setFun(IRHSFunction* fun) = 0;
	virtual	std::vector<std::unique_ptr<ISolverData>>&& getSolution() = 0 ;

};

#endif /* IMASTERSOLVER_H_ */
