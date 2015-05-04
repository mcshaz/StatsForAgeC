#ifndef CentileData_included
#define CentileData_included
#include "LMS.h"


namespace StatsForAge
{
	const int TermGestation = 40;
	const double DaysPerMonth = 365.25 / 12.0;
	const double WeeksPerMonth = DaysPerMonth / 7.0;
	const double MaximumGestationalCorrection = 43.0;
	const double CeaseCorrectingDaysOfAge = DaysPerMonth * 24.0;
	const double roundingFactor = 0.00001;

	class STATSFORAGE_API CentileData
	{

	public:
		CentileData(GenderRange* gestAgeRange = nullptr, GenderRange *ageWeeksRange = nullptr, GenderRange *ageMonthsRange = nullptr);
		GenderRange GetGestAgeRange(void) const;
		GenderRange GetAgeWeeksRange(void) const;
		GenderRange GetAgeMonthsRange(void) const;
		double CumSnormForAge(double value, double daysOfAge, bool isMale, double totalWeeksGestAtBirth = TermGestation) const;
		double ZForAge(double value, double daysOfAge, bool isMale, double totalWeeksGestAtBirth = TermGestation) const;
		LMS LMSForAge(double daysOfAge, bool isMale, double totalWeeksGestAtBirth = TermGestation) const;

	protected:
		virtual LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const;
		virtual LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const;
		virtual LMS LMSForAgeMonths(int ageMonths, bool isMale) const;
		bool IsDataAvailable(double daysOfAge, bool isMale, double totalWeeksGestAtBirth = TermGestation) const;

	private:
		GenderRange gestAgeRange_;
		GenderRange ageWeeksRange_;
		GenderRange ageMonthsRange_;

	};

	struct STATSFORAGE_API GenderRange
	{
		GenderRange(AgeRange& maleRange, AgeRange& femaleRange) : MaleRange(maleRange), FemaleRange(femaleRange) {}
		GenderRange(int min, int max) : MaleRange(AgeRange(min, max)), FemaleRange(AgeRange(min, max)){}
		AgeRange const MaleRange;
		AgeRange const FemaleRange;
	};

	struct STATSFORAGE_API AgeRange
	{
		AgeRange(const int min, const int max) : Min(min), Max(max){};
		int const Min;
		int const Max;
	};
}
#endif