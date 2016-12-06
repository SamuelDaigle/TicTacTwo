#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(SDLWindowAPITests)
	{
	public:
		IWindowAPI* windowAPI;

		TEST_METHOD_INITIALIZE(SDLWindowAPITests_Initialize)
		{
			windowAPI = new SDLWindowAPI(600, 400, "name");
		}

		TEST_METHOD_CLEANUP(SDLWindowAPITests_Cleanup)
		{
			delete windowAPI;
		}
		
		TEST_METHOD(loading_an_existing_bmp_image_should_not_throw_an_exception)
		{
			// Arrange
			bool anyExceptionThrown = false;

			// Action
			try
			{
				windowAPI->drawImage("christophe.bmp", 0, 0, 100, 100);
			}
			catch (...)
			{
				anyExceptionThrown = true;
			}


			// Assert
			Assert::IsFalse(anyExceptionThrown);
		}
	};
}