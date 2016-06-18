/*
 * GeochemistryRHSFunction.h
 *
 *  Created on: Dec 1, 2015
 *      Author: delpopol
 */

#ifndef GEOCHEMISTRYRHSFUNCTION_H_
#define GEOCHEMISTRYRHSFUNCTION_H_


#include "IRHSFunction.h"
#include "GeochemistryRHSFunction/GeochemistryParameters.h"

//! Geochemistry function

class GeochemistryRHSFunction : public IRHSFunction{
public:
	GeochemistryRHSFunction();
	virtual ~GeochemistryRHSFunction();

	const GeochemistryParameters& getParameters() const;

	void setParameters(const GeochemistryParameters& parameters);

	//! Returns a vector that it is the RHS evaluated at a certain time and solution.
	RealVector evalF(Real time, RealVector& y);
	//! Returns a vector that it is the RHS evaluated at a certain time and solution only for the active components.
	RealVector evalF(Real time, RealVector& y, IntegerVector& ref);
	//! Returns the Jacobian matrix at a certain time and solution.
	/*! It can be the analytical one or compute with finite difference,
	 * it depends by the implementation.
	*/
	RealMatrixSparse evaldFdY(Real time, RealVector& y);
	//! Returns the Jacobian matrix at a certain time and solution only for the active components.
	/*! It can be the analytical one or compute with finite difference,
	 * it depends by the implementation.
	 */
	RealMatrixSparse evaldFdY(Real time, RealVector& y, IntegerVector& ref);

private:
	GeochemistryParameters parameters; /*!< Parameters */

};

#endif /* GEOCHEMISTRYRHSFUNCTION_H_ */
