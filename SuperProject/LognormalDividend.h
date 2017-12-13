#include "Dividend.h"
#ifndef LognormalDividend_H
#define LognormalDividend_H
class LognormalDividend:public Dividend
{
  public:
	LognormalDividend(double alphaEquity,double gammaEquity, double deltaEquity);
	virtual double operator()(double EquityNormal, double previousDividend,double dt,double rate,double Stock,double Vol) const;
	
	virtual Dividend* clone() const;
	~LognormalDividend(){};


private:
	double alphaEquity;
	double gammaEquity;
	double deltaEquity;
	
};
#endif