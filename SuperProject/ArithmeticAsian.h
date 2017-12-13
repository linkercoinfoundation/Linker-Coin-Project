#include "PathDependency.h"
#ifndef ArithmeticAsian_H
#define ArithmeticAsian_H
class ArithmeticAsian:public PathDependency
{
public:
	ArithmeticAsian(double number){};
	
	virtual double operator()(double StockValue,double previousVal,int currentStep) const;
	virtual double getpreviousVal() ;
	virtual PathDependency* clone() const;

private:
	double previousVal;
	double StockValue;
	int currentStep;


};
#endif