// ANthroStataLink.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
//#include "AnthroStataLink.h"
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
		int nvars(SF_nvars());
		if (nvars < noOfOptions) { // too few variables specified
			std::stringstream errmsg;
			errmsg << "{err}" << noOfOptions << " varnames expected, only " << nvars << " supplied.{break}";
			displayStataMsg_(errmsg.str().c_str());
			return 102;
		}
		return 103;
	}

	if (argc != 1){
		displayStataMsg_("{error}only 1 argument allowed.{break}");
		return 198; //option incorrectly specified
	}

	CentileData* statData;

	if (strcmp(argv[0],"length")==0)
	{
		statData = new UKLengthData();
	}
	else if (strcmp(argv[0], "headcircumference") == 0)
	{
		statData = new UKHeadCircumferenceData();
	}
	else if (strcmp(argv[0], "bmi") == 0)
	{
		statData = new UKBMIData();
	}
	else if (strcmp(argv[0], "weight") == 0)
	{
		statData = new UKWeightData();
	}
	else
	{
		std::stringstream errmsg;
		errmsg << "{error}unrecognised argument: \"" << argv[0] << "\"{break}";
		displayStataMsg_(errmsg.str().c_str());
		return 198; //option incorrectly specified
	}

	std::stringstream ss;
	ss << "{text}" << argv[0] << " data is available from ";
	if (statData->GetGestAgeRange().GetMaleRange().GetMin() == statData->GetGestAgeRange().GetFemaleRange().GetMin() && statData->GetAgeMonthsRange().GetMaleRange().GetMax() == statData->GetAgeMonthsRange().GetFemaleRange().GetMax())
	{
		ss << statData->GetGestAgeRange().GetMaleRange().GetMin() << " weeks gestation to " << statData->GetAgeMonthsRange().GetMaleRange().GetMax() / 12 << " years";
	}
	else
	{
		ss << "female (" << statData->GetGestAgeRange().GetFemaleRange().GetMin() << " weeks gestation to " << statData->GetAgeMonthsRange().GetFemaleRange().GetMax() / 12 << " years)"
			<< " male (" << statData->GetGestAgeRange().GetMaleRange().GetMin() << " weeks gestation to " << statData->GetAgeMonthsRange().GetMaleRange().GetMax() / 12 << " years)";
	}
	ss << "{break}Values within these ranges are interpolated, and outside calculated as per the closest datapoint.{break}";

	displayStataMsg_(ss.str().c_str());
	ST_int missingCount(0), zerocount(0);
	ST_int lastIn(SF_in2());
	for (ST_int j = SF_in1(); j <= lastIn; j++) {
		if (SF_ifobs(j)) {
			ST_double value, daysOfAge, isMale, weeksGestationAtBirth, z;
			ST_retcode rc;
			rc = SF_vdata(1, j, &value);
			if (rc) { return(rc); }
			rc = SF_vdata(2, j, &daysOfAge);
			if (rc) { return(rc); }
			rc = SF_vdata(3, j, &isMale);
			if (rc) { return(rc); }
			rc = SF_vdata(4, j, &weeksGestationAtBirth);
			if (rc) { return(rc); }

			if (SF_is_missing(value) || SF_is_missing(daysOfAge) 
					|| SF_is_missing(isMale) || SF_is_missing(weeksGestationAtBirth) ){
				++missingCount;
			}
			else if (weeksGestationAtBirth <= 0 || value <= 0 || daysOfAge<0){
				++missingCount;
				++zerocount;
			} else {
				z = statData->ZForAge(value, daysOfAge, isMale != 0, weeksGestationAtBirth);
				rc = SF_vstore(5, j, z);
				if (rc) { return(rc); }
			}

		}
	}
	delete statData;
	if (missingCount != 0){
		std::stringstream misstream;
		misstream << "{txt}(" << missingCount << " missing variables generated){break}";
		if (zerocount != 0){
			misstream << "{err}Including " << zerocount << " values where the variable was inappropriately 0 or less";
		}
		displayStataMsg_(misstream.str().c_str());
	}
	return 0;
}

//STDLL stata_testlib(int argc) { return _stata_testlib_retint; }