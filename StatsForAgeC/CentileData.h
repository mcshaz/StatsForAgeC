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
		AgeRange(const int min, const int max) : min_(min), max_(max)
		{
			if (min < 0) { throw std::out_of_range("min must be >=0"); }
			if (max < min) { throw std::out_of_range("max must be >= min"); }
		};
		int GetMin(void) const;
		int GetMax(void) const;
	private:
		AgeRange() : min_(0), max_(0) {}; //private empty constructor - i.e. should not be used
		const int min_;
		const int max_;
	};

	class STATSFORAGE_API GenderRange
	{
	public:
		GenderRange(AgeRange* maleRange, AgeRange* femaleRange);
		GenderRange(const int min, const int max);
		~GenderRange(void);
		AgeRange GetMaleRange(void);
		AgeRange GetFemaleRange(void);
	private:
		GenderRange():iOwnRanges_(false){}; //private default constructor - should not be used
		AgeRange* maleRange_;
		AgeRange* femaleRange_;
		const bool iOwnRanges_;
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
			gestAgeRange_((gestAgeRange == nullptr) ? new GenderRange(23, 43) : gestAgeRange),
			ageWeeksRange_((ageWeeksRange == nullptr) ? new GenderRange(4, 13) : gestAgeRange),
			ageMonthsRange_((ageMonthsRange == nullptr) ? new GenderRange(3, 240) : gestAgeRange),
			throwUnderRange_(false){
			iOwnRange = (gestAgeRange == nullptr) & (ageWeeksRange == nullptr) << 1 & (ageMonthsRange == nullptr) << 2;
		};
		~CentileData(void);
		virtual LMS LMSForGestAge(int gestAgeWeeks, bool isMale) const=0;
		virtual LMS LMSForAgeWeeks(int ageWeeks, bool isMale) const=0;
		virtual LMS LMSForAgeMonths(int ageMonths, bool isMale) const=0;
		GenderRange* gestAgeRange_;
		GenderRange* ageWeeksRange_;
		GenderRange* ageMonthsRange_;

	private:
		bool throwUnderRange_;
		int iOwnRange;
	};
}
#endif