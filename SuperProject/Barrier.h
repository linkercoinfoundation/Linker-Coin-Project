using namespace std;
#include <vector>
#ifndef Barrier_H
#define Barrier_H
class Barrier{
public:
	Barrier(){};
	virtual vector<double> operator()(vector<double> StockPath,vector<double> VolatilityPath,double dt) const=0;
	virtual Barrier* clone() const=0;
	~Barrier(){};


private:
	

};
#endif