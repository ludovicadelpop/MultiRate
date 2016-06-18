/*
 * Restab.h
 *
 *  Created on: 15 déc. 2015
 *      Author: delpopol
 */

#ifndef RESTAB_H_
#define RESTAB_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

#include "StandardTypes.h"
using namespace Utils;

namespace Restab{

template <class T> class Array : public std::vector<T>{
public :

	void add(T t){
		this->push_back(t);
	}

	T get(Integer i){
		return *this[i];
	}
};

class IndexDescription{
public :
	String label;
	String name;

public :

	IndexDescription(){;}
	IndexDescription(String _label,String _name){
		label = _label ;
		name  = _name;
	}

};

class VariableDescription{
public :
	String label;


	VariableDescription(){;}
	VariableDescription(String _label){
			label = _label ;

		}
};

class DataCube{
public :

	Array<IndexDescription> list_of_index_description;
	Array<VariableDescription> list_of_variable_description;

	Array<MapInteger> table_of_index_values;
	Array<MapReal> table_of_variable_values;

public :

	String toString(){
		String textA = toStringDescription();
		String textB = toStringData();

		return textA + "\n" + textB;
	}

	String toStringDescription(){

		///===========================================
		/// Description File
		///===========================================

		Integer numVariable = list_of_variable_description.size();
		Integer numIndex    = list_of_index_description.size();

		//std::cout << "Size = " << numVariable << " " << numIndex << "\n";

		//===========================================

		std::ostringstream out;

		out << "#INDEX"
				<< "\t" << "Label"
				<< "\t" << "Name"
				<< "\n";

		out << "#VARIABLE"
				<< "\t" << "Label"
				<< "\n";

		out << "\n";

		for (Integer i = 0; i < numIndex ; i++ ){
			IndexDescription & index = list_of_index_description[i];
			out << "INDEX"
					<< "\t" << index.label
					<< "\t" << index.name
					<< "\n";
		}

		out << "\n";

		for (Integer i = 0; i < numVariable ; i++ ){
			VariableDescription & var = list_of_variable_description[i];
			out << "VARIABLE"
					<< "\t" << var.label
					<< "\n";
		}

		//===========================================

		String text;
		text += out.str();

		return text;
	}

	String toStringData(){

		///===========================================
		/// Data File
		///============================================

		Integer numLine     = table_of_index_values.size();
		Integer numVariable = list_of_variable_description.size();
		Integer numIndex    = list_of_index_description.size();


		std::ostringstream out;


		for (Integer i = 0; i < numIndex ; i++ ){
			IndexDescription & index = list_of_index_description[i];
			out << index.label;
			out << "\t";
		}

		for (Integer i = 0; i < numVariable ; i++ ){
			VariableDescription & var = list_of_variable_description[i];
			out << var.label;
			out << "\t";
		}

		out << "\n";

		for (Integer iLine = 0; iLine < numLine ; iLine++ ){

			MapInteger & map_index = table_of_index_values[iLine];
			MapReal & map_var   = table_of_variable_values[iLine];

			for (Integer i = 0; i < numIndex ; i++ ){
				IndexDescription & index = list_of_index_description[i];
				String key = index.label;
				//std::cout << "Index Key = " << key << "\n";
				Integer index_value = map_index.at(key);
				//std::cout << "Index Value = " << index_value << "\n";

				out << index_value << "\t";
			}

			for (Integer i = 0; i < numVariable ; i++ ){
				VariableDescription & var = list_of_variable_description[i];
				String key = var.label;
				//std::cout << "Var Key = " << key << "\n";
				Real var_value = map_var.at(key);
				//std::cout << "Var Value = " << var_value << "\n";

				out << var_value << "\t";
			}

			out << "\n";
		}

		//===========================================

		String text;
		text += out.str();

		return text;

	}

	void writeDescription(String filename){
		std::ofstream myfile;
		myfile.open(filename.c_str());

		String text = toStringDescription();
		myfile << text;

		myfile.close();

	}

	void writeData(String filename){
		std::ofstream myfile;
		myfile.open(filename.c_str());

		String text = toStringData();
		myfile << text;

		myfile.close();


	}
};

}



#endif /* RESTAB_H_ */
