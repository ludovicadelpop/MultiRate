/*
 * GeochemistryRHSUtils.h
 *
 *  Created on: 8 d�c. 2015
 *      Author: delpopol
 */

#ifndef GEOCHEMISTRYRHSUTILS_H_
#define GEOCHEMISTRYRHSUTILS_H_

#include "GeochemistryParameters.h"

//!  Functions to use inside the method evalF for the Geochemistry RHS.

namespace GeochemistryRHSUtils{
//! Builds the activity parameter
RealVector PhaseActivityModel(RealVector& n,const GeochemistryParameters& parameters);
//! Builds the two vector: \Omega_{reac} and \Omega_{prod}.
void ReactionThermodynamics(RealVector& Omega_reac, RealVector& Omega_prod, RealVector& activity, const GeochemistryParameters& parameters);
//! Builds the RHS vector for the geochemistry problem
void ReactiveChemistryPb(RealVector& R, RealVector& reac,const GeochemistryParameters& parameters);
}

#endif /* GEOCHEMISTRYRHSUTILS_H_ */
