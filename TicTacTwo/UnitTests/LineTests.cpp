#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Platform/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(LineTests)
	{
	public:
		Line * line;

		TEST_METHOD_INITIALIZE(LineTests_Initialize)
		{
			line = new Line();
		}

		TEST_METHOD_CLEANUP(LineTests_CleanUp)
		{
			delete line;
		}

		TEST_METHOD(getOrientation_should_return_the_line_orientation)
		{
			//Arrange
			Line::LINE_ORIENTATION orientation = Line::VERTICAL;
			Tile * tile1 = new Tile();
			Tile * tile2 = new Tile();
			tile1->setPosition(Point(0, 1));
			tile2->setPosition(Point(0, 2));
			line->addFront(tile1);
			line->addFront(tile2);

			//Action
			Line::LINE_ORIENTATION returnedOrientation = line->getOrientation();

			//Assert
			Assert::IsTrue(orientation == returnedOrientation);

			delete tile1, tile2;
		}

		TEST_METHOD(getSize_should_return_the_number_of_tile_composing_the_line)
		{
			//Arrange
			const int lineSize = 2;
			Line::LINE_ORIENTATION orientation = Line::VERTICAL;
			Tile * tile1 = new  Tile();
			Tile * tile2 = new Tile();
			tile1->setPosition(Point(0, 1));
			tile2->setPosition(Point(0, 2));
			line->addFront(tile1);
			line->addFront(tile2);

			//Action
			const int returnedSize = line->getSize();

			//Assert
			Assert::AreEqual(lineSize, returnedSize);

			delete tile1, tile2;
		}

		TEST_METHOD(addFront_should_add_tile_to_the_front)
		{
			//Arrange
			Line::LINE_ORIENTATION orientation = Line::VERTICAL;
			Tile * tile1 = new  Tile(Tile::X_TYPE);
			Tile * tile2 = new Tile(Tile::O_TYPE); //Front tile
			tile1->setPosition(Point(0, 1));
			tile2->setPosition(Point(0, 2));

			//Action
			line->addFront(tile1);
			line->addFront(tile2);

			const Tile returnedTile = line->getFrontTile();
			
			//Assert
			Assert::IsTrue(tile2->getTileType() == returnedTile.getTileType());

			delete tile2, tile1;
		}

		TEST_METHOD(addBack_should_add_tile_to_the_front)
		{
			//Arrange
			Line::LINE_ORIENTATION orientation = Line::VERTICAL;
			Tile * tile1 = new  Tile(Tile::X_TYPE);
			Tile * tile2 = new Tile(Tile::O_TYPE); //Back tile
			tile1->setPosition(Point(0, 1));
			tile2->setPosition(Point(0, 2));

			//Action
			line->addBack(tile1);
			line->addBack(tile2);

			const Tile returnedTile = line->getBackTile();

			//Assert
			Assert::IsTrue(tile2->getTileType() == returnedTile.getTileType());

		}

		TEST_METHOD(getFrontTile_should_reuturn_the_front_tile)
		{
			//Arrange
			Line::LINE_ORIENTATION orientation = Line::VERTICAL;
			Tile * tile1 = new  Tile(Tile::X_TYPE);
			Tile * tile2 = new Tile(Tile::O_TYPE);
			Tile * tile3 = new Tile(Tile::EMPTY_TYPE);
			tile1->setPosition(Point(0, 0));
			tile2->setPosition(Point(0, 1));
			tile3->setPosition(Point(0, 2));
			line->addFront(tile3);
			line->addFront(tile2);
			line->addFront(tile1);

			Tile::TILE_TYPE typeOfFirstAddedTile = Tile::X_TYPE;

			//Action
			Tile::TILE_TYPE returnedType = line->getFrontTile().getTileType();

			//Assert
			Assert::IsTrue(typeOfFirstAddedTile == returnedType);

			delete tile1, tile2, tile3;
		}

		TEST_METHOD(getBackTile_should_return_the_last_added_tile)
		{
			//Arrange
			Line::LINE_ORIENTATION orientation = Line::VERTICAL;

			Tile * tile1 = new  Tile(Tile::X_TYPE);
			Tile * tile2 = new Tile(Tile::O_TYPE);
			Tile * tile3 = new Tile(Tile::EMPTY_TYPE);
			tile1->setPosition(Point(0, 0));
			tile2->setPosition(Point(0, 1));
			tile3->setPosition(Point(0, 2));
			line->addBack(tile1);
			line->addBack(tile2);
			line->addBack(tile3);

			Tile::TILE_TYPE typeOfFirstAddedTile = Tile::EMPTY_TYPE;

			//Action
			Tile::TILE_TYPE returnedType = line->getBackTile().getTileType();

			//Assert
			Assert::IsTrue(typeOfFirstAddedTile == returnedType);

			delete tile1, tile2, tile3;
		}
	};
}