/*
 * VectorUtility.h
 *
 *  Created on: 2 d�c. 2015
 *      Author: delpopol
 */

#ifndef VECTORUTILITY_H_
#define VECTORUTILITY_H_

#include "StandardTypes.h"
using namespace Utils;

namespace VectorUtility {
	/*!
	 * Takes two vector and returns a reduced vector with dimension equal to the number of
	 * no zero element in ref and value equal to y(i) in that positions.
	 */
	RealVector vectorReduce(RealVector& y,IntegerVector& ref);
	/*!
	 * Takes two vector and returns a vector with dimension equal to the number of
	 * components of the system. For the not-computed components it puts value equal to zero.
	 */
	RealVector vectorProlong(RealVector& y,IntegerVector& ref);

};

#endif /* VECTORUTILITY_H_ */
