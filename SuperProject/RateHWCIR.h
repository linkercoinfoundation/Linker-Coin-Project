#include<vector>
#include "Rate.h"
#ifndef RateHWCIR_H
#define RateHWCIR_H
class RateHWCIR:public Rate
{
public:
	RateHWCIR(double k,double theta,double sigma);
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const;
	virtual Rate* clone() const;
	~RateHWCIR(){};

private: 
	double k;
	double theta;
	double sigma;


};

#endif