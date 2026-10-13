#include "pch.h"
#include "CppUnitTest.h"
#include "UtilityFunctions.h"
//#include <CommonUtilities.h>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Uppgift12TemplateUtilitiesCUUnitTest
{
	TEST_CLASS(MinTests)
	{
	public:
		
		TEST_METHOD(LesserNumberFirst)
		{
			Assert::AreEqual(CommonUtilities::Min(0, 10), 0);
		}

		TEST_METHOD(LesserNumberSecond)
		{
			Assert::AreEqual(CommonUtilities::Min(10, 0), 0);
		}

		TEST_METHOD(FirstParameterNegative)
		{
			Assert::AreEqual(CommonUtilities::Min(-10, 0), -10);
		}

		TEST_METHOD(SecondParameterNegative)
		{
			Assert::AreEqual(CommonUtilities::Min(0, -10), -10);
		}

		TEST_METHOD(DoubleNegative_LeastFirst)
		{
			Assert::AreEqual(CommonUtilities::Min(-10, -1), -10);
		}

		TEST_METHOD(DoubleNegative_LeastSecond)
		{
			Assert::AreEqual(CommonUtilities::Min(-1, -10), -10);
		}
	};

	TEST_CLASS(MaxTests)
	{
	public:
		TEST_METHOD(LesserNumberFirst)
		{
			Assert::AreEqual(CommonUtilities::Max(0, 10), 10);
		}

		TEST_METHOD(LesserNumberSecond)
		{
			Assert::AreEqual(CommonUtilities::Max(10, 0), 10);
		}

		TEST_METHOD(FirstParameterNegative)
		{
			Assert::AreEqual(CommonUtilities::Max(-10, 0), 0);
		}

		TEST_METHOD(SecondParameterNegative)
		{
			Assert::AreEqual(CommonUtilities::Max(0, -10), 0);
		}

		TEST_METHOD(DoubleNegative_LeastFirst)
		{
			Assert::AreEqual(CommonUtilities::Max(-10, -1), -1);
		}

		TEST_METHOD(DoubleNegative_LeastSecond)
		{
			Assert::AreEqual(CommonUtilities::Max(-1, -10), -1);
		}
	};

	TEST_CLASS(ClampTests)
	{
	public: // (VALUE , MIN , MAX)
		TEST_METHOD(NumberIsInRange)
		{
			Assert::AreEqual(CommonUtilities::Clamp(5, 0, 10), 5);
		}

		TEST_METHOD(NumberIsAtMax)
		{
			Assert::AreEqual(CommonUtilities::Clamp(0, 10, 10), 10);
		}

		TEST_METHOD(NumberIsAtMin)
		{
			Assert::AreEqual(CommonUtilities::Clamp(0, 0, 10), 0);
		}

		TEST_METHOD(NumberIsHigher)
		{
			Assert::AreEqual(CommonUtilities::Clamp(0, 10, 100), 10);
		}

		TEST_METHOD(NumberIsLower)
		{
			Assert::AreEqual(CommonUtilities::Clamp(-100, 0, 10), 0);
		}

		TEST_METHOD(NegativeNumbers)
		{
			Assert::AreEqual(CommonUtilities::Clamp(-100, -50, -10), -50);
			Assert::AreEqual(CommonUtilities::Clamp(-500, -100, -10), -100);
			Assert::AreEqual(CommonUtilities::Clamp(-100, -50, -20), -50);
		}

		TEST_METHOD(NegativeAndPositiveNumbersMixed)
		{
			Assert::AreEqual(CommonUtilities::Clamp(100, -50, 10), 10);
			Assert::AreEqual(CommonUtilities::Clamp(-100, -50, 10), -50);
			Assert::AreEqual(CommonUtilities::Clamp(30, -150, 50), 30);
		}

		TEST_METHOD(MinMaxSameValue)
		{
			Assert::AreEqual(CommonUtilities::Clamp(100, 50, 50), 50);
			Assert::AreEqual(CommonUtilities::Clamp(30, 10, 10), 10);
			Assert::AreEqual(CommonUtilities::Clamp(-50, 100, 100), 100);
		}

		TEST_METHOD(MinHigherThanMax_ShouldAssert)
		{
			Assert::AreEqual(CommonUtilities::Clamp(60, 500, 50), 50);
		}

	};

	TEST_CLASS(AbsTests)
	{
	public:
		TEST_METHOD(NegativeNumber)
		{
			Assert::AreEqual(CommonUtilities::Abs(-10), 10);
		}
		TEST_METHOD(PositiveNumber)
		{
			Assert::AreEqual(CommonUtilities::Abs(10), 10);
		}
	};

	TEST_CLASS(SwapTests)
	{
	public:
		TEST_METHOD(PositiveVariables)
		{
			int a = 10;
			int b = 20;
			CommonUtilities::Swap(a, b);
			Assert::AreEqual(a, 20);
			Assert::AreEqual(b, 10);
		}

		TEST_METHOD(NegativeVariables)
		{
			int a = -10;
			int b = -20;
			CommonUtilities::Swap(a, b);
			Assert::AreEqual(a, -20);
			Assert::AreEqual(b, -10);
		}

		TEST_METHOD(SameVariableInBothArguments)
		{
			int a = 42;
			CommonUtilities::Swap(a, a);
			Assert::AreEqual(a, 42);
		}
	};

	TEST_CLASS(LerpTests)
	{
	public:
		TEST_METHOD(LerpValueZero)
		{
			Assert::AreEqual(CommonUtilities::Lerp(-10, 10, 0.f), -10);
		}

		TEST_METHOD(LerpValueMiddle)
		{
			Assert::AreEqual(CommonUtilities::Lerp(10, -10, 0.5f), 0);
		}

		TEST_METHOD(LerpValueHigh)
		{
			Assert::AreEqual(CommonUtilities::Lerp(10, -10, 1.f), -10);
		}
	};

}