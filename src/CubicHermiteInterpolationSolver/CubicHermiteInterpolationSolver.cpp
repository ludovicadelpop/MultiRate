/*
 * CubicHermiteInterpolationSolver.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: delpopol
 */

#include "CubicHermiteInterpolationSolver.h"

CubicHermiteInterpolationSolver::CubicHermiteInterpolationSolver() {}

CubicHermiteInterpolationSolver::~CubicHermiteInterpolationSolver() {}

void CubicHermiteInterpolationSolver::setInput(const InterpolationInputSolver& input) {
	this->input = input;
}

const InterpolationOutputSolver& CubicHermiteInterpolationSolver::getOutput() const {
	return output;
}

void CubicHermiteInterpolationSolver::compute(Real t1, Real t2, Real gm){
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
			if (t1 < t1_int(i)){
				Real v0 = y0_int(i);
				Real v1 = gm * z0_int(i);
				Real v2 = y1_int(i) -y0_int(i) - v1;
				Real v3 = gm * (z1_int(i) - z0_int(i));
				Real r = (t1 - t0_int(i))/(gm * h_int(i));

				y1(i) = (v3 - 2*v2) * (r*r*r) + (3*v2 - v3) * (r*r) + v1*r + v0;
			}else if(t1 > t1_int(i)){
				Real v0 = y1_int(i);
				Real v1 = (1 - gm) * z1_int(i);
				Real v2 = y2_int(i) -y1_int(i) - v1;
				Real v3 = (1 - gm) * (z2_int(i) - z1_int(i));
				Real r1 = (t1 - t1_int(i))/((1-gm) * h_int(i));

				y1(i) = (v3 - 2*v2) * (r1*r1*r1)  + (3*v2 - v3) * (r1*r1) + v1*r1 + v0;
			}
			if(t2 < t1_int(i)){
				Real v0 = y0_int(i);
				Real v1 = gm * z0_int(i);
				Real v2 = y1_int(i) -y0_int(i) - v1;
				Real v3 = gm * (z1_int(i) - z0_int(i));
				Real r = (t2 - t0_int(i))/(gm * h_int(i));

				y2(i) = (v3 - 2*v2) * (r*r*r)  + (3*v2 - v3) * (r*r) + v1*r + v0;
			}else if(t2 > t1_int(i)){
				Real v0 = y1_int(i);
				Real v1 = (1 - gm) * z1_int(i);
				Real v2 = y2_int(i) -y1_int(i) - v1;
				Real v3 = (1 - gm) * (z2_int(i) - z1_int(i));
				Real r = (t2 - t1_int(i))/((1-gm) * h_int(i));

				y2(i) = (v3 - 2*v2) * (r*r*r)  + (3*v2 - v3) * (r*r) + v1*r + v0;

			}
		}

	}

	output.setY1(y1);
	output.setY2(y2);

}


;
