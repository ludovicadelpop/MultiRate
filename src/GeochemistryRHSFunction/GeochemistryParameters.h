/*
 * GeochemistryParameters.h
 *
 *  Created on: Dec 1, 2015
 *      Author: delpopol
 */

#ifndef GEOCHEMISTRYPARAMETERS_H_
#define GEOCHEMISTRYPARAMETERS_H_

#include "StandardTypes.h"
using namespace Utils;

//! Parameters necessary to build the Geochemistry RHS Function

class GeochemistryParameters {
public:
	GeochemistryParameters();
	virtual ~GeochemistryParameters();

	const RealVector& getKReaction() const;

	void setKReaction(const RealVector& reactions);

	const RealVector& getLogK() const;

	void setLogK(const RealVector& logK);

	const StringVector& getPhase() const;

	void setPhase(const StringVector& phase);

	const StringVector& getPhaseLaw() const;

	void setPhaseLaw(const StringVector& phaseLaw);

	const StringVector& getPhaseModel() const;

	void setPhaseModel(const StringVector& phaseModel);

	const StringVector& getReaction() const;

	void setReaction(const StringVector& reaction);

	const RealMatrixSparse& getMatrix() const;

	void setMatrix(const RealMatrixSparse& matrix);

	const StringVector& getSModel() const;

	void setSModel(const StringVector& model);

	const StringVector& getSpecies() const;

	void setSpecies(const StringVector& species);

	const StringVector& getSpeciesModel() const;

	void setSpeciesModel(const StringVector& speciesModel);

	const StringVector& getSpeciesPhase() const;

	void setSpeciesPhase(const StringVector& speciesPhase);

	const RealVector& getScostant() const;

	void setScostant(const RealVector& scostant);

private:
	StringVector Phase;         /*!< Phases present in the system  */
	StringVector PhaseModel;	/*!< Name of the phases present in the system */
	StringVector PhaseLaw;		/*!< Laws of the phases present in the system */
	StringVector Species;		/*!< Species present in the system */
	StringVector SpeciesPhase;	/*!< In which phase the species are in the system */
	StringVector SpeciesModel;	/*!< types species present in the system */
	StringVector SModel;		/*!< Model of the species */
	RealVector LogK;			/*!< Logarithmic values of the k parameters */
	StringVector Reaction;		/*!< Reactions present in the system  */
	RealVector KReaction;		/*!< kinetic values of the reactions  */
	RealMatrixSparse S_matrix;	/*!< Stechiometric matrix  */
	RealVector Scostant;		/*!< Source Rate vector */
};

#endif /* GEOCHEMISTRYPARAMETERS_H_ */
