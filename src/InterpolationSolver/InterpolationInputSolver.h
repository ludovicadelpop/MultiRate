/*
 * InterpolationInputSolver.h
 *
 *  Created on: Feb 17, 2016
 *      Author: delpopol
 */

#ifndef INTERPOLATIONINPUTSOLVER_H_
#define INTERPOLATIONINPUTSOLVER_H_

#include "StandardTypes.h"
using namespace Utils;

class InterpolationInputSolver {
public:
	InterpolationInputSolver();
	virtual ~InterpolationInputSolver();
	void setRef(const IntegerVector& ref);

	void setT0Int(const RealVector& t0Int);

	void setT1Int(const RealVector& t1Int);

	void setT2Int(const RealVector& t2Int);

	void setY0Int(const RealVector& y0Int);

	void setY1Int(const RealVector& y1Int);

	void setY2Int(const RealVector& y2Int);

	void setZ0Int(const RealVector& z0Int);

	void setZ1Int(const RealVector& z1Int);

	void setZ2Int(const RealVector& z2Int);

	const IntegerVector& getRef() const;

	const RealVector& getT0Int() const;

	const RealVector& getT1Int() const;

	const RealVector& getT2Int() const;

	const RealVector& getY0Int() const;

	const RealVector& getY1Int() const;

	const RealVector& getY2Int() const;

	const RealVector& getZ0Int() const;

	const RealVector& getZ1Int() const;

	const RealVector& getZ2Int() const;

private:
	IntegerVector ref;  /*!< Vector with 1 for the active components and 0 for the others */
	RealVector y0_int;	/*!< Solution vector at time t0 */
	RealVector y1_int;	/*!< Solution vector at time t1 */
	RealVector y2_int;	/*!< Solution vector at time t2 */
	RealVector z0_int;	/*!< Approximations of hy0' (h:size of the time step) at time t0 */
	RealVector z1_int;	/*!< Approximations of hy1' (h:size of the time step) at time t1 */
	RealVector z2_int;	/*!< Approximations of hy2' (h:size of the time step) at time t2 */
	RealVector t0_int;	/*!< Time t0 */
	RealVector t1_int;	/*!< Time t1 */
	RealVector t2_int;	/*!< Time t2 */
};

#endif /* INTERPOLATIONINPUTSOLVER_H_ */
