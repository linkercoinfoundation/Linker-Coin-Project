#include "Uniform_Generator.h"
using namespace std;
#include <vector>
#ifndef Quasi_Random_Generator_H
#define Quasi_Random_Generator_H
class Quasi_Random_Generator:public Uniform_Generator
{
public:
Quasi_Random_Generator(double seed);
virtual vector<vector<double>> operator()(int numberOfPaths, int numberOfPathSteps,int numberOfFactors) const;
virtual Uniform_Generator* clone() const;
~Quasi_Random_Generator(){};
private:
	double seed;
};

#endif