/*
 * ISolverData.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef ISOLVERDATA_H_
#define ISOLVERDATA_H_

#include "StandardTypes.h"
using namespace Utils;

class ISolverData {
public:
	ISolverData(){}
	virtual ~ISolverData(){}

	virtual const RealVector& getError() const = 0;

	virtual void setError(const RealVector& error) = 0;

	virtual Real getH() const = 0;

	virtual void setH(Real h) = 0;

	virtual Bool isHasSucceded() const = 0;

	virtual void setHasSucceded(Bool hasSucceded) = 0;

	virtual Real getTime() const = 0;

	virtual void setTime(Real time) = 0;

	virtual const RealVector& getY() const = 0;

	virtual void setY(const RealVector& y) = 0;

	virtual const IntegerVector& getMesh() const = 0;

	virtual void setMesh(const IntegerVector& mesh) = 0;

	virtual Bool isRefining() const = 0;

	virtual void setRefining(Bool refining) = 0;

	virtual const IntegerVector& getNumbComponentsSolve() const = 0;

	virtual void setNumbComponentsSolve(const IntegerVector& numbComponentsSolve) = 0;

};

#endif /* ISOLVERDATA_H_ */
