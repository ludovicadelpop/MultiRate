/*
 * HyperbolicEquationUpwindRHSFunction.h
 *
 *  Created on: 22 déc. 2015
 *      Author: delpopol
 */

#ifndef HYPERBOLICEQUATIONUPWINDRHSFUNCTION_H_
#define HYPERBOLICEQUATIONUPWINDRHSFUNCTION_H_

#include "IRHSFunction.h"
#include "IBCFunction.h"
#include "IFluxFunction.h"

//! Class to describe a Hyperbolic PDE, we use upwind volume finite for the space discretization.

class HyperbolicEquationUpwindRHSFunction: public IRHSFunction {
public:
	HyperbolicEquationUpwindRHSFunction();
	virtual ~HyperbolicEquationUpwindRHSFunction();

	Integer getNx() const;
	void setNx(Integer nx);
	Real getX0() const;
	void setX0(Real x0);
	Real getXL() const;
	void setXL(Real l);
	void setBcFunc(IBCFunction* bcFunc);
	void setFluxFunc(IFluxFunction* fl_func);

	//! Returns a vector that it is the RHS evaluated at a certain time and solution.
	RealVector evalF(Real time, RealVector& y);
	//! Returns a vector that it is the RHS evaluated at a certain time and solution only for the active components.
	RealVector evalF(Real time, RealVector& y, IntegerVector& ref);
	//! Returns the Jacobian matrix at a certain time and solution.
	/*! It can be the analytical one or compute with finite difference,
	* it depends by the implementation.
	*/
	RealMatrixSparse evaldFdY(Real time, RealVector& y);
	//! Returns the Jacobian matrix at a certain time and solution only for the active components.
	/*! It can be the analytical one or compute with finite difference,
	 * it depends by the implementation.
	 */
	RealMatrixSparse evaldFdY(Real time, RealVector& y,IntegerVector& ref);



private:
	Integer Nx;						 /*!< Numbers of space nodes */
	Real x0;						 /*!< Initial space node */
	Real xL;						 /*!< Final space node */
	IBCFunction *bc_func;			 /*!< Boundary Condition function */
	IFluxFunction *flux_func;		 /*!< Flux Function */
};

#endif /* HYPERBOLICEQUATIONUPWINDRHSFUNCTION_H_ */
