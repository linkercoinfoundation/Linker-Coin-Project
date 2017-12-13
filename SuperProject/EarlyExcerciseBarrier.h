#include "Excercise.h"
#include <vector>

#ifndef EarlyExcerciseBarrier_H
#define EarlyExcerciseBarrier_H
class EarlyExcerciseBarrier:public Excercise
{
public:
	EarlyExcerciseBarrier(const Simulation& theSimulation, const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EarlyExcerciseBarrier(){};

private:
	Simulation* simulationptr;
	Vanilla* theVanillaPtr;

};
#endif