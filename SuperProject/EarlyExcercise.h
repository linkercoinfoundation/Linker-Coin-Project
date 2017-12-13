#include "Excercise.h"
#include <vector>

#ifndef EarlyExcercise_H
#define EarlyExcercise_H
class EarlyExcercise:public Excercise
{
public:
	EarlyExcercise(const Simulation& theSimulation, const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EarlyExcercise(){};

private:
	Simulation* simulationptr;
	Vanilla* theVanillaPtr;
	
};
#endif