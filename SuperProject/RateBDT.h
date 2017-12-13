#include<vector>
#include "Rate.h"
#ifndef RateBDT_H
#define RateBDT_H
class RateBDT:public Rate
{
public:
	RateBDT(double k,double theta,double sigma);
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const;
	virtual Rate* clone() const;
	~RateBDT(){};

private: 
	double k;
	double theta;
	double sigma;


};

#endif