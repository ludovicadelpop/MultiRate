/*
 * CourantNumber.h
 *
 *  Created on: Feb 22, 2016
 *      Author: delpopol
 */

#ifndef COURANTNUMBER_H_
#define COURANTNUMBER_H_

#include "IFluxFunction.h"
#include "ISolverData.h"
#include "StandardTypes.h"
#include <memory>
using namespace Utils;
namespace CourantNumber {
//! Computes Courant number for any accepted solution.
/*!
 * @param vect_solution		solution vector
 * @param dx				size of space interval
 * @param f_flux			flux function
 * @param tol				tolerance
 */
std::vector<Real> compute(std::vector<std::unique_ptr<ISolverData>>&& vect_solution, Real dx, IFluxFunction& f_flux);
}

#endif /* COURANTNUMBER_H_ */
