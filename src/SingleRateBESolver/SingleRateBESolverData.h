/*
 * SingleRateBESolverData.h
 *
 *  Created on: 8 janv. 2016
 *      Author: delpopol
 */

#ifndef SINGLERATEBESOLVERDATA_H_
#define SINGLERATEBESOLVERDATA_H_

#include "ISolverData.h"
#include "StandardTypes.h"
using namespace Utils;

//! Output class for the SingleRateBESolver
class SingleRateBESolverData : public ISolverData{
public:
	SingleRateBESolverData();
	virtual ~SingleRateBESolverData();

	const RealVector& getError() const;

	void setError(const RealVector& error);

	Real getH() const;

	void setH(Real h);

	Bool isHasSucceded() const;

	void setHasSucceded(Bool hasSucceded);

	Real getTime() const;

	void setTime(Real time);

	const RealVector& getY() const;

	void setY(const RealVector& y);

	const IntegerVector& getMesh() const;

	Bool isRefining() const;

	void setRefining(Bool refining);

	const IntegerVector& getNumbComponentsSolve() const;

	void setNumbComponentsSolve(const IntegerVector& numbComponentsSolve);

	void setMesh(const IntegerVector& mesh);



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

#endif /* SINGLERATEBESOLVERDATA_H_ */
