/*
 * FESolverUtils.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#include "FESolverUtils.h"


FESolverUtils::FESolverUtils() {}

FESolverUtils::~FESolverUtils() {}

void FESolverUtils::printInfo(FESolverOutput output){
	info()<< "y_final =  " ;
	std::cout<< output.getYFinal()<<std::endl;
}
