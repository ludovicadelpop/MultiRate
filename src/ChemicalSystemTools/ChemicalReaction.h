/*
 * ChemicalReaction.h
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#ifndef CHEMICALREACTION_H_
#define CHEMICALREACTION_H_

#include "StandardTypes.h"
using namespace Utils;

//! Class to store the reactions in the Geochemistry problem
class ChemicalReaction {
public:
	ChemicalReaction();
	virtual ~ChemicalReaction();

	ChemicalReaction(String nameReaction,Real kinValue);

	void setChemicalReaction(String nameReaction,Real kinValue);

	void addSpecies(KeyReal species);

	const String& getNameReaction() const;

	Real getKinValue() const;

	const std::vector<KeyReal >& getSpecies() const;

private:
	String NameReaction;				/*!< Name of the reaction */
	std::vector<KeyReal> Species;		/*!< Species that are involved with the stochiometric value*/
	Real KinValue;						/*!< Reaction speed */
};

#endif /* CHEMICALREACTION_H_ */
