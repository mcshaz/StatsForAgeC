#include "stdafx.h"
#include "..\StatsForAgeC\LMS.h"
#include "..\StatsForAgeC\UKCentileImplementations.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace StatsForAge;

namespace UnitTestStatsForAge
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			UKWeightData wtData;
			Assert::AreEqual(23, wtData.GetGestAgeRange().GetMaleRange().GetMin(), L"Male Gestational Age Min Data");
			Assert::AreEqual(23, wtData.GetGestAgeRange().GetMaleRange().GetMin(), L"Male Gestational Age Min changed on look");
			LMS a = wtData.LMSForAge(365 * 20, true);
			LMS b = wtData.LMSForAge(365 * 20, true);
			std::stringstream ss;
			ss << "compare:\n" << a << '\n' << b << '\n';
			Logger::WriteMessage(ss.str().c_str());
			ss.str(std::string());
			Assert::IsTrue(a == b, L"20 year old LMS not looked up correctly");
			LMS c = wtData.LMSForAge(3, true, 40.0);
			LMS d = wtData.LMSForAge(0, true, 40.0 + 3.0 / 7.0);
			ss << "compare:\n" << c << '\n' << d << '\n';
			Logger::WriteMessage(ss.str().c_str());

			Assert::IsTrue( c == d, L"difference between 3 day old term and 40+3 0 day old");
		}

	};
}