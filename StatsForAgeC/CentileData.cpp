#include "stdafx.h"
#include "CentileData.h"

#include <math.h>

namespace StatsForAge
{
	AgeRange::AgeRange(const int min, const int max) : min_(min), max_(max)
	{
		if (min < 0) { throw std::out_of_range("min must be >=0"); }
		if (max < min) { throw std::out_of_range("max must be >= min"); }
	}
	int AgeRange::GetMin(void) const { return min_; }
	int AgeRange::GetMax(void) const { return max_; }

	GenderRange::GenderRange(const int min, const int max){
		maleRange_ = femaleRange_ = &AgeRange(min, max);
	}

	GenderRange::GenderRange(AgeRange* maleRange, AgeRange* femaleRange){
		maleRange = maleRange;
		femaleRange_ = femaleRange;
	}

	GenderRange::~GenderRange(void){
		//deleting pointer which may not be ours if injected
		delete maleRange_;
		delete femaleRange_;
	}
	AgeRange GenderRange::GetMaleRange(void) { return *maleRange_; }
	AgeRange GenderRange::GetFemaleRange(void) { return *femaleRange_; }

	CentileData::~CentileData()
	{
		//these can be injected in, so we might not be the original instantiator of what we are deleting, however in its current form this will always work work
		delete gestAgeRange_;
		delete ageWeeksRange_;
		delete ageMonthsRange_;
	}

	void CentileData::SetThrowUnderRange(bool value){ throwUnderRange_ = value; }

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
        int maxVal = (isMale?gestAgeRange_->GetMaleRange():gestAgeRange_->GetFemaleRange()).GetMax();
        if (lookupAge == maxVal)
        {
            int nextLookupAge = lookupAge + 1;
            return LMSForGestAge(lookupAge, isMale)
                .LinearInterpolate(LMSForAgeWeeks(nextLookupAge - TermGestation, isMale), lookupTotalAge - (double)lookupAge);
        }
        if (lookupAge < maxVal)
        {
			int min = (isMale ? gestAgeRange_->GetMaleRange() : gestAgeRange_->GetFemaleRange()).GetMin();
			if (lookupAge < min) {
				if (throwUnderRange_){
					throw std::out_of_range("age less than data range. SetThrowUnderRange to false (default) to avoid this exception");
				} 
				lookupAge = min; 
			}
            int nextLookupAge = lookupAge + 1;
            return LMSForGestAge(lookupAge, isMale)
                .LinearInterpolate(LMSForGestAge(nextLookupAge, isMale), lookupTotalAge - (double)lookupAge);
        }
        lookupTotalAge -= TermGestation;
        lookupAge = (int)(lookupTotalAge + roundingFactor);
        maxVal = (isMale ? ageWeeksRange_->GetMaleRange() : ageWeeksRange_->GetFemaleRange()).GetMax();
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
        maxVal = (isMale ? ageMonthsRange_->GetMaleRange() : ageMonthsRange_->GetFemaleRange()).GetMax();
        if (lookupAge >= maxVal) 
        {
            return LMSForAgeMonths(maxVal, isMale); 
        }
        int nextAge = lookupAge + 1;
        return LMSForAgeMonths(lookupAge, isMale)
            .LinearInterpolate(LMSForAgeMonths(nextAge, isMale), lookupTotalAge - (double)lookupAge);
	};

}
