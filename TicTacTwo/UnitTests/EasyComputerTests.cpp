#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AI/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(EasyComputerTests)
	{
	public:
		Grid * testGrid;
		Computer * easyComputer;
		Tile::TILE_TYPE computerTileType = Tile::O_TYPE;

		TEST_METHOD_INITIALIZE(EasyComputerTests_Initialize)
		{
			testGrid = new Grid();
			easyComputer = new EasyComputer(*testGrid, computerTileType);
		}

		TEST_METHOD_CLEANUP(EasyComputerTests_CleanUp)
		{
			delete testGrid;
			delete easyComputer;
		}

		TEST_METHOD(getChoice_should_return_one_of_the_available_tile_in_grid)
		{
			//Arrange
			const Point DIAL_POSITION (0, 0);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);
			testGrid->setTile(Tile::X_TYPE, 0, 0);
			testGrid->setTile(Tile::O_TYPE, 2, 0);
			testGrid->setTile(Tile::X_TYPE, 1, 1);
			
			//Action
			const Point * chosenTile = easyComputer->getChoice();

			//Assert
			Assert::IsTrue(isChosenTileEmpty(*chosenTile));

		}

		TEST_METHOD(when_only_one_tile_is_available_get_choice_should_return_the_tile)
		{
			//Arrange
			const Point DIAL_POSITION(0, 0);
			const Point ONLY_EMPTY_TILE(2, 2);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);
			testGrid->setTile(Tile::X_TYPE, 0, 0);
			testGrid->setTile(Tile::O_TYPE, 0, 1);
			testGrid->setTile(Tile::O_TYPE, 1, 0);
			testGrid->setTile(Tile::X_TYPE, 1, 1);
			testGrid->setTile(Tile::X_TYPE, 0, 2);
			testGrid->setTile(Tile::O_TYPE, 2, 0);
			testGrid->setTile(Tile::O_TYPE, 2, 1);
			testGrid->setTile(Tile::O_TYPE, 1, 2);

			//Action
			const Point * chosenTile = easyComputer->getChoice();

			//Assert
			Assert::IsTrue(ONLY_EMPTY_TILE == *chosenTile);
		}

		TEST_METHOD(getChoice_when_no_dials_are_available_should_throw_exception)
		{
			//Arrange


			//Action
			bool exceptionThrown = false;

			try
			{
				easyComputer->getChoice();
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);

		}

		TEST_METHOD(getChoice_when_the_available_dials_are_full_should_throw_exception)
		{
			//Arrange
			const Point DIAL_POSITION(0, 0);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);
			testGrid->setTile(Tile::X_TYPE, 0, 0);
			testGrid->setTile(Tile::O_TYPE, 0, 1);
			testGrid->setTile(Tile::O_TYPE, 1, 0);
			testGrid->setTile(Tile::X_TYPE, 1, 1);
			testGrid->setTile(Tile::X_TYPE, 0, 2);
			testGrid->setTile(Tile::O_TYPE, 2, 0);
			testGrid->setTile(Tile::O_TYPE, 2, 1);
			testGrid->setTile(Tile::X_TYPE, 1, 2);
			testGrid->setTile(Tile::X_TYPE, 2, 2);

			//Action
			bool exceptionThrown = false;

			try
			{
				easyComputer->getChoice();
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}			

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		bool isChosenTileEmpty(const Point & _chosenTile)
		{
			Tile * tile = testGrid->getTile(_chosenTile.x, _chosenTile.y);

			return tile->getTileType() == Tile::EMPTY_TYPE;
		}
	};
}