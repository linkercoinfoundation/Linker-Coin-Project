#include "stdafx.h"
#include "Stratified_Random_Generator.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Stratified_Random_Generator::Stratified_Random_Generator(double seed)
{
    this->seed=seed;
}
Uniform_Generator* Stratified_Random_Generator::clone() const
{
   return new Stratified_Random_Generator(*this);

}



vector<vector<double>> Stratified_Random_Generator::operator()(int numberOfPaths, int numberOfPathSteps,int numberOfFactors) const
{
  vector<vector<double>> StratifiedRandomNumbers(numberOfPaths, vector<double>(numberOfPathSteps,0));
 
  return StratifiedRandomNumbers;

}