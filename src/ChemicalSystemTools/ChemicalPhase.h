/*
 * ChemicalPhase.h
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#ifndef CHEMICALPHASE_H_
#define CHEMICALPHASE_H_

#include "StandardTypes.h"
using namespace Utils;

//! Class to store the phases in the Geochemistry problem
class ChemicalPhase {
public:
	ChemicalPhase();
	virtual ~ChemicalPhase();

	ChemicalPhase(String phase,String phaseModel,String law);

	void setChemicalPhase(String phase,String phaseModel,String law);

	const String& getLaw() const;

	const String& getPhase() const;

	const String& getPhaseModel() const;
private:
	String Phase;       /*!< Symbol of the phase */
	String PhaseModel;	/*!< Name of the phase*/
	String Law;			/*!< Law's name utilized to modeling the phase */

};

#endif /* CHEMICALPHASE_H_ */
