#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Platform/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TileTests)
	{
	public:
		
		TEST_METHOD(getType_should_return_the_right_type)
		{
			//Arrange
			const Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;
			Tile tile = Tile(TILE_TYPE);

			//Action
			Tile::TILE_TYPE returnedType = tile.getTileType();

			//Assert
			Assert::AreEqual((char)TILE_TYPE, (char)returnedType);
		}

		TEST_METHOD(default_tile_type_is_empty)
		{
			//Arrange
			Tile tile;

			//Assert
			Assert::AreEqual((char)Tile::EMPTY_TYPE, (char)tile.getTileType());
		}

		TEST_METHOD(changeTileType_should_correctly_change_the_tile_type)
		{
			//Arrange
			const Tile::TILE_TYPE NEW_TYPE = Tile::X_TYPE;
			Tile tile = Tile();

			//Action
			tile.changeType(NEW_TYPE);
			Tile::TILE_TYPE returnedType = tile.getTileType();

			//Assert
			Assert::AreEqual((char)NEW_TYPE, (char)returnedType);
		}

		TEST_METHOD(changing_the_type_of_non_empty_tile_should_throw_exception)
		{
			//Arrange
			const Tile::TILE_TYPE NEW_TYPE = Tile::X_TYPE;
			Tile tile = Tile(Tile::O_TYPE);

			//Action
			bool exceptionThrown = false;
			try
			{
				tile.changeType(NEW_TYPE);
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);			
		}

		TEST_METHOD(the_operator_double_equal_should_return_true_when_comparing_tiles_of_same_type)
		{
			//Arrange
			const Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;
			Tile tile1 = Tile(TILE_TYPE);
			Tile tile2 = Tile(TILE_TYPE);

			//Action
			bool trueIsReturned = (tile1 == tile2);

			//Assert
			Assert::IsTrue(trueIsReturned);
		}

		TEST_METHOD(setPosition_should_set_the_position)
		{
			//Arrange
			const Tile::TILE_TYPE TILE_TYPE = Tile::X_TYPE;
			const Point SET_POSITION(2, 2);
			Tile tile1 = Tile(TILE_TYPE);
			
			//Action
			tile1.setPosition(SET_POSITION);
			Point returnedPoint = tile1.getPosition();

			//Assert
			Assert::IsTrue(SET_POSITION == returnedPoint);

		}

	};
}