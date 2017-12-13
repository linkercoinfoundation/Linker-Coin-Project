#ifndef   GETTINGGAUSSIANBYBOXMUELLER_H
#define   GETTINGGAUSSIANBYBOXMUELLER_H
class GettingGaussianByBoxMueller{
public:
	GettingGaussianByBoxMueller(double storedValue);
	double GettingTheGaussian();
	~GettingGaussianByBoxMueller(){};
	GettingGaussianByBoxMueller* clone() const;


private:
	double storedValue;

};
#endif