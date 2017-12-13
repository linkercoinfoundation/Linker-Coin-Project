#include "stdafx.h"
#include "EuropeanExcerciseBarrier.h"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

#include<vector>
EuropeanExcerciseBarrier::EuropeanExcerciseBarrier(const Simulation& theSimulation,const Vanilla& theVanilla)
{
	this-> thesimulationptr=theSimulation.clone();
	this->theVanillaPtr=theVanilla.clone();
	
}




vector<double> EuropeanExcerciseBarrier::Results() const
{
	//if the option is path independent the   will simply give the stock paths
	vector<double> Results(2,1);
	this->thesimulationptr->operator()();
	vector<vector<double>> StockPaths=this->thesimulationptr->getStockPaths();
	vector<vector<double>> RatePaths=this->thesimulationptr->getRatesPaths();
	vector<vector<double>>PathDependents=this->thesimulationptr->getPathDependents();
	vector<vector<double>> BarrierPaths=this->thesimulationptr->getBarrierDependents();
	vector<double> FinalValues(PathDependents.size(),1);
	double Average=0.0;
	double AverageSquare=0.0;
	double summ=0;
	for(unsigned i=0;i<BarrierPaths.size();i++)
	{
		
		
		if(BarrierPaths[i][BarrierPaths[0].size()-1]==0)
		{
			FinalValues[i]=0;
		}
		else
		{
		FinalValues[i]=theVanillaPtr->VanillaPayoff(BarrierPaths[i][BarrierPaths[0].size()-1])*RatePaths[i][RatePaths[0].size()-1];//Getting the terminal payoff of each path
		}
		Average+=FinalValues[i]/(static_cast<double>(BarrierPaths.size()));
		AverageSquare+=FinalValues[i]*FinalValues[i]/(static_cast<double>(BarrierPaths.size()));
	}
	Results[0]=Average;
	Results[1]=sqrt(AverageSquare-Average*Average)/(sqrt(static_cast<double>(BarrierPaths.size())));
	return Results;
}

Excercise* EuropeanExcerciseBarrier::clone() const
{
	return new EuropeanExcerciseBarrier(*this);
 }