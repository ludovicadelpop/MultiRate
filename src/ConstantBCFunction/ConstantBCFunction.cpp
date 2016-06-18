/*
 * ConstantBCFunction.cpp
 *
 *  Created on: 4 janv. 2016
 *      Author: delpopol
 */

#include "ConstantBCFunction.h"

ConstantBCFunction::ConstantBCFunction() {
	value = 0;
}

ConstantBCFunction::~ConstantBCFunction() {}

Real ConstantBCFunction::getValue(Real time){
	return value;
}
void ConstantBCFunction::setValue(Real BCvalue){
	value = BCvalue;
}
