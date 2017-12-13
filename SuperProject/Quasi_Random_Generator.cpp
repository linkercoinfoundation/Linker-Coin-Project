#include "stdafx.h"
#include "Quasi_Random_Generator.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Quasi_Random_Generator::Quasi_Random_Generator(double seed)
{
    this->seed=seed;
}
Uniform_Generator* Quasi_Random_Generator::clone() const
{
   return new Quasi_Random_Generator(*this);

}



vector<vector<double>> Quasi_Random_Generator::operator()(int numberOfPaths, int numberOfPathSteps,int numberOfFactors) const
{
  vector<vector<double>> QuasiRandomNumbers(numberOfPaths, vector<double>(numberOfPathSteps,0));
 
  return QuasiRandomNumbers;

}