/*
 * BESolverUtils.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "BESolverUtils.h"


BESolverUtils::BESolverUtils() {}

BESolverUtils::~BESolverUtils() {}

void BESolverUtils::printInfo(BESolverOutput output){
	info()<< "y_final =  " ;
	std::cout<< output.getYFinal();
	std::cout<<std::endl;
}
