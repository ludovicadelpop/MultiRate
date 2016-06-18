/*
 * HyperbolicEquationRusanovFlux.h
 *
 *  Created on: 19/gen/2016
 *      Author: ludovicadelpopolo
 */

#ifndef HYPERBOLICEQUATIONRUSANOVFLUX_H_
#define HYPERBOLICEQUATIONRUSANOVFLUX_H_

#include "IRHSFunction.h"
#include "IBCFunction.h"
#include "IFluxFunction.h"

//! Class to solve the hyperbolic problem with the Rusanov numerical flux
class HyperbolicEquationRusanovFlux:  public IRHSFunction {
public:
	HyperbolicEquationRusanovFlux();
	virtual ~HyperbolicEquationRusanovFlux();

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
	Integer Nx;						 		 /*!< Numbers of space nodes */
	Real x0;								 /*!< Initial space node */
	Real xL;								 /*!< Final space node */
	IBCFunction *bc_func;			 		 /*!< Boundary Condition function */
	IFluxFunction *flux_func;		 		 /*!< Flux Function */

};

#endif /* HYPERBOLICEQUATIONRUSANOVFLUX_H_ */
