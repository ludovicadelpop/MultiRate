/*
 * LinearFluxFunction.h
 *
 *  Created on: 5 janv. 2016
 *      Author: delpopol
 */

#ifndef LINEARFLUXFUNCTION_H_
#define LINEARFLUXFUNCTION_H_

#include "IFluxFunction.h"

//! Linear flux for the Hyperbolic PDE.
/*!
 * \f$ f(u) = a u(x,t) \f$
 */

class LinearFluxFunction: public IFluxFunction{
public:

	LinearFluxFunction();
	virtual ~LinearFluxFunction();

	Real getA() const;
	void setA(Real a);

	//!Evaluates the flux function component by component.
	Real evalF(Real time, Real y_sol);
	//! Evaluates the flux derivative function component by component.
	Real evalFderivative(Real time, Real y_sol);

private:
	Real a;       /*!< Coefficient */
};

#endif /* LINEARFLUXFUNCTION_H_ */
