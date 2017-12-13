#include "stdafx.h"
#include "PayoffPut.h"
#include<minmax.h>
PayoffPut::PayoffPut(double Strike)
{
	this->Strike=Strike;

}

double PayoffPut::operator()(double Spot) const
{

	return max(Strike-Spot,0);
}
 
Payoff* PayoffPut::clone() const
{
	return new PayoffPut(*this);

}