/*
 * ConstantBCFunction.h
 *
 *  Created on: 4 janv. 2016
 *      Author: delpopol
 */

#ifndef CONSTANTBCFUNCTION_H_
#define CONSTANTBCFUNCTION_H_

#include "IBCFunction.h"

//! Class to store the Dirichlet boundary condition for the Hyperbolic PDE.
/*!
 * In this class we have a constant function.
 */
class ConstantBCFunction: public IBCFunction{
public:
	ConstantBCFunction();
	virtual ~ConstantBCFunction();

	Real getValue(Real time);
	void setValue(Real BCvalue);

private:
	Real value;  /*!< Constant value of the boundary condition  */
};

#endif /* CONSTANTBCFUNCTION_H_ */
