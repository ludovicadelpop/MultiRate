/*
 * ChemicalSpecies.h
 *
 *  Created on: 9 d�c. 2015
 *      Author: delpopol
 */

#ifndef CHEMICALSPECIES_H_
#define CHEMICALSPECIES_H_

#include "StandardTypes.h"
using namespace Utils;

//! Class to store the species in the Geochemistry problem
class ChemicalSpecies {
public:
	ChemicalSpecies();

	ChemicalSpecies(String species, String speciesPhase, String speciesModel, String sModel, Real logk);

	virtual ~ChemicalSpecies();

	void setChemicalSpecies(String species, String speciesPhase, String speciesModel, String sModel, Real logk);

	Real getLogk() const;

	const String& getSModel() const;

	const String& getSpecies() const;

	const String& getSpeciesModel() const;

	const String& getSpeciesPhase() const;

private:
	String Species;			/*!< Species name */
	String SpeciesPhase;	/*!< In which phase it is present */
	String SpeciesModel;	/*!< Type species */
	String SModel;			/*!< Species model */
	Real Logk;				/*!< Logarithmic value of the k coefficient  */
};

#endif /* CHEMICALSYSTEMTOOLS_CHEMICALSPECIES_H_ */
