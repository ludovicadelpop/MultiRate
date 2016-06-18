/*
 * GenerateCourantNumberRestabFile.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: pacs_student
 */

#include "GenerateCourantNumberRestabFile.h"

using namespace Restab;

int GenerateCourantNumberRestabFile::CourantRestab(std::vector<Real>cour_numb){
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

				var.label = "Courant_number";

				datacube.list_of_variable_description.add(var);
			}

			///====================================
			/// Add Step Values
			///====================================

			MapInteger step_index_values;
			MapReal step_var_values;

			Integer num_solution = cour_numb.size();

			//!Steps

			for(Integer i = 1; i < num_solution; i++){

				step_index_values.clear();
				step_var_values.clear();

				step_index_values.insert(KeyInteger("timeStep",i));

				Real cour = cour_numb[i];

				step_var_values.insert(KeyReal("Courant_number" ,cour));

				datacube.table_of_index_values.add(step_index_values);
				datacube.table_of_variable_values.add(step_var_values);
			}
				///======================================
				/// Write Results
				///======================================

				String filename = "Courantresult";

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

