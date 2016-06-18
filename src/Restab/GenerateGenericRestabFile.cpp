/*
 * GenarateGenericRestabFile.cpp
 *
 *  Created on: 16 déc. 2015
 *      Author: delpopol
 */

#include "GenerateGenericRestabFile.h"
using namespace Restab;

int GenerateGenericRestabFile::GenericRestab(std::vector<MasterSolution>& vect_solution){
	DataCube datacube;
	RealVector y_sol0 = vect_solution[0].getY();
	///====================================
	/// Set Description
	///====================================

	{
	IndexDescription index;

	index.label = "TimeStep";
	index.name  = "iTimeStep";

	datacube.list_of_index_description.add(index);
	}
	{

	VariableDescription var;

	var.label = "Time";

	datacube.list_of_variable_description.add(var);
	}

	Integer num_components = y_sol0.size();

	StringVector name(num_components);
	for(Integer idx = 0; idx< num_components;idx++){
		String tmp_name = "Component"+std::to_string(idx);
		name[idx] = tmp_name ;
	}


	for(Integer idx = 1; idx <= num_components; idx++){
		Restab::VariableDescription var;

		var.label = name[idx-1];

		datacube.list_of_variable_description.add(var);
	}
	///====================================
	/// Add Step Values
	///====================================

	MapInteger step_index_values;
	MapReal step_var_values;

	Integer num_solution = vect_solution.size();

	//!Steps

	for(Integer i = 0; i < num_solution; i++){

		step_index_values.clear();
		step_var_values.clear();

		step_index_values.insert(KeyInteger("TimeStep",i+1));
		step_var_values.insert(KeyReal("Time",vect_solution[i].getT()));

		RealVector y_sol = vect_solution[i].getY();
		for(Integer j = 0; j < y_sol.size(); j++){
			String current_name = name[j];
			step_var_values.insert(KeyReal(current_name ,y_sol[j]));
		}
		datacube.table_of_index_values.add(step_index_values);
		datacube.table_of_variable_values.add(step_var_values);
	}
	///======================================
	/// Write Results
	///======================================

	String filename = "GenericResult";

	//! Description

	String filenameDesc = filename + ".restab.desc";

	String text_desc = datacube.toStringDescription();
	std::cout << text_desc << "\n";

	datacube.writeDescription(filenameDesc);

	//! Data

	String filenameData = filename + ".restab";

	String text_data = datacube.toStringData();
	//std::cout << text_data << "\n";

	datacube.writeData(filenameData);

	//======================================

	return 0;

}
