/*
 * BESolverInput.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef BESOLVERINPUT_H_
#define BESOLVERINPUT_H_

#include "StandardTypes.h"

using namespace Utils;


//! Input class for BESolver
class BESolverInput{
public:
	BESolverInput();
	virtual ~BESolverInput();
	//! Sets the input
	/*!
	 * @param t0					initial time
	 * @param dt					time step
	 * @param y0					initial solution
	 * @param Newton_tol_rel 		Newton relative tolerance
	 * @param Newton_tol_abs		Newton absolute tolerance
	 */
	void set(Real t0, Real dt, RealVector& y0, Real Newton_tol_rel, Real Newton_tol_abs);
	Real getDt() const;
	Real getT0() const;
	RealVector& getY0();
	Real getNewtonTolAbs() const;
	Real getNewtonTolRel() const;

private:
	Real t0;				/*!< Initial time  */
	Real dt;				/*!< Size of the time step */
	RealVector y0;			/*!< Previous solution */
	Real Newton_tol_rel;	/*!< Relative tolerance for the Newton solver */
	Real Newton_tol_abs;	/*!< Absolute tolerance for the Newton solver */
};

#endif /* BESOLVERINPUT_H_ */
