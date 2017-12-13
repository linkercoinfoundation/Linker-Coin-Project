#include "stdafx.h"
using namespace std;
#include "DoubleKnockOutBarrier.h"

DoubleKnockOutBarrier::DoubleKnockOutBarrier(double UpBarrier,double DownBarrier)
{
	this->UpBarrier=UpBarrier;
	this->DownBarrier=DownBarrier;

}


vector<double> DoubleKnockOutBarrier::operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const
{
	int summ=0;int index;
	for(unsigned i=0;i<StockPath.size();i++)
	{
		summ=0;index=0;
		if(StockPath[i]<=this->DownBarrier*exp(-0.5826*sqrt(dt)*sqrt(VolatilityPath[i]))|| StockPath[i]>=this->UpBarrier*exp(0.5826*sqrt(dt)*sqrt(VolatilityPath[i])))
		{
		    summ+=1;
			index=i;
			break;
		}
	}
		if(summ>0)
		{
			for(unsigned i=index;i<StockPath.size();i++)
				StockPath[i]=0;
		}
	
   return StockPath;

}

 Barrier* DoubleKnockOutBarrier::clone() const
 {

	 return new DoubleKnockOutBarrier(*this);

 }