// SuperProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "GettingGaussianByBoxMueller.h"
#include "Payoff.h"
#include "PayoffCall.h"
#include "PayoffPut.h"
#include "Vanilla.h"


#include "Excercise.h"

#include "EuropeanExcercise.h"
#include "EuropeanExcerciseBarrier.h"
#include "EuropeanExcercisePathDependent.h"
#include "EuropeanExcerciseBarrierPathDependent.h"

#include "EarlyExcercise.h"
#include "EarlyExcercisePathDependent.h"
#include "EarlyExcerciseRateVol.h"
#include "EarlyExcerciseRateVolPathDependent.h"
#include "EarlyExcerciseBarrier.h"
#include "EarlyExcerciseRateVolBarrier.h"
#include "EarlyExcerciseRateVolPathDependentBarrier.h"

#include "Volatility.h"
#include "Rate.h"
#include "RateBDT.h"
#include "RateCIR.h"
#include "RateConstant.h"
#include "RateHoLee.h"
#include "RateHWCIR.h"
#include "RateHWVasicek.h"
#include "RateVasicek.h"
#include "HestonVolatility.h"
#include "ConstantVolatility.h"
#include "Dividend.h"
#include "ConstantDividend.h"
#include "LognormalDividend.h"


#include "Simulation.h"


#include "PathDependency.h"
#include "PathIndependent.h"
#include "ArithmeticAsian.h"
#include "GeometricAsian.h"
#include "Barrier.h"
#include "NoBarrier.h"
#include "UpAndOutBarrier.h"
#include "UpAndInBarrier.h"
#include "DownAndInBarrier.h"
#include "DownAndOutBarrier.h"
#include "DoubleKnockInBarrier.h"
#include "DoubleKnockOutBarrier.h"

using namespace std;
int main()
{
	/*
	//Finding American Put Option with stochastic rate and stochastic volatility
	double Spot=100;double Strike=90; double Vol=0.09; 	double r=0.04;double T=0.5;
	int NumberOfPaths=1e4;int numberOfPathSteps=50;
	double deltaEquity=0.00;double alphaEquity=0.0;	double gammaEquity=0.0;	double rho=-0.26;	
	PayoffPut thepayoff(Strike);Vanilla myVanilla(thepayoff);
	//Volatility model parameters
	double thetaVol=0.03;double kVol=1.58;double gammaVol=0.2;
	//Rate model parameters
	double thetaRate=0.04;double kRate=0.26;double sigmaRate=0.08;
	RateCIR myrate(kRate,thetaRate,sigmaRate);HestonVolatility myvol(gammaVol,thetaVol,kVol);
	GettingGaussianByBoxMueller getgaussian(0.0); 
	ConstantDividend thedividend(alphaEquity, gammaEquity, deltaEquity);
	PathIndependent pathdependency(0.0);NoBarrier mybarrier(85.0);
	
	Simulation mysim(Vol,r,T,Strike,NumberOfPaths,numberOfPathSteps,rho,Spot,myrate,myvol,getgaussian,thedividend,pathdependency,mybarrier,alphaEquity,gammaEquity,deltaEquity);
	EarlyExcerciseRateVol MyOption(mysim,myVanilla );
	*/
	
	/*
	//Finding a European call option with Stochastic Volatility
	 
	    double Spot=100;double Strike=105; double Vol=0.04; 	double r=0.06;double T=0.5;
	int NumberOfPaths=1e4;int numberOfPathSteps=50;
	double deltaEquity=0.02;double alphaEquity=0.0;	double gammaEquity=0.0;	double rho=0.5;	
	PayoffCall thepayoff(Strike);Vanilla myVanilla(thepayoff);
	//Volatility model parameters
	double thetaVol=0.0625;double kVol=0.5;double gammaVol=0.3;
	//Rate model parameters
	double thetaRate=0.00;double kRate=0.00;double sigmaRate=0.00;
	RateConstant myrate(kRate,thetaRate,sigmaRate);HestonVolatility myvol(gammaVol,thetaVol,kVol);
	GettingGaussianByBoxMueller getgaussian(0.0); 
	ConstantDividend thedividend(alphaEquity, gammaEquity, deltaEquity);
	PathIndependent pathdependency(0.0);NoBarrier mybarrier(85.0);
	
	Simulation mysim(Vol,r,T,Strike,NumberOfPaths,numberOfPathSteps,rho,Spot,myrate,myvol,getgaussian,thedividend,pathdependency,mybarrier,alphaEquity,gammaEquity,deltaEquity);
	EuropeanExcercise MyOption(mysim,myVanilla );
	*/

	/*
	//Finding an European Asian call with constant parameters
	 double Spot=100;double Strike=90; double Vol=0.04; 	double r=0.15;double T=1.0;
	int NumberOfPaths=1e4;int numberOfPathSteps=50;
	double deltaEquity=0.00;double alphaEquity=0.0;	double gammaEquity=0.0;	double rho=0.0;	
	PayoffCall thepayoff(Strike);Vanilla myVanilla(thepayoff);
	//Volatility model parameters
	double thetaVol=0.00;double kVol=0.0;double gammaVol=0.0;
	//Rate model parameters
	double thetaRate=0.00;double kRate=0.00;double sigmaRate=0.00;
	RateConstant myrate(kRate,thetaRate,sigmaRate);ConstantVolatility myvol(gammaVol,thetaVol,kVol);
	GettingGaussianByBoxMueller getgaussian(0.0); 
	ConstantDividend thedividend(alphaEquity, gammaEquity, deltaEquity);
	ArithmeticAsian pathdependency(0.0);NoBarrier mybarrier(85.0);
	Simulation mysim(Vol,r,T,Strike,NumberOfPaths,numberOfPathSteps,rho,Spot,myrate,myvol,getgaussian,thedividend,pathdependency,mybarrier,alphaEquity,gammaEquity,deltaEquity);
	EuropeanExcercisePathDependent MyOption(mysim,myVanilla );
	vector<double> theResults=MyOption.Results();
	*/

	/*
	//Finding an American Asian call with constant parameters
	 double Spot=100;double Strike=95; double Vol=0.04; 	double r=0.1;double T=0.25;
	int NumberOfPaths=1e4;int numberOfPathSteps=50;
	double deltaEquity=0.00;double alphaEquity=0.0;	double gammaEquity=0.0;	double rho=0.0;	
	PayoffCall thepayoff(Strike);Vanilla myVanilla(thepayoff);
	//Volatility model parameters
	double thetaVol=0.00;double kVol=0.0;double gammaVol=0.0;
	//Rate model parameters
	double thetaRate=0.00;double kRate=0.00;double sigmaRate=0.00;
	RateConstant myrate(kRate,thetaRate,sigmaRate);ConstantVolatility myvol(gammaVol,thetaVol,kVol);
	GettingGaussianByBoxMueller getgaussian(0.0); 
	ConstantDividend thedividend(alphaEquity, gammaEquity, deltaEquity);
	ArithmeticAsian pathdependency(0.0);NoBarrier mybarrier(85.0);
	Simulation mysim(Vol,r,T,Strike,NumberOfPaths,numberOfPathSteps,rho,Spot,myrate,myvol,getgaussian,thedividend,pathdependency,mybarrier,alphaEquity,gammaEquity,deltaEquity);
	EarlyExcercisePathDependent MyOption(mysim,myVanilla );
	vector<double> theResults=MyOption.Results();
	*/
	/*
	//Finding a European Up and Out Call Barrier Option
	double Spot=110;double Strike=100; double Vol=0.09; 	double r=0.1;double T=0.2;double UpBarrier=155;
	int NumberOfPaths=1e4;int numberOfPathSteps=50;
	double deltaEquity=0.00;double alphaEquity=0.0;	double gammaEquity=0.0;	double rho=0.0;	
	PayoffCall thepayoff(Strike);Vanilla myVanilla(thepayoff);
	//Volatility model parameters
	double thetaVol=0.00;double kVol=0.0;double gammaVol=0.0;
	//Rate model parameters
	double thetaRate=0.00;double kRate=0.00;double sigmaRate=0.00;
	RateConstant myrate(kRate,thetaRate,sigmaRate);ConstantVolatility myvol(gammaVol,thetaVol,kVol);
	GettingGaussianByBoxMueller getgaussian(0.0); 
	ConstantDividend thedividend(alphaEquity, gammaEquity, deltaEquity);
	PathIndependent pathdependency(0.0);UpAndOutBarrier mybarrier(UpBarrier);//DownAndInBarrier mybarrier(DownBarrier);
	Simulation mysim(Vol,r,T,Strike,NumberOfPaths,numberOfPathSteps,rho,Spot,myrate,myvol,getgaussian,thedividend,pathdependency,mybarrier,alphaEquity,gammaEquity,deltaEquity);
	EuropeanExcerciseBarrier MyOption(mysim,myVanilla);
	vector<double> theResults=MyOption.Results();
	*/


	/*
	//Finding an European Up and Out Put Barrier Option  //5.18
	double Spot=40;double Strike=45; double Vol=0.04; 	double r=0.0488;double T=1.0;double UpBarrier=50;
	int NumberOfPaths=1e4;int numberOfPathSteps=50;
	double deltaEquity=0.00;double alphaEquity=0.0;	double gammaEquity=0.0;	double rho=0.0;	
	PayoffPut thepayoff(Strike);Vanilla myVanilla(thepayoff);
	//Volatility model parameters
	double thetaVol=0.00;double kVol=0.0;double gammaVol=0.0;
	//Rate model parameters
	double thetaRate=0.00;double kRate=0.00;double sigmaRate=0.00;
	RateConstant myrate(kRate,thetaRate,sigmaRate);ConstantVolatility myvol(gammaVol,thetaVol,kVol);
	GettingGaussianByBoxMueller getgaussian(0.0); 
	ConstantDividend thedividend(alphaEquity, gammaEquity, deltaEquity);
	PathIndependent pathdependency(0.0);UpAndOutBarrier mybarrier(UpBarrier);//DownAndInBarrier mybarrier(DownBarrier);
	Simulation mysim(Vol,r,T,Strike,NumberOfPaths,numberOfPathSteps,rho,Spot,myrate,myvol,getgaussian,thedividend,pathdependency,mybarrier,alphaEquity,gammaEquity,deltaEquity);
	EuropeanExcerciseBarrier MyOption(mysim,myVanilla);
	vector<double> theResults=MyOption.Results();
	*/
     
     
     //Finding an American Up and Out Put Barrier Option  //5.38
	double Spot=40.0;double Strike=45.0; double Vol=0.04; 
	double r=0.0488;double T=1.0;double UpBarrier=50;
	int NumberOfPaths=(int)1e4;int numberOfPathSteps=50;
	double deltaEquity=0.00;double alphaEquity=0.0;	double gammaEquity=0.0;	double rho=0.0;	
	
	//Volatility model parameters
	//Volatility model parameters
	double thetaVol=0.0625;double kVol=0.5;double gammaVol=0.3;
	//double thetaVol=0.00;double kVol=0.0;double gammaVol=0.0;
	//Rate model parameters
	double thetaRate=0.00;double kRate=0.00;double sigmaRate=0.00;


	
	PayoffPut thepayoff(Strike); Vanilla myVanilla(thepayoff);
	
	RateConstant myrate(kRate,thetaRate,sigmaRate);//ConstantVolatility myvol(gammaVol,thetaVol,kVol);
	HestonVolatility myvol(gammaVol,thetaVol,kVol);
	GettingGaussianByBoxMueller getgaussian(0.0); 
	ConstantDividend thedividend(alphaEquity, gammaEquity, deltaEquity);
	
	PathIndependent pathdependency(0.0);UpAndOutBarrier mybarrier(UpBarrier);//DownAndInBarrier mybarrier(DownBarrier);
   /*
	Simulation mysim(Vol,r,T,Strike,NumberOfPaths,numberOfPathSteps,rho,Spot,myrate,myvol,getgaussian,thedividend,pathdependency,mybarrier,alphaEquity,gammaEquity,deltaEquity);
	EarlyExcerciseBarrier MyOption(mysim,myVanilla);
	vector<double> theResults=MyOption.Results();
	cout<<"The value of the option is: "<<theResults[0]<<endl;
	cout<<"The standard deviation is: "<<theResults[1]<<endl;
	*/
	cout << "Manos" << endl;
	system("pause");
	
	return 0;
}

