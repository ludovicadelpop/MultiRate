/*
 * SetProblemAllenCahn.h
 *
 *  Created on: 11 déc. 2015
 *      Author: delpopol
 */

#ifndef SETPROBLEMALLENCAHN_H_
#define SETPROBLEMALLENCAHN_H_

#include "StandardTypes.h"
using namespace Utils;

namespace SetProblemAllenCahn{

void InitAllenCahn(RealVector& y0, Real& sigma, Integer& Nx, Real& x0, Real& xL){

	Real ssigma = 2*sqrt(sigma);
	RealVector x(Nx);
	x.setLinSpaced(Nx,x0,xL);

	Integer size = x.size();
	y0.resize(size);

	for(Integer i=0; i < size; ++i){
		if(x[i] >=-1.0 && x[i]<-0.7){
			Real value = (x[i]+0.9)/ssigma;
			y0[i] = tanh(value);
		}else{
			if(x[i] >=-0.7 && x[i]<0.28){
				Real value = (0.2-x[i])/ssigma;
				y0[i] = tanh(value);
			}else{
				if(x[i] >=0.28 && x[i]<0.4865){
					Real value = (x[i]-0.36)/ssigma;
					y0[i] = tanh(value);
				}else{
					if(x[i] >=0.4865 && x[i]<0.7065){
						Real value = (0.613-x[i])/ssigma;
						y0[i] = tanh(value);
					}else{
						if(x[i] >=0.7065 && x[i]<=2.1){
							Real value = (x[i]-0.8)/ssigma;
							y0[i] = tanh(value);
						}
					}
				}
			}
		}
	}
}


}


#endif /* SETPROBLEMALLENCAHN_H_ */
