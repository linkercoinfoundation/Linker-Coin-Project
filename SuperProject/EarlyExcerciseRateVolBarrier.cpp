#include "stdafx.h"
#include "EarlyExcerciseRateVolBarrier.h"
#include <cstdlib>
#include <ctime>
using namespace std;
#include<vector>
//needs correction
#include "Regression.h"

EarlyExcerciseRateVolBarrier::EarlyExcerciseRateVolBarrier(const Simulation& theSimulation, const Vanilla& theVanilla)
{
	this->simulationptr=theSimulation.clone();
	this->theVanillaPtr=theVanilla.clone();
	
	
}



vector<double> EarlyExcerciseRateVolBarrier::Results() const
{
	//We value with BarrierDependents in case we have path dependency. If we are path independent, then BarrierDependents will have the same inputs as the StockPaths.
	Regression theregression(0.0);
	const Doub TOL=1.e-12;
	vector<double> Results(2,1);
	this->simulationptr->operator()();
	vector<vector<double>> StockPaths=this->simulationptr->getStockPaths();
	vector<vector<double>> RatePaths=this->simulationptr->getRatesPaths();
	vector<vector<double>> VolPaths=this->simulationptr->getVolatilityPaths();
	vector<vector<double>>BarrierDependents=this->simulationptr->getBarrierDependents();
	double IndicatorOfAsian=this->simulationptr->getIndicatorAsian();
	vector<double> FinalValues(StockPaths.size(),1);
	double Average=0.0;
	double AverageSquare=0.0;
	vector<double> Y;//The the intrinsic payoffs
	
	vector<double> X;//The value of the Stock
	vector<double> X1; //The value of the rates
	vector<double> X2; //The value of the volatility
	vector<double> X3; // The value of the Barrier Dependency
	VecDoub Xnr,Ynr,SIC,A;
	MatDoub XRatesVolStockBarrier;
	double temporary;
	vector<int> MoneynessIndex;
	int sumfwd;

	
	//Evaluating the Payoff of the American Option using the Longstaff-Schwarz algorithm

	int sumfwdtimes=0;
	for(unsigned i=0;i<BarrierDependents.size();i++)
	{
		BarrierDependents[i][BarrierDependents[0].size()-1]=theVanillaPtr->VanillaPayoff(BarrierDependents[i][BarrierDependents[0].size()-1]);
		//cout<<"The terminal value of the path is: "<<Paths[i][Paths[0].size()-1][0]<<endl;
				
	}
	
	
	
	
	for(int time=BarrierDependents[0].size()-2;time>0;time--)//for every time instant
	{
					//Finding the X variable and the index (where the payoff of the current time is nonzero)
					for(unsigned pathindex=0;pathindex<BarrierDependents.size();pathindex++)//for every path
					{				
						if(theVanillaPtr->VanillaPayoff(BarrierDependents[pathindex][time])>0)
						{
							X.push_back(StockPaths[pathindex][time]);//Creates X StockPaths
							X1.push_back(RatePaths[pathindex][time]);//Creates X1 rates
							X2.push_back(sqrt(VolPaths[pathindex][time]));//Creates X2 of volatility
							X3.push_back(BarrierDependents[pathindex][time]);//Creates X3 of barrier dependency
							MoneynessIndex.push_back(pathindex);
							//creating Y
							temporary=0; //finding the temporary
							for(unsigned ftime=time+1;ftime<BarrierDependents[0].size();ftime++)
							{
								sumfwd=0;
								if(BarrierDependents[pathindex][ftime]>0)
								{
                                    temporary=BarrierDependents[pathindex][ftime]*RatePaths[pathindex][ftime]/RatePaths[pathindex][time];
									sumfwd+=1;
									if(sumfwd>1)
										throw("More than one non zero payoffs!");
								}

							}
							Y.push_back(temporary); //creating the Y
							//StockPaths[pathindex][time]=theVanillaPtr->VanillaPayoff(StockPaths[pathindex][time]);
						}else
						{
							BarrierDependents[pathindex][time]=0.0; //making zero the values at that time instant where the payoffs are not positive
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
                double var=0;

				Xnr.resize(X.size());
				Ynr.resize(Y.size());
				SIC.resize(X.size());
				A.resize(20);
				XRatesVolStockBarrier.resize(X.size(),4); //Change dimension
				if(Xnr.size()==0)
				{
				   for(int indexi=0;indexi<20;indexi++)
					   A[indexi]=0.0;
				}
				else{
					cout<<BarrierDependents[MoneynessIndex[1]][time];

				
					for(unsigned i=0;i<Y.size();i++)
					{
                      XRatesVolStockBarrier[i][0]=X[i];//MatDoub assigning the StockValues
					  XRatesVolStockBarrier[i][1]=X1[i];//MatDoub assigning the RateValues
					  XRatesVolStockBarrier[i][2]=X2[i];//MatDoub assigning the VolatilityValues
					  XRatesVolStockBarrier[i][3]=X3[i];//MatDoub assigning the Barrier Dependency
					   Ynr[i]=Y[i];//VecDoub assigning the payoffs
					}
				

				    A=theregression.regressratevolPathDependent(XRatesVolStockBarrier,Ynr);
				}
				    

					   for(int i=0;i<Xnr.size();i++)
					   {
						   //When it is optimal to exercise( if the intrinsic value is greater than the expected value
						   double intrinsicvalue=theVanillaPtr->VanillaPayoff(BarrierDependents[MoneynessIndex[i]][time]);
						   // need to amend for the case of stock apths as well.
						   double expectedvalue=0.0;


						   //Change this
 expectedvalue=A[0]+A[1]*StockPaths[MoneynessIndex[i]][time]+A[2]*RatePaths[MoneynessIndex[i]][time]+A[3]*VolPaths[MoneynessIndex[i]][time]+A[4]*BarrierDependents[MoneynessIndex[i]][time];
 expectedvalue+=A[5]*StockPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]+A[6]*RatePaths[MoneynessIndex[i]][time]*RatePaths[MoneynessIndex[i]][time];
 expectedvalue+=A[7]*VolPaths[MoneynessIndex[i]][time]*VolPaths[MoneynessIndex[i]][time]+A[8]*BarrierDependents[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time]+A[9]*StockPaths[MoneynessIndex[i]][time]*RatePaths[MoneynessIndex[i]][time];
 expectedvalue+=A[10]*VolPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]+A[11]*StockPaths[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time];
 expectedvalue+=A[12]*RatePaths[MoneynessIndex[i]][time]*VolPaths[MoneynessIndex[i]][time]+A[13]*RatePaths[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time];
 expectedvalue+=A[14]*VolPaths[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time];
 expectedvalue+=A[15]*VolPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]*RatePaths[MoneynessIndex[i]][time];	
 expectedvalue+=A[16]*VolPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time];
 expectedvalue+=A[17]*BarrierDependents[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]*RatePaths[MoneynessIndex[i]][time];	
 expectedvalue+=A[18]*VolPaths[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time]*RatePaths[MoneynessIndex[i]][time];	
 expectedvalue+=A[19]*VolPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time]*RatePaths[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time];	
							 
							 
							 if(intrinsicvalue>expectedvalue)
						   {
							   for(unsigned forwardtime=time+1;forwardtime<BarrierDependents[0].size();forwardtime++)
								{
                                    BarrierDependents[MoneynessIndex[i]][forwardtime]=0;

								}
							    BarrierDependents[MoneynessIndex[i]][time]=theVanillaPtr->VanillaPayoff(BarrierDependents[MoneynessIndex[i]][time]);

						   }
						   else
						   {
							   BarrierDependents[MoneynessIndex[i]][time]=0.0;//Setting zero again when there is continuation
						   }
					   }
					  
					   Xnr.resize(0);
					   Ynr.resize(0);
					   SIC.resize(0);
					   A.resize(0);
					   X.erase(X.begin(),X.end());
					   Y.erase(Y.begin(),Y.end());
					   X1.erase(X1.begin(),X1.end());
					   XRatesVolStockBarrier.resize(0,0);
					   MoneynessIndex.erase(MoneynessIndex.begin(),MoneynessIndex.end());
					   
	}
	double summ=0;
	for(unsigned i=0;i<BarrierDependents.size();i++)
	{
		for(unsigned j=1;j<BarrierDependents[0].size();j++)
		{
			summ+=BarrierDependents[i][j];
			BarrierDependents[i][j]=BarrierDependents[i][j]*RatePaths[i][j];
			Average+=BarrierDependents[i][j]/(static_cast<double>(BarrierDependents.size()));
			AverageSquare+=BarrierDependents[i][j]*BarrierDependents[i][j]/(static_cast<double>(BarrierDependents.size()));
			
		}
	}
	double value=summ/(static_cast<double>(BarrierDependents.size()));
	Results[0]=Average;
	Results[1]=sqrt(AverageSquare-Average*Average)/(sqrt(static_cast<double>(BarrierDependents.size())));
	return Results;
}


 Excercise* EarlyExcerciseRateVolBarrier::clone() const
{
	return new EarlyExcerciseRateVolBarrier(*this);
 }