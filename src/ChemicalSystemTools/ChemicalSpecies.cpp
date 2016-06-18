/*
 * ChemicalSpecies.cpp
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#include "ChemicalSpecies.h"

ChemicalSpecies::ChemicalSpecies() {
	Logk = 0;
}

ChemicalSpecies::~ChemicalSpecies() {}

ChemicalSpecies::ChemicalSpecies(String species, String speciesPhase, String speciesModel, String sModel, Real logk){
	setChemicalSpecies(species,speciesPhase,speciesModel,sModel,logk);
}

void ChemicalSpecies::setChemicalSpecies(String species, String speciesPhase, String speciesModel, String sModel, Real logk){
	this->Species = species;
	this->SpeciesPhase = speciesPhase;
	this->SpeciesModel = speciesModel;
	this->SModel = sModel;
	this->Logk = logk;
}

Real ChemicalSpecies::getLogk() const {
	return Logk;
}

const String& ChemicalSpecies::getSModel() const {
	return SModel;
}

const String& ChemicalSpecies::getSpecies() const {
	return Species;
}

const String& ChemicalSpecies::getSpeciesModel() const {
	return SpeciesModel;
}

const String& ChemicalSpecies::getSpeciesPhase() const {
	return SpeciesPhase;
}


