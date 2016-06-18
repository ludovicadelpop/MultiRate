/*
 * InterpolationOutputSolver.h
 *
 *  Created on: Feb 17, 2016
 *      Author: delpopol
 */

#ifndef INTERPOLATIONOUTPUTSOLVER_H_
#define INTERPOLATIONOUTPUTSOLVER_H_

#include "StandardTypes.h"
using namespace Utils;


class InterpolationOutputSolver {
public:
	InterpolationOutputSolver();
	virtual ~InterpolationOutputSolver();
	const RealVector& getY1() const;

	void setY1(const RealVector& y1);

	const RealVector& getY2() const;

	void setY2(const RealVector& y2);
private:
	RealVector y1;	/*!< Solution at time t1 */
	RealVector y2;	/*!< Solution at time t2 */
};

#endif /* INTERPOLATIONOUTPUTSOLVER_H_ */
