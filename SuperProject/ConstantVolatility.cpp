#include "stdafx.h"
#include "ConstantVolatility.h"
#include <cmath>
ConstantVolatility::ConstantVolatility(double gamma, double theta, double k)
{
	this->gamma=gamma;
	this->k=k;
	this->theta=theta;
	


}
	 double ConstantVolatility::operator()(double CorrelatedNormal, double previousVol,double dt) const
	 {
	
		 double vol=previousVol;

	     return vol;
	 }



	 Volatility* ConstantVolatility::clone() const
	 {
		 return new ConstantVolatility(*this);

	 }
	