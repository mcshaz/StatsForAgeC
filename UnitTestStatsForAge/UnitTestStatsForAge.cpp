#include "stdafx.h"
#include "..\StatsForAgeC\LMS.h"
#include "..\StatsForAgeC\UKCentileImplementations.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace StatsForAge;

namespace UnitTestStatsForAge
{		
	TEST_CLASS(UnitTestCentileData)
	{
	public:
		
		TEST_METHOD(TestCentileData)
		{
			UKWeightData wtData;
			Assert::AreEqual(23, wtData.GetGestAgeRange().GetMaleRange().GetMin(), L"Male Gestational Age Min Data");
			Assert::AreEqual(23, wtData.GetGestAgeRange().GetMaleRange().GetMin(), L"Male Gestational Age Min changed on get");
			LMS a = wtData.LMSForAge(365 * 20, true);
			LMS b = wtData.LMSForAge(365 * 20, true);
			std::stringstream ss;
			ss << "compare:\n" << a << '\n' << b << '\n';
			Logger::WriteMessage(ss.str().c_str());
			
			Assert::IsTrue(a == b, L"20 year old LMS not looked up correctly");
			LMS c = wtData.LMSForAge(3, true, 40.0);
			LMS d = wtData.LMSForAge(0, true, 40.0 + 3.0 / 7.0);
			ss.str(std::string());
			ss << "compare:\n" << c << '\n' << d << '\n';
			Logger::WriteMessage(ss.str().c_str());

			Assert::IsTrue( c == d, L"difference between 3 day old term and 40+3 0 day old");

			LMS e = b.LinearInterpolate(c, 0.5);
			ss.str(std::string());
			ss << "linear interpolation between 1st and 2nd output above:\n" << e;
			Logger::WriteMessage(ss.str().c_str());
			Assert::AreEqual(e.L, (b.L + c.L) / 2.0, L"linear interpolation not working as expected on L");
			Assert::AreEqual(e.M, (b.M + c.M) / 2.0, L"linear interpolation not working as expected on M");
			Assert::AreEqual(e.S, (b.S + c.S) / 2.0, L"linear interpolation not working as expected on S");
		}

	};
}