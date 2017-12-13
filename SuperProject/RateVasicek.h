#include<vector>
#include "Rate.h"
#ifndef RateVasicek_H
#define RateVasicek_H
class RateVasicek:public Rate
{
public:
	RateVasicek(double k,double theta,double sigma);
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const;
	virtual Rate* clone() const;
	~RateVasicek(){};

private: 
	double k;
	double theta;
	double sigma;


};

#endif