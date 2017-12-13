#include "stdafx.h"
#include "ConstantDividend.h"
#include <cmath>
ConstantDividend::ConstantDividend(double alphaEquity,double gammaEquity, double deltaEquity)
{
	this->alphaEquity=alphaEquity;
	this->gammaEquity=gammaEquity;
	this->deltaEquity=deltaEquity;
	
	


}
	 double ConstantDividend::operator()(double EquityNormal, double previousDividend,double dt,double rate,double Stock,double Vol) const
	 {
	
		 double dividend=previousDividend;

	     return dividend;
	 }



	 Dividend* ConstantDividend::clone() const
	 {
		 return new ConstantDividend(*this);

	 }