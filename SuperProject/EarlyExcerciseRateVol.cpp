#include "stdafx.h"
#include "EarlyExcerciseRateVol.h"
#include "cubicfitratevolstock.h"
#include <cstdlib>
#include <ctime>
using namespace std;
#include<vector>
#include "Regression.h"

EarlyExcerciseRateVol::EarlyExcerciseRateVol(const Simulation& theSimulation, const Vanilla& theVanilla)
{
	this->simulationptr=theSimulation.clone();
	this->theVanillaPtr=theVanilla.clone();
	
	
}



vector<double> EarlyExcerciseRateVol::Results() const
{
	//We value with PathDependents in case we have path dependency. If we are path independent, then PathDependents will have the same inputs as the StockPaths.
	Regression theregression(0.0);
	VecDoub ForExpVal(3);
	VecDoub ExpectedValue(11);
	const Doub TOL=1.e-12;
	vector<double> Results(2,1);
	this->simulationptr->operator()();
	vector<vector<double>> StockPaths=this->simulationptr->getStockPaths();
	vector<vector<double>> RatePaths=this->simulationptr->getRatesPaths();
	vector<vector<double>> VolPaths=this->simulationptr->getVolatilityPaths();
	vector<vector<double>>PathDependents=this->simulationptr->getPathDependents();
	vector<vector<double>> shortrates=this->simulationptr->getshortrates();
	double IndicatorOfAsian=this->simulationptr->getIndicatorAsian();
	vector<double> FinalValues(StockPaths.size(),1);
	double Average=0.0;
	double AverageSquare=0.0;
	vector<double> Y;//The the intrinsic payoffs
	
	vector<double> X;//The value of the Stock
	vector<double> X1; //The value of the rates
	vector<double> X2; //The value of the volatility
	vector<double> X3; // The value of the Path Dependency
	VecDoub Xnr,Ynr,SIC,A;
	MatDoub XRatesVolStock;
	double temporary;
	vector<int> MoneynessIndex;
	int sumfwd;

	
	//Evaluating the Payoff of the American Option using the Longstaff-Schwarz algorithm

	int sumfwdtimes=0;
	for(unsigned i=0;i<StockPaths.size();i++)
	{
		StockPaths[i][StockPaths[0].size()-1]=theVanillaPtr->VanillaPayoff(StockPaths[i][StockPaths[0].size()-1]);
		//cout<<"The terminal value of the path is: "<<Paths[i][Paths[0].size()-1][0]<<endl;
				
	}
	
	
	
	
	for(int time=StockPaths[0].size()-2;time>0;time--)//for every time instant
	{
					//Finding the X variable and the index (where the payoff of the current time is nonzero)
					for(unsigned pathindex=0;pathindex<StockPaths.size();pathindex++)//for every path
					{				
						if(theVanillaPtr->VanillaPayoff(StockPaths[pathindex][time])>0)
						{
							X.push_back(StockPaths[pathindex][time]);//Creates X StockPaths
							X1.push_back(shortrates[pathindex][time]);//Creates X1 rates
							X2.push_back(sqrt(VolPaths[pathindex][time]));//Creates X2 of volatility
							MoneynessIndex.push_back(pathindex);
							//creating Y
							temporary=0; //finding the temporary
							for(unsigned ftime=time+1;ftime<StockPaths[0].size();ftime++)
							{
								sumfwd=0;
								if(StockPaths[pathindex][ftime]>0)
								{
                                    temporary=StockPaths[pathindex][ftime]*RatePaths[pathindex][ftime]/RatePaths[pathindex][time];
									sumfwd+=1;
									if(sumfwd>1)
										throw("More than one non zero payoffs!");
								}

							}
							Y.push_back(temporary); //creating the Y
							//StockPaths[pathindex][time]=theVanillaPtr->VanillaPayoff(StockPaths[pathindex][time]);
						}else
						{
							StockPaths[pathindex][time]=0.0; //making zero the values at that time instant where the payoffs are not positive
						}
					}

					


					if(X.size()!=Y.size())
					{
						cout<<"This happens at time: "<<time<<endl;
						throw("The size of X is not equal to the size of Y!");
						throw("something is wrong!");
						break;
					}

				//Preparing for the regression
                
				Xnr.resize(X.size());
				Ynr.resize(Y.size());
				SIC.resize(X.size());
				A.resize(11);
				XRatesVolStock.resize(X.size(),3); //Change dimension
				if(X.size()==0)
				{
					cout<<"No moneyness at that time step"<<endl;
					for(int i=0;i<11;i++)
						A[i]=0;
				}
				else
				{
				cout<<StockPaths[MoneynessIndex[0]][time];
				

				
					for(unsigned i=0;i<Y.size();i++)
					{
                      XRatesVolStock[i][0]=X[i];//MatDoub assigning the StockValues
					  XRatesVolStock[i][1]=X1[i];//MatDoub assigning the RateValues
					  XRatesVolStock[i][2]=X2[i];//MatDoub assigning the VolatilityValues
					  Ynr[i]=Y[i];//VecDoub assigning the payoffs
					}
				

				    A=theregression.regressratevolstoc(XRatesVolStock,Ynr);
				}
					
				

					   for(int i=0;i<Xnr.size();i++)
					   {
						   //When it is optimal to exercise( if the intrinsic value is greater than the expected value
						   double intrinsicvalue=theVanillaPtr->VanillaPayoff(StockPaths[MoneynessIndex[i]][time]);
						   // need to amend for the case of stock apths as well.
						   double expectedvalue=0.0;


						   ForExpVal[0]=StockPaths[MoneynessIndex[i]][time];
						   ForExpVal[1]=shortrates[MoneynessIndex[i]][time];
						   ForExpVal[2]=VolPaths[MoneynessIndex[i]][time];
						 
						   
						   
						   ExpectedValue=cubicfitratevolstock(ForExpVal);
						   //Change this
						   expectedvalue=A[0];
						   for(int jjj=1;jjj<11;jjj++)
							   expectedvalue+=ExpectedValue[jjj]*A[jjj]; //Coefficients of regression times the orthogonal polynomial
						   /*
                             expectedvalue=A[0]+A[1]*StockPaths[MoneynessIndex[i]][time]+A[2]*shortrates[MoneynessIndex[i]][time]+A[3]*VolPaths[MoneynessIndex[i]][time];
                             expectedvalue+=A[4]*StockPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]+A[5]*shortrates[MoneynessIndex[i]][time]*shortrates[MoneynessIndex[i]][time];
							 expectedvalue+=A[6]*VolPaths[MoneynessIndex[i]][time]*VolPaths[MoneynessIndex[i]][time]+A[7]*StockPaths[MoneynessIndex[i]][time]*shortrates[MoneynessIndex[i]][time];
							 expectedvalue+=A[8]*VolPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]+A[9]*shortrates[MoneynessIndex[i]][time]*VolPaths[MoneynessIndex[i]][time];						   
							 expectedvalue+=A[10]*VolPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]*shortrates[MoneynessIndex[i]][time];						  
							*/
							 
							 if(intrinsicvalue>expectedvalue)
						   {
							   for(unsigned forwardtime=time+1;forwardtime<StockPaths[0].size();forwardtime++)
								{
                                    StockPaths[MoneynessIndex[i]][forwardtime]=0;

								}
							    StockPaths[MoneynessIndex[i]][time]=theVanillaPtr->VanillaPayoff(StockPaths[MoneynessIndex[i]][time]);

						   }
						   else
						   {
							   StockPaths[MoneynessIndex[i]][time]=0.0;//Setting zero again when there is continuation
						   }
					   }
					  
					   Xnr.resize(0);
					   Ynr.resize(0);
					   SIC.resize(0);
					   A.resize(0);
					   X.erase(X.begin(),X.end());
					   Y.erase(Y.begin(),Y.end());
					   X1.erase(X1.begin(),X1.end());
					   XRatesVolStock.resize(0,0);
					   MoneynessIndex.erase(MoneynessIndex.begin(),MoneynessIndex.end());
					   
	}
	double summ=0;
	for(unsigned i=0;i<StockPaths.size();i++)
	{
		for(unsigned j=1;j<StockPaths[0].size();j++)
		{
			summ+=StockPaths[i][j];
			StockPaths[i][j]=StockPaths[i][j]*RatePaths[i][j];//discounting
			Average+=StockPaths[i][j]/(static_cast<double>(StockPaths.size()));
			AverageSquare+=StockPaths[i][j]*StockPaths[i][j]/(static_cast<double>(StockPaths.size()));
			
		}
	}
	double value=summ/(static_cast<double>(StockPaths.size()));
	Results[0]=Average;
	Results[1]=sqrt(AverageSquare-Average*Average)/(sqrt(static_cast<double>(StockPaths.size())));
	return Results;
}


 Excercise* EarlyExcerciseRateVol::clone() const
{
	return new EarlyExcerciseRateVol(*this);
 }