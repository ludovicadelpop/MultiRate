/*
 * IRHSFunction.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef IRHSFUNCTION_H_
#define IRHSFUNCTION_H_

#include "StandardTypes.h"

using namespace Utils;

//! Base class for the right-hand side function
class IRHSFunction {
public:
	IRHSFunction(){}
	virtual ~IRHSFunction(){}
	virtual RealVector evalF(Real time, RealVector& y)=0;
	virtual RealVector evalF(Real time, RealVector& y, IntegerVector& ref)=0;
	virtual RealMatrixSparse evaldFdY(Real time, RealVector& y)=0;
	virtual RealMatrixSparse evaldFdY(Real time, RealVector& y,IntegerVector& ref)=0;
};

#endif /* IRHSFUNCTION_H_ */
