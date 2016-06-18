/*
 * BasicNewtonSolver.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef BASICNEWTONSOLVER_H_
#define BASICNEWTONSOLVER_H_

#include "INewtonFunction.h"
#include "INewtonSolver.h"
#include "TraceMng.h"

 //! Derived class from INewtonSolver.
class BasicNewtonSolver : public TraceMng, public INewtonSolver{
public:

	BasicNewtonSolver() {}
	virtual ~BasicNewtonSolver() {}

	//! Computes the solution with the Newton method for non linear system.
	/*!
	 * Returns the solution by reference
	 */
	void compute(INewtonFunction& fun, RealMatrixSparse& J,RealVector& Y, const Real tol_rel,const Real tol_abs,
									Bool& diverge_Newton,const Integer MaxNewtonStep );

};


#endif /* BASICNEWTONSOLVER_H_ */
