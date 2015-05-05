
#include "stdafx.h"
#include "LMS.h"
#include "CentileData.h"

namespace StatsForAge
{
	/// <summary>
	/// centile data for weight in kg
	/// </summary>
	class STATSFORAGE_API UKWeightData : public CentileData //final
	{
	protected:
		LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const;
		LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const;
		LMS LMSForAgeMonths(int ageMonths, bool isMale) const;
	};

	class STATSFORAGE_API UKBMIData : public CentileData //final
	{
	public:
		UKBMIData(void);
		~UKBMIData(void);
	protected:
		LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const;
		LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const;
		LMS LMSForAgeMonths(int ageMonths, bool isMale) const;
	};

	class STATSFORAGE_API UKLengthData : public CentileData //final
	{
	public:
		UKLengthData(void);
		~UKLengthData(void);
	protected:
		LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const;
		LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const;
		LMS LMSForAgeMonths(int ageMonths, bool isMale) const;
	};

	class STATSFORAGE_API UKHeadCircumferenceData : public CentileData //final
	{
	public:
		UKHeadCircumferenceData(void);
		~UKHeadCircumferenceData(void);
	protected:
		LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const;
		LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const;
		LMS LMSForAgeMonths(int ageMonths, bool isMale) const;
	};
}
