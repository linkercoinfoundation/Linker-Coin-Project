#include "stdafx.h"
#include "cubicfitratevolstockpathdependent.h"
VecDoub cubicfitratevolstockpathdependent(VecDoub_I&  xx)
{
	

	
	VecDoub ans(20);
	Doub x1=xx[0],x2=xx[1],x3=xx[2],x4=xx[3];
	ans[0]=1.;
	ans[1]=x1;ans[2]=x2;ans[3]=x3;ans[4]=x4;
	ans[5]=x1*x1;ans[6]=x2*x2;ans[7]=x3*x3;ans[8]=x4*x4;
	ans[9]=x1*x2;ans[10]=x1*x3;ans[11]=x1*x4;ans[12]=x2*x3;ans[13]=x2*x4;ans[14]=x3*x4;
	ans[15]=x1*x2*x3;ans[16]=x1*x2*x4;ans[17]=x1*x3*x4;ans[18]=x2*x3*x4;
	ans[19]=x1*x2*x3*x4;
	return ans;
}