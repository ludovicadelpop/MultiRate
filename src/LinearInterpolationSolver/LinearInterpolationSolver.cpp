/*
 * LinearInterpolationSolver.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: pacs_student
 */

#include "LinearInterpolationSolver.h"

LinearInterpolationSolver::LinearInterpolationSolver() {}

LinearInterpolationSolver::~LinearInterpolationSolver() {}

void LinearInterpolationSolver::setInput(const InterpolationInputSolver& input) {
	this->input = input;
}

const InterpolationOutputSolver& LinearInterpolationSolver::getOutput() const {
	return output;
}

void LinearInterpolationSolver::compute(Real t1, Real t2, Real gm){
	RealVector y0_int = input.getY0Int();
	RealVector y1_int = input.getY1Int();
	RealVector y2_int= input.getY2Int();
	RealVector z0_int = input.getZ0Int();
	RealVector z1_int = input.getZ1Int();
	RealVector z2_int = input.getZ2Int();
	RealVector t0_int = input.getT0Int();
	RealVector t1_int = input.getT1Int();
	RealVector t2_int = input.getT2Int();
	IntegerVector ref = input.getRef();

	RealVector h_int = t2_int - t0_int;
	Integer ref_size = ref.cast<Real>().size();

	RealVector y1(ref_size);
	RealVector y2(ref_size);
	y1.fill(0.0);
	y2.fill(0.0);


	for (Integer i = 0; i < ref_size; ++i){
		if (ref(i) == 0){

			y1(i) = y0_int(i) + (y2_int(i) - y0_int(i))*((t1-t0_int(i))/h_int(i));
			y2(i) = y0_int(i) + (y2_int(i) - y0_int(i))*((t2-t0_int(i))/h_int(i));

		}
	}

	output.setY1(y1);
	output.setY2(y2);

}
;
