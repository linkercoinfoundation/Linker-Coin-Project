#ifndef Volatility_H
#define Volatility_H
class Volatility{
public:
	Volatility(){};
	virtual double operator()(double CorrelatedNormal, double previousVol,double dt) const=0;
	virtual Volatility* clone() const=0;
	~Volatility(){};


private:
	double gamma;
	double theta;
	double k;

};
#endif