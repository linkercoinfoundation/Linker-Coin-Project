#include "stdafx.h"
#include "RateHWVasicek.h"

     RateHWVasicek::RateHWVasicek(double k,double theta,double sigma)
	 {
       this->k=k;
	   this->theta=theta;
	   this->sigma=sigma;

	 }

	  double RateHWVasicek::operator()(double CorrelatedNormal, double previousr,double dt) const
	 {

		 return previousr+k*(theta-previousr)*dt+sigma*sqrt(previousr)*sqrt(dt)*CorrelatedNormal;

	 }



	 Rate* RateHWVasicek::clone() const
	 {

		 return new RateHWVasicek(*this);

	 }
	