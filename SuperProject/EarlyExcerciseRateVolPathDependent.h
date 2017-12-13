#include "Excercise.h"
#include <vector>

#ifndef EarlyExcerciseRateVolPathDependent_H
#define EarlyExcerciseRateVolPathDependent_H
class EarlyExcerciseRateVolPathDependent:public Excercise
{
public:
	EarlyExcerciseRateVolPathDependent(const Simulation& theSimulation, const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EarlyExcerciseRateVolPathDependent(){};

private:
	Simulation* simulationptr;
	Vanilla* theVanillaPtr;

};
#endif