#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Platform/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(GridTests)
	{
	public:
		const unsigned int GRID_X_DIMENSION = 6;
		const unsigned int GRID_Y_DIMENSION = 6;
		const unsigned int GRID_X_DIALS = 2;
		const unsigned int GRID_Y_DIALS = 2;
		Grid * grid;

		TEST_METHOD_INITIALIZE(GridTests_Initialize)
		{
			grid = new Grid();
		}

		TEST_METHOD_CLEANUP(GridTests_CleanUp)
		{
			delete grid;
		}

		TEST_METHOD(enabledDial_should_enable_the_dial_at_specified_position)
		{
			//Arrange
			const int X_POSITION = 0;
			const int Y_POSITION = 0;
			const Tile::TILE_TYPE TILE_TYPE = Tile::O_TYPE;

			//Action
			grid->enableDial(X_POSITION, Y_POSITION);

				//If dial is not activated, seTile() will launch exception
			bool exceptionThrown = false;
			try
			{
				grid->setTile(TILE_TYPE, X_POSITION, Y_POSITION);
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsFalse(exceptionThrown);
			
		}

		TEST_METHOD(getTile_should_return_the_tile_from_the_specified_position)
		{
			//Arrange
			int DIAL_X_POSITION = 1;
			int DIAL_Y_POSITION = 1;
			int TILE_X_POSITION = 5;
			int TILE_Y_POSITION = 5;
			Tile::TILE_TYPE TILE_TYPE = Tile::EMPTY_TYPE;

			grid->enableDial(DIAL_X_POSITION, DIAL_Y_POSITION);

			//Action
			Tile::TILE_TYPE returnedType = grid->getTile(TILE_X_POSITION, TILE_Y_POSITION)->getTileType();

			//Assert
			Assert::IsTrue(TILE_TYPE == returnedType);
		}

		TEST_METHOD(setTile_should_set_the_tile_at_the_specified_position)
		{
			//Arrange
			const int X_POSITION = 0;
			const int Y_POSITION = 0;
			const Tile::TILE_TYPE TILE_TYPE = Tile::O_TYPE;

			grid->enableDial(X_POSITION, Y_POSITION);

			//Action
			grid->setTile(TILE_TYPE, X_POSITION, Y_POSITION);

			Tile::TILE_TYPE returnedType = grid->getTile(X_POSITION, Y_POSITION)->getTileType();

			//Assert
			Assert::IsTrue(TILE_TYPE == returnedType);
		}

		TEST_METHOD(addLine_should_add_a_line_to_the_grid)
		{
			//Arrange
			const int NUMBER_OF_LINES = 1;
			Line * line = new Line();

			//Action
			grid->addLine(line);

			const int numberOfStoredLines = grid->getLines().size();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, numberOfStoredLines);
		}

		TEST_METHOD(getLines_should_return_all_the_lines)
		{
			//Arrange
			const int NUMBER_OF_LINES = 4;
			Line * line = new Line();

			//Action
			grid->addLine(line);
			grid->addLine(line);
			grid->addLine(line);
			grid->addLine(line);

			const int numberOfStoredLines = grid->getLines().size();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, numberOfStoredLines);
		}

		TEST_METHOD(isFull_should_return_true_if_all_dials_are_enbled_and_full)
		{
			//Arrange
			fillGrid();

			//Action
			bool isFull = grid->isFull();

			//Assert
			Assert::IsTrue(isFull);
		}

		TEST_METHOD(isFull_should_return_false_if_all_dials_are_enbled_and_full)
		{
			//Arrange
			grid->enableDial(0, 0);

			//Action
			bool isFull = grid->isFull();

			//Assert
			Assert::IsFalse(isFull);
		}

		TEST_METHOD(getTile_on_a_disabled_dial_should_return_null)
		{
			//Arrange
			const unsigned int X_POSITION = 0;
			const unsigned int Y_POSITION = 0;
			const Tile * TILE = nullptr;

			//Action
			const Tile * tile = grid->getTile(X_POSITION, Y_POSITION);

			//Assert
			Assert::IsTrue(TILE == tile);
		}

		TEST_METHOD(getTile_with_invalid_x_position_should_return_null)
		{
			//Arrange
			const unsigned int X_POSITION = 34;
			const unsigned int Y_POSITION = 0;
			const Tile * TILE = nullptr;

			enableAllDials();

			//Action
			const Tile * tile = grid->getTile(X_POSITION, Y_POSITION);

			//Assert
			Assert::IsTrue(TILE == tile);
		}

		TEST_METHOD(getTile_with_invalid_y_position_should_return_null)
		{
			//Arrange
			const unsigned int X_POSITION = 0;
			const unsigned int Y_POSITION = 34;
			const Tile * TILE = nullptr;

			enableAllDials();

			//Action
			const Tile * tile = grid->getTile(X_POSITION, Y_POSITION);

			//Assert
			Assert::IsTrue(TILE == tile);
		}

		TEST_METHOD(setTile_on_a_disabled_dial_should_throw_exception)
		{
			//Arrange
			const unsigned int X_POSITION = 0;
			const unsigned int Y_POSITION = 0;
			const Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;

			//Action
			bool exceptionThrown = false;
			try
			{
				grid->setTile(TILE_TYPE, X_POSITION, Y_POSITION);
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(setTile_with_invalid_x_position_should_throw_exception)
		{
			//Arrange
			const unsigned int X_POSITION = 43;
			const unsigned int Y_POSITION = 0;
			const Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;

			enableAllDials();

			//Action
			bool exceptionThrown = false;
			try
			{
				grid->setTile(TILE_TYPE, X_POSITION, Y_POSITION);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(setTile_with_invalid_y_position_should_throw_exception)
		{
			//Arrange
			const unsigned int X_POSITION = 0;
			const unsigned int Y_POSITION = 43;
			const Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;

			enableAllDials();

			//Action
			bool exceptionThrown = false;
			try
			{
				grid->setTile(TILE_TYPE, X_POSITION, Y_POSITION);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(setTile_on_a_non_changeble_tile_should_throw_exception)
		{
			//Arrange
			const unsigned int X_POSITION = 0;
			const unsigned int Y_POSITION = 0;
			const Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;

			enableAllDials();

			grid->setTile(TILE_TYPE, X_POSITION, Y_POSITION);

			//Action
			bool exceptionThrown = false;
			try
			{
				grid->setTile(TILE_TYPE, X_POSITION, Y_POSITION);
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(when_enabling_dial_all_tiles_should_have_their_position)
		{
			//Arrange
			int DIAL_X_POSITION = 0;
			int DIAL_Y_POSITION = 0;

			//Action
			grid->enableDial(DIAL_X_POSITION, DIAL_Y_POSITION);

			//Assert
			Assert::IsTrue(isTilesPositionGood());
			
		}

		TEST_METHOD(enableDial_with_point_parameter_enable_the_dial_at_specified_position)
		{
			//Arrange
			const Point * POSITION = new Point(0, 0);
			const Tile::TILE_TYPE TILE_TYPE = Tile::O_TYPE;

			//Action
			grid->enableDial(POSITION);

			//If dial is not activated, seTile() will launch exception
			bool exceptionThrown = false;
			try
			{
				grid->setTile(TILE_TYPE, POSITION);
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsFalse(exceptionThrown);
			delete POSITION;
		}

		TEST_METHOD(setTile_with_point_parameter_should_set_the_tile_at_the_specified_position)
		{
			//Arrange
			const Point * POSITION = new Point(0,0);
			const Tile::TILE_TYPE TILE_TYPE = Tile::O_TYPE;

			grid->enableDial(POSITION);

			//Action
			grid->setTile(TILE_TYPE,POSITION);

			Tile::TILE_TYPE returnedType = grid->getTile(POSITION)->getTileType();

			//Assert
			Assert::IsTrue(TILE_TYPE == returnedType);
			delete POSITION;
		}

		TEST_METHOD(getTile_with_point_parameter_should_return_the_tile_from_the_specified_position)
		{
			//Arrange
			int DIAL_X_POSITION = 1;
			int DIAL_Y_POSITION = 1;
			const Point * TILE_POSITION = new Point(5, 5);
			Tile::TILE_TYPE TILE_TYPE = Tile::EMPTY_TYPE;

			grid->enableDial(DIAL_X_POSITION, DIAL_Y_POSITION);

			//Action
			Tile::TILE_TYPE returnedType = grid->getTile(TILE_POSITION)->getTileType();

			//Assert
			Assert::IsTrue(TILE_TYPE == returnedType);
			delete TILE_POSITION;
		}

		TEST_METHOD(enableDial_with_null_point_should_throw_exception)
		{
			//Arrange
			const Point * DIAL_POSITION = nullptr;

			//Action
			bool exceptionThrown = false;
			try
			{
				grid->enableDial(DIAL_POSITION);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(getTile_with_null_point_should_return_null)
		{
			//Arrange
			int DIAL_X_POSITION = 1;
			int DIAL_Y_POSITION = 1;
			const Point * TILE_POSITION = nullptr;
			Tile::TILE_TYPE TILE_TYPE = Tile::EMPTY_TYPE;

			grid->enableDial(DIAL_X_POSITION, DIAL_Y_POSITION);

			//Action
			 Tile * returnedTile = grid->getTile(TILE_POSITION);

			//Assert
			Assert::IsTrue(nullptr == returnedTile);
		}

		TEST_METHOD(setTile_with_null_point_should_throw_exception)
		{
			//Arrange
			int DIAL_X_POSITION = 1;
			int DIAL_Y_POSITION = 1;
			const Point * TILE_POSITION = nullptr;
			Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;

			grid->enableDial(DIAL_X_POSITION, DIAL_Y_POSITION);

			//Action
			bool exceptionThrown = false;
			try
			{
				grid->setTile(TILE_TYPE, TILE_POSITION);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}			

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(eraseLine_should_reduce_the_size_of_the_vetor_of_lines)
		{
			//Assert
			Line * line1 = new Line();
			Line * line2 = new Line();
			const int NEW_SIZE = 1;
			grid->addLine(line1);
			grid->addLine(line2);

			//Action
			grid->eraseLine(1);
			int size = grid->getLines().size();

			//Assert
			Assert::AreEqual(size, NEW_SIZE);

			delete line1, line2;

		}

		TEST_METHOD(eraseLine_with_invalid_index_should_throw_exception)
		{
			//Assert
			Line * line1 = new Line();
			Line * line2 = new Line();
			grid->addLine(line1);
			grid->addLine(line2);

			//Action
			bool exceptionThrown = false;
			try
			{
				grid->eraseLine(10);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}

			grid->eraseLine(1);

			//Assert
			Assert::IsTrue(exceptionThrown);

			delete line1, line2;
		}

		void fillGrid()
		{
			grid->enableDial(0, 0);
			grid->enableDial(0, 1);
			grid->enableDial(1, 0);
			grid->enableDial(1, 1);

			const Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;

			for (unsigned int indexX = 0; indexX < GRID_X_DIMENSION; ++indexX)
			{
				for (unsigned int indexY = 0; indexY < GRID_Y_DIMENSION; ++indexY)
				{
					grid->setTile(TILE_TYPE, indexX, indexY);
				}
			}
		}

		void enableAllDials()
		{
			for (unsigned int indexX = 0; indexX < GRID_X_DIALS; ++indexX)
			{
				for (unsigned int indexY = 0; indexY < GRID_Y_DIALS; ++indexY)
				{
					grid->enableDial(indexX, indexY);
				}
			}
		}

		bool isTilesPositionGood()
		{
			for (unsigned int indexX = 0; indexX < 3; ++indexX)
			{
				for (unsigned int indexY = 0; indexY < 3; ++indexY)
				{
					if (grid->getTile(indexX, indexY)->getPosition() != Point(indexX, indexY))
					{
						return false;
					}
				}
			}
			return true;
		}

	};
}