#include "stdafx.h"
#include "cubicfitratevolstockpathdependentbarrier.h"
VecDoub cubicfitratevolstockpathdependentbarrier(VecDoub_I&  xx)
{
	

	
	VecDoub ans(67);
	Doub x1=xx[0],x2=xx[1],x3=xx[2],x4=xx[3],x5=xx[4],x6=xx[5];
	ans[0]=1.;
	ans[1]=x1;ans[2]=x2;ans[3]=x3;ans[4]=x4;ans[5]=x5;ans[6]=x6;
	ans[7]=x1*x1;ans[8]=x2*x2;ans[9]=x3*x3;ans[10]=x4*x4;ans[11]=x5*x5;ans[12]=x6*x6;
	ans[13]=x1*x2;ans[14]=x1*x3;ans[15]=x1*x4;ans[16]=x1*x5;ans[17]=x1*x6;
	ans[18]=x2*x3;ans[19]=x2*x4;ans[20]=x2*x5;ans[21]=x2*x6;
	ans[22]=x3*x4;ans[23]=x3*x5;ans[24]=x3*x6;
	ans[25]=x4*x5;ans[26]=x4*x6;
	ans[27]=x5*x6;
	
	ans[28]=x1*x2*x3;ans[29]=x1*x2*x4;ans[30]=x1*x2*x5;ans[31]=x1*x2*x6;
	ans[32]=x1*x3*x4;ans[33]=x1*x3*x5;ans[34]=x1*x3*x6;
	ans[35]=x1*x4*x5;ans[36]=x1*x4*x6;
	ans[37]=x1*x5*x6;

	ans[38]=x2*x3*x4;ans[39]=x2*x3*x5;ans[40]=x2*x3*x6;
	ans[41]=x2*x4*x5;ans[42]=x2*x4*x6;
	ans[43]=x2*x5*x6;

	ans[44]=x3*x4*x5;ans[45]=x3*x4*x6;
	ans[46]=x3*x5*x6;

	ans[47]=x4*x5*x6;

	
	ans[48]=x1*x2*x3*x4;ans[49]=x1*x2*x3*x5;ans[50]=x1*x2*x3*x6;
	ans[51]=x1*x2*x4*x5;ans[52]=x1*x2*x4*x6;
	ans[53]=x1*x2*x5*x6;

	ans[54]=x1*x3*x4*x5;ans[55]=x1*x3*x4*x6;ans[56]=x1*x3*x5*x6;
	ans[57]=x1*x4*x5*x6;

	ans[58]=x2*x3*x4*x5;ans[59]=x2*x3*x5*x6;ans[60]=x2*x4*x5*x6;
	ans[61]=x3*x4*x5*x6;

	ans[62]=x1*x2*x3*x4*x5;ans[63]=x1*x2*x3*x4*x6;ans[64]=x1*x3*x4*x5*x6;ans[65]=x2*x3*x4*x5*x6;
	ans[66]=x1*x2*x3*x4*x5*x6;


	return ans;
}