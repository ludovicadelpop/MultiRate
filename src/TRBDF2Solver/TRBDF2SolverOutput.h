/*
 * TRBDF2SolverOutput.h
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#ifndef TRBDF2SOLVEROUTPUT_H_
#define TRBDF2SOLVEROUTPUT_H_

#include "StandardTypes.h"
using namespace Utils;

//! Class to store the output of the TRBDF2 Solver
class TRBDF2SolverOutput {
public:
	TRBDF2SolverOutput();
	virtual ~TRBDF2SolverOutput();

	const RealVector& getEst() const;

	void setEst(const RealVector& est);

	Bool isNewtonDiverge() const;

	void setNewtonDiverge(Bool newtonDiverge);

	Real getT2() const;

	void setT2(Real t2);

	const RealVector& getY2() const;

	void setY2(const RealVector& y2);

	const RealVector& getZ2() const;

	void setZ2(const RealVector& z2);

	Real getT1() const;

	void setT1(Real t1);

	const RealVector& getY1() const;

	void setY1(const RealVector& y1);

	const RealVector& getZ0() const;

	void setZ0(const RealVector& z0);

	const RealVector& getZ1() const;

	void setZ1(const RealVector& z1);

private:
	RealVector z0;
	RealVector z1;
	RealVector z2;
	RealVector y1;
	RealVector y2;
	Real t1;
	Real t2;
	RealVector est;
	Bool newton_diverge;
};

#endif /* TRBDF2SOLVEROUTPUT_H_ */
