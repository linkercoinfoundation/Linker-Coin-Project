#include "stdafx.h"
#include "PathIndependent.h"
#include "cmath"

PathDependency* PathIndependent::clone() const
{
	return new PathIndependent(*this);

}

double PathIndependent::getpreviousVal()
{
	
	return 0.0;

}

double PathIndependent::operator()(double StockValue,double previousVal,int currentStep) const
{
	
	return StockValue;


}