#include "Uniform_Generator.h"
using namespace std;
#include <vector>
#ifndef Stratified_Random_Generator_H
#define Stratified_Random_Generator_H
class Stratified_Random_Generator:public Uniform_Generator
{
public:
Stratified_Random_Generator(double seed);
virtual vector<vector<double>> operator()(int numberOfPaths, int numberOfPathSteps,int numberOfFactors) const;
virtual Uniform_Generator* clone() const;
~Stratified_Random_Generator(){};
private:
	double seed;
};

#endif