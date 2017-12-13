#include "stdafx.h"
#include "cubicfit1.h"
VecDoub cubicfit1(VecDoub_I&  xx)
{
	

	
	VecDoub ans(6);
	Doub x1=xx[0],x2=xx[1];
	ans[0]=1.;
	ans[1]=x1;ans[2]=x2;
	ans[3]=x1*x1;ans[4]=x1*x2;ans[5]=x2*x2;
	return ans;
}