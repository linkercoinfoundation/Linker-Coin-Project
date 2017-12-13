#include "Barrier.h"
#ifndef UpAndInBarrier_H
#define UpAndInBarrier_H
class UpAndInBarrier:public Barrier
{
public:
	UpAndInBarrier(double theBarrier);
	virtual vector<double> operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const;
	virtual Barrier* clone() const;
	~UpAndInBarrier(){};

private:
	double theBarrier;

};
#endif
