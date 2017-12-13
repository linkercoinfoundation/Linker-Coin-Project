#include "Dividend.h"
#ifndef ConstantDividend_H
#define ConstantDividend_H
class ConstantDividend:public Dividend
{
  public:
	ConstantDividend(double alphaEquity,double gammaEquity, double deltaEquity);
	virtual double operator()(double EquityNormal, double previousDividend,double dt,double rate,double Stock,double Vol) const;
	
	virtual Dividend* clone() const;
	~ConstantDividend(){};


private:
	double alphaEquity;
	double gammaEquity;
	double deltaEquity;
	

};
#endif