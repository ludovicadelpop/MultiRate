/*
 * CourantNumber.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: delpopol
 */

#include "CourantNumber.h"

std::vector<Real> CourantNumber::compute(std::vector<std::unique_ptr<ISolverData>>&& vect_solution, Real dx, IFluxFunction& f_flux){

	std::vector<Real> Cour_numb;
	unsigned int size_sol = vect_solution.size();
	Cour_numb.resize(size_sol);


	RealVector y_sol = vect_solution[0]->getY();
	Integer y_size = y_sol.size();
	Real time;
	Real f_first = 0.0;

	for(Integer i=1; i<size_sol;i++){
		y_sol = vect_solution[i]->getY();
		time = vect_solution[i]->getTime();
		for (Integer j=0; j<y_size; j++){
			Real y_i = y_sol[j];
			f_first = std::max(f_first,fabs(f_flux.evalFderivative(time, y_i)));
		}
	Real dt = vect_solution[i]->getH();
	Cour_numb[i] = f_first*(dt)/dx;
	}

	return Cour_numb;
}

