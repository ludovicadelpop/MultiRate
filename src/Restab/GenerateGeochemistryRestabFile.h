/*
 * GenerateGeochemistryRestabFile.h
 *
 *  Created on: 15 déc. 2015
 *      Author: delpopol
 */

#ifndef GENERATEGEOCHEMISTRYRESTABFILE_H_
#define GENERATEGEOCHEMISTRYRESTABFILE_H_

#include <iostream>
#include "Restab.h"
#include "GeochemistryRHSFunction/GeochemistryParameters.h"
#include "MasterSolverOutputManipulator/MasterSolution.h"

namespace GenerateGeochemistryRestabFile{
/*!
 * Generates a restab file where we have the evolution in time of the solution for each species.
 */
int GeochemistryRestab(GeochemistryParameters& param, std::vector<MasterSolution>& vect_solution);

}


#endif /* GENERATEGEOCHEMISTRYRESTABFILE_H_ */
