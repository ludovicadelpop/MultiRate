/*
 * ChemicalSystemState.h
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#ifndef CHEMICALSYSTEMSTATE_H_
#define CHEMICALSYSTEMSTATE_H_


#include "StandardTypes.h"
using namespace Utils;

//! Class to store the initial state of the system in the Geochemistry problem
class ChemicalSystemState {
public:
	ChemicalSystemState();
	virtual ~ChemicalSystemState();

	void setAmountSpecies(KeyReal stateSpecies);

	const std::vector<KeyReal >& getStateSpecies() const;


private:
	std::vector<KeyReal> StateSpecies;	/*!< Vector of pair: name of species and initial value */
};

#endif /* CHEMICALSYSTEMSTATE_H_ */
