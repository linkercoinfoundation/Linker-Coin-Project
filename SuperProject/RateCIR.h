#include<vector>
#include "Rate.h"
#ifndef RateCIR_H
#define RateCIR_H
class RateCIR:public Rate
{
public:
	RateCIR(double k,double theta,double sigma);
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const;
	virtual Rate* clone() const;
	~RateCIR(){};

private: 
	double k;
	double theta;
	double sigma;


};

#endif