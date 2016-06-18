/*
 * IInterpolationSolver.h
 *
 *  Created on: Feb 17, 2016
 *      Author: pacs_student
 */

#ifndef IINTERPOLATIONSOLVER_H_
#define IINTERPOLATIONSOLVER_H_

#include "InterpolationSolver/InterpolationInputSolver.h"
#include "InterpolationSolver/InterpolationOutputSolver.h"


#include "StandardTypes.h"

using namespace Utils;

//! Base class for the interpolator
class IInterpolationSolver {
public:
	IInterpolationSolver() {}
	virtual ~IInterpolationSolver() {}

	virtual void compute(Real t1, Real t2, Real gm) = 0;
	virtual void setInput(const InterpolationInputSolver& input) = 0;
	virtual const InterpolationOutputSolver& getOutput() const = 0;

};




#endif /* IINTERPOLATIONSOLVER_H_ */
