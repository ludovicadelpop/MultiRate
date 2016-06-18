/*
 * CubicHermiteInterpolationSolver.h
 *
 *  Created on: Nov 23, 2015
 *      Author: delpopol
 */

#ifndef CUBICHERMITEINTERPOLATIONSOLVER_H_
#define CUBICHERMITEINTERPOLATIONSOLVER_H_

#include "InterpolationSolver/InterpolationOutputSolver.h"
#include "InterpolationSolver/InterpolationInputSolver.h"
#include "IInterpolationSolver.h"

#include "StandardTypes.h"
using namespace Utils;

//! Interpolator for the components that are not active.
/*!
 * We use a Cubic Hermite Interpolator for the TRBDF2 Multirate method.
 */

class CubicHermiteInterpolationSolver: public IInterpolationSolver {
public:
	CubicHermiteInterpolationSolver();
	virtual ~CubicHermiteInterpolationSolver();
	//! Compute method
	/*!
	 * As input is required the time t1 and t2 to do interpolation (TRBDF2 is a two step method) and the coefficient gamma
	 * In the input class we need the solution at a previous and next time where we want to do the interpolation
	 * We store the solution in the output class: for the active components the value is equal to zero.
	 */
	void compute(Real t1, Real t2, Real gm);

	void setInput(const InterpolationInputSolver& input);

	const InterpolationOutputSolver& getOutput() const;

	InterpolationInputSolver input;
	InterpolationOutputSolver output;
};

#endif /* CUBICHERMITEINTERPOLATIONSOLVER_H_ */
