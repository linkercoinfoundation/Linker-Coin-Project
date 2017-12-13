#include "stdafx.h"
#include "Regression.h"
#include "cubicfit.h"
#include "cubicfit1.h"
#include "cubicfitratevolstock.h"
#include "cubicfitratevolstockpathdependent.h"
#include "cubicfitratevolstockpathdependentbarrier.h"
#include <svd.h>
#include <fitsvd.h>
#include <fstream>

Regression* Regression::clone() const
{
	return new Regression(*this);
}

    VecDoub Regression::regress(VecDoub Xnr,VecDoub Ynr)
	{
		const Doub TOL=1.e-12;      
		VecDoub SIC(Xnr.size());
		
		
		Fitsvd myfit(Xnr,Ynr,SIC,cubicfit,TOL);
					myfit.fit();
				return	myfit.a;//The regression coefficients

	}
	VecDoub Regression::regressPathDependent(MatDoub Xnr, VecDoub Ynr)
	{
		const Doub TOL=1.e-12;      
		VecDoub SIC(Xnr.nrows());
		
		
		Fitsvd myfit(Xnr,Ynr,SIC,cubicfit1,TOL);
					myfit.fit();
				return	myfit.a;//The regression coefficients

	}
	VecDoub Regression::regressratevolstoc(MatDoub Xnr,VecDoub Ynr)
	{
		const Doub TOL=1.e-12;      
		VecDoub SIC(Xnr.nrows());
		int NumRows = Xnr.nrows();
		vector<vector<double>> Returns(NumRows, vector<double>(4,0));
		ofstream fileOutput("Aris.txt");
				for(int i=0;i<Xnr.nrows();i++){
					for(int j=0;j<Xnr.ncols();j++)
					{
						fileOutput<<Xnr[i][j];
						fileOutput<<" ";
					}
					fileOutput<<Ynr[i];
					fileOutput<<endl;
					Returns[i][0]=Xnr[i][0];
					Returns[i][1]=Xnr[i][1];
					Returns[i][2]=Xnr[i][2];
					Returns[i][3]=Ynr[i];

				}
				fileOutput.close();



		//SIC.resize(11);
		
		Fitsvd myfit(Xnr,Ynr,SIC,cubicfitratevolstock,TOL);
					myfit.fit();
				return	myfit.a;//The regression coefficients

	}
	VecDoub Regression::regressratevolPathDependent(MatDoub Xnr,VecDoub Ynr)
	{

		const Doub TOL=1.e-12;      
		VecDoub SIC;
		SIC.resize(Xnr.nrows());
		
		Fitsvd myfit(Xnr,Ynr,SIC,cubicfitratevolstockpathdependent,TOL);
					myfit.fit();
				return	myfit.a;//The regression coefficients
		return SIC;

	}


	VecDoub Regression::regressratevolPathDependentBarrier(MatDoub Xnr,VecDoub Ynr)
	{

		const Doub TOL=1.e-12;      
		VecDoub SIC;
		SIC.resize(Xnr.nrows());
		
		Fitsvd myfit(Xnr,Ynr,SIC,cubicfitratevolstockpathdependentbarrier,TOL);
					myfit.fit();
				return	myfit.a;//The regression coefficients
		return SIC;


	}