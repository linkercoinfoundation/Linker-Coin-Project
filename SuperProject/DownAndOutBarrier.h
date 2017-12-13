#include "Barrier.h"
#ifndef DownAndOutBarrier_H
#define DownAndOutBarrier_H
class DownAndOutBarrier:public Barrier
{
public:
	DownAndOutBarrier(double theBarrier);
	virtual vector<double> operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const;
	virtual Barrier* clone() const;
	~DownAndOutBarrier(){};

private:
	double theBarrier;

};
#endif