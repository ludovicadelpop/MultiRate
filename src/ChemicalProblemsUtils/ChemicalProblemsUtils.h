/*
 * ChelicalProblemsUtils.h
 *
 *  Created on: 10 d�c. 2015
 *      Author: delpopol
 */

#ifndef CHEMICALPROBLEMSUTILS_H_
#define CHEMICALPROBLEMSUTILS_H_

#include "StandardTypes.h"
#include "ChemicalSystemTools/ChemicalSystem.h"
#include "GeochemistryRHSFunction/GeochemistryParameters.h"
#include "ChemicalSystemTools/ChemicalSystemState.h"
#include "ChemicalSystemTools/ChemicalSourceRate.h"

using namespace Utils;

namespace ChemicalProblemsUtils {
	//! Returns the parameters that we need for the Geochemistry function
	GeochemistryParameters buildParameters(ChemicalSystem& system);
	//! Returns the parameters that we need for the Geochemistry function if it is present the source rate term
	GeochemistryParameters buildParameters(ChemicalSystem& system, ChemicalSourceRate& sourceRate);
	//! Builds the initial condition for the Geochemistry System ODE
	RealVector buildInitialCondition(ChemicalSystemState& systemState,StringVector& species);


};

#endif /* CHEMICALPROBLEMSUTILS_H_ */
