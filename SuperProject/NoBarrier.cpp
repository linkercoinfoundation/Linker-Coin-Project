#include "stdafx.h"
using namespace std;
#include "NoBarrier.h"

NoBarrier::NoBarrier(double theBarrier)
{
	this->theBarrier=theBarrier;
}


vector<double> NoBarrier::operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const
{
	
	
   return StockPath;

}

 Barrier* NoBarrier::clone() const
 {

	 return new NoBarrier(*this);

 }