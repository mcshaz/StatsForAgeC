#include "stdafx.h"
#include "CentileData.h"

#include <math.h>

namespace StatsForAge
{
	CentileData::CentileData(GenderRange* gestAgeRange, GenderRange* ageWeeksRange, GenderRange* ageMonthsRange)
	{
		gestAgeRange_ = (gestAgeRange == nullptr) ? &GenderRange(23, 43) : gestAgeRange;
		ageWeeksRange_ = (ageWeeksRange == nullptr) ? &GenderRange(4, 13) : gestAgeRange;
		ageMonthsRange_ = (ageMonthsRange == nullptr) ? &GenderRange(3, 240) : gestAgeRange;
	};
	CentileData::~CentileData()
	{
		//these can be injected in, so we might not be the owner, however in its current form this will work
		delete gestAgeRange_;
		delete ageWeeksRange_;
		delete ageMonthsRange_;
	}
	bool CentileData::IsDataAvailable(double daysOfAge, bool isMale, double totalWeeksGestAtBirth) const
    {
        return (isMale ? gestAgeRange_->MaleRange : gestAgeRange_->FemaleRange).Min <= (int)(totalWeeksGestAtBirth + daysOfAge / 7.0);
    }
	double CentileData::CumSnormForAge(double value, double daysOfAge, bool isMale, double totalWeeksGestAtBirth) const
    {
        return LMSForAge(daysOfAge, isMale, totalWeeksGestAtBirth).CumNormalDistribution(value);
    }

	double CentileData::ZForAge(double value, double daysOfAge, bool isMale, double totalWeeksGestAtBirth) const
    {
        return LMSForAge(daysOfAge, isMale, totalWeeksGestAtBirth).Zscore(value);
    }

	LMS CentileData::LMSForAge(double daysOfAge, bool isMale, double totalWeeksGestAtBirth) const
    {
        if (!IsDataAvailable(daysOfAge, isMale, totalWeeksGestAtBirth))
        {
            throw std::out_of_range("totalWeeksGestAtBirth less than GestAgeRange");
        }
        if (totalWeeksGestAtBirth > MaximumGestationalCorrection)
        {
            totalWeeksGestAtBirth = MaximumGestationalCorrection;
        }
        if (daysOfAge < 0)
        {
			throw std::out_of_range("daysOfAge must be >= 0");
        }
        if (daysOfAge > CeaseCorrectingDaysOfAge) 
        {
            totalWeeksGestAtBirth = TermGestation;
        }
        double lookupTotalAge = daysOfAge/7.0 + totalWeeksGestAtBirth;
        int lookupAge = (int)(lookupTotalAge+roundingFactor);
        int maxVal = isMale?gestAgeRange_->MaleRange.Max:gestAgeRange_->FemaleRange.Max;
        if (lookupAge == maxVal)
        {
            int nextLookupAge = lookupAge + 1;
            return LMSForGestAge(lookupAge, isMale)
                .LinearInterpolate(LMSForAgeWeeks(nextLookupAge - TermGestation, isMale), lookupTotalAge - (double)lookupAge);
        }
        if (lookupAge < maxVal)
        {
            int nextLookupAge = lookupAge + 1;
            return LMSForGestAge(lookupAge, isMale)
                .LinearInterpolate(LMSForGestAge(nextLookupAge, isMale), lookupTotalAge - (double)lookupAge);
        }
        lookupTotalAge -= TermGestation;
        lookupAge = (int)(lookupTotalAge + roundingFactor);
        maxVal = isMale ? ageWeeksRange_->MaleRange.Max : ageWeeksRange_->FemaleRange.Max;
        if (lookupAge == maxVal)
        {
            double ageMonthsLookup = ceil((daysOfAge + totalWeeksGestAtBirth - TermGestation) / DaysPerMonth);
            double fraction = (lookupTotalAge - (double)maxVal) / (ageMonthsLookup * WeeksPerMonth - (double)maxVal);
            return LMSForAgeWeeks(lookupAge, isMale)
                .LinearInterpolate(LMSForAgeMonths((int)ageMonthsLookup, isMale), fraction);
        }
        if (lookupAge < maxVal)
        {
            int nextLookupAge = lookupAge + 1;
            return LMSForAgeWeeks(lookupAge, isMale)
                .LinearInterpolate(LMSForAgeWeeks(nextLookupAge, isMale), lookupTotalAge - (double)lookupAge);
        }
        lookupTotalAge = (daysOfAge + totalWeeksGestAtBirth - TermGestation)/DaysPerMonth;
        lookupAge = (int)(lookupTotalAge + roundingFactor);
        maxVal = (isMale ? ageMonthsRange_->MaleRange.Max : ageMonthsRange_->FemaleRange.Max);
        if (lookupAge >= maxVal) 
        {
            return LMSForAgeMonths(maxVal, isMale); 
        }
        int nextAge = lookupAge + 1;
        return LMSForAgeMonths(lookupAge, isMale)
            .LinearInterpolate(LMSForAgeMonths(nextAge, isMale), lookupTotalAge - (double)lookupAge);
	};

    AgeRange::AgeRange(const int min, const int max) : Min(min), Max(max)
    {
        if (min < 0) { throw std::out_of_range("min must be >=0"); }
		if (max < min) { throw std::out_of_range("max must be >= min"); }
    }
}
