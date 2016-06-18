/*
 * BESolverNewtonFunction.h
 *
 *  Created on: Nov 6, 2015
 *      Author: delpopol
 */

#ifndef _BESOLVERNEWTONFUNCTION_H_
#define _BESOLVERNEWTONFUNCTION_H_

#include "IRHSFunction.h"
#include "INewtonFunction.h"

//! Newton Function for BESolver
/*!
 * \f$
 * F(y) = y - y_{n} - dt*(f_{RHS}(t_{n+1},y))
 * \f$
 */
class BESolverNewtonFunction : public INewtonFunction{
public:
	BESolverNewtonFunction();
	virtual ~BESolverNewtonFunction();

	void setDt(Real dt);
	void setFun(IRHSFunction* fun);
	void setYn(const RealVector& yn);
	void setTnp(Real tnp);

	//! Returns as references the evaluate of Newton function (F) and Newton Jacobian (J) in Y.
	void evalFJ(RealVector& Y, RealVector& F, RealMatrixSparse& J);
	//! Returns as reference the evaluate of Newton function (F) in Y.
	void evalF(RealVector& Y, RealVector& F);

private:
	IRHSFunction* fun;		/*!< RHS Function */
	RealVector yn;			/*!< Vector of the solution at the previous time */
	Real dt;				/*!< Size time step */
	Real tnp;				/*!< Time where we compute the solution */
};

#endif /*_BESOLVERNEWTONFUNCTION_H_ */
