#include "Excercise.h"
#include <vector>

#ifndef EarlyExcerciseRateVol_H
#define EarlyExcerciseRateVol_H
class EarlyExcerciseRateVol:public Excercise
{
public:
	EarlyExcerciseRateVol(const Simulation& theSimulation, const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EarlyExcerciseRateVol(){};

private:
	Simulation* simulationptr;
	Vanilla* theVanillaPtr;

};
#endif