#include<vector>
#include "Rate.h"
#ifndef RateConstant_H
#define RateConstant_H
class RateConstant:public Rate
{
public:
	RateConstant(double k,double theta,double sigma);
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const;
	virtual Rate* clone() const;
	~RateConstant(){};

private: 
	double k;
	double theta;
	double sigma;


};

#endif