/*
 * GenerateGenericRestabFile.h
 *
 *  Created on: 16 déc. 2015
 *      Author: delpopol
 */

#ifndef GENERATEGENERICRESTABFILE_H_
#define GENERATEGENERICRESTABFILE_H_

#include "MasterSolverOutputManipulator/MasterSolution.h"
#include "Restab.h"

namespace GenerateGenericRestabFile {

/*!
 * Generates a restab file for a ODEs system where we have the solution of each components in function of the time.
 */
int GenericRestab(std::vector<MasterSolution>& vect_solution);

}

#endif /* GENERATEGENERICRESTABFILE_H_ */
