/*
 * ChemicalSourceRate.cpp
 *
 *  Created on: 14 déc. 2015
 *      Author: delpopol
 */

#include "ChemicalSourceRate.h"

ChemicalSourceRate::ChemicalSourceRate() {}

ChemicalSourceRate::~ChemicalSourceRate() {}

void ChemicalSourceRate::setSourceRate(KeyReal sourceRate){
	this->SourceRate.push_back(sourceRate);
}

const std::vector<KeyReal >& ChemicalSourceRate::getSourceRate() const {
	return SourceRate;
}
