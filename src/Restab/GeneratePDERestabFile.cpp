/*
 * GeneratePDERestabFile.cpp
 *
 *  Created on: 22 déc. 2015
 *      Author: delpopol
 */

#include "GeneratePDERestabFile.h"

using namespace Restab;

int GeneratePDERestabFile::PDERestab(Real x0, Real Nx, Real xL,  std::vector<MasterSolution>& vect_solution){
	DataCube datacube;

	RealVector x_vect(Nx);
	x_vect.setLinSpaced(Nx,x0,xL);
	Integer num_solution = vect_solution.size();

	///====================================
	/// Set Description
	///====================================

	{
	IndexDescription index;

	index.label = "x_node";
	index.name  = "numbNode";

	datacube.list_of_index_description.add(index);
	}



	{
		VariableDescription var;

		var.label ="x_value";

		datacube.list_of_variable_description.add(var);
		}


	{
	VariableDescription var;

	var.label = "Time t0";

	datacube.list_of_variable_description.add(var);
	}

	{
	VariableDescription var;

	var.label = "Time tend";

	datacube.list_of_variable_description.add(var);
	}

	///====================================
	/// Add Step Values
	///====================================

	MapInteger step_index_values;
	MapReal step_var_values;

	//Steps

	RealVector y_sol0 = vect_solution[0].getY();
	RealVector y_solend = vect_solution[num_solution-1].getY();
	for (Integer i = 0; i< y_sol0.size(); ++i ){
		step_index_values.clear();
		step_var_values.clear();
		step_index_values.insert(KeyInteger("x_node",i+1));
		step_var_values.insert(KeyReal("x_value",x_vect[i]));
		step_var_values.insert(KeyReal("Time t0",y_sol0[i]));
		step_var_values.insert(KeyReal("Time tend",y_solend[i]));

		datacube.table_of_index_values.add(step_index_values);
		datacube.table_of_variable_values.add(step_var_values);

	}



	///======================================
	/// Write Results
	///======================================

	String filename = "PDEResult";

	//! Description

	String filenameDesc = filename + ".restab.desc";

	String text_desc = datacube.toStringDescription();
	//std::cout << text_desc << "\n";

	datacube.writeDescription(filenameDesc);

	// Data

	String filenameData = filename + ".restab";

	String text_data = datacube.toStringData();
	//std::cout << text_data << "\n";

	datacube.writeData(filenameData);

	//======================================

	return 0;

}
