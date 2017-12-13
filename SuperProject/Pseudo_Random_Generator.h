#include "Uniform_Generator.h"
using namespace std;
#include <vector>
#ifndef Pseudo_Random_Generator_H
#define Pseudo_Random_Generator_H
class Pseudo_Random_Generator:public Uniform_Generator
{
public:
Pseudo_Random_Generator(double seed);
virtual vector<vector<double>> operator()(int numberOfPaths, int numberOfPathSteps,int numberOfFactors) const;
virtual Uniform_Generator* clone() const;
~Pseudo_Random_Generator(){};
private:
	double seed;

};

#endif