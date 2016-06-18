/*
 * GeneratePDERestabFile.h
 *
 *  Created on: 22 déc. 2015
 *      Author: delpopol
 */

#ifndef GENERATEPDERESTABFILE_H_
#define GENERATEPDERESTABFILE_H_

#include <iostream>
#include "Restab.h"
#include "MasterSolverOutputManipulator/MasterSolution.h"

//! Generates a restab file for PDE

namespace GeneratePDERestabFile{
/*!
 * in the x-axis we have the space uniform grid
 * in the y-axis we have the solution for a fixed time: the initial and the final.
 */
int PDERestab(Real x0, Real Nx, Real xL,  std::vector<MasterSolution>& vect_solution);

}



#endif /* SRC_RESTAB_GENERATEPDERESTABFILE_H_ */
