#include "Volatility.h"
#ifndef HestonVolatility_H
#define HestonVolatility_H
class HestonVolatility: public Volatility
{
public:
	HestonVolatility(double gamma, double theta, double k);
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const;
	
	virtual Volatility* clone() const;
	~HestonVolatility(){};


private:
	double gamma;
	double theta;
	double k;

};
#endif