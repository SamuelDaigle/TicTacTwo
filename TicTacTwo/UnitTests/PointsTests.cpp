#include "stdafx.h"
#include "../Utility/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PointTests)
	{
	public:
		TEST_METHOD(given_2_points_to_compare_when_they_are_not_equal_then_should_return_false)
		{
			//arrange
			Point point1(0, 1);
			Point point2(0, 2);
			
			//action 
			bool compareResult = point1 == point2;
			
			//assert
			Assert::IsFalse(compareResult);
		}

		TEST_METHOD(given_2_points_to_compare_when_they_are_equal_then_should_return_true)
		{
			//arrange
			Point point1(1, 1);
			Point point2(1, 1);

			//action 
			bool compareResult = point1 == point2;

			//assert
			Assert::IsTrue(compareResult);
		}

		TEST_METHOD(given_2_points_to_compare_difference_when_they_are_not_equal_then_should_return_true)
		{
			//arrange
			Point point1(1, 0);
			Point point2(2, 0);

			//action 
			bool compareResult = point1 != point2;

			//assert
			Assert::IsTrue(compareResult);
		}

		TEST_METHOD(given_2_points_to_compare_difference_when_they_are_equal_then_should_return_false)
		{
			//arrange
			Point point1(1, 1);
			Point point2(1, 1);

			//action 
			bool compareResult = point1 != point2;

			//assert
			Assert::IsFalse(compareResult);
		}

	};
}