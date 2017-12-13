#include "stdafx.h"
#include "HestonVolatility.h"
#include <cmath>
HestonVolatility::HestonVolatility(double gamma, double theta, double k)
{
	this->gamma=gamma;
	this->k=k;
	this->theta=theta;
	


}
	 double HestonVolatility::operator()(double CorrelatedNormal, double previousVol,double dt) const
	 {
	
		 double vol=previousVol+k*(theta-previousVol)*dt+gamma*sqrt(previousVol)*sqrt(dt)*CorrelatedNormal;

	     return vol;
	 }



	 Volatility* HestonVolatility::clone() const
	 {
		 return new HestonVolatility(*this);

	 }
	
