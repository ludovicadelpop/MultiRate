/*
 * BESolverUtils.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef BESOLVERUTILS_H_
#define BESOLVERUTILS_H_

#include "BESolverOutput.h"
#include "TraceMng.h"


//! Utility class to print the output of the BESolver

class BESolverUtils: public TraceMng{
public:
	BESolverUtils();
	virtual ~BESolverUtils();

	//! Prints some info of the time step solver
	void printInfo(BESolverOutput output);
};

#endif /* BESOLVERUTILS_H_ */
