#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Controllers/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(MenuControllerTests)
	{
	public:
		FakeWindowAPI * fakeWindowAPI;
		Window * window;
		MenuController * controller;
		GameConfiguration * config;

		TEST_METHOD_INITIALIZE(GameControllerTests_Initialize)
		{
			fakeWindowAPI = new FakeWindowAPI(640, 480, "Super beau dessin");
			window = new Window(*fakeWindowAPI);
			config = new GameConfiguration();
			controller = new MenuController(config);

			window->setWindowController(*controller);
		}

		TEST_METHOD_CLEANUP(GameControllerTests_CleanUp)
		{
			delete controller;
			delete fakeWindowAPI;
			delete window;
			delete config;
		}

		TEST_METHOD(menu_at_loading_should_get_four_buttons)
		{
			//Arrange
			const int TOTAL_BUTTONS_ON_GAME_SCREEN = 4;

			//Action
			window->render();

			//Assert
			Assert::AreEqual(TOTAL_BUTTONS_ON_GAME_SCREEN, fakeWindowAPI->drawButton_getnumberOfCall());
		}
		TEST_METHOD(menu_should_not_try_to_manage_an_input_if_window_observer_is_invalid)
		{
			//Arrange
			bool exceptionThrown = false;

			//Action
			try
			{
				Window * invalidWindow = nullptr;
				controller->addWindowObservers(*invalidWindow);
				window->mouseInput(Point(151, 100));
			}
			catch (invalid_argument e)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}
		TEST_METHOD(if_player_clicks_on_play_button_a_game_is_started)
		{
			//Arrange
			const int NUMBER_OF_BUTTONS_LOADED_ON_GAME_SCREEN = 10;
			window->mouseInput(Point(151, 100));  //Coordinates of Play button

			//Action
			window->render();

			//Assert
			Assert::AreEqual(NUMBER_OF_BUTTONS_LOADED_ON_GAME_SCREEN, fakeWindowAPI->drawButton_getnumberOfCall());
		}
		TEST_METHOD(if_player_clicks_on_the_gear_then_options_are_shown)
		{
			//Arrange
			const int NUMBER_OF_BUTTONS_LOADED_ON_OPTION_SCREEN = 13;
			window->mouseInput(Point(541, 381));  //Coordinates of Option button

			//Action
			window->render();

			//Assert
			Assert::AreEqual(NUMBER_OF_BUTTONS_LOADED_ON_OPTION_SCREEN, fakeWindowAPI->drawButton_getnumberOfCall());
		}
	};
}