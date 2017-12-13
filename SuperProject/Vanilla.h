#include "Payoff.h"
#ifndef Vanilla_H
#define Vanilla_H
class Vanilla{
public:
	Vanilla(const Payoff& thePayoff);
	double VanillaPayoff(double Spot);
	Vanilla* clone() const;

private:
	
	Payoff* thePayoffPtr;
};


#endif