#include "stdafx.h"
#include "PayoffCall.h"
#include <minmax.h>
PayoffCall::PayoffCall(double Strike)
{

	this->Strike=Strike;

}

 double PayoffCall::operator()(double Spot) const
{
	return max(Spot-this->Strike,0);

}
Payoff* PayoffCall::clone() const
{

return new PayoffCall(*this);

}