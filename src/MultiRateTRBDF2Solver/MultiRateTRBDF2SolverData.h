/*
 * MultiRateTRBDF2SolverData.h
 *
 *  Created on: Nov 23, 2015
 *      Author: delpopol
 */

#ifndef MULTIRATETRBDF2SOLVERDATA_H_
#define MULTIRATETRBDF2SOLVERDATA_H_

#include "ISolverData.h"
#include "StandardTypes.h"
using namespace Utils;

//! Class to store the Outputs of MultiRateTRBDF2Solver
class MultiRateTRBDF2SolverData: public ISolverData {
public:
	MultiRateTRBDF2SolverData();
	virtual ~MultiRateTRBDF2SolverData();
	//! Gets the error estimation
	const RealVector& getError() const;
	//! Sets the error estimation
	void setError(const RealVector& error);
	//! Gets the size of the time step
	Real getH() const;
	//! Sets the size of the time step
	void setH(Real h);
	//! Gets the boolean variable that says if the time step is accepted
	Bool isHasSucceded() const;
	//! Sets the boolean variable that says if the time step is accepted
	void setHasSucceded(Bool hasSucceded);
	//! Gets the time where is computed the solution
	Real getTime() const;
	//! Sets the time where is computed the solution
	void setTime(Real time);
	//! Gets the solution
	const RealVector& getY() const;
	//! Sets the solution
	void setY(const RealVector& y);
	//! Gets the mesh vector, useful to see the active and latent components
	const IntegerVector& getMesh() const;
	//! Sets the mesh vector, useful to see the active and latent components
	void setMesh(const IntegerVector& mesh);
	//! Gets the boolean value, it is true if we have to refine the time step
	Bool isRefining() const;
	//! Sets the boolean value, it is true if we have to refine the time step
	void setRefining(Bool refining);
	/*! Gets a vector of 0 and 1(if for the i-th component it is equal to 1 means that we are
	 * 	computed the solution with the TRBDF2 method, if it is equal to 0 it means that we are
	 * 	interpolating that component's solution)
	 */
	const IntegerVector& getNumbComponentsSolve() const;
	//! Sets the vector NumbComponentsSolve
	void setNumbComponentsSolve(const IntegerVector& numbComponentsSolve);


private:
	Real time;									 /*!< Solution's time*/
	Real h;										 /*!< Size of the time step from the previous solution to the current one*/
	RealVector y;								 /*!< Solution*/
	RealVector error;							 /*!< Error estimation */
	IntegerVector numb_components_solve;		 /*!< Components computed with the method at this time*/
	IntegerVector mesh;							 /*!< Active components in the current iteration*/
	Bool has_succeded;							 /*!< Boolean: it is true if we accept the iteration*/
	Bool refining;								 /*!< Boolean: it is true if we have to refine this time step*/
};

#endif /* MULTIRATETRBDF2SOLVERDATA_H_ */
