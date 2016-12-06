#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(WindowTests)
	{
	public:

		FakeWindowAPI * fakeWindowAPI;
		Window * window;
		Button * button;

		TEST_METHOD_INITIALIZE(WindowTestsInitialize)
		{
			fakeWindowAPI = new FakeWindowAPI(640, 480, "Super beau dessin");
			window = new Window(*fakeWindowAPI);
			button = new Button();
		}	
		TEST_METHOD_CLEANUP(WindowTestsCleanUp)
		{
			delete fakeWindowAPI;
			delete window;
			delete button;
		}
		TEST_METHOD(window_should_draw_a_button_if_one_is_added_to_window)
		{
			//Arrange
			const int BUTTONS_ALREADY_IN_MENU_CONTROLLER = 4;
			window->addButton(*button);

			//Action
			window->render();

			//Assert
			Assert::AreEqual(fakeWindowAPI->drawButton_getnumberOfCall() - BUTTONS_ALREADY_IN_MENU_CONTROLLER, 1);
		}
		TEST_METHOD(updateButtonImage_with_invalid_image_path_should_launch_an_exception)
		{
			//Arrange
			button->setText("buttonToModify");
			bool exceptionThrown = false;

			window->addButton(*button);

			//Action
			try
			{
				window->updateButtonImage("buttonToModify", nullptr);
			}
			catch (invalid_argument e)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}
		TEST_METHOD(rendering_a_window_with_invalid_windowAPI_should_launch_an_exception)
		{
			//Arrange
			bool exceptionThrown = false;
			FakeWindowAPI * fake2 = nullptr;
			Window * window2 = new Window(*fake2);

			//Action
			try
			{
				window2->render();
			}
			catch (runtime_error e)
			{
				exceptionThrown = true;
			}

			delete fake2;
			delete window2;

			//Assert
			Assert::IsTrue(exceptionThrown);
		}
		TEST_METHOD(click_on_exit_should_close_the_application)
		{
			//Arrange
			
			//Action
			window->mouseInput(Point(200,400));
			
			//Assert
			Assert::IsTrue(fakeWindowAPI->quit_HasBeenCalled());
		}
	};
}