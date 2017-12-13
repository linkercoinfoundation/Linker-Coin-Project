#ifndef PayoffCall_H
#define PayoffCall_H
#include "Payoff.h"
class PayoffCall:public Payoff
{
public:
	PayoffCall(double Strike); //The strike is the characteristic of the PAyoff
	virtual double operator()(double Spot) const;
	virtual Payoff* clone() const;
	~PayoffCall(){};

private:
	double Strike;

};


#endif