// StatsForAgeC.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "StatsForAgeC.h"


// This is an example of an exported variable
STATSFORAGEC_API int nStatsForAgeC=0;

// This is an example of an exported function.
STATSFORAGEC_API int fnStatsForAgeC(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see StatsForAgeC.h for the class definition
CStatsForAgeC::CStatsForAgeC()
{
	return;
}
