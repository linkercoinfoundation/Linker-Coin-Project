#include "Excercise.h"
#include <vector>

#ifndef EarlyExcercisePathDependent_H
#define EarlyExcercisePathDependent_H
class EarlyExcercisePathDependent:public Excercise
{
public:
	EarlyExcercisePathDependent(const Simulation& theSimulation, const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EarlyExcercisePathDependent(){};

private:
	Simulation* simulationptr;
	Vanilla* theVanillaPtr;

};
#endif