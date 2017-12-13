#include<vector>
#ifndef Rate_H
#define Rate_H
class Rate{
public:
	Rate(){};
	virtual double operator()(double CorrelatedNormal, double previousr,double dt) const=0;
	virtual Rate* clone() const=0;
	~Rate(){};

private: 
	double k;
	double theta;
	double sigma;


};

#endif