#include "stdafx.h"
#include "GettingGaussianByBoxMueller.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
GettingGaussianByBoxMueller::GettingGaussianByBoxMueller(double storedValue)
{

	this->storedValue=0.0;
	srand((unsigned)time(NULL));

}

double GettingGaussianByBoxMueller::GettingTheGaussian()
{
	double R;
	double u;
	double v;
	do{
	 u=2*rand()/(static_cast<double>(RAND_MAX))-1.0;
	 v=2*rand()/(static_cast<double>(RAND_MAX))-1.0;
	 R=u*u+v*v;}while(R>=1||R==0);
	 return sqrt(-2*log(R))*u/sqrt(R);

}

GettingGaussianByBoxMueller* GettingGaussianByBoxMueller::clone() const
{

	return new GettingGaussianByBoxMueller(*this);

}