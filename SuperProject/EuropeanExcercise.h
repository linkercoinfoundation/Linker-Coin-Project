#include "Excercise.h"
#include <vector>
#ifndef EuropeanExcercise_H
#define EuropeanExcercise_H
class EuropeanExcercise:public Excercise
{
public:
	EuropeanExcercise(const Simulation& theSimulation,const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EuropeanExcercise(){};

private:
	
	Vanilla* theVanillaPtr;
	Simulation* thesimulationptr;

};
#endif