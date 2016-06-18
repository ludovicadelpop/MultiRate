/*
 * ChemicalSystemState.cpp
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#include "ChemicalSystemState.h"

ChemicalSystemState::ChemicalSystemState() {}

ChemicalSystemState::~ChemicalSystemState() {}

void ChemicalSystemState::setAmountSpecies(KeyReal stateSpecies){
	this->StateSpecies.push_back(stateSpecies);
}

const std::vector<KeyReal >& ChemicalSystemState::getStateSpecies() const {
	return StateSpecies;
}
