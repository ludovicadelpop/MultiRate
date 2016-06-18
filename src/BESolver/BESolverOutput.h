/*
 * BESolverOutput.h
 *
 *  Created on: Nov 5, 2015
 *      Author: delpopol
 */

#ifndef BESOLVEROUTPUT_H_
#define BESOLVEROUTPUT_H_

#include "StandardTypes.h"

using namespace Utils;

//! Output for the single time step BEsolver
class BESolverOutput {
public:
	BESolverOutput();
	virtual ~BESolverOutput();

	void setYFinal(const RealVector& final);
	const RealVector& getYFinal() const;
	Real getTFinal() const;
	Bool getIsConverged() const;
	void setIsConverged(Bool isConverged);
	void setTFinal(const Real  final);
	Real getDt() const;
	void setDt(Real dt);

private:
	RealVector y_final;  /*!< Solution */
	Real t_final;        /*!< Time where is computed the solution y_final */
	Real dt;			 /*!< Size of the time step */
	Bool is_converged;   /*!< Boolean if Newton solver has converged */
};

#endif /* BESOLVEROUTPUT_H_ */
