#include<vector>
#include "Rate.h"
#ifndef RateHoLee_H
#define RateHoLee_H
class RateHoLee:public Rate
{
public:
	RateHoLee(double k,double theta,double sigma);
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const;
	virtual Rate* clone() const;
	~RateHoLee(){};

private: 
	double k;
	double theta;
	double sigma;


};

#endif