#include "Payoff.h"
#ifndef PayoffPut_H
#define PayoffPut_H
class PayoffPut:public Payoff
{
public:
	PayoffPut(double Strike);
	virtual double operator()(double Spot) const;
	virtual Payoff* clone() const;
	PayoffPut(){};
private:
	double Strike;



};
#endif