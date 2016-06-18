/*
 * ChemicalReaction.cpp
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#include "ChemicalReaction.h"

ChemicalReaction::ChemicalReaction() {
	KinValue = 0.0;
}

ChemicalReaction::~ChemicalReaction() {}

ChemicalReaction::ChemicalReaction(String nameReaction,Real kinValue){
	setChemicalReaction(nameReaction,kinValue);
}

void ChemicalReaction::setChemicalReaction(String nameReaction,Real kinValue){
	this->NameReaction = nameReaction;
	this->KinValue = kinValue;
}

void ChemicalReaction::addSpecies(KeyReal species){
	this->Species.push_back(species);
}

const String& ChemicalReaction::getNameReaction() const {
	return NameReaction;
}

Real ChemicalReaction::getKinValue() const {
	return KinValue;
}

const std::vector<KeyReal >& ChemicalReaction::getSpecies() const {
	return Species;
}
