#include<vector>
#ifndef Payoff_H
#define Payoff_H
class Payoff{
public:
	Payoff(){};
	virtual double operator()(double Spot) const=0;
	virtual Payoff* clone() const=0;
	~Payoff(){};

private: 
	double Strike;


};

#endif