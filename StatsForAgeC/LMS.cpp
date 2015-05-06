#include "stdafx.h"
#include "LMS.h"
#include "Stats.h"
#include <iostream>

namespace StatsForAge
{
        /// <summary>
        /// linear interpolation between 2 LMS values
        /// </summary>
        /// <param name="with"></param>
        /// <param name="fraction"> proportion of linear interpolation applied to With</param>
        /// <returns></returns>
	LMS LMS::LinearInterpolate(LMS with, double fraction)
    {
        if (fraction <0 || fraction >1)
        {
            throw  std::out_of_range("fraction must be between 0 and 1");
        }
        double oppFraction = 1 - fraction;
        return LMS
        {
            oppFraction * L + fraction * with.L,
            oppFraction * M + fraction * with.M,
            oppFraction * S + fraction * with.S
        };
    }

	double LMS::Zscore(double param) const
    {
        return Stats::ZfromParams(param, M, S, L);
    }

	double LMS::CumNormalDistribution(double param) const
    {
		return Stats::CumSnorm(Zscore(param));
    }

	double LMS::Centile(double param) const
    {
        return 100 * CumNormalDistribution(param);
    }

	double LMS::XfromZscore(double param) const
    {
		return Stats::XfromZscore(param, M, S, L);
    }

	bool LMS::operator== (const LMS &other) const{
		return L == other.L && M == other.M && S == other.S;
	}

	bool LMS::operator!= (const LMS &other) const{
		return !(*this == other);
	}

	void LMS::Print(std::ostream &out) const{
		out << "L:" << L << "M:" << M << "S:" << S;
	}

	std::ostream& operator<< (std::ostream& stream, const LMS& obj){
		obj.Print(stream);
		return stream;
	}
}
