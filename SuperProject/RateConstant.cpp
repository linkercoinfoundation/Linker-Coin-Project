#include "stdafx.h"
#include "RateConstant.h"
#include <cmath>
     RateConstant::RateConstant(double k,double theta,double sigma)
	 {
       this->k=k;
	   this->theta=theta;
	   this->sigma=sigma;

	 }

	  double RateConstant::operator()(double CorrelatedNormal, double previousr,double dt) const
	 {

		 return previousr;

	 }



	 Rate* RateConstant::clone() const
	 {

		 return new RateConstant(*this);

	 }