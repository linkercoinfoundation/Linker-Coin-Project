#include <nr3.h>

#ifndef Regression_H
#define Regression_H
class Regression{
public:
	Regression(double value){};
	
	VecDoub regress(VecDoub Xnr,VecDoub Ynr);
	VecDoub regressPathDependent(MatDoub Xnr, VecDoub Ynr);
	VecDoub regressratevolstoc(MatDoub Xnr,VecDoub Ynr);
	VecDoub regressratevolPathDependent(MatDoub Xnr,VecDoub Ynr);
	VecDoub regressratevolPathDependentBarrier(MatDoub Xnr,VecDoub Ynr);
Regression* clone() const;
	
private:

};
#endif