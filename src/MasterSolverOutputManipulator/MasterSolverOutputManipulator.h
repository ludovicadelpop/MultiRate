/*
 * MasterSolverOutputManipulator.h
 *
 *  Created on: 15 déc. 2015
 *      Author: delpopol
 */

#ifndef MASTERSOLVEROUTPUTMANIPULATOR_H_
#define MASTERSOLVEROUTPUTMANIPULATOR_H_

#include <SingleRateBESolver/SingleRateBESolver.h>
#include "SingleRateTRBDF2Solver/SingleRateTRBDF2SolverData.h"
#include "MultiRateTRBDF2Solver/MultiRateTRBDF2SolverData.h"
#include "MasterSolution.h"

#include "StandardTypes.h"
using namespace Utils;


namespace MasterSolverOutputManipulator{

//! Function that transform a vector of SolverData into MasterSolution vector.
//! Inside there are only the successful time steps.

std::vector<MasterSolution> getOutputVectorRestab(std::vector<std::unique_ptr<ISolverData>>&& vector_output_mastersolver);

}



#endif /* MASTERSOLVEROUTPUTMANIPULATOR_H_ */
