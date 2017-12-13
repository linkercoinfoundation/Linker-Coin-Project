#include "stdafx.h"
#include "Simulation.h"
#include "GettingGaussianByBoxMueller.h"
#include <cstdlib>
#include <ctime>
using namespace std;
#include<vector>
#include <nr3.h>
#include <cholesky.h>
Simulation::Simulation(double Vol,double r,double T,double Strike, int NumberOfPaths, int numberOfTimeInstants,double rho,double Spot, const Rate& theRate,const Volatility& theVolatility,const GettingGaussianByBoxMueller& getgaussian,const Dividend& theDividend,const PathDependency& thePathDependent,const Barrier& theBarrier,double alphaEquity,double gammaEquity,double deltaEquity)
{
	this->r=r;
	this->Vol=Vol;
	this->T=T;
	this->Strike=Strike;
	
	this->theRatePtr=theRate.clone();
	this->theVolatilityPtr=theVolatility.clone();
	this->NumberOfPaths=NumberOfPaths;
	this->numberOfTimeInstants=numberOfTimeInstants;
	this->pathdependentptr=thePathDependent.clone();
	this->rho=rho;
	this->Spot=Spot;
	this->gaussianptr=getgaussian.clone();
	this->thedividendptr=theDividend.clone();
	this->barrierptr=theBarrier.clone();
	this->alphaEquity=alphaEquity;
	this->gammaEquity=gammaEquity;	
	this->deltaEquity=deltaEquity;//the y
	this->DividendPaths.resize(this->NumberOfPaths,vector<double>(this->numberOfTimeInstants+1));
	this->RatesPaths.resize(this->NumberOfPaths,vector<double>(this->numberOfTimeInstants+1));
	this->VolatilityPaths.resize(this->NumberOfPaths,vector<double>(this->numberOfTimeInstants+1));
	this->StockPaths.resize(this->NumberOfPaths,vector<double>(this->numberOfTimeInstants+1));
	this->PathDependents.resize(this->NumberOfPaths,vector<double>(this->numberOfTimeInstants+1));
	this->shortrates.resize(this->NumberOfPaths,vector<double>(this->numberOfTimeInstants+1));
	this->BarrierDependents.resize(this->NumberOfPaths,vector<double>(this->numberOfTimeInstants+1));
	this->PathBarrierDependents.resize(this->NumberOfPaths,vector<double>(this->numberOfTimeInstants+1));
	this->IndicatorofAsian=0;
}


void Simulation::operator()()  //Returning the mean and the standard deviation
{
	double ratefactor;
	MatDoub correlation(3,3);
  correlation[0][0]=1.0;
  correlation[0][1]=rho;
  correlation[0][2]=0;
   correlation[1][0]=rho;
   correlation[1][1]=1;
   correlation[1][2]=0;
   correlation[2][0]=0;
   correlation[2][1]=0;
   correlation[2][2]=1;
	Cholesky chol(correlation);
	correlation=chol.el;	
	/*
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			cout<<chol.el[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	VecDoub CorrStd(3,1);
	VecDoub CorrelatedNormals(3,1);
	vector<double> barrierpath;
	vector<double> barrierpathdependent;
	vector<double> volatilitypath;
	
	barrierpath.resize(this->numberOfTimeInstants);
	barrierpathdependent.resize(this->numberOfTimeInstants);
	volatilitypath.resize(this->numberOfTimeInstants);
	GettingGaussianByBoxMueller getgaussian(0.0);
	CorrStd[0]=this->gaussianptr->GettingTheGaussian();		
	CorrStd[1]=this->gaussianptr->GettingTheGaussian();	
	CorrStd[2]=this->gaussianptr->GettingTheGaussian();	
	chol.elmult(CorrStd,CorrelatedNormals);
	
	/*vector<vector<double>> StockPaths(NumberOfPaths,this->numberOfTimeInstants+1);   
	vector<vector<double>>VolatilityPaths(NumberOfPaths,this->numberOfTimeInstants+1);
	vector<vector<double>> RatePaths(NumberOfPaths,this->numberOfTimeInstants+1);
	vector<vector<double>> DividendPaths(NumberOfPaths,this->numberOfTimeInstants+1);*/
	//vector<vector<vector<double>>> Paths =
		//vector<vector<vector<double>>>(this->NumberOfPaths,vector<vector<double>>(this->numberOfTimeInstants+1,vector<double>(3,0.)));
	
	for(int i=0;i<NumberOfPaths;i++)
	{
        this->setStockPaths(i,0,this->Spot);
		this->setVolatilityPaths(i,0,this->Vol);
	    this->setRatesPaths(i,0,1.0);
		this->setDividendPaths(i,0,this->deltaEquity);
		this->setPathDependents(i,0,this->Spot);
	    this->setshortrates(i,0,this->r);
		this->setPathDependents(i,0,this->Spot);
		
		
	}
	double dt=T/(static_cast<double>(numberOfTimeInstants));
	double rate;
	double vol;
	double div;
	double PathDependent;
	double rateprevious;
	for(int i=0;i<NumberOfPaths;i++)
	{
		rate=this->r;//The volatility and the rates are reset at each path!!!
		vol=this->Vol;//The volatility should be always positive
		div=this->deltaEquity;
		PathDependent=this->pathdependentptr->getpreviousVal();
	for(int j=1;j<numberOfTimeInstants+1;j++)
		{
			CorrStd[0]=this->gaussianptr->GettingTheGaussian();		
	        CorrStd[1]=this->gaussianptr->GettingTheGaussian();	
			CorrStd[2]=this->gaussianptr->GettingTheGaussian();
			chol.elmult(CorrStd,CorrelatedNormals);
			ratefactor=(alphaEquity*gammaEquity+sqrt(vol)*rate-deltaEquity*sqrt(vol))/(sqrt(vol)+gammaEquity);//vol is the square of the volatility as in Heston
			this->setStockPaths(i,j,StockPaths[i][j-1]+StockPaths[i][j-1]*((ratefactor)*dt+sqrt(vol)*sqrt(dt)*CorrelatedNormals[0]));
			PathDependent=this->pathdependentptr->operator()(StockPaths[i][j],PathDependent,j);
			this->setPathDependents(i,j,PathDependent); //For the Asian and the rest path dependent options
			this->setIndicatorOfAsian(abs(PathDependents[i][j]-StockPaths[i][j]));
			div=this->thedividendptr->operator()(CorrelatedNormals[0],div,dt,rate,StockPaths[i][j],vol);
			vol=abs(this->theVolatilityPtr->operator()(CorrelatedNormals[1],vol,dt)); //Invoking the volatility function
			rateprevious=rate;
			rate=abs(this->theRatePtr->operator()(CorrelatedNormals[2],rate,dt)); //invoking the rates' function
			this->setshortrates(i,j,(rate+rateprevious)*0.5);
			this->setVolatilityPaths(i,j,vol);//Setting the square of volatility paths
	        this->setRatesPaths(i,j, exp(-rate*dt)*RatesPaths[i][j-1] );//RatesPaths is exponential negative the integral of the rates
		    this->setDividendPaths(i,j,div);

		}
	  for(unsigned ii=1;ii<PathDependents[i].size();ii++)
	  {
	  barrierpath[ii-1]=StockPaths[i][ii];//Takes as input the stock path and applies the barrier condition check
	  barrierpathdependent[ii-1]=PathDependents[i][ii];//Takes as input the Path Dependent output (the arithmetic average for instance) and checks the barrier condition
	  //we need the volatility path to calculate the barrier adjustment
	  volatilitypath[ii-1]=VolatilityPaths[i][ii-1];//We store the previous volatility, because the volatility is calculated at the beggining of the step
	  }
	  barrierpath=this->barrierptr->operator()(barrierpath,volatilitypath,dt);
	  barrierpathdependent=this->barrierptr->operator()(barrierpathdependent,volatilitypath,dt);

	  this->setBarrierPath(barrierpath,i); //Amending the paths in case of a barrier
	  this->setPathBarrierDependents(barrierpathdependent,i);
	 // cout<<barrierpath[0]<<endl;
	    
	}
	

}


Simulation* Simulation::clone() const
{

	return new Simulation(*this);

}


vector<vector<double>> Simulation::getStockPaths() const
{
	return this->StockPaths;

}
vector<vector<double>> Simulation::getVolatilityPaths() const
{
	return this->VolatilityPaths;

}
vector<vector<double>> Simulation::getRatesPaths() const
{
	return this->RatesPaths;

}
vector<vector<double>> Simulation::getDividendPaths() const
{

	return this->DividendPaths;

}

vector<vector<double>> Simulation::getPathDependents() const
{

	return this->PathDependents;

}

vector<vector<double>> Simulation::getPathBarrierDependents() const
{

	return this->PathBarrierDependents;

}


vector<vector<double>> Simulation::getBarrierDependents() const
{

	return this->BarrierDependents;

}



vector<vector<double>> Simulation::getshortrates() const
{

	return this->shortrates;

}

void Simulation::setDividendPaths(int row,int col,double value) 
{
     DividendPaths[row][col] = value;
}

void Simulation::setVolatilityPaths(int row,int col,double value) 
{
    VolatilityPaths[row][col] = value;
}

void Simulation::setRatesPaths(int row,int col,double value)
{
    RatesPaths[row][col] = value;
}

void Simulation::setshortrates(int row,int col,double value)
{
    shortrates[row][col] = value;
}

void Simulation::setStockPaths(int row,int col,double value)
{
    StockPaths[row][col] = value;
}

void Simulation::setPathDependents(int row,int col,double value)
{
    PathDependents[row][col] = value;
}

void Simulation::setIndicatorOfAsian(double InputValue )
{

	this->IndicatorofAsian+=InputValue;
}

double Simulation::getIndicatorAsian() const
{
	return this->IndicatorofAsian;
}




void Simulation::setBarrierPath(vector<double> barrierpath,int i)
{
	for(unsigned j=0;j<PathDependents[i].size()-1;j++)
	{
		BarrierDependents[i][j+1]=barrierpath[j];

	}
}

void Simulation::setPathBarrierDependents(vector<double> barrierpath,int i)
{
	for(unsigned j=0;j<PathBarrierDependents[i].size()-1;j++)
	{
		PathBarrierDependents[i][j+1]=barrierpath[j];

	}
}