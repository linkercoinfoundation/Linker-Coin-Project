#include "stdafx.h"
#include "RateVasicek.h"

     RateVasicek::RateVasicek(double k,double theta,double sigma)
	 {
       this->k=k;
	   this->theta=theta;
	   this->sigma=sigma;

	 }

	  double RateVasicek::operator()(double CorrelatedNormal, double previousr,double dt) const
	 {

		 return previousr+k*(theta-previousr)*dt+sigma*sqrt(dt)*CorrelatedNormal;

	 }



	 Rate* RateVasicek::clone() const
	 {

		 return new RateVasicek(*this);

	 }
	