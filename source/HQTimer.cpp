#include "HQTimer.h"


//  Timer class

HQTimer::HQTimer()
	:cc(0.0), fq(10000000.0)
	,t(0),st(0), dt1(0),st1(0), iFR(0)
	,dt(0.0), FR(0.0), iv(0.0), iv1(0.5), first(true)
{
	LARGE_INTEGER FQ;
	if (QueryPerformanceFrequency( &FQ ))
		fq = double( FQ.QuadPart );
	QueryPerformanceCounter( &CC );
	st = double( CC.QuadPart ) / fq;
}

bool HQTimer::update()
{
	QueryPerformanceCounter( &CC );
	cc = double( CC.QuadPart );
	t = cc / fq;
	
	if (first)
	{	first = false;
		st = st1 = t;
	}
	
	dt = t - st;  // delta time
	if (dt < iv)  // interval
		return false;
	
	st = t;  // old time
	iFR++;  // frames count
	
	//  framerate update
	dt1 = t - st1;
	if (dt1 >= iv1)
	{
		FR = iFR / dt1;
		if (FR < 1.)  FR = 0.;
		iFR = 0.;
		st1 = t;
	}
	return true;
}
