#ifndef Dividend_H
#define Dividend_H
class Dividend{
public:
	Dividend(){};
	virtual double operator()(double EquityNormal, double previousDividend,double dt,double rate,double Stock,double Vol) const=0;
	virtual Dividend* clone() const=0;
	~Dividend(){};


private:
	double alphaEquity;
	double gammaEquity;
	double deltaEquity;
	

};
#endif