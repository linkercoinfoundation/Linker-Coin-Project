#include "PathDependency.h"
#ifndef GeometricAsian_H
#define GeometricAsian_H
class GeometricAsian:public PathDependency
{
public:
	GeometricAsian(double number){};
	
	virtual double operator()(double StockValue,double previousVal,int currentStep) const;
	virtual double getpreviousVal() ;
	virtual PathDependency* clone() const;

private:
	


};
#endif