/*
 * TRBDF2MultirateSolverParameters.h
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#ifndef TRBDF2SOLVERPARAMETERS_H_
#define TRBDF2SOLVERPARAMETERS_H_

#include "StandardTypes.h"
using namespace Utils;

//! Class to set the parameters of the TR-BDF2 method
class TRBDF2SolverParameters {
public:
	TRBDF2SolverParameters();
	virtual ~TRBDF2SolverParameters();
	Real getD() const;

	Real getE0() const;

	Real getE1() const;

	Real getE2() const;

	Real getGm() const;

	Real getPd0() const;

	Real getPd1() const;

	Real getPd2() const;

	Real getW() const;

	void setParam(Real pd0,Real pd1, Real pd2, Real e0, Real e1, Real e2, Real gm, Real d, Real w);


private:
	Real pd0;
	Real pd1;
	Real pd2;
	Real e0;
	Real e1;
	Real e2;
	Real gm;
	Real d;
	Real w;
};

#endif /* TRBDF2SOLVERPARAMETERS_H_ */
