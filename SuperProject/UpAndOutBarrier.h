#include "Barrier.h"
#ifndef UpAndOutBarrier_H
#define UpAndOutBarrier_H
class UpAndOutBarrier:public Barrier
{
public:
	UpAndOutBarrier(double theBarrier);
	virtual vector<double> operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const;
	virtual Barrier* clone() const;
	~UpAndOutBarrier(){};

private:
	double theBarrier;

};
#endif
