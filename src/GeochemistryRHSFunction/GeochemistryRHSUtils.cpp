/*
 * GeochemistryRHSUtils.cpp
 *
 *  Created on: 8 d�c. 2015
 *      Author: delpopol
 */

#include "GeochemistryRHSUtils.h"

RealVector GeochemistryRHSUtils::PhaseActivityModel(RealVector& n,const GeochemistryParameters& parameters){

	Integer num_species = parameters.getSpecies().size();

	RealVector activity_param(num_species);
	activity_param.fill(1.0);

	String Water = "H2O";
	String wat = "w";

	StringVector species = parameters.getSpecies();
	StringVector species_phase = parameters.getSpeciesPhase();


	Integer idx_wat = 0;
	for (Integer i = 0; i < num_species; ++i){
		String tmp = species[i];
		if( tmp.compare(Water) == 0){
			idx_wat = i;
			break;
		}
	}

	for(Integer i=0; i < num_species; ++i){

		String sp1 = species[i];

		//////////////////////////////
		/// H20 activity
		//////////////////////////////
		if (sp1.compare(Water) == 0 ){

			Real sum = 0.0;

			for(Integer j = 0; j < num_species; j++){

				String phs1 = species_phase[j];

				if(phs1.compare(wat) ==  0 )
					sum = sum +n[j];
			}
			activity_param[i] = n[i] /sum;
		}

		/////////////////////////////////////////
		/// activity for species in Water != H2O
		/////////////////////////////////////////

		else{
			String specie_phase = species_phase[i];
			if(specie_phase.compare(wat) == 0 )
				activity_param[i] = n[i]/(n[idx_wat]*18.0e-3);

			/////////////////////////////
			///activity for other species
			/////////////////////////////

			//vector initialized with 1
		}
	}
	return activity_param;
}

void GeochemistryRHSUtils::ReactionThermodynamics(RealVector& Omega_reac, RealVector& Omega_prod, RealVector& activity, const GeochemistryParameters& parameters){

	Integer num_species = parameters.getSpecies().size();
	Integer num_reactions = parameters.getKReaction().size();

	Omega_reac.resize(num_reactions);
	Omega_reac.fill(1.0);

	Omega_prod.resize(num_reactions);
	Omega_prod.fill(1.0);

	RealMatrixSparse S_matrix = parameters.getMatrix();

	for (Integer i = 0; i < num_reactions; ++i){
		for (Integer j = 0; j<num_species; ++j){

			Real S_value = S_matrix.coeff(j,i);

			if( S_value < 0  ){

				Real expn1 = parameters.getLogK()[j];
				Real base = activity[j]/(pow(10.0,expn1));
				Real expn2 = fabs(S_value);
				Omega_reac[i] *= (pow(base,expn2));
		    }else {
		    	if(S_value > 0){
		    		Real expn1 = parameters.getLogK()[j];
		    		Real base = activity[j]/(pow(10.0,expn1));
					Real expn2 = fabs(S_value);
					Omega_prod[i] *= (pow(base,expn2));
				}

			}
		}
	}


}

void GeochemistryRHSUtils::ReactiveChemistryPb(RealVector& R, RealVector& reac,const GeochemistryParameters& parameters){

	Integer num_species = parameters.getSpecies().size();
	Integer num_reactions = parameters.getKReaction().size();

	RealMatrixSparse S_matrix = parameters.getMatrix();

	for( Integer i = 0; i < num_species; i++){
		for( Integer j = 0; j < num_reactions; j++){

			R[i] += S_matrix.coeff(i,j)*reac[j];

		}
	}

}
