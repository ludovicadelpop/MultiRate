/*
 * VectorUtility.cpp
 *
 *  Created on: 2 d�c. 2015
 *      Author: delpopol
 */
#include <ostream>
#include "VectorUtility.h"

RealVector VectorUtility::vectorProlong(RealVector& y,IntegerVector& ref){

	Integer ref_size = ref.cast<Real>().size();
	RealVector y_long(ref_size);
	y_long.fill(0.0);

	Integer elem_ref = ref.sum();
	Integer idx = 0;

	Integer y_size = y.size();

	if(y_size != elem_ref){
		std::cerr<<"Vector dimension not equal to number of components refined"<<std::endl;
	}

	if (elem_ref == ref_size){
		 y_long = y;
	}else{
		for(Integer i = 0; i < ref_size; ++i ){
			if (ref(i) == 1){
				y_long(i) = y(idx);
				idx += 1;
			}
		}
	}

	return y_long;
}

RealVector VectorUtility::vectorReduce(RealVector& y,IntegerVector& ref){

	Integer elem_ref = ref.sum();
	Integer y_size = y.size();

	RealVector y_new(elem_ref);
	y_new.fill(0.0);
	Integer idx = 0;

	for (Integer i = 0; i < y_size; i++){
		if(ref(i) == 1){
			y_new(idx) = y(i);
			idx += 1;
		}
	}
	return  y_new;
}
