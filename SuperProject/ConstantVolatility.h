#include "Volatility.h"
#ifndef ConstantVolatility_H
#define ConstantVolatility_H
class ConstantVolatility:public Volatility
{
  public:
	ConstantVolatility(double gamma, double theta, double k);
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const;
	
	virtual Volatility* clone() const;
	~ConstantVolatility(){};


private:
	double gamma;
	double theta;
	double k;


};
#endif