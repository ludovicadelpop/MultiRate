/*
 * INewtonFunction.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef INEWTONFUNCTION_H_
#define INEWTONFUNCTION_H_

#include "StandardTypes.h"

using namespace Utils;

//! Base class for the Newton function
class INewtonFunction {
public:
	INewtonFunction(){}
	virtual ~INewtonFunction(){}

	virtual void evalFJ(RealVector& Y, RealVector& F, RealMatrixSparse& J) = 0;
	virtual void evalF(RealVector& Y, RealVector& F) = 0;

};

#endif /* INEWTONFUNCTION_H_ */
