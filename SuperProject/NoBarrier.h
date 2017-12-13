#include "Barrier.h"
#ifndef NoBarrier_H
#define NoBarrier_H
class NoBarrier:public Barrier
{
public:
	NoBarrier(double theBarrier);
	virtual vector<double> operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const;
	virtual Barrier* clone() const;
	~NoBarrier(){};

private:
	double theBarrier;

};
#endif