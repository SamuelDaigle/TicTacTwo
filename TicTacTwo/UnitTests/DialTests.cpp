#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Platform/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(DialTests)
	{
	public:
		Dial * dial;
		const unsigned int DIAL_X_DIMENSION = 3;
		const unsigned int DIAL_Y_DIMENSION = 3;

		TEST_METHOD_INITIALIZE(DialTests_Initialize)
		{
			dial = new Dial();
		}

		TEST_METHOD_CLEANUP(DialTests_CleanUp)
		{
			delete dial;
		}
		
		TEST_METHOD(isEnabled_should_return_the_state_of_the_dial)
		{
			//Arrange
			bool isEnabled = true;

			//Action
			isEnabled = dial->isEnabled();

			//Assert
			Assert::IsFalse(isEnabled);
		}

		TEST_METHOD(setEnabled_should_enable_the_dial)
		{
			//Arrange
			bool enabled = false;

			//Action
			dial->setEnabled();
			enabled = dial->isEnabled();

			//Assert
			Assert::IsTrue(enabled);
		}

		TEST_METHOD(getTile_should_return_the_right_tile)
		{
			//Arrange
			dial->setEnabled();
			const Tile::TILE_TYPE TILE_TYPE = Tile::EMPTY_TYPE;
			const int X_POSITION = 2;
			const int Y_POSITION = 2;
			
			//Action

			//Assert
			Assert::AreEqual((char)TILE_TYPE, (char)dial->getTile(X_POSITION, Y_POSITION).getTileType());

		}

		TEST_METHOD(all_tiles_of_new_dial_should_be_empty)
		{
			//Arrange
			dial->setEnabled();

			//Action
			bool areAllEmpty = areTilesAllEmpty();

			//Assert
			Assert::IsTrue(areAllEmpty);
		}

		TEST_METHOD(setTile_should_change_the_type_of_the_tile)
		{
			//Arrange
			dial->setEnabled();
			const int X_POSITION = 2;
			const int Y_POSITION = 2;
			Tile::TILE_TYPE newType = Tile::O_TYPE;

			//Action
			dial->setTile(newType, X_POSITION, Y_POSITION);

			//Assert
			Assert::AreEqual((char)newType, (char)dial->getTile(X_POSITION, Y_POSITION).getTileType());
		}

		TEST_METHOD(setTile_on_a_non_changeble_tile_should_throw_exception)
		{
			//Arrange
			dial->setEnabled();
			const int X_POSITION = 2;
			const int Y_POSITION = 2;
			Tile::TILE_TYPE type = Tile::O_TYPE;
			dial->setTile(type, X_POSITION, Y_POSITION);

			//Action
			bool exceptionThrown = false;
			try
			{
				dial->setTile(type, X_POSITION, Y_POSITION);
			}
			catch(std::runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(isFull_should_return_false_if_dial_contains_empty_tiles)
		{
			//Arrange
			dial->setEnabled();
			dial->setTile(Tile::O_TYPE, 2, 1);
			dial->setTile(Tile::O_TYPE, 1, 1);
			dial->setTile(Tile::O_TYPE, 0, 2);
			dial->setTile(Tile::O_TYPE, 0, 0);

			//Action
			bool isFull = dial->isFull();

			//Assert
			Assert::IsFalse(isFull);
		}

		TEST_METHOD(isFull_should_return_true_if_dial_doesnt_contain_empty_tiles)
		{
			//Arrange
			dial->setEnabled();
			fillDial();

			//Action
			bool isFull = dial->isFull();

			//Assert
			Assert::IsTrue(isFull);
		}

		TEST_METHOD(call_setTile_when_dial_is_disabled_should_throw_exception)
		{
			//Arrange
			const int X_POSITION = 2;
			const int Y_POSITION = 2;
			Tile::TILE_TYPE type = Tile::O_TYPE;
			
			//Action
			bool exceptionThrown = false;
			try
			{
				dial->setTile(type, X_POSITION, Y_POSITION);
			}
			catch (std::runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(call_getTile_when_dial_is_disabled_should_throw_exception)
		{
			//Arrange
			const int X_POSITION = 2;
			const int Y_POSITION = 2;

			//Action
			bool exceptionThrown = false;
			try
			{
				dial->getTile(X_POSITION, Y_POSITION);
			}
			catch (std::runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(call_isFull_when_dial_is_disabled_should_throw_exception)
		{		
			//Arrange
			const int X_POSITION = 2;
			const int Y_POSITION = 2;

			//Action
			bool exceptionThrown = false;
			try
			{
				dial->getTile(X_POSITION, Y_POSITION);
			}
			catch (std::runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(getTile_with_invalid_x_position_should_throw_exception)
		{
			//Arrange
			const int X_POSITION = 20;
			const int Y_POSITION = 2;
			dial->setEnabled();
			//Action
			bool exceptionThrown = false;
			try
			{
				dial->getTile(X_POSITION, Y_POSITION);
			}
			catch (std::invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(getTile_with_invalid_y_position_should_throw_exception)
		{
			//Arrange
			const int X_POSITION = 2;
			const int Y_POSITION = 20;
			dial->setEnabled();
			//Action
			bool exceptionThrown = false;
			try
			{
				dial->getTile(X_POSITION, Y_POSITION);
			}
			catch (std::invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(setTile_with_invalid_x_position_should_throw_exception)
		{
			//Arrange
			const int X_POSITION = 20;
			const int Y_POSITION = 2;
			const Tile::TILE_TYPE TILE_TYPE = Tile::O_TYPE;

			dial->setEnabled();
			//Action
			bool exceptionThrown = false;
			try
			{
				dial->setTile(TILE_TYPE, X_POSITION, Y_POSITION);
			}
			catch (std::invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(setTile_with_invalid_y_position_should_throw_exception)
		{
			//Arrange
			const int X_POSITION = 2;
			const int Y_POSITION = -20;
			Tile::TILE_TYPE TILE_TYPE = Tile::O_TYPE;

			dial->setEnabled();
			//Action
			bool exceptionThrown = false;
			try
			{
				dial->setTile(TILE_TYPE, X_POSITION, Y_POSITION);
			}
			catch (std::invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		

		bool areTilesAllEmpty()
		{
			for (unsigned int indexX = 0; indexX < DIAL_X_DIMENSION; ++indexX)
			{
				for (unsigned int indexY = 0; indexY < DIAL_Y_DIMENSION; ++indexY)
				{
					if (dial->getTile(indexX, indexY).getTileType() != Tile::EMPTY_TYPE)
					{
						return false;
					}
				}
			}
			return true;
		}

		void fillDial()
		{
			for (unsigned int indexX = 0; indexX < DIAL_X_DIMENSION; ++indexX)
			{
				for (unsigned int indexY = 0; indexY < DIAL_Y_DIMENSION; ++indexY)
				{
					dial->setTile(Tile::X_TYPE, indexX, indexY);
				}
			}
		}
	};
}