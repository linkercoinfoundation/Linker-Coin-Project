#ifndef Uniform_Generator_H
#define Uniform_Generator_H
using namespace std;
#include <vector>
class Uniform_Generator
{
public:
Uniform_Generator(){};
virtual vector<vector<double>> operator()(int numberOfPaths, int numberOfPathSteps,int numberOfFactors) const=0;
virtual Uniform_Generator* clone() const=0;
~Uniform_Generator(){};
private:
	double seed;

};

#endif