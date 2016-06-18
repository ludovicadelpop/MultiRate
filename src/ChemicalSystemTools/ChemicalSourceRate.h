/*
 * ChemicalSourceRate.h
 *
 *  Created on: 14 déc. 2015
 *      Author: delpopol
 */

#ifndef CHEMICALSOURCERATE_H_
#define CHEMICALSOURCERATE_H_

#include "StandardTypes.h"

using namespace Utils;

//! Class to store the source rate term in the Geochemistry problem
class ChemicalSourceRate {
public:
	ChemicalSourceRate();
	virtual ~ChemicalSourceRate();

	void setSourceRate(KeyReal sourceRate);

	const std::vector<KeyReal>& getSourceRate() const;

private:
	std::vector<KeyReal> SourceRate;   /*!< vector of the source rate values for each species  */
};

#endif /* CHEMICALSOURCERATE_H_ */
