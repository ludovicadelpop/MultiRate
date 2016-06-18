/*
 * ChemicalPhase.cpp
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#include "ChemicalPhase.h"

ChemicalPhase::ChemicalPhase() {}

ChemicalPhase::~ChemicalPhase() {}

ChemicalPhase::ChemicalPhase(String phase,String phaseModel,String law){
	setChemicalPhase(phase,phaseModel,law);
}

void ChemicalPhase::setChemicalPhase(String phase,String phaseModel, String law){
	this->Phase = phase;
	this->PhaseModel = phaseModel;
	this->Law = law;
}


const String& ChemicalPhase::getLaw() const {
	return Law;
}

const String& ChemicalPhase::getPhase() const {
	return Phase;
}

const String& ChemicalPhase::getPhaseModel() const {
	return PhaseModel;
}


