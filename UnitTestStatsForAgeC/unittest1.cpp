#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace StatsForAge;

namespace UnitTestStatsForAgeC
{		
	TEST_CLASS(BasicUnitTest)
	{
	public:
		
		TEST_METHOD(TestLMS)
		{
			UKWeightData wtData = UKWeightData();
			Assert::AreEqual(24, wtData.GetGestAgeRange().GetMaleRange().GetMin());
			Assert::IsTrue(wtData.LMSForAge(365 * 20, true) == LMS{ -0.718, 69.524, 0.13088 });
			Assert::IsTrue(wtData.LMSForAge(3, true, 40.0) == wtData.LMSForAge(0, true, 40.0 + 3/7));
		}

	};
}