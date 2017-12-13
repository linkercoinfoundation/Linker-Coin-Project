#include "stdafx.h"
#include "RateHoLee.h"

     RateHoLee::RateHoLee(double k,double theta,double sigma)
	 {
       this->k=k;
	   this->theta=theta;
	   this->sigma=sigma;

	 }

	  double RateHoLee::operator()(double CorrelatedNormal, double previousr,double dt) const
	 {

		 return previousr+theta*dt+sigma*sqrt(dt)*CorrelatedNormal;

	 }



	 Rate* RateHoLee::clone() const
	 {

		 return new RateHoLee(*this);

	 }
	
    