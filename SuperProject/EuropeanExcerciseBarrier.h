#include "Excercise.h"
#include <vector>
#ifndef EuropeanExcerciseBarrier_H
#define EuropeanExcerciseBarrier_H
class EuropeanExcerciseBarrier:public Excercise
{
public:
	EuropeanExcerciseBarrier(const Simulation& theSimulation,const Vanilla& theVanilla);
	virtual Excercise* clone() const;
	
    virtual vector<double> Results() const;
	

	~EuropeanExcerciseBarrier(){};

private:
	
	Vanilla* theVanillaPtr;
	Simulation* thesimulationptr;

};
#endif