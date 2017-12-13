#include "stdafx.h"
#include "RateHWCIR.h"

     RateHWCIR::RateHWCIR(double k,double theta,double sigma)
	 {
       this->k=k;
	   this->theta=theta;
	   this->sigma=sigma;

	 }

	  double RateHWCIR::operator()(double CorrelatedNormal, double previousr,double dt) const
	 {

		 return previousr+k*(theta-previousr)*dt+sigma*sqrt(previousr)*sqrt(dt)*CorrelatedNormal;

	 }



	 Rate* RateHWCIR::clone() const
	 {

		 return new RateHWCIR(*this);

	 }
	