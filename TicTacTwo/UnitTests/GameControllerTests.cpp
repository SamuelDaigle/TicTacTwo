#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Controllers/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(GameControllerTests)
	{
	public:
		FakeWindowAPI * fakeWindowAPI;
		Window * window;
		GameController * controller;
		GameConfiguration * config;

		TEST_METHOD_INITIALIZE(GameControllerTests_Initialize)
		{
			fakeWindowAPI = new FakeWindowAPI(640, 480, "Super beau dessin");
			window = new Window(*fakeWindowAPI);
			config = new GameConfiguration();
			controller = new GameController(config);

			window->setWindowController(*controller);
		}

		TEST_METHOD_CLEANUP(GameControllerTests_CleanUp)
		{
			delete fakeWindowAPI;
			delete window;
			delete config;
		}

		TEST_METHOD(when_a_game_controller_is_created_there_should_be_10_buttons_on_screen)
		{
			//Arrange
			const int TOTAL_BUTTONS_ON_GAME_SCREEN = 10;

			//Action
			window->render();

			//Assert
			Assert::AreEqual(TOTAL_BUTTONS_ON_GAME_SCREEN, fakeWindowAPI->drawButton_getnumberOfCall());
		}

		TEST_METHOD(when_player_clicks_on_back_he_will_be_returned_to_the_menu)
		{
			//Arrange
			const int TOTAL_BUTTONS_ON_MENU_SCREEN = 4;
			window->mouseInput(Point(545, 1));

			//Action
			window->render();

			//Assert
			Assert::AreEqual(TOTAL_BUTTONS_ON_MENU_SCREEN, fakeWindowAPI->drawButton_getnumberOfCall());
		}


		TEST_METHOD(if_tile_chosen_does_not_complete_dial_then_no_buttons_are_added)
		{
			//Arrange
			const int TOTAL_BUTTONS_ON_GAME_SCREEN = 10;
			window->mouseInput(Point(20, 20));

			//Action
			window->render();

			//Assert
			Assert::AreEqual(TOTAL_BUTTONS_ON_GAME_SCREEN, fakeWindowAPI->drawButton_getnumberOfCall());
		}

		TEST_METHOD(when_a_dial_is_complete_a_new_dial_is_created)
		{
			//Arrange
			const int TOTAL_BUTTONS_ON_GAME_SCREEN = 20;

			//Moves required to complete a dial
			for (int x = 1; x <= 141; x += 70)
			{
				for (int y = 1; y <= 141; y += 70)
				{
					window->mouseInput(Point(x, y));
				}
			}

			//Action
			window->render();

			//Assert
			Assert::AreEqual(TOTAL_BUTTONS_ON_GAME_SCREEN, fakeWindowAPI->drawButton_getnumberOfCall());
		}

		TEST_METHOD(when_the_grid_is_complete_no_more_tiles_are_created)
		{
			//Arrange
			const int TOTAL_BUTTONS_ON_GAME_SCREEN = 41;

			//Moves required to complete the first dial
			for (int x = 1; x <= 141; x += 70)
			{
				for (int y = 1; y <= 141; y += 70)
				{
					window->mouseInput(Point(x, y));
					controller->updateWindow();
				}
			}

			//Moves required to complete the second dial
			for (int x = 211; x <= 351; x += 70)
			{
				for (int y = 1; y <= 141; y += 70)
				{
					window->mouseInput(Point(x, y));
					controller->updateWindow();
				}
			}

			//Moves required to complete the third dial
			for (int x = 1; x <= 141; x += 70)
			{
				for (int y = 211; y <= 351; y += 70)
				{
					window->mouseInput(Point(x, y));
					controller->updateWindow();
				}
			}	//All dials are created

			//Moves required to complete the fourth dial
			for (int x = 211; x <= 351; x += 70)
			{
				for (int y = 211; y <= 351; y += 70)
				{
					window->mouseInput(Point(x, y));
					controller->updateWindow();
				}
			}	//Grid is now complete

			//Action
			window->render();

			//Assert
			Assert::AreEqual(fakeWindowAPI->drawButton_getnumberOfCall(), TOTAL_BUTTONS_ON_GAME_SCREEN);
		}
	};
}