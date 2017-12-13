#include "stdafx.h"
#include "EarlyExcerciseRateVolPathDependentBarrier.h"
#include "cubicfitratevolstockpathdependentbarrier.h"
#include <cstdlib>
#include <ctime>
using namespace std;
#include<vector>
//needs correction
#include "Regression.h"

EarlyExcerciseRateVolPathDependentBarrier::EarlyExcerciseRateVolPathDependentBarrier(const Simulation& theSimulation, const Vanilla& theVanilla)
{
	this->simulationptr=theSimulation.clone();
	this->theVanillaPtr=theVanilla.clone();
	
	
}



vector<double> EarlyExcerciseRateVolPathDependentBarrier::Results() const
{
	//We value with BarrierDependents in case we have path dependency. If we are path independent, then BarrierDependents will have the same inputs as the StockPaths.
	Regression theregression(0.0);
	VecDoub ForExpVal(6);
	VecDoub ExpectedValue(67);
	const Doub TOL=1.e-12;
	vector<double> Results(2,1);
	this->simulationptr->operator()();
	vector<vector<double>> StockPaths=this->simulationptr->getStockPaths();
	vector<vector<double>> RatePaths=this->simulationptr->getRatesPaths();
	vector<vector<double>> VolPaths=this->simulationptr->getVolatilityPaths();
	vector<vector<double>> BarrierDependents=this->simulationptr->getBarrierDependents();
	vector<vector<double>> PathDependents=this->simulationptr->getPathDependents();
	vector<vector<double>> PathBarrierDependents=this->simulationptr->getPathBarrierDependents();
	double IndicatorOfAsian=this->simulationptr->getIndicatorAsian();
	vector<double> FinalValues(StockPaths.size(),1);
	double Average=0.0;
	double AverageSquare=0.0;
	vector<double> Y;//The the intrinsic payoffs
	
	vector<double> X;//The value of the Stock
	vector<double> X1; //The value of the rates
	vector<double> X2; //The value of the volatility
	vector<double> X3; // The value of the Barrier Dependency
	vector<double> X4; //The value of the Path Dependency
	vector<double> X5; //The value of the Path Barrier Dependency
	VecDoub Xnr,Ynr,SIC,A;
	MatDoub XRatesVolStockPathDependentBarrier;
	double temporary;
	vector<int> MoneynessIndex;
	int sumfwd;

	
	//Evaluating the Payoff of the American Option using the Longstaff-Schwarz algorithm

	int sumfwdtimes=0;
	for(unsigned i=0;i<PathBarrierDependents.size();i++)
	{
		PathBarrierDependents[i][PathBarrierDependents[0].size()-1]=theVanillaPtr->VanillaPayoff(PathBarrierDependents[i][PathBarrierDependents[0].size()-1]);
		//cout<<"The terminal value of the path is: "<<Paths[i][Paths[0].size()-1][0]<<endl;
				
	}
	
	
	
	
	for(int time=PathBarrierDependents[0].size()-2;time>0;time--)//for every time instant
	{
					//Finding the X variable and the index (where the payoff of the current time is nonzero)
					for(unsigned pathindex=0;pathindex<PathBarrierDependents.size();pathindex++)//for every path
					{				
						if(theVanillaPtr->VanillaPayoff(PathBarrierDependents[pathindex][time])>0)
						{
							X.push_back(StockPaths[pathindex][time]);//Creates X Stock Paths
							X1.push_back(RatePaths[pathindex][time]);//Creates X1 rates
							X2.push_back(sqrt(VolPaths[pathindex][time]));//Creates X2 of volatility
							X3.push_back(BarrierDependents[pathindex][time]);//Creates X3 of barrier dependency
							X4.push_back(PathDependents[pathindex][time]); //Creates X4 of path dependency
							X5.push_back(PathBarrierDependents[pathindex][time]); // Creates X5 of path barrier (barrier on the path) dependency
							MoneynessIndex.push_back(pathindex);
							//creating Y
							temporary=0; //finding the temporary
							for(unsigned ftime=time+1;ftime<PathBarrierDependents[0].size();ftime++)
							{
								sumfwd=0;
								if(PathBarrierDependents[pathindex][ftime]>0)
								{
                                    temporary=PathBarrierDependents[pathindex][ftime]*RatePaths[pathindex][ftime]/RatePaths[pathindex][time];
									sumfwd+=1;
									if(sumfwd>1)
										throw("More than one non zero payoffs!");
								}

							}
							Y.push_back(temporary); //creating the Y
							//PathBarrierDependents[pathindex][time]=theVanillaPtr->VanillaPayoff(PathBarrierDependents[pathindex][time]);
						}else
						{
							PathBarrierDependents[pathindex][time]=0.0; //making zero the values at that time instant where the payoffs are not positive
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
				XRatesVolStockPathDependentBarrier.resize(X.size(),6); //Change dimension
				if(Xnr.size()==0)
				{
				   for(int indexi=0;indexi<67;indexi++)
					   A[indexi]=0.0;
				}
				else{
					cout<<PathBarrierDependents[MoneynessIndex[1]][time];

				
					for(unsigned i=0;i<Y.size();i++)
					{
                      XRatesVolStockPathDependentBarrier[i][0]=X[i];//MatDoub assigning the StockValues
					  XRatesVolStockPathDependentBarrier[i][1]=X1[i];//MatDoub assigning the RateValues
					  XRatesVolStockPathDependentBarrier[i][2]=X2[i];//MatDoub assigning the VolatilityValues
					  XRatesVolStockPathDependentBarrier[i][3]=X3[i];//MatDoub assigning the Barrier Dependency
					  XRatesVolStockPathDependentBarrier[i][4]=X4[i];//MatDoub assigning the Path Dependency
					  XRatesVolStockPathDependentBarrier[i][5]=X5[i];//MatDoub assigning the Path Barrier Dependency
					   Ynr[i]=Y[i];//VecDoub assigning the payoffs
					}
				

				    A=theregression.regressratevolPathDependent(XRatesVolStockPathDependentBarrier,Ynr);
				}
				    

					   for(int i=0;i<Xnr.size();i++)
					   {
						   //When it is optimal to exercise( if the intrinsic value is greater than the expected value
						   double intrinsicvalue=theVanillaPtr->VanillaPayoff(PathBarrierDependents[MoneynessIndex[i]][time]);
						   // need to amend for the case of stock apths as well.
						   double expectedvalue=0.0;

						   ForExpVal[0]=StockPaths[MoneynessIndex[i]][time];
						   ForExpVal[1]=RatePaths[MoneynessIndex[i]][time];
						   ForExpVal[2]=VolPaths[MoneynessIndex[i]][time];
						   ForExpVal[3]=BarrierDependents[MoneynessIndex[i]][time];
						   ForExpVal[4]=PathDependents[MoneynessIndex[i]][time];
						   ForExpVal[5]=PathBarrierDependents[MoneynessIndex[i]][time];
						   ExpectedValue=cubicfitratevolstockpathdependentbarrier(ForExpVal);
						   //Change this
						   expectedvalue=A[0];
						   for(int jjj=1;jjj<67;jjj++)
							   expectedvalue+=ExpectedValue[jjj]*A[jjj]; //Coefficients of regression times the orthogonal polynomial

 					 
							 
							 if(intrinsicvalue>expectedvalue)
						   {
							   for(unsigned forwardtime=time+1;forwardtime<PathBarrierDependents[0].size();forwardtime++)
								{
                                    PathBarrierDependents[MoneynessIndex[i]][forwardtime]=0;

								}
							    PathBarrierDependents[MoneynessIndex[i]][time]=theVanillaPtr->VanillaPayoff(PathBarrierDependents[MoneynessIndex[i]][time]);

						   }
						   else
						   {
							   PathBarrierDependents[MoneynessIndex[i]][time]=0.0;//Setting zero again when there is continuation
						   }
					   }
					  
					   Xnr.resize(0);
					   Ynr.resize(0);
					   SIC.resize(0);
					   A.resize(0);
					   X.erase(X.begin(),X.end());
					   Y.erase(Y.begin(),Y.end());
					   X1.erase(X1.begin(),X1.end());
					   XRatesVolStockPathDependentBarrier.resize(0,0);
					   MoneynessIndex.erase(MoneynessIndex.begin(),MoneynessIndex.end());
					   
	}
	double summ=0;
	for(unsigned i=0;i<PathBarrierDependents.size();i++)
	{
		for(unsigned j=1;j<PathBarrierDependents[0].size();j++)
		{
			summ+=PathBarrierDependents[i][j];
			PathBarrierDependents[i][j]=PathBarrierDependents[i][j]*RatePaths[i][j];
			Average+=PathBarrierDependents[i][j]/(static_cast<double>(PathBarrierDependents.size()));
			AverageSquare+=PathBarrierDependents[i][j]*PathBarrierDependents[i][j]/(static_cast<double>(PathBarrierDependents.size()));
			
		}
	}
	double value=summ/(static_cast<double>(PathBarrierDependents.size()));
	Results[0]=Average;
	Results[1]=sqrt(AverageSquare-Average*Average)/(sqrt(static_cast<double>(PathBarrierDependents.size())));
	return Results;
}


 Excercise* EarlyExcerciseRateVolPathDependentBarrier::clone() const
{
	return new EarlyExcerciseRateVolPathDependentBarrier(*this);
 }