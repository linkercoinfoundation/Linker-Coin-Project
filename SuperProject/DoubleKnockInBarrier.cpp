#include "stdafx.h"
using namespace std;
#include "DoubleKnockInBarrier.h"

DoubleKnockInBarrier::DoubleKnockInBarrier(double UpBarrier,double DownBarrier)
{
	this->UpBarrier=UpBarrier;
	this->DownBarrier=DownBarrier;

}


vector<double> DoubleKnockInBarrier::operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const
{
	int summ=0;int index=0;
	for(unsigned i=0;i<StockPath.size();i++)
	{
		
		if(StockPath[i]<=this->DownBarrier*exp(-0.5826*sqrt(dt)*sqrt(VolatilityPath[i]))|| StockPath[i]>=this->UpBarrier*exp(0.5826*sqrt(dt)*sqrt(VolatilityPath[i])))
		{
		    summ+=1;
			index=i;
			break;
		}
	}
		if(summ==0)
		{
			for(unsigned i=0;i<StockPath.size();i++)
				StockPath[i]=0;
		}
		else
		{
			for(int i=0;i<index;i++)
				StockPath[i]=0;
		}
	
   return StockPath;

}

 Barrier* DoubleKnockInBarrier::clone() const
 {

	 return new DoubleKnockInBarrier(*this);

 }