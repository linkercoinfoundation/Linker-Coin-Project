#include "Simulation.h"
#include "Vanilla.h"


using namespace std;

#ifndef Excercise_H
#define Excercise_H
class Excercise
{
public:
	Excercise(){};
	virtual Excercise* clone() const=0;
	
	virtual vector<double> Results() const=0;
	~Excercise(){};

private:
	Simulation* simulationptr;
	Vanilla* theVanillaPtr;
	

};
#endif