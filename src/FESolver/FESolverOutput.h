/*
 * FESolverOutput.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef FESOLVEROUTPUT_H_
#define FESOLVEROUTPUT_H_

#include "StandardTypes.h"

using namespace Utils;

//! Output class for the FESolver
class FESolverOutput {
public:
	FESolverOutput();
	virtual ~FESolverOutput();

	void setYFinal(const RealVector& final);
	const RealVector& getYFinal() const;
	Real getTFinal() const;
	Bool getIsConverged() const;
	void setIsConverged(Bool isConverged);
	void setTFinal(const Real  final);

private:
	RealVector y_final;		/*!< Solution computed */
	Real t_final;			/*!< Time of the solution */
	Bool is_converged;		/*!< Boolean indicates if Newton is converged( in this case we don't need it is an explicit method) */
};

#endif /* FESOLVEROUTPUT_H_ */
