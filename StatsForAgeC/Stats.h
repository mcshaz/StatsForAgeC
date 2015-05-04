
namespace StatsForAge
{
	namespace Stats
	{
		double CumSnorm(double Zscore);
		/// <summary>
		/// Returns the Z score for a value given statistical parameters
		/// </summary>
		/// <param name="xVal">measurement for evaluation</param>
		/// <param name="M">median</param>
		/// <param name="S">generalized coefficient of variation</param>
		/// <param name="L">power of box-cox transformation(optional)</param>
		/// <returns>Z</returns>
		double ZfromParams(double xVal, double M, double S, double L = 0);
		/// <summary>
		/// to obtain the value of a measurement for a particular Z score
		/// </summary>
		/// <param name="Z">Z score</param>
		/// <param name="M">median</param>
		/// <param name="S">generalized coefficient of variation</param>
		/// <param name="L">power of box-cox transformation(optional)</param>
		/// <returns>value of a measurement given statistical parameters </returns>
		double XfromZscore(double Z, double M, double S, double L = 0);
		double InverseCumSnorm(double p);
	}
}
