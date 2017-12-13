#include<vector>
#include "Rate.h"
#ifndef RateHWVasicek_H
#define RateHWVasicek_H
class RateHWVasicek:public Rate
{
public:
	RateHWVasicek(double k,double theta,double sigma);
	virtual double operator()(double CorrelatedNormal, double previousr,double dt) const;
	virtual Rate* clone() const;
	~RateHWVasicek(){};

private: 
	double k;
	double theta;
	double sigma;


};

#endif