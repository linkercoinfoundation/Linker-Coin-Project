#include "stdafx.h"
#include "EarlyExcerciseBarrier.h"
#include <cstdlib>
#include <ctime>
using namespace std;
#include<vector>
#include <cmath>
#include "Regression.h"
//#include "cubicfit.h"
//#include "fitsvd.h"
//#include "cubicfit1.h"
EarlyExcerciseBarrier::EarlyExcerciseBarrier(const Simulation& theSimulation, const Vanilla& theVanilla)
{
	this->simulationptr=theSimulation.clone();
	this->theVanillaPtr=theVanilla.clone();
	
	
}



vector<double> EarlyExcerciseBarrier::Results() const
{
	//We value with Barriers in case we have path dependency. If we are path independent, then Barriers will have the same inputs as the StockPaths.
	Regression theregression(0.0);
	const Doub TOL=1.e-12;
	vector<double> Results(2,1);
	vector<int>   KnockOutIndex;
	this->simulationptr->operator()();
	vector<vector<double>> StockPaths=this->simulationptr->getStockPaths();
	vector<vector<double>> RatePaths=this->simulationptr->getRatesPaths();
	vector<vector<double>> BarrierDependents=this->simulationptr->getBarrierDependents();
	double IndicatorOfAsian=this->simulationptr->getIndicatorAsian();
	vector<double> FinalValues(StockPaths.size(),1);
	double Average=0.0;
	double AverageSquare=0.0;
	vector<double> Y;//The the intrinsic payoffs
	
	vector<double> X;//The value of the Path Dependency
	vector<double> X1; //The value of the Stock
	VecDoub Xnr,Ynr,SIC,A;
	MatDoub XBarrier;
	double temporary;
	vector<int> MoneynessIndex;
	int sumfwd;
	double expectedvalue;
	double intrinsicvalue;
	
	//Evaluating the Payoff of the American Option using the Longstaff-Schwarz algorithm

	int sumfwdtimes=0;
	double summ;
	for(unsigned i=0;i<BarrierDependents.size();i++)
	{
		
		
		if(BarrierDependents[i][BarrierDependents[0].size()-1]==0)
		{
			BarrierDependents[i][BarrierDependents[0].size()-1]=0; //in place replacement
			KnockOutIndex.push_back(0);
		}else
		{
		BarrierDependents[i][BarrierDependents[0].size()-1]=theVanillaPtr->VanillaPayoff(BarrierDependents[i][BarrierDependents[0].size()-1]);
		KnockOutIndex.push_back(1);
		//cout<<"The terminal value of the path is: "<<Paths[i][Paths[0].size()-1][0]<<endl;
		}		
	}
	
	
	
	
	for(int time=BarrierDependents[0].size()-2;time>0;time--)//for every time instant
	{
					//Finding the X variable and the index (where the payoff of the current time is nonzero)
					for(unsigned pathindex=0;pathindex<BarrierDependents.size();pathindex++)//for every path
					{				
					 
						 if( BarrierDependents[pathindex][time]>0)
						{   
							if(theVanillaPtr->VanillaPayoff(BarrierDependents[pathindex][time])>0)
							{
								X.push_back(BarrierDependents[pathindex][time]);//Creates X BarrierDependents
								X1.push_back(StockPaths[pathindex][time]); //Creates X1 of Stock paths if path dependent
								// need to put stock paths as well(when the condition holds)
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
						     }
							  else
								{
									BarrierDependents[pathindex][time]=0;
								}
							//StockPaths[pathindex][time]=theVanillaPtr->VanillaPayoff(StockPaths[pathindex][time]);
						}else
						{
							BarrierDependents[pathindex][time]=0;

					     }//Endif

					

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
				A.resize(6);
				XBarrier.resize(X.size(),2);
				cout<<BarrierDependents[MoneynessIndex[1]][time];
				for(unsigned i=0;i<Y.size();i++)
				{
					Xnr[i]=X[i];
					Ynr[i]=Y[i];
				}


				if(IndicatorOfAsian>1e-5)
				{
					for(unsigned i=0;i<Y.size();i++)
					{
                      XBarrier[i][0]=X[i];//MatDoub assigning the BarrierValues
					  XBarrier[i][1]=X1[i];//MatDoub assigning the StockValues

					}
				}

				//Performing the regression
				
					
				   // A=theregression.regressPathDependent(XBarrier,Ynr);
				    A=theregression.regress(Xnr,Ynr);
					   int theknockoutindex=0;
					   for(int i=0;i<Xnr.size();i++)
					   {
						   //When it is optimal to exercise( if the intrinsic value is greater than the expected value
						     
							
							
						    intrinsicvalue=theVanillaPtr->VanillaPayoff(BarrierDependents[MoneynessIndex[i]][time]);
							
							
							
						   // need to amend for the case of stock apths as well.
						   expectedvalue=0.0;
						   
                             expectedvalue=A[0]+A[1]*(1.-BarrierDependents[MoneynessIndex[i]][time]);//+A[2]*StockPaths[MoneynessIndex[i]][time];
							 expectedvalue+=A[2]*0.5*(BarrierDependents[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time]-4*BarrierDependents[MoneynessIndex[i]][time]+2.);//e+=
							
							 expectedvalue+=A[3]*(1./6.)*(-BarrierDependents[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time]+9*BarrierDependents[MoneynessIndex[i]][time]*BarrierDependents[MoneynessIndex[i]][time]-18*BarrierDependents[MoneynessIndex[i]][time]+6.);
							 //expectedvalue+=A[4]*pow(BarrierDependents[MoneynessIndex[i]][time],4.0);
							// expectedvalue+=A[4]*pow(BarrierDependents[MoneynessIndex[i]][time],5.0);
						   
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
					   XBarrier.resize(0,0);
					   MoneynessIndex.erase(MoneynessIndex.begin(),MoneynessIndex.end());
					  
					   
	}
	 summ=0;
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


 Excercise* EarlyExcerciseBarrier::clone() const
{
	return new EarlyExcerciseBarrier(*this);
 }