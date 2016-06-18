/*
 * ChelicalProblemsUtils.cpp
 *
 *  Created on: 10 d�c. 2015
 *      Author: delpopol
 */

#include "ChemicalProblemsUtils.h"


GeochemistryParameters ChemicalProblemsUtils::buildParameters(ChemicalSystem& system){

	GeochemistryParameters param;

	std::vector<ChemicalPhase> phase = system.getPhase();
	std::vector<ChemicalSpecies> species = system.getSpecies();
	std::vector<ChemicalReaction> reaction = system.getReaction();

	//=============Build vectors Phase

	Integer num_phase = phase.size();

	StringVector vector_phase(num_phase);
	StringVector vector_phaseModel(num_phase);
	StringVector vector_phaseLaw(num_phase);

	for(Integer i = 0; i < num_phase; ++i ){
		vector_phase[i] = phase[i].getPhase();
		vector_phaseModel[i] = phase[i].getPhaseModel();
		vector_phaseLaw[i] = phase[i].getLaw();
	}

	param.setPhase(vector_phase);
	param.setPhaseModel(vector_phaseModel);
	param.setPhaseLaw(vector_phaseLaw);

	//=============Build vectors Species

	Integer num_species = species.size();

	StringVector vector_species(num_species);
	StringVector vector_speciesPhase(num_species);
	StringVector vector_speciesModel(num_species);
	StringVector vector_sModel(num_species);
	RealVector vector_logk(num_species);

	for(Integer i = 0; i < num_species; ++i ){
		vector_species[i] = species[i].getSpecies();
		vector_speciesPhase[i] = species[i].getSpeciesPhase();
		vector_speciesModel[i] = species[i].getSpeciesModel();
		vector_sModel[i] = species[i].getSModel();
		vector_logk[i] = species[i].getLogk();
	}

	param.setSpecies(vector_species);
	param.setSpeciesPhase(vector_speciesPhase);
	param.setSpeciesModel(vector_speciesModel);
	param.setSModel(vector_sModel);
	param.setLogK(vector_logk);

	//=============Build Source Rate

	RealVector source(num_species);
	source.fill(0.0);

	param.setScostant(source);

	//=============Build vectors Reaction

	Integer num_reaction = reaction.size();

	StringVector vector_reaction(num_reaction);
	RealVector vector_kReaction(num_reaction);

	for(Integer i = 0; i< num_reaction; ++i){
		vector_reaction[i] = reaction[i].getNameReaction();
		vector_kReaction[i] = reaction[i].getKinValue();
	}

	param.setKReaction(vector_kReaction);
	param.setReaction(vector_reaction);

	//=============Build stechiometric  matrix

	RealMatrixSparse s_matrix(num_species,num_reaction);
	s_matrix.setZero();

	for(Integer i = 0; i < num_reaction; ++i){
		std::vector<KeyReal> tmp = reaction[i].getSpecies();
		Integer tmp_size = tmp.size();
		for(Integer j = 0; j < tmp_size; ++j){
			std::string tmp_string = tmp[j].first;

			for(Integer k = 0; k < num_species; ++k){
					std::string name_species = vector_species[k];
				if(tmp_string.compare(name_species) == 0)
					s_matrix.insert(k,i) = tmp[j].second;
			}
		}
	}

	param.setMatrix(s_matrix);

	return param;

}

GeochemistryParameters ChemicalProblemsUtils::buildParameters(ChemicalSystem& system, ChemicalSourceRate& sourceRate){
	GeochemistryParameters param;

	std::vector<ChemicalPhase> phase = system.getPhase();
	std::vector<ChemicalSpecies> species = system.getSpecies();
	std::vector<ChemicalReaction> reaction = system.getReaction();

	//=============Build vectors Phase

	Integer num_phase = phase.size();

	StringVector vector_phase(num_phase);
	StringVector vector_phaseModel(num_phase);
	StringVector vector_phaseLaw(num_phase);

	for(Integer i = 0; i < num_phase; ++i ){
		vector_phase[i] = phase[i].getPhase();
		vector_phaseModel[i] = phase[i].getPhaseModel();
		vector_phaseLaw[i] = phase[i].getLaw();
	}

	param.setPhase(vector_phase);
	param.setPhaseModel(vector_phaseModel);
	param.setPhaseLaw(vector_phaseLaw);

	//=============Build vectors Species

	Integer num_species = species.size();

	StringVector vector_species(num_species);
	StringVector vector_speciesPhase(num_species);
	StringVector vector_speciesModel(num_species);
	StringVector vector_sModel(num_species);
	RealVector vector_logk(num_species);

	for(Integer i = 0; i < num_species; ++i ){
		vector_species[i] = species[i].getSpecies();
		vector_speciesPhase[i] = species[i].getSpeciesPhase();
		vector_speciesModel[i] = species[i].getSpeciesModel();
		vector_sModel[i] = species[i].getSModel();
		vector_logk[i] = species[i].getLogk();
	}

	param.setSpecies(vector_species);
	param.setSpeciesPhase(vector_speciesPhase);
	param.setSpeciesModel(vector_speciesModel);
	param.setSModel(vector_sModel);
	param.setLogK(vector_logk);

	//=============Build Source Rate

	std::vector<KeyReal> vector_source = sourceRate.getSourceRate();
	Integer num_source = vector_source.size();

	if(num_source != num_species){
			std::cerr<<"different number of species";
		}
		RealVector source(num_species);

		for(Integer i = 0; i < num_species; ++i){
			std::string tmp_species = vector_species[i];
			for(Integer j = 0; j< num_source; ++j){
				if(tmp_species.compare(vector_source[j].first) == 0){
					source[i] = vector_source[j].second;
					break;
				}else{
					if(j == (num_species-1)){
						std::cerr<<"state missing";
					}
				}
			}

		param.setScostant(source);
		}

	//=============Build vectors Reaction

	Integer num_reaction = reaction.size();

	StringVector vector_reaction(num_reaction);
	RealVector vector_kReaction(num_reaction);

	for(Integer i = 0; i< num_reaction; ++i){
		vector_reaction[i] = reaction[i].getNameReaction();
		vector_kReaction[i] = reaction[i].getKinValue();
	}

	param.setKReaction(vector_kReaction);
	param.setReaction(vector_reaction);

	//=============Build stechiometric  matrix

	RealMatrixSparse s_matrix(num_species,num_reaction);
	s_matrix.setZero();

	for(Integer i = 0; i < num_reaction; ++i){
		std::vector<KeyReal> tmp = reaction[i].getSpecies();
		Integer tmp_size = tmp.size();
		for(Integer j = 0; j < tmp_size; ++j){
			String tmp_string = tmp[j].first;

			for(Integer k = 0; k < num_species; ++k){
					String name_species = vector_species[k];
				if(tmp_string.compare(name_species) == 0)
					s_matrix.insert(k,i) = tmp[j].second;
			}
		}
	}

	param.setMatrix(s_matrix);

	return param;

}

RealVector ChemicalProblemsUtils::buildInitialCondition(ChemicalSystemState& systemState,StringVector& species){

	std::vector<KeyReal> vector_state = systemState.getStateSpecies();

	Integer num_species = vector_state.size();

	if(num_species != species.size()){
		std::cerr<<"different number of species";
	}
	RealVector n_initial(num_species);

	for(Integer i = 0; i < species.size(); ++i){
		String tmp_species = species[i];
		for(Integer j = 0; j< num_species; ++j){
			if(tmp_species.compare(vector_state[j].first) == 0){
				n_initial[i] = vector_state[j].second;
				break;
			}else{
				if(j == (num_species-1)){
					std::cerr<<"state missing";
				}
			}
		}


	}
	return n_initial;
}

