#ifndef __LMS_H_included
#define __LMS_H_included

#include "stdafx.h"

namespace StatsForAge
{
	struct STATSFORAGE_API LMS
	{
		double const L;
		double const M;
		double const S;
		/// <summary>
		/// linear interpolation between 2 LMS values
		/// </summary>
		/// <param name="with"></param>
		/// <param name="fraction"> proportion of linear interpolation applied to With</param>
		/// <returns></returns>
		LMS LinearInterpolate(LMS with, double fraction);

		double Zscore(double param) const;

		double CumNormalDistribution(double param) const;

		double Centile(double param) const;

		double XfromZscore(double param) const;

		bool operator== (const LMS &rhs) const;

		bool operator!= (const LMS &rhs) const;

		void Print(std::ostream& stream) const;
	};

	STATSFORAGE_API std::ostream& operator<< (std::ostream& stream, const LMS& obj);
}
#endif
