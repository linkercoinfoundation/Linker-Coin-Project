#include "stdafx.h"
#include "EuropeanExcercise.h"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

#include<vector>
EuropeanExcercise::EuropeanExcercise(const Simulation& theSimulation,const Vanilla& theVanilla)
{
	this-> thesimulationptr=theSimulation.clone();
	this->theVanillaPtr=theVanilla.clone();
	
}




vector<double> EuropeanExcercise::Results() const
{
	//if the option is path independent the PathDependents will simply give the stock paths
	vector<double> Results(2,1);
	this->thesimulationptr->operator()();
	vector<vector<double>> StockPaths=this->thesimulationptr->getStockPaths();
	vector<vector<double>> RatePaths=this->thesimulationptr->getRatesPaths();
	vector<vector<double>>PathDependents=this->thesimulationptr->getPathDependents();
	vector<double> FinalValues(PathDependents.size(),1);
	double Average=0.0;
	double AverageSquare=0.0;
	
	for(unsigned i=0;i<PathDependents.size();i++)
	{
		FinalValues[i]=PathDependents[i][PathDependents[0].size()-1];
		FinalValues[i]=theVanillaPtr->VanillaPayoff(FinalValues[i])*RatePaths[i][RatePaths[0].size()-1];//Getting the terminal payoff of each path
		Average+=FinalValues[i]/(static_cast<double>(PathDependents.size()));
		AverageSquare+=FinalValues[i]*FinalValues[i]/(static_cast<double>(PathDependents.size()));
	}
	Results[0]=Average;
	Results[1]=sqrt(AverageSquare-Average*Average)/(sqrt(static_cast<double>(PathDependents.size())));
	return Results;
}

Excercise* EuropeanExcercise::clone() const
{
	return new EuropeanExcercise(*this);
 }