/*
 * FESolverInput.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef FESOLVERINPUT_H_
#define FESOLVERINPUT_H_

#include "StandardTypes.h"

using namespace Utils;


//! Input class for the FESolver
class FESolverInput {
public:
	FESolverInput();
	virtual ~FESolverInput();

	void set(Real t0, Real dt, RealVector& y0);
	Real getDt() const;
	Real getT0() const;
	const RealVector& getY0()const ;

private:
	Real t0;		/*!< Initial time */
	Real dt;		/*!< Time step */
	RealVector y0;	/*!< Solution at time t0 */
};

#endif /* FESOLVERINPUT_H_ */
