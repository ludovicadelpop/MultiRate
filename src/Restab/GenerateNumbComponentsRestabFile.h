/*
 * GenerateNumbComponentsRestabFile.h
 *
 *  Created on: 22 déc. 2015
 *      Author: delpopol
 */

#ifndef GENERATENUMBCOMPONENTSRESTABFILE_H_
#define GENERATENUMBCOMPONENTSRESTABFILE_H_

#include <iostream>
#include "Restab.h"
#include "MultiRateTRBDF2Solver/MultiRateTRBDF2SolverData.h"
#include "ISolverData.h"
#include <memory>

namespace GenerateNumbComponentsRestabFile{

//! Generates a restab file where we have the number of components that are involved for each iteration.
int ComponentsRestab( std::vector<std::unique_ptr<ISolverData>>&& vect_solution);

}

#endif /* GENERATENUMBCOMPONENTSRESTABFILE_H_ */
