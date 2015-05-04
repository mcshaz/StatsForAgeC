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

	class STATSFORAGE_API AgeRange
	{
	public:
		AgeRange(const int min, const int max);
		int GetMin(void) const;
		int GetMax(void) const;
	private:
		const int min_;
		const int max_;
	};

	class STATSFORAGE_API GenderRange
	{
	public:
		GenderRange(AgeRange* maleRange, AgeRange* femaleRange);
		GenderRange(const int min, const int max);
		AgeRange GetMaleRange(void);
		AgeRange GetFemaleRange(void);
		~GenderRange(void);
	private:
		AgeRange* maleRange_;
		AgeRange* femaleRange_;
		//do I need a destructor anywhere?
	};

	class STATSFORAGE_API CentileData
	{

	public:
		GenderRange GetGestAgeRange(void) const;
		GenderRange GetAgeWeeksRange(void) const;
		GenderRange GetAgeMonthsRange(void) const;
		double CumSnormForAge(double value, double daysOfAge, bool isMale, double totalWeeksGestAtBirth = TermGestation) const;
		double ZForAge(double value, double daysOfAge, bool isMale, double totalWeeksGestAtBirth = TermGestation) const;
		LMS LMSForAge(double daysOfAge, bool isMale, double totalWeeksGestAtBirth = TermGestation) const;
		void SetThrowUnderRange(bool value);

	protected:
		CentileData(GenderRange* gestAgeRange = nullptr, GenderRange* ageWeeksRange = nullptr, GenderRange* ageMonthsRange = nullptr) :
			gestAgeRange_((gestAgeRange == nullptr) ? &GenderRange(23, 43) : gestAgeRange),
			ageWeeksRange_((ageWeeksRange == nullptr) ? &GenderRange(4, 13) : gestAgeRange),
			ageMonthsRange_((ageMonthsRange == nullptr) ? &GenderRange(3, 240) : gestAgeRange),
			throwUnderRange_(false){};
		~CentileData(void);
		virtual LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const=0;
		virtual LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const=0;
		virtual LMS LMSForAgeMonths(int ageMonths, bool isMale) const=0;

	private:
		GenderRange* gestAgeRange_;
		GenderRange* ageWeeksRange_;
		GenderRange* ageMonthsRange_;
		bool throwUnderRange_;
	};
}
#endif