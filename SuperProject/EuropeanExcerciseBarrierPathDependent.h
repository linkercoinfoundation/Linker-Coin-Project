#include "Excercise.h"
#include <vector>
#ifndef EuropeanExcerciseBarrierPathDependent_H
#define EuropeanExcerciseBarrierPathDependent_H
class EuropeanExcerciseBarrierPathDependent:public Excercise
{
public:
	EuropeanExcerciseBarrierPathDependent(const Simulation& theSimulation,const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EuropeanExcerciseBarrierPathDependent(){};

private:
	
	Vanilla* theVanillaPtr;
	Simulation* thesimulationptr;

};
#endif