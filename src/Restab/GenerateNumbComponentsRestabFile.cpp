/*
 * GenerateNumbComponentsRestabFile.cpp
 *
 *  Created on: 22 déc. 2015
 *      Author: delpopol
 */

#include "GenerateNumbComponentsRestabFile.h"

using namespace Restab;

int GenerateNumbComponentsRestabFile::ComponentsRestab( std::vector<std::unique_ptr<ISolverData>>&& vect_solution){
	DataCube datacube;

			///====================================
			/// Set Description
			///====================================

			{
				IndexDescription index;

				index.label = "timeStep";
				index.name  = "iTimeStep";

				datacube.list_of_index_description.add(index);
			}

			{
				Restab::VariableDescription var;

				var.label = "number_of_components";

				datacube.list_of_variable_description.add(var);
			}

			///====================================
			/// Add Step Values
			///====================================

			MapInteger step_index_values;
			MapReal step_var_values;

			Integer num_solution = vect_solution.size();

			//!Steps

			for(Integer i = 1; i < num_solution; i++){

				step_index_values.clear();
				step_var_values.clear();

				step_index_values.insert(KeyInteger("timeStep",i));

				IntegerVector ref = vect_solution[i]->getNumbComponentsSolve();
				Integer numb_comp = ref.sum();

				step_var_values.insert(KeyReal("number_of_components" ,numb_comp));

				datacube.table_of_index_values.add(step_index_values);
				datacube.table_of_variable_values.add(step_var_values);
			}
				///======================================
				/// Write Results
				///======================================

				String filename = "Componentsresult";

				//! Description

				String filenameDesc = filename + ".restab.desc";

				String text_desc = datacube.toStringDescription();
				//std::cout << text_desc << "\n";

				datacube.writeDescription(filenameDesc);

				//! Data

				String filenameData = filename + ".restab";

				String text_data = datacube.toStringData();
				//std::cout << text_data << "\n";

				datacube.writeData(filenameData);

				//======================================


			return 0;
}
