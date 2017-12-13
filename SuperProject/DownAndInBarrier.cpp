#include "stdafx.h"
using namespace std;
#include "DownAndInBarrier.h"
#include <cmath>

DownAndInBarrier::DownAndInBarrier(double theBarrier)
{
	this->theBarrier=theBarrier;
}


vector<double> DownAndInBarrier::operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const
{
	int summ=0; int index=0;
	for(unsigned i=0;i<StockPath.size();i++)
	{
		if(StockPath[i]<=this->theBarrier*exp(-0.5826*sqrt(dt)*sqrt(VolatilityPath[i])))
		{
		    summ+=1;
			index=i;
			
		}
	}
		if(summ==0)
		{
			for(unsigned i=0;i<StockPath.size();i++)
				StockPath[i]=0;
		}else
		{
           for(int i=0;i<index;i++)
			   StockPath[i]=0;

		}
	
   return StockPath;

}

 Barrier* DownAndInBarrier::clone() const
 {

	 return new DownAndInBarrier(*this);

 }