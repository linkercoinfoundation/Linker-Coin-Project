#include "stdafx.h"
#include "LognormalDividend.h"
#include <cmath>
LognormalDividend::LognormalDividend(double alphaEquity,double gammaEquity, double deltaEquity)
{
	this->alphaEquity=alphaEquity;
	this->gammaEquity=gammaEquity;
	this->deltaEquity=deltaEquity;
	
	


}
	 double LognormalDividend::operator()(double EquityNormal, double previousDividend,double dt,double rate,double Stock,double vol) const
	 {
	     // We put sqrt(vol) because vol is the square of the volatility as in the Heston model
		 double dividend=previousDividend+((deltaEquity*sqrt(vol)+gammaEquity*rate-gammaEquity*alphaEquity)/(sqrt(vol)+gammaEquity))*Stock*dt+EquityNormal*sqrt(dt)*Stock*gammaEquity;

	     return dividend;
	 }



	 Dividend* LognormalDividend::clone() const
	 {
		 return new LognormalDividend(*this);

	 }