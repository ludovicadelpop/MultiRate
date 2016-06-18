/*
 * IsConservativeMethod.h
 *
 *  Created on: 23 déc. 2015
 *      Author: delpopol
 */

#ifndef ISCONSERVATIVEMETHOD_H_
#define ISCONSERVATIVEMETHOD_H_

#include "ISolverData.h"
#include "IFluxFunction.h"
#include <vector>
#include <memory>


namespace IsConservativeMethod{
//! Checks if the method is mass conservative.
/*!
 * @param vect_solution		solution vector
 * @param dx				size of space interval
 * @param f_flux			flux function
 * @param tol				tolerance
 */
Bool check(std::vector<std::unique_ptr<ISolverData>>&& vect_solution, Real dx, IFluxFunction& f_flux, Real tol);
}



#endif /* ISCONSERVATIVEMETHOD_H_ */
