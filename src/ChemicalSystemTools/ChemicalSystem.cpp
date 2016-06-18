/*
 * ChemicalSystem.cpp
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#include "ChemicalSystem.h"

ChemicalSystem::ChemicalSystem() {}

ChemicalSystem::~ChemicalSystem() {}

const std::vector<ChemicalPhase>& ChemicalSystem::getPhase() const {
	return Phase;
}

const std::vector<ChemicalReaction>& ChemicalSystem::getReaction() const {
	return Reaction;
}

const std::vector<ChemicalSpecies>& ChemicalSystem::getSpecies() const {
	return Species;
}

void ChemicalSystem::addPhase(ChemicalPhase phase){
	this->Phase.push_back(phase);
}

void ChemicalSystem::addSpecies(ChemicalSpecies species){
	this->Species.push_back(species);
}

void ChemicalSystem::addReaction(ChemicalReaction reaction){
	this->Reaction.push_back(reaction);
}
