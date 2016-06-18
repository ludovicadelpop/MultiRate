/*
 * IBCFunction.h
 *
 *  Created on: 4 janv. 2016
 *      Author: delpopol
 */

#ifndef IBCFUNCTION_H_
#define IBCFUNCTION_H_

#include "StandardTypes.h"

using namespace Utils;

//! Base class for the Dirichlet boundary condition of the Hyperbolic equation.
class IBCFunction {
public:
	IBCFunction(){}
	virtual ~IBCFunction(){}

	virtual Real getValue(Real time) = 0;

};



#endif /* IBCFUNCTION_H_ */
