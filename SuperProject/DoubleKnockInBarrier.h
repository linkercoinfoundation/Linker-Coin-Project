#include "Barrier.h"
#ifndef DoubleKnockInBarrier_H
#define DoubleKnockInBarrier_H
class DoubleKnockInBarrier:public Barrier
{
public:
	DoubleKnockInBarrier(double UpBarrier,double DownBarrier);
	virtual vector<double> operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const;
	virtual Barrier* clone() const;
	~DoubleKnockInBarrier(){};

private:
	double UpBarrier;
	double DownBarrier;

};
#endif
