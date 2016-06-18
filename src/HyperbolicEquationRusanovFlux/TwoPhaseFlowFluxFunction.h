/*
 * TwoPhaseFlowFluxFunction.h
 *
 *  Created on: 6 janv. 2016
 *      Author: delpopol
 */

#ifndef TWOPHASEFLOWFLUXFUNCTION_H_
#define TWOPHASEFLOWFLUXFUNCTION_H_

#include "IFluxFunction.h"

//! Flux for the Hyperbolic PDE.
/*!
 * Bucklety-Leverett equation
 *
 */

class TwoPhaseFlowFluxFunction : public IFluxFunction {
public:
	TwoPhaseFlowFluxFunction();
	virtual ~TwoPhaseFlowFluxFunction();


	Real getA() const;
	void setA(Real a);
	//!Evaluates the flux function component by component, we can't put as input a vector.
	Real evalF(Real time, Real y_sol);
	Real evalFderivative(Real time, Real y_sol);

private:
	Real a;		 /*!< Coefficient */


};

#endif /* TWOPHASEFLOWFLUXFUNCTION_H_ */
