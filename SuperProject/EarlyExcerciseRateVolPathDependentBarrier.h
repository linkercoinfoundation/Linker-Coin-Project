#include "Excercise.h"
#include <vector>

#ifndef EarlyExcerciseRateVolPathDependentBarrier_H
#define EarlyExcerciseRateVolPathDependentBarrier_H
class EarlyExcerciseRateVolPathDependentBarrier:public Excercise
{
public:
	EarlyExcerciseRateVolPathDependentBarrier(const Simulation& theSimulation, const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EarlyExcerciseRateVolPathDependentBarrier(){};

private:
	Simulation* simulationptr;
	Vanilla* theVanillaPtr;

};
#endif