#ifndef LMS_included
#define LMS_included
namespace StatsForAge
{
	struct LMS
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
	};
}
#endif
