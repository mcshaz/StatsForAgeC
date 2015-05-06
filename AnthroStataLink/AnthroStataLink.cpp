// ANthroStataLink.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "AnthroStataLink.h"
#include "..\StatsForAgeC\UKCentileImplementations.h"
#include "stplugin.h"
#include <sstream>

inline void displayStataMsg_(const char* str){
	char* out = _strdup(str); //heading into C code, accepting char* - i think manual memory management called for
	SF_display(out);
	free(out);
}

// This is an example of an exported variable
STDLL stata_call(int argc, char *argv[]) {
	using namespace StatsForAge;
	#define noOfOptions 5
	if (SF_nvars() != noOfOptions) {
		if (SF_nvars() < noOfOptions) { return 102; }	    // too few variables specified
		return 103;
	}

	if (argc != 1){
		displayStataMsg_("as err \"only 1 argument allowed\"");
		return 198; //option incorrectly specified
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
		displayStataMsg_("as err \"unrecognised argument\"");
		return 198; //option incorrectly specified
	}

	std::stringstream ss;
	ss << "as txt \"" << argv[0] << " data is available from ";
	if (statData->GetGestAgeRange().GetMaleRange().GetMin() == statData->GetGestAgeRange().GetFemaleRange().GetMin() && statData->GetAgeMonthsRange().GetMaleRange().GetMax() == statData->GetAgeMonthsRange().GetFemaleRange().GetMax())
	{
		ss << statData->GetGestAgeRange().GetMaleRange().GetMin() << " weeks gestation to " << statData->GetAgeMonthsRange().GetMaleRange().GetMax() / 12 << " years";
	}
	else
	{
		ss << "female (" << statData->GetGestAgeRange().GetFemaleRange().GetMin() << " weeks gestation to " << statData->GetAgeMonthsRange().GetFemaleRange().GetMax() / 12 << " years)"
			<< " male (" << statData->GetGestAgeRange().GetMaleRange().GetMin() << " weeks gestation to " << statData->GetAgeMonthsRange().GetMaleRange().GetMax() / 12 << " years)";
	}
	ss << "\" _newline \"Values within these ranges are interpolated, and outside calculated as per the closest datapoint.\"";

	displayStataMsg_(ss.str().c_str());
	ST_int missingCount(0);
	ST_int lastIn(SF_in2());
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

			if (SF_is_missing(weightInKg) || SF_is_missing(daysOfAge) || SF_is_missing(isMale) || SF_is_missing(weeksGestationAtBirth)){
				++missingCount;
			} else {
				z = statData->ZForAge(weightInKg, daysOfAge, isMale != 0, weeksGestationAtBirth);
				rc = SF_vstore(5, j, z);
				if (rc) { return(rc); }
			}
			
		}
	}
	if (missingCount != 0){
		std::stringstream ss;
		ss << "as txt \"" << missingCount << " missing variables generated.\"";
	}
	return 0;
}

STDLL stata_testlib(int argc) { return _stata_testlib_retint; }