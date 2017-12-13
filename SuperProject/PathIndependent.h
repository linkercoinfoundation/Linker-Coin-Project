#include "PathDependency.h"
#ifndef PathIndependent_H
#define PathIndependent_H
class PathIndependent:public PathDependency
{
public:
	PathIndependent(double number){};
	
	virtual double operator()(double StockValue,double previousVal,int currentStep) const;
	virtual double getpreviousVal() ;
	virtual PathDependency* clone() const;

private:
	


};
#endif