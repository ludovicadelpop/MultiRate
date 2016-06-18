/*
 * GeochemistryParameters.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: delpopol
 */

#include "GeochemistryParameters.h"

GeochemistryParameters::GeochemistryParameters() {}

GeochemistryParameters::~GeochemistryParameters() {}

const RealVector& GeochemistryParameters::getKReaction() const {
	return KReaction;
}

void GeochemistryParameters::setKReaction(const RealVector& reaction) {
	KReaction = reaction;
}

const RealVector& GeochemistryParameters::getLogK() const {
	return LogK;
}

void GeochemistryParameters::setLogK(const RealVector& logK) {
	LogK = logK;
}

const StringVector& GeochemistryParameters::getPhase() const {
	return Phase;
}

void GeochemistryParameters::setPhase(const StringVector& phase) {
	Phase = phase;
}

const StringVector& GeochemistryParameters::getPhaseLaw() const {
	return PhaseLaw;
}

void GeochemistryParameters::setPhaseLaw(const StringVector& phaseLaw) {
	PhaseLaw = phaseLaw;
}

const StringVector& GeochemistryParameters::getPhaseModel() const {
	return PhaseModel;
}

void GeochemistryParameters::setPhaseModel(const StringVector& phaseModel) {
	PhaseModel = phaseModel;
}

const StringVector& GeochemistryParameters::getReaction() const {
	return Reaction;
}

void GeochemistryParameters::setReaction(const StringVector& reaction) {
	Reaction = reaction;
}

const RealMatrixSparse& GeochemistryParameters::getMatrix() const {
	return S_matrix;
}

void GeochemistryParameters::setMatrix(const RealMatrixSparse& matrix) {
	S_matrix = matrix;
}

const StringVector& GeochemistryParameters::getSModel() const {
	return SModel;
}

void GeochemistryParameters::setSModel(const StringVector& model) {
	SModel = model;
}

const StringVector& GeochemistryParameters::getSpecies() const {
	return Species;
}

void GeochemistryParameters::setSpecies(const StringVector& species) {
	Species = species;
}

const StringVector& GeochemistryParameters::getSpeciesModel() const {
	return SpeciesModel;
}

void GeochemistryParameters::setSpeciesModel(const StringVector& speciesModel) {
	SpeciesModel = speciesModel;
}

const StringVector& GeochemistryParameters::getSpeciesPhase() const {
	return SpeciesPhase;
}

void GeochemistryParameters::setSpeciesPhase(const StringVector& speciesPhase) {
	SpeciesPhase = speciesPhase;
}

const RealVector& GeochemistryParameters::getScostant() const {
	return Scostant;
}

void GeochemistryParameters::setScostant(const RealVector& scostant) {
	Scostant = scostant;
}
