//=================================
// include guard
#ifndef __CENTILEIMPLEMETATION_H_INCLUDED__
#define __CENTILEIMPLEMETATION_H_INCLUDED__

//=================================
// forward declared dependencies

//=================================
// included dependencies
#include "stdafx.h"
#include "CentileData.h"

//=================================
// the actual class

namespace StatsForAge
{
	struct LMS;
	/// <summary>
	/// centile data for weight in kg
	/// </summary>
	class STATSFORAGE_API UKWeightData : public CentileData //final
	{
	protected:
		LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const override;
		LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const override;
		LMS LMSForAgeMonths(int ageMonths, bool isMale) const override;
	};

	class STATSFORAGE_API UKBMIData : public CentileData //final
	{
	public:
		UKBMIData(void);
		~UKBMIData(void);
	protected:
		LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const override;
		LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const override;
		LMS LMSForAgeMonths(int ageMonths, bool isMale) const override;
	};

	class STATSFORAGE_API UKLengthData : public CentileData //final
	{
	public:
		UKLengthData(void);
		~UKLengthData(void);
	protected:
		LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const override;
		LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const override;
		LMS LMSForAgeMonths(int ageMonths, bool isMale) const override;
	};

	class STATSFORAGE_API UKHeadCircumferenceData : public CentileData //final
	{
	public:
		UKHeadCircumferenceData(void);
		~UKHeadCircumferenceData(void);
	protected:
		LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const override;
		LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const override;
		LMS LMSForAgeMonths(int ageMonths, bool isMale) const override;
	};
}
#endif