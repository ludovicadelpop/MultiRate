/*
 * FixedJacobianNewtonSolver.h
 *
 *  Created on: Nov 9, 2015
 *      Author: delpopol
 */

#ifndef FIXEDJACOBIANNEWTONSOLVER_H_
#define FIXEDJACOBIANNEWTONSOLVER_H_

#include "INewtonFunction.h"
#include "INewtonSolver.h"
#include "TraceMng.h"

#include "StandardTypes.h"
using namespace Utils;

//! Derived class of INewtonSolver
class FixedJacobianNewtonSolver : public TraceMng, public INewtonSolver {
public:
	FixedJacobianNewtonSolver();
	virtual ~FixedJacobianNewtonSolver();

	//! Function to compute the solution with the inexact Newton method for non linear system the Jacobian is fixed.
	/*!
	 * Returns the solution by reference
	 */

	void compute(INewtonFunction& fun, RealMatrixSparse& J,RealVector& Y, const Real tol_rel,const Real tol_abs,
										Bool& diverge_Newton,const Integer MaxNewtonStep );

};

#endif /* FIXEDJACOBIANNEWTONSOLVER_H_ */
