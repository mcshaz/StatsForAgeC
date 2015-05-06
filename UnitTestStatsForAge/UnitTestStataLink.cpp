#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\AnthroStataLink\AnthroStataLink.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestStatsForAge
{
	TEST_CLASS(UnitTestStataLink)
	{
	public:
		
		TEST_METHOD(TestStataLink)
		{
			int a = stata_testlib(3);
			Assert::AreEqual(a, _stata_testlib_retint, L"correct value not returned from test function");
		}

	};
}