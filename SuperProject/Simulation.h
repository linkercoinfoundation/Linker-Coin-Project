#include "Vanilla.h"
#include "Rate.h"
#include "Volatility.h"
#include "Dividend.h"
#include "GettingGaussianByBoxMueller.h"
#include "PathDependency.h"
#include "Barrier.h"
using namespace std;
#include <vector>

#ifndef Simulation_H
#define Simulation_H
class Simulation{
public:
Simulation(double Vol,double r,double T,double Strike, int NumberOfPaths, int numberOfTimeInstants,double rho,double Spot, const Rate& theRate,const Volatility& theVolatility,const GettingGaussianByBoxMueller& getgaussian,const Dividend& theDividend,const PathDependency& thePathDependent,const Barrier& theBarrier,double alphaEquity,double gammaEquity,double deltaEquity);

void operator()(); //Returning the mean and the standard deviation

Simulation* clone() const;
vector<vector<double>> getStockPaths() const;
vector<vector<double>> getVolatilityPaths() const;
vector<vector<double>> getRatesPaths() const;
vector<vector<double>> getDividendPaths() const;
vector<vector<double>> getPathDependents() const;
vector<vector<double>> getshortrates() const; 
vector<vector<double>> getBarrierDependents() const;
vector<vector<double>> getPathBarrierDependents() const;

double getIndicatorAsian() const;

void setStockPaths(int row,int col,double value);
void setVolatilityPaths(int row,int col,double value);
void setRatesPaths(int row,int col,double value);
void setDividendPaths(int row,int col,double value);
void setPathDependents(int row,int col,double value);
void setshortrates(int row,int col,double value);
void setIndicatorOfAsian(double inputValue);
void setBarrierPath(vector<double> stockpath, int i);
void setPathBarrierDependents(vector<double> pathdependentstockpath,int i);
private:
	double Vol;
	double r;
	double T;
	double Strike;
	double IndicatorofAsian;
	Volatility* theVolatilityPtr;
	Rate* theRatePtr;
	Dividend* thedividendptr;
	double rho;	
	 int NumberOfPaths;
	int numberOfTimeInstants;
	double Spot;
	GettingGaussianByBoxMueller* gaussianptr;
	PathDependency* pathdependentptr;
	Barrier* barrierptr;
	double alphaEquity;
	double gammaEquity;
	double deltaEquity;
	vector<vector<double>> StockPaths;
	vector<vector<double>> VolatilityPaths;
	vector<vector<double>> RatesPaths; //the negative exponential integral of short rate
	vector<vector<double>> shortrates; 
	vector<vector<double>> DividendPaths;
	vector<vector<double>> PathDependents;
	vector<vector<double>> BarrierDependents;
	vector<vector<double>> PathBarrierDependents;




};
#endif