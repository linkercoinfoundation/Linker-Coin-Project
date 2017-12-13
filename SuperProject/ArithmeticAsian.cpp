#include "stdafx.h"
#include "ArithmeticAsian.h"
#include "cmath"


PathDependency* ArithmeticAsian::clone() const
{
	return new ArithmeticAsian(*this);

}

double ArithmeticAsian::getpreviousVal()
{
	
	return 0.0;

}

double ArithmeticAsian::operator()(double StockValue,double previousVal,int currentStep) const
{
	double x= ( ((previousVal*(static_cast<double>(currentStep)-1.0)+StockValue) /( static_cast<double>(currentStep)))-previousVal )/StockValue;
	return previousVal+x*StockValue;


}