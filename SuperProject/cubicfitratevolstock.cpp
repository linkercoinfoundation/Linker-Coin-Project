#include "stdafx.h"
#include "cubicfitratevolstock.h"
VecDoub cubicfitratevolstock(VecDoub_I&  xx)
{
	

	
	VecDoub ans(11);
	Doub x1=xx[0],x2=xx[1],x3=xx[2];
	ans[0]=1.;
	ans[1]=x1;ans[2]=x2;ans[3]=x3;
	ans[4]=x1*x1;ans[5]=x2*x2;ans[6]=x3*x3;
	ans[7]=x1*x2;ans[8]=x1*x3;ans[9]=x2*x3;
	ans[10]=x1*x2*x3;
	return ans;
}