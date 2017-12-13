#include "stdafx.h"
#include "EarlyExcercisePathDependent.h"
#include <cstdlib>
#include <ctime>
using namespace std;
#include<vector>

#include "Regression.h"
//#include "cubicfit.h"
//#include "fitsvd.h"
//#include "cubicfit1.h"
EarlyExcercisePathDependent::EarlyExcercisePathDependent(const Simulation& theSimulation, const Vanilla& theVanilla)
{
	this->simulationptr=theSimulation.clone();
	this->theVanillaPtr=theVanilla.clone();
	
	
}



vector<double> EarlyExcercisePathDependent::Results() const
{
	//We value with PathDependents in case we have path dependency. If we are path independent, then PathDependents will have the same inputs as the StockPaths.
	Regression theregression(0.0);
	const Doub TOL=1.e-12;
	vector<double> Results(2,1);
	this->simulationptr->operator()();
	vector<vector<double>> StockPaths=this->simulationptr->getStockPaths();
	vector<vector<double>> RatePaths=this->simulationptr->getRatesPaths();
	vector<vector<double>>PathDependents=this->simulationptr->getPathDependents();
	double IndicatorOfAsian=this->simulationptr->getIndicatorAsian();
	vector<double> FinalValues(StockPaths.size(),1);
	double Average=0.0;
	double AverageSquare=0.0;
	vector<double> Y;//The the intrinsic payoffs
	
	vector<double> X;//The value of the Path Dependency
	vector<double> X1; //The value of the Stock
	VecDoub Xnr,Ynr,SIC,A;
	MatDoub XPathDependent;
	double temporary;
	vector<int> MoneynessIndex;
	int sumfwd;

	
	//Evaluating the Payoff of the American Option using the Longstaff-Schwarz algorithm

	int sumfwdtimes=0;
	for(unsigned i=0;i<PathDependents.size();i++)
	{
		PathDependents[i][PathDependents[0].size()-1]=theVanillaPtr->VanillaPayoff(PathDependents[i][PathDependents[0].size()-1]);
		//cout<<"The terminal value of the path is: "<<Paths[i][Paths[0].size()-1][0]<<endl;
				
	}
	
	
	
	
	for(int time=PathDependents[0].size()-2;time>0;time--)//for every time instant
	{
					//Finding the X variable and the index (where the payoff of the current time is nonzero)
					for(unsigned pathindex=0;pathindex<PathDependents.size();pathindex++)//for every path
					{				
						if(theVanillaPtr->VanillaPayoff(PathDependents[pathindex][time])>0)
						{
							X.push_back(PathDependents[pathindex][time]);//Creates X PathDependents
							if(IndicatorOfAsian>1e-5) //if pathdependent
								X1.push_back(StockPaths[pathindex][time]); //Creates X1 of Stock paths if path dependent
							// need to put stock paths as well(when the condition holds)
							MoneynessIndex.push_back(pathindex);
							//creating Y
							temporary=0; //finding the temporary
							for(unsigned ftime=time+1;ftime<PathDependents[0].size();ftime++)
							{
								sumfwd=0;
								if(PathDependents[pathindex][ftime]>0)
								{
                                    temporary=PathDependents[pathindex][ftime]*RatePaths[pathindex][ftime]/RatePaths[pathindex][time];
									sumfwd+=1;
									if(sumfwd>1)
										throw("More than one non zero payoffs!");
								}

							}
							Y.push_back(temporary); //creating the Y
							//StockPaths[pathindex][time]=theVanillaPtr->VanillaPayoff(StockPaths[pathindex][time]);
						}else
						{
							PathDependents[pathindex][time]=0.0; //making zero the values at that time instant where the payoffs are not positive
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
				A.resize(6);
				XPathDependent.resize(X.size(),2);
				cout<<PathDependents[MoneynessIndex[1]][time];
				for(unsigned i=0;i<Y.size();i++)
				{
					Xnr[i]=X[i];
					Ynr[i]=Y[i];
				}


				if(IndicatorOfAsian>1e-5)
				{
					for(unsigned i=0;i<Y.size();i++)
					{
                      XPathDependent[i][0]=X[i];//MatDoub assigning the PathDependentValues
					  XPathDependent[i][1]=X1[i];//MatDoub assigning the StockValues

					}
				}

				//Performing the regression
				
					
				    A=theregression.regressPathDependent(XPathDependent,Ynr);
				

					   for(int i=0;i<Xnr.size();i++)
					   {
						   //When it is optimal to exercise( if the intrinsic value is greater than the expected value
						   double intrinsicvalue=theVanillaPtr->VanillaPayoff(PathDependents[MoneynessIndex[i]][time]);
						   // need to amend for the case of stock apths as well.
						   double expectedvalue=0.0;
						   
                             expectedvalue=A[0]+A[1]*PathDependents[MoneynessIndex[i]][time]+A[2]*StockPaths[MoneynessIndex[i]][time];
							 expectedvalue+=A[3]*PathDependents[MoneynessIndex[i]][time]*PathDependents[MoneynessIndex[i]][time]+A[4]*PathDependents[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time];
							 expectedvalue+=A[5]*StockPaths[MoneynessIndex[i]][time]*StockPaths[MoneynessIndex[i]][time];
						   
						   if(intrinsicvalue>expectedvalue)
						   {
							   for(unsigned forwardtime=time+1;forwardtime<PathDependents[0].size();forwardtime++)
								{
                                    PathDependents[MoneynessIndex[i]][forwardtime]=0;

								}
							    PathDependents[MoneynessIndex[i]][time]=theVanillaPtr->VanillaPayoff(PathDependents[MoneynessIndex[i]][time]);

						   }
						   else
						   {
							   PathDependents[MoneynessIndex[i]][time]=0.0;//Setting zero again when there is continuation
						   }
					   }
					  
					   Xnr.resize(0);
					   Ynr.resize(0);
					   SIC.resize(0);
					   A.resize(0);
					   X.erase(X.begin(),X.end());
					   Y.erase(Y.begin(),Y.end());
					   X1.erase(X1.begin(),X1.end());
					   XPathDependent.resize(0,0);
					   MoneynessIndex.erase(MoneynessIndex.begin(),MoneynessIndex.end());
					   
	}
	double summ=0;
	for(unsigned i=0;i<PathDependents.size();i++)
	{
		for(unsigned j=1;j<PathDependents[0].size();j++)
		{
			summ+=PathDependents[i][j];
			PathDependents[i][j]=PathDependents[i][j]*RatePaths[i][j];
			Average+=PathDependents[i][j]/(static_cast<double>(PathDependents.size()));
			AverageSquare+=PathDependents[i][j]*PathDependents[i][j]/(static_cast<double>(PathDependents.size()));
			
		}
	}
	double value=summ/(static_cast<double>(PathDependents.size()));
	Results[0]=Average;
	Results[1]=sqrt(AverageSquare-Average*Average)/(sqrt(static_cast<double>(PathDependents.size())));
	return Results;
}


 Excercise* EarlyExcercisePathDependent::clone() const
{
	return new EarlyExcercisePathDependent(*this);
 }