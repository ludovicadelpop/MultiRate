/*
 * TRBDF2SolverNewtonFunction.h
 *
 *  Created on: Nov 12, 2015
 *      Author: delpopol
 */

#ifndef TRBDF2SOLVERNEWTONFUNCTION_H_
#define TRBDF2SOLVERNEWTONFUNCTION_H_

#include "IRHSFunction.h"
#include "INewtonFunction.h"

//! Derived class of INewtonFunction interface to solve the Newton system for the TR-BDF2 method
class TRBDF2SolverNewtonFunction: public INewtonFunction {
public:
	TRBDF2SolverNewtonFunction();
	virtual ~TRBDF2SolverNewtonFunction();

	void setDt(Real dt);
	void setFun(IRHSFunction* fun);
	void setYn(RealVector& ya);
	void setTnp(Real tnp);
	void setRef(IntegerVector& ref);
	void setD(Real d);


	//! Returns as references the evaluate of Newton function (F) and Newton Jacobian (J) for the vector Y.
	void evalFJ(RealVector& Y, RealVector& F, RealMatrixSparse& J);
	//! Returns as reference the evaluate of Newton function (F) for the vector Y.
	void evalF(RealVector& Y, RealVector& F);

private:
	IRHSFunction* fun;			/*!< RHS Function */
	RealVector ya;				/*!< Vector useful for the evaluation of the RHS function*/
	Real dt;					/*!< Size time step */
	Real tnp;					/*!< Time that we compute solution */
	IntegerVector ref;			/*!< Vector to know for which components we have to compute the solution*/
	Real d;						/*!< Parameters of the TR-BDF2 method*/
};

#endif /* TRBDF2SOLVERNEWTONFUNCTION_H_ */
