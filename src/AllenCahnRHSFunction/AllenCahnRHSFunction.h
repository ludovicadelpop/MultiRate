/*
 * AllenCahnRHSFunction.h
 *
 *  Created on: Nov 16, 2015
 *      Author: delpopol
 */

#ifndef ALLENCAHNRHSFUNCTION_H_
#define ALLENCAHNRHSFUNCTION_H_

#include "IRHSFunction.h"
/*!
 * Class to define the Allen-Chan problem
 */
class AllenCahnRHSFunction: public IRHSFunction {
public:
	AllenCahnRHSFunction();
	virtual ~AllenCahnRHSFunction();


	void setSigma(const Real sigma);
	void setNx(const Integer nx);
	Real getSigma();
	Integer getNx();
	Real getX0() const;
	void setX0(Real x0);
	Real getXL() const;
	void setXL(Real l);

	//! Returns a vector that it is the RHS evaluated at a certain time and solution.
	RealVector evalF(Real time, RealVector& y);
	//! Returns a vector that it is the RHS evaluated at a certain time and solution only for the active components.
	RealVector evalF(Real time, RealVector& y, IntegerVector& ref);
	//! Returns the Jacobian matrix at a certain time and solution.
	RealMatrixSparse evaldFdY(Real time, RealVector& y);
	//! Returns the Jacobian matrix at a certain time and solution only for the active components.
	RealMatrixSparse evaldFdY(Real time, RealVector& y,IntegerVector& ref);



private:
	Real sigma;         /*!< Diffusion coefficient */
	Integer Nx;		    /*!< Number of space nodes*/
	Real x0;			/*!< Initial space node*/
	Real xL;			/*!< Final space node*/
};

#endif /* ALLENCAHNRHSFUNCTION_H_ */
