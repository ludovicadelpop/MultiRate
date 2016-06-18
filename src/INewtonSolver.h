/*
 * INewtonSolver.h
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#ifndef INEWTONSOLVER_H_
#define INEWTONSOLVER_H_

#include "StandardTypes.h"
#include "INewtonFunction.h"
using namespace Utils;

//! Base class for the Newton solver
class INewtonSolver {
public:
	INewtonSolver(){}
	virtual ~INewtonSolver(){}
	//! Function to compute the solution with the Newton method for non linear system.
	/*!
	 * Returns the solution by reference
	 * @param  	INewtonfunction  		Newton function
	 * @param	RealMatrixSparse		Jacobian
	 * @param	RealVector				solution
	 * @param	Real 					relative tolerance
	 * @param   Real 					absolute tolerance
	 * @param   Bool					Newton diverge
	 * @param   Integer 				maximum number of Newton iteration
	 */
	virtual void compute(INewtonFunction& fun, RealMatrixSparse& J,RealVector& Y, const Real tol_rel,const Real tol_abs,
											Bool& diverge_Newton,const Integer MaxNewtonStep )=0;
};

#endif /* INEWTONSOLVER_H_ */
