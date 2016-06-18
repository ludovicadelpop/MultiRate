/*
 * IsConservativeMethod.cpp
 *
 *  Created on: 23 déc. 2015
 *      Author: delpopol
 */

#include "IsConservativeMethod.h"

Bool IsConservativeMethod::check(std::vector<std::unique_ptr<ISolverData>>&& vect_solution, Real dx, IFluxFunction& f_flux, Real tol){

	Bool isConservative = true;

	RealVector y0 = vect_solution[0]->getY();
	Real sum_value = y0.sum();
	Integer num_iteration =  vect_solution.size();

	for(Integer i=1; i <num_iteration; ++i){
		Bool has_succ = vect_solution[i]->isHasSucceded();
		Bool ref = vect_solution[i]->isRefining();

		// we check the conservation only f the time step is accepted and it has not to refine.
		if(has_succ == true && ref == false){

			RealVector yi = vect_solution[i]->getY();
			Real dt =  vect_solution[i]->getH();
			Real t = vect_solution[i]->getTime();

			Real tmp_value = yi.sum();

			Real yi_0 = yi[0];
			Real f_u0 = f_flux.evalF(t,yi_0);
			Real yi_N = yi[yi.size()-1];
			Real f_uN = f_flux.evalF(t,yi_N);

			Real value = fabs(tmp_value - sum_value - (f_u0 - f_uN)*dt/(dx));
			std::cout<<"value "<<value<<std::endl;

			if (value > tol ){
				std::cout<<"sum time n+1 "<<tmp_value<<std::endl;
				std::cout<<"sum time n "<<sum_value<<std::endl;
				isConservative = false;
				std::cout<<"is conservative "<<isConservative<<" iter "<<i<<std::endl;
				break;
			}
			std::cout<<"is conservative "<<isConservative<<" iter "<<i<<std::endl;
			std::cout<<std::endl;
			sum_value = tmp_value;
		}
	}
	return isConservative;
}




