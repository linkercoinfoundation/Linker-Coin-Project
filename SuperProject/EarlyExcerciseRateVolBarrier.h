#include "Excercise.h"
#include <vector>

#ifndef EarlyExcerciseRateVolBarrier_H
#define EarlyExcerciseRateVolBarrier_H
class EarlyExcerciseRateVolBarrier:public Excercise
{
public:
	EarlyExcerciseRateVolBarrier(const Simulation& theSimulation, const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EarlyExcerciseRateVolBarrier(){};

private:
	Simulation* simulationptr;
	Vanilla* theVanillaPtr;

};
#endif