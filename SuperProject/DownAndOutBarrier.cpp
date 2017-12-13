#include "stdafx.h"
using namespace std;
#include "DownAndOutBarrier.h"
#include <cmath>

DownAndOutBarrier::DownAndOutBarrier(double theBarrier)
{
	this->theBarrier=theBarrier;
}


vector<double> DownAndOutBarrier::operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const
{
	int summ=0;int index=0;
	for(unsigned i=0;i<StockPath.size();i++)
	{
		summ=0;
		if(StockPath[i]<=this->theBarrier*exp(-0.5826*sqrt(dt)*sqrt(VolatilityPath[i]))) //*exp(-0.5826*sqrt(dt)*VolatilityPath[i])
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

 Barrier* DownAndOutBarrier::clone() const
 {

	 return new DownAndOutBarrier(*this);

 }