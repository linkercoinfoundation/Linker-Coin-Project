#include "stdafx.h"
#include "Pseudo_Random_Generator.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Pseudo_Random_Generator::Pseudo_Random_Generator(double seed)
{
    this->seed=seed;
}
Uniform_Generator* Pseudo_Random_Generator::clone() const
{
   return new Pseudo_Random_Generator(*this);

}



vector<vector<double>> Pseudo_Random_Generator::operator()(int numberOfPaths, int numberOfPathSteps,int numberOfFactors) const
{
  vector<vector<double>> PseudoRandomNumbers;//(numberOfPaths,numberOfPathSteps);
  for(int i=0;i<numberOfPaths;i++)
  {
	  PseudoRandomNumbers.push_back(vector<double> ());
	  for(int j=0;j<numberOfPathSteps;j++)
	  {
		  PseudoRandomNumbers[i].push_back(rand()/(static_cast<double>(RAND_MAX)));

	  }
  }
 
  return PseudoRandomNumbers;

}