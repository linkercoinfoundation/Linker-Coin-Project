#include "stdafx.h"
#include "RateCIR.h"
#include <cmath>
     RateCIR::RateCIR(double k,double theta,double sigma)
	 {
       this->k=k;
	   this->theta=theta;
	   this->sigma=sigma;

	 }

	  double RateCIR::operator()(double CorrelatedNormal, double previousr,double dt) const
	 {

		 return previousr+k*(theta-previousr)*dt+sigma*sqrt(previousr)*sqrt(dt)*CorrelatedNormal;

	 }



	 Rate* RateCIR::clone() const
	 {

		 return new RateCIR(*this);

	 }
	