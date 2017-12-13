#include "stdafx.h"
#include <nr3.h>
#include "cubicfit.h"
VecDoub cubicfit(const Doub xx)
{
	

	
	VecDoub ans(4);
	//laguerre
	ans[0]=1.;
	ans[1]=1.0-xx;
	ans[2]=0.5*(xx*xx-4.0*xx+2.);
	ans[3]=(1./6.)*(-xx*xx*xx+9*xx*xx-18*xx+6.);
	//ans[3]=xx*xx*xx;
	//ans[4]=xx*xx*xx*xx;
	//ans[5]=xx*xx*xx*(xx*xx);

	
	return ans;
}