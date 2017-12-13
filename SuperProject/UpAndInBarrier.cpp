#include "stdafx.h"
using namespace std;
#include "UpAndInBarrier.h"

UpAndInBarrier::UpAndInBarrier(double theBarrier)
{
	this->theBarrier=theBarrier;
}


vector<double> UpAndInBarrier::operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const
{
	int summ=0;int index=0;
	for(unsigned i=0;i<StockPath.size();i++)
	{
		
		if(StockPath[i]>=this->theBarrier*exp(0.5826*sqrt(dt)*sqrt(VolatilityPath[i])))
		{
		    index=i;
			summ+=1;
			
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

 Barrier* UpAndInBarrier::clone() const
 {

	 return new UpAndInBarrier(*this);

 }