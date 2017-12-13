#include "stdafx.h"
#include "GeometricAsian.h"
#include "cmath"


PathDependency* GeometricAsian::clone() const
{
	return new GeometricAsian(*this);

}

double GeometricAsian::getpreviousVal()
{
	
	return 1.0;

}

double GeometricAsian::operator()(double StockValue,double previousVal,int currentStep) const
{
	return pow(pow(previousVal,static_cast<double>(currentStep-1)),(1.0/(static_cast<double>(currentStep))))*pow(StockValue,(1.0/(static_cast<double>(currentStep))));


}