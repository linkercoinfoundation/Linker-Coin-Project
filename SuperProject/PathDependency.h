#ifndef PathDependency_H
#define PathDependency_H
class PathDependency
{
public:
	PathDependency(){};
	virtual double operator()(double StockValue,double previousVal,int currentStep) const=0;
	virtual double getpreviousVal() =0;
	virtual PathDependency* clone() const=0;

private:



};
#endif