/*
 * GeochemistryRHSFunction.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: delpopol
 */

#include "GeochemistryRHSFunction.h"
#include "GeochemistryRHSUtils.h"


GeochemistryRHSFunction::GeochemistryRHSFunction() {}

GeochemistryRHSFunction::~GeochemistryRHSFunction() {}

const GeochemistryParameters& GeochemistryRHSFunction::getParameters() const {
	return parameters;
}

void GeochemistryRHSFunction::setParameters(const GeochemistryParameters& parameters) {
	this->parameters = parameters;
}

RealVector GeochemistryRHSFunction::evalF(Real time, RealVector& y){

	RealVector n = y;

	/////////////////////////
	/// ACTIVITY PARAMETER
	/////////////////////////


	RealVector activity_param = GeochemistryRHSUtils::PhaseActivityModel(n,parameters);


	///////////////////////////////////
	/// Reaction Thermodynamics
	///////////////////////////////////

	RealVector Omega_reac;
	RealVector Omega_prod;

	GeochemistryRHSUtils::ReactionThermodynamics(Omega_reac,Omega_prod,activity_param,parameters);

	//////////////////////////////////////
	///Kinetic Reaction
	/////////////////////////////////////

	Integer num_reactions = parameters.getKReaction().size();
	RealVector reac(num_reactions);

	RealVector KinRate = parameters.getKReaction();

	RealVector diff = Omega_reac - Omega_prod;
	reac = KinRate.cwiseProduct(diff);

    /////////////////////////////////////////
	/// Reactive Chemistry Problem
	////////////////////////////////////////

	RealVector R(n.size());
	R.fill(0.0);
	GeochemistryRHSUtils::ReactiveChemistryPb(R, reac, parameters);

	RealVector Scostant = parameters.getScostant();
	R += Scostant;

	RealVector f = R;
	return f;

}


RealVector GeochemistryRHSFunction::evalF(Real time, RealVector& y, IntegerVector& ref){
	RealVector n = y;

	/////////////////////////
	/// ACTIVITY PARAMETER
	////////////////////////


	RealVector activity_param = GeochemistryRHSUtils::PhaseActivityModel(n,parameters);


	///////////////////////////////////
	/// Reaction Thermodynamics
	//////////////////////////////////

	RealVector Omega_reac;
	RealVector Omega_prod;

	GeochemistryRHSUtils::ReactionThermodynamics(Omega_reac,Omega_prod,activity_param,parameters);

	//////////////////////////////////////
	///Kinetic Reaction
	/////////////////////////////////////

	Integer num_reactions = parameters.getKReaction().size();
	RealVector reac(num_reactions);

	RealVector KinRate = parameters.getKReaction();

	RealVector diff = Omega_reac - Omega_prod;
	reac = KinRate.cwiseProduct(diff);

    /////////////////////////////////////////
	/// Reactive Chemistry Problem
	////////////////////////////////////////

	RealVector R(n.size());
	R.fill(0.0);
	GeochemistryRHSUtils::ReactiveChemistryPb(R, reac, parameters);

	RealVector Scostant = parameters.getScostant();

	R += Scostant;

	Integer num_species = parameters.getSpecies().size();
	Integer elem_ref = ref.sum();
	RealVector f(elem_ref);
	f.fill(0.0);
	Integer idx = 0;

	for( Integer i = 0; i < num_species; i++){
		if(ref[i]==1){
			f[idx] = R[i];
			idx = idx+1;
		}
	}
	return f;
}

RealMatrixSparse GeochemistryRHSFunction::evaldFdY(Real time, RealVector& y){
	///
	/// this is not the exact Jacobian!
	///
	Integer y_size = y.size();
	RealMatrixSparse J(y_size,y_size);
	J.setZero();

	Integer col = 0;
	Real epsi = 1.0e-5;
	Real iepsi = 1.0 / epsi;
	RealVector F = evalF(time,y);

	for (Integer j = 0; j < y_size; ++j){

		RealVector yd = y;
		yd(j) = yd(j) + epsi;

		RealVector Fd = evalF(time,yd);
		for(Integer i=0; i< Fd.size(); i++){
			J.insert(i,col) = (Fd[i] - F[i]) * iepsi;
		}
		col += 1;
	}

	return J;
}


RealMatrixSparse GeochemistryRHSFunction::evaldFdY(Real time, RealVector& y, IntegerVector& ref){
	///
	/// this is not the exact Jacobian!
	///
		Integer y_size = y.size();
		Integer elem_ref = ref.sum();
		RealMatrixSparse J(elem_ref,elem_ref);
		J.setZero();

		Integer col = 0;
		Real epsi = 1.0e-5;
		Real iepsi = 1.0 / epsi;
		RealVector F = evalF(time,y,ref);
		RealVector Ftot = evalF(time,y) ;
		for (Integer j = 0; j < y_size; ++j){
			if(ref(j) == 1){
				RealVector yd = y;
				yd(j) = yd(j) + epsi;

				RealVector Fd = evalF(time,yd,ref);

				for(Integer i=0; i< Fd.size(); i++){
						J.insert(i,col) = (Fd[i] - F[i]) * iepsi;
				}
				col = col + 1;
			}
		}

		return J;
}
