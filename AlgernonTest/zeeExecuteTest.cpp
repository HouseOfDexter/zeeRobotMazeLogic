#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\zeeExecute.h"
#include "gmock/gmock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgernonTest
{		
	TEST_CLASS(zeeExecuteTest)
	{
	public:
		
		TEST_METHOD(Execute)
		{
      int value = 42;
      Assert::AreEqual(42, value);
		}

	};
}