#include "Barrier.h"
#ifndef DoubleKnockOutBarrier_H
#define DoubleKnockOutBarrier_H
class DoubleKnockOutBarrier:public Barrier
{
public:
	DoubleKnockOutBarrier(double UpBarrier,double DownBarrier);
	virtual vector<double> operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const;
	virtual Barrier* clone() const;
	~DoubleKnockOutBarrier(){};

private:
	double UpBarrier;
	double DownBarrier;

};
#endif
