/*
 * GenerateDebugRestabFile.h
 *
 *  Created on: 6 janv. 2016
 *      Author: delpopol
 */

#ifndef GENERATEDEBUGRESTABFILE_H_
#define GENERATEDEBUGRESTABFILE_H_

#include <SingleRateBESolver/SingleRateBESolver.h>
#include <iostream>
#include "Restab.h"
#include "MultiRateTRBDF2Solver/MultiRateTRBDF2SolverData.h"

namespace GenerateDebugRestabFile{

//! Generates a restab file useful to debug because we have the solution in function of the space for each iteration
int DebugRestab(Real x0, Real Nx, Real xL,  std::vector<std::unique_ptr<ISolverData>>&& vect_solution);

}

#endif /* GENERATEDEBUGRESTABFILE_H_ */
