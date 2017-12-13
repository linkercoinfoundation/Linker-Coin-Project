#include "stdafx.h"
using namespace std;
#include "UpAndOutBarrier.h"

UpAndOutBarrier::UpAndOutBarrier(double theBarrier)
{
	this->theBarrier=theBarrier;
}


vector<double> UpAndOutBarrier::operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const
{
	int summ=0;int index;
	for(unsigned i=0;i<StockPath.size();i++)
	{
		
		if(StockPath[i]>=this->theBarrier*exp(0.5826*sqrt(dt)*sqrt(VolatilityPath[i])))
		{
		    summ+=1;
			index=i;
			break;
		}
	}
		if(summ>0)
		{
			for(unsigned i=index-1;i<StockPath.size();i++)//Changed from index to index-1
				StockPath[i]=0;
		}
	
   return StockPath;

}

 Barrier* UpAndOutBarrier::clone() const
 {

	 return new UpAndOutBarrier(*this);

 }