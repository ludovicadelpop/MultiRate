/*
 * FESolverUtils.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef FESOLVERUTILS_H_
#define FESOLVERUTILS_H_

#include "FESolverOutput.h"
#include "TraceMng.h"


//! Utility class to print the FESolver output
class FESolverUtils: public TraceMng{
public:
	FESolverUtils();
	virtual ~FESolverUtils();
	//! Prints some info of the time step solver
	void printInfo(FESolverOutput output);
};

#endif /* FESOLVERUTILS_H_ */
