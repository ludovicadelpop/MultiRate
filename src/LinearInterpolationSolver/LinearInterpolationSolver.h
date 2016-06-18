/*
 * LinearInterpolationSolver.h
 *
 *  Created on: Feb 17, 2016
 *      Author: delpopol
 */

#ifndef LINEARINTERPOLATIONSOLVER_H_
#define LINEARINTERPOLATIONSOLVER_H_

#include "InterpolationSolver/InterpolationOutputSolver.h"
#include "InterpolationSolver/InterpolationInputSolver.h"
#include "IInterpolationSolver.h"

#include "StandardTypes.h"
using namespace Utils;

class LinearInterpolationSolver:  public IInterpolationSolver {
public:
	LinearInterpolationSolver();
	virtual ~LinearInterpolationSolver();
	void compute(Real t1, Real t2, Real gm);

	void setInput(const InterpolationInputSolver& input);

	const InterpolationOutputSolver& getOutput() const;

	InterpolationInputSolver input;
	InterpolationOutputSolver output;
};

#endif /* LINEARINTERPOLATIONSOLVER_H_ */
