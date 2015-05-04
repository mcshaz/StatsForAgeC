// StataAnthropometry.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "StataAnthropometry.h"
#include "UKCentileImplementations.h"
#include <string>
#include <sstream>

STDLL stata_call(int argc, char *argv[]) {
	using namespace StatsForAge;
	if (SF_nvars() != 5) {
		return(102);  	    // not enough variables specified
	}

	if (argc != 1){
		return(198); //wrong number of arguments
	}

	CentileData* statData;

	if (argv[0] == "length")
	{
		statData = &UKLengthData();
	}
	else if (argv[0] = "headcircumference")
	{
		statData = &UKHeadCircumferenceData();
	}
	else if (argv[0] = "bmi")
	{
		statData = &UKBMIData();
	}
	else if (argv[0] = "weight")
	{
		statData = &UKWeightData();
	}
	else
	{
		return(198); //unrecognised argument
	}

	std::stringstream ss;
	ss << argv[0] << " data is available from ";
	if (statData->GetGestAgeRange().MaleRange.Min == statData->GetGestAgeRange().FemaleRange.Min &&  statData->GetAgeMonthsRange().MaleRange.Max == statData->GetAgeMonthsRange().FemaleRange.Max)
	{
		ss << statData->GetGestAgeRange().MaleRange.Min << " weeks gestation to " << statData->GetAgeMonthsRange().MaleRange.Max / 12 << " years";
	}
	else
	{
		ss << "female (" << statData->GetGestAgeRange().FemaleRange.Min << " weeks gestation to " << statData->GetAgeMonthsRange().FemaleRange.Max / 12 << " years)"
			<< " male (" << statData->GetGestAgeRange().MaleRange.Min << " weeks gestation to " << statData->GetAgeMonthsRange().MaleRange.Max / 12 << " years)";
	}
	ss << " _newline Values within these ranges are interpolated, and outside calculated as per the closest datapoint.";

	char* chr = strdup(ss.str().c_str); //heading into C code, accepting char* - i think manual memory management called for
	SF_display(chr); 
	free(chr);

	ST_int lastIn = SF_in2();
	for (ST_int j = SF_in1(); j <= lastIn; j++) {
		if (SF_ifobs(j)) {
			ST_double weightInKg, daysOfAge, isMale, weeksGestationAtBirth, z;
			ST_retcode rc;
			rc = SF_vdata(1, j, &weightInKg);
			if (rc) { return(rc); }
			rc = SF_vdata(2, j, &daysOfAge);
			if (rc) { return(rc); }
			rc = SF_vdata(3, j, &isMale);
			if (rc) { return(rc); }
			rc = SF_vdata(4, j, &weeksGestationAtBirth);
			if (rc) { return(rc); }

			z = statData->ZForAge(weightInKg, daysOfAge, isMale, weeksGestationAtBirth);
			rc = SF_vstore(5, j, z);

			if (rc) { return(rc); }
		}
	}
}
