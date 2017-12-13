#include "Excercise.h"
#include <vector>
#ifndef EuropeanExcercisePathDependent_H
#define EuropeanExcercisePathDependent_H
class EuropeanExcercisePathDependent:public Excercise
{
public:
	EuropeanExcercisePathDependent(const Simulation& theSimulation,const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EuropeanExcercisePathDependent(){};

private:
	
	Vanilla* theVanillaPtr;
	Simulation* thesimulationptr;

};
#endif