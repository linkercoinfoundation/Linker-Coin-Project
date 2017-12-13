#include "Barrier.h"
#ifndef DownAndInBarrier_H
#define DownAndInBarrier_H
class DownAndInBarrier:public Barrier
{
public:
	DownAndInBarrier(double theBarrier);
	virtual vector<double> operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const;
	virtual Barrier* clone() const;
	~DownAndInBarrier(){};

private:
	double theBarrier;

};
#endif