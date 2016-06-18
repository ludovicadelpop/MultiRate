/*
 * TRBDF2SolverInput.h
 *
 *  Created on: Nov 19, 2015
 *      Author: delpopol
 */

#ifndef TRBDF2SOLVERINPUT_H_
#define TRBDF2SOLVERINPUT_H_

#include "StandardTypes.h"
using namespace Utils;

//! Class to set the input useful to compute the solution with TRBDF2 method
class TRBDF2SolverInput {
public:
	TRBDF2SolverInput();
	virtual ~TRBDF2SolverInput();

	void setInput(Real t0,Real h,RealVector& hz1,RealVector& y0,RealVector& y1,RealVector& y2,RealMatrixSparse& matrixiter,Real tolAbsolute, Real tolRelative, IntegerVector& ref);

	Real getH() const;

	RealVector& getHz1();

	Real getT0() const;

	Real getTolAbs() const;

	Real getTolRel() const;

	RealVector& getY0();

	RealMatrixSparse& getMatrixIter();

	const IntegerVector& getRef() const;

	const RealVector& getY1() const;

	const RealVector& getY2() const;

private:
	Real t0; 							/*!< Previous time */
	Real h;								/*!< Time step */
	Real tol_rel;						/*!< Relative tolerance for Newton solver */
	Real tol_abs;						/*!< Absolute tolerance for Newton solver */
	RealVector hz_1;					/*!< Initial guess y0' */
	RealVector y0;						/*!< Solution at time t0 */
	RealVector y1;						/*!< Solution at time t1 */
	RealVector y2;						/*!< Solution at time t2 */
	IntegerVector ref;					/*!< Vector of the components that we have to compute the solution */
	RealMatrixSparse matrix_iter;		/*!< Jacobian Matrix for z variables M = I - d*h*Jac   */
};

#endif /* TRBDF2SOLVERINPUT_H_ */
