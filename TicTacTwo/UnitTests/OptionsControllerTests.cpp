#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Controllers/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(OptionsControllerTests)
	{
	public:
		GameConfiguration * config;
		OptionsController * controller;
		string oTypeSkin1 = "OType.bmp";
		string oTypeSkin2 = "computerChoice.bmp";
		string xTypeSkin1 = "XType.bmp";
		string xTypeSkin2 = "christophe.bmp";

		TEST_METHOD_INITIALIZE(OptionsControllerTests_Initialize)
		{
			config = new GameConfiguration();
			controller = new OptionsController(config);
		}

		TEST_METHOD_CLEANUP(OptionsControllerTests_CleanUp)
		{
			delete config;
			delete controller;
		}

		TEST_METHOD(when_user_changes_difficulty_controller_changes_the_game_configuration)
		{
			//Arrange
			GameConfiguration::DIFFICULTY FIRST_SET = GameConfiguration::NORMAL;
			GameConfiguration::DIFFICULTY SECOND_SET = GameConfiguration::EASY;
			Button EASY_SELECTION;
			Button NORMAL_SELECTION;
			EASY_SELECTION.setText("EASY");
			NORMAL_SELECTION.setText("NORMAL");

			//Action
			controller->manageChoice(NORMAL_SELECTION);
			GameConfiguration::DIFFICULTY firstSet = config->gameDifficulty;

			controller->manageChoice(EASY_SELECTION);
			GameConfiguration::DIFFICULTY secondSet = config->gameDifficulty;

			//Assert
			Assert::IsTrue(FIRST_SET == firstSet);
			Assert::IsTrue(SECOND_SET == secondSet);
		}
		
		TEST_METHOD(when_user_changes_tile_type_controller_changes_the_game_configuration)
		{
			//Arrange
			Tile::TILE_TYPE FIRST_SET = Tile::O_TYPE;
			Tile::TILE_TYPE SECOND_SET = Tile::X_TYPE;
			Button O_SELECTION;
			Button X_SELECTION;
			O_SELECTION.setText("O_TYPE");
			X_SELECTION.setText("X_TYPE");

			//Action
			controller->manageChoice(O_SELECTION);
			Tile::TILE_TYPE firstSet = config->playerType;

			controller->manageChoice(X_SELECTION);
			Tile::TILE_TYPE secondSet = config->playerType;

			//Assert
			Assert::IsTrue(FIRST_SET == firstSet);
			Assert::IsTrue(SECOND_SET == secondSet);
		}

		TEST_METHOD(when_user_changes_tile_type_controller_changes_the_tiles_skin_options)
		{
			//Arrange
			Button O_SELECTION;
			Button X_SELECTION;
			O_SELECTION.setText("O_TYPE");
			X_SELECTION.setText("X_TYPE");

			//Action
			controller->manageChoice(O_SELECTION);
			string firstSet = config->playerImage;

			controller->manageChoice(X_SELECTION);
			string secondSet = config->playerImage;

			//Assert
			Assert::IsTrue(oTypeSkin1 == firstSet);
			Assert::IsTrue(xTypeSkin1 == secondSet);
		}

		TEST_METHOD(when_user_changes_tile_skin_controller_changes_the_game_configuration)
		{
			//Arrange
			string FIRST_SET = xTypeSkin2;
			string SECOND_SET = xTypeSkin1;
			Button CUSTOM_SKIN;
			Button DEFAULT_SKIN;
			CUSTOM_SKIN.setText("CUSTOM");
			DEFAULT_SKIN.setText("DEFAULT");

			//Action
			controller->manageChoice(CUSTOM_SKIN);
			string firstSet = config->playerImage;

			controller->manageChoice(DEFAULT_SKIN);
			string secondSet = config->playerImage;

			//Assert
			Assert::IsTrue(FIRST_SET == firstSet);
			Assert::IsTrue(SECOND_SET == secondSet);
		}
	};
}