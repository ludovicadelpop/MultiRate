/*
 * SingleRateTRBDF2SolverData.h
 *
 *  Created on: Nov 10, 2015
 *      Author: delpopol
 */

#ifndef SINGLERATETRBDF2SOLVERDATA_H_
#define SINGLERATETRBDF2SOLVERDATA_H_

#include "ISolverData.h"
#include "StandardTypes.h"
#include <vector>

using namespace Utils;

//! Output class for the SIngleRateTRBDF2Solver
class SingleRateTRBDF2SolverData : public ISolverData{

public:
	SingleRateTRBDF2SolverData();
	virtual ~SingleRateTRBDF2SolverData();

	const RealVector& getError() const;

	void setError(const RealVector& err);

	Real getH() const;

	void setH(Real vec);

	Bool isHasSucceded() const;

	void setHasSucceded(Bool hasSucceded);

	Real getTime() const;

	void setTime(Real t);

	const RealVector& getY() const;

	void setY(const RealVector& yn);

	const IntegerVector& getMesh() const;

	void setMesh(const IntegerVector& mesh);

	const IntegerVector& getNumbComponentsSolve() const;

	void setNumbComponentsSolve(const IntegerVector& numbComponentsSolve);

	Bool isRefining() const;

	void setRefining(Bool refining);

private:
	Real time;									 /*!< Solution's time*/
	Real h;										 /*!< Size of the time step from the previous solution to the current one*/
	RealVector y;								 /*!< Solution*/
	RealVector error;							 /*!< Error estimation */
	IntegerVector numb_components_solve;		 /*!< Active components in the current iteration*/
	IntegerVector mesh;							 /*!< Components computed with the method at this time    */
	Bool has_succeded;							 /*!< Boolean: it is true if we accept the iteration*/
	Bool refining;								 /*!< Boolean: it is true if we have to refine this time step*/

};

#endif /* SINGLERATETRBDF2SOLVERDATA_H_ */
