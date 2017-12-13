#include "stdafx.h"
#include "RateBDT.h"

     RateBDT::RateBDT(double k,double theta,double sigma)
	 {
       this->k=k;
	   this->theta=theta;
	   this->sigma=sigma;

	 }

	  double RateBDT::operator()(double CorrelatedNormal, double previousr,double dt) const
	 {

		 return previousr+theta*previousr*dt+sigma*(previousr)*sqrt(dt)*CorrelatedNormal;

	 }



	 Rate* RateBDT::clone() const
	 {

		 return new RateBDT(*this);

	 }
	