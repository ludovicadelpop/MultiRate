/*
 * MasterSolution.h
 *
 *  Created on: 15 déc. 2015
 *      Author: delpopol
 */

#ifndef MASTERSOLUTION_H_
#define MASTERSOLUTION_H_

#include"StandardTypes.h"
using namespace Utils;

//! Class to store only some attributes of the successful time step.
class MasterSolution {
public:
	MasterSolution();
	virtual ~MasterSolution();

	Real getT() const;
	void setT(Real t);
	const RealVector& getY() const;
	void setY(const RealVector& y);

private:
	RealVector y;    /*!< Solution */
	Real t;			 /*!< Solution time */
};

#endif /* MASTERSOLUTION_H_ */
