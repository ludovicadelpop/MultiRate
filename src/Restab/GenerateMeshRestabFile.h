/*
 * GenerateMeshRestabFile.h
 *
 *  Created on: 5 janv. 2016
 *      Author: delpopol
 */

#ifndef GENERATEMESHRESTABFILE_H_
#define GENERATEMESHRESTABFILE_H_

#include <iostream>
#include "Restab.h"
#include "ISolverData.h"
#include <memory>

namespace GenerateMeshRestabFile{



//!Generates a restab file where we have for each time step the components that are computed.
/*!
 * @param x0				initial point for PDE problem
 * @param Nx				number of points
 * @param xL				final point for PDe problem
 * @parram vect_solution	vector of class ISolverData that is the solution of the solver
*/
int MeshRestab(Real x0, Integer Nx, Real xL, std::vector<std::unique_ptr<ISolverData>>&& vect_solution);
int MeshRestab(std::vector<std::unique_ptr<ISolverData>>&& vect_solution);
}

#endif /* GENERATEMESHRESTABFILE_H_ */
