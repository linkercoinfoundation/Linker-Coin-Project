#include "stdafx.h"
#include "Vanilla.h"
Vanilla::Vanilla(const Payoff& thePayoff)
{
	this->thePayoffPtr=thePayoff.clone();


}

double Vanilla::VanillaPayoff(double Spot)
{

return this->thePayoffPtr->operator()( Spot);

}

Vanilla* Vanilla::clone() const
{
	return new Vanilla(*this);

}