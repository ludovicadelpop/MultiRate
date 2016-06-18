/*
 * ChemicalSystem.h
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#ifndef CHEMICALSYSTEM_H_
#define CHEMICALSYSTEM_H_

#include "ChemicalPhase.h"
#include "ChemicalSpecies.h"
#include "ChemicalReaction.h"


//! Class to store the system in the Geochemistry problem
class ChemicalSystem {
public:
	ChemicalSystem();
	virtual ~ChemicalSystem();

	const std::vector<ChemicalPhase>& getPhase() const;

	const std::vector<ChemicalReaction>& getReaction() const;

	const std::vector<ChemicalSpecies>& getSpecies() const;

	void addPhase(ChemicalPhase phase);

	void addSpecies(ChemicalSpecies species);

	void addReaction(ChemicalReaction reaction);


private:
	std::vector<ChemicalPhase> Phase;			/*!< Phases present in the system */
	std::vector<ChemicalSpecies> Species;		/*!< Species present in the system */
	std::vector<ChemicalReaction> Reaction;		/*!< Reactions present in the system */
};

#endif /* CHEMICALSYSTEM_H_ */
