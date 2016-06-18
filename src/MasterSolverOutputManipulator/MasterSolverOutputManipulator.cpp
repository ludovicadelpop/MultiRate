/*
 * MasterSolverOutputManipulator.cpp
 *
 *  Created on: 15 déc. 2015
 *      Author: delpopol
 */

#include "MasterSolverOutputManipulator.h"

std::vector<MasterSolution> MasterSolverOutputManipulator::getOutputVectorRestab(std::vector<std::unique_ptr<ISolverData>>&& vector_output_mastersolver){
	std::vector<MasterSolution> vect_solution;
	MasterSolution solution;

	Integer output_size = vector_output_mastersolver.size();
	for( Integer i = 0; i < output_size; i++){
		Bool has_succeded = vector_output_mastersolver[i]->isHasSucceded();
		if ( has_succeded == true ){
			RealVector y = vector_output_mastersolver[i]->getY();
			Real t = vector_output_mastersolver[i]->getTime();
			solution.setY(y);
			solution.setT(t);
			vect_solution.emplace_back(solution);
		}
	}
	return vect_solution;
}


