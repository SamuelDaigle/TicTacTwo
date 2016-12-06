#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTests
{
	TEST_CLASS(GameRepositoryTests)
	{
	public:
		GameDatabaseHelper* databaseHelper;
		GameRepository* repository;
		Grid* emptyGrid;
		const string DATABASE_PATH = "game.bd";

		TEST_METHOD_INITIALIZE(GameRepositoryTests_Initialize)
		{
			databaseHelper = new GameDatabaseHelper(DATABASE_PATH);
			repository = new GameRepository(DATABASE_PATH);
			repository->setCurrentGame(1);
			emptyGrid = new Grid;

			databaseHelper->dropDatabase(); // in case other tests failed before.
			databaseHelper->createDatabase();
			databaseHelper->seedGameDatabase(1);
		}

		TEST_METHOD_CLEANUP(GameRepositoryTests_CleanUp)
		{
			databaseHelper->dropDatabase(); // in case other tests failed before.
			delete databaseHelper;
			delete repository;
			delete emptyGrid;
		}

		TEST_METHOD(reading_tiles_from_an_empty_grid_should_only_return_empty_tiles)
		{
			//Arrange
			bool foundNonEmptyTile = false;
			enableAllDials();

			//Action
			Grid* gridWithEmptyTiles = repository->getGridFromGame();
			foundNonEmptyTile = areAllTilesEmpty(*gridWithEmptyTiles);

			//Assert
			Assert::IsFalse(foundNonEmptyTile);
		}

		TEST_METHOD(reading_if_it_is_enabled_should_return_true_when_the_dial_is_enabled)
		{
			//Arrange

			//Action
			repository->enableDial(0, 0);
			bool isEnabledDial = repository->isDialEnabled(0, 0);

			//Assert
			Assert::IsTrue(isEnabledDial);
		}

		TEST_METHOD(reading_if_it_is_enabled_should_return_false_when_the_dial_is_disabled)
		{
			//Arrange

			//Action
			bool isEnabledDial = repository->isDialEnabled(1, 0);

			//Assert
			Assert::IsFalse(isEnabledDial);
		}

		TEST_METHOD(enabling_a_dial_should_return_true_when_reading_if_it_is_enabled)
		{
			//Arrange

			//Action
			repository->enableDial(1, 1);
			bool isEnabledDial = repository->isDialEnabled(1, 1);

			//Assert
			Assert::IsTrue(isEnabledDial);
		}

		TEST_METHOD(enabling_all_dials_should_return_4_true_when_reading_if_it_is_enabled)
		{
			//Arrange
			const int EXPECTED_NB_ENABLED_DIALS = 4;
			int nbEnabledDials = 0;

			//Action
			enableAllDials();
			if (repository->isDialEnabled(0, 0)) nbEnabledDials++;
			if (repository->isDialEnabled(1, 0)) nbEnabledDials++;
			if (repository->isDialEnabled(0, 1)) nbEnabledDials++;
			if (repository->isDialEnabled(1, 1)) nbEnabledDials++;

			//Assert
			Assert::AreEqual(EXPECTED_NB_ENABLED_DIALS, nbEnabledDials);
		}

		TEST_METHOD(reading_an_empty_tile_should_return_an_empty_tile)
		{
			//Arrange
			const Tile::TILE_TYPE& EXPECTED_TILE_TYPE = Tile::EMPTY_TYPE;

			//Action
			const Tile::TILE_TYPE& tileType = repository->getTileType(0, 0);

			//Assert
			Assert::AreEqual(static_cast<int>(EXPECTED_TILE_TYPE), static_cast<int>(tileType)); // to compare enums.
		}

		TEST_METHOD(updating_to_an_x_tile_should_return_an_x_tile)
		{
			//Arrange
			const Tile::TILE_TYPE& EXPECTED_TILE_TYPE = Tile::X_TYPE;

			//Action
			repository->updateTileType(0, 0, Tile::X_TYPE);
			const Tile::TILE_TYPE& tileType = repository->getTileType(0, 0);

			//Assert
			Assert::AreEqual(static_cast<int>(EXPECTED_TILE_TYPE), static_cast<int>(tileType)); // to compare enums.
		}

		TEST_METHOD(updating_to_an_o_tile_should_return_an_o_tile)
		{
			//Arrange
			const Tile::TILE_TYPE& EXPECTED_TILE_TYPE = Tile::O_TYPE;

			//Action
			repository->updateTileType(0, 0, Tile::O_TYPE);
			const Tile::TILE_TYPE& tileType = repository->getTileType(0, 0);

			//Assert
			Assert::AreEqual(static_cast<int>(EXPECTED_TILE_TYPE), static_cast<int>(tileType)); // to compare enums.
		}

		TEST_METHOD(updating_to_an_x_tile_should_return_an_x_tile_inside_the_grid)
		{
			//Arrange
			const Tile::TILE_TYPE EXPECTED_TILE_TYPE = Tile::X_TYPE;
			enableAllDials();

			//Action
			repository->updateTileType(2, 3, Tile::X_TYPE);
			Grid* grid = repository->getGridFromGame();
			Tile::TILE_TYPE actualTileTypeInGrid = grid->getTile(2, 3)->getTileType();

			//Assert
			Assert::AreEqual(static_cast<int>(EXPECTED_TILE_TYPE), static_cast<int>(actualTileTypeInGrid)); // to compare enums.
		}

		TEST_METHOD(updating_5_x_tiles_should_have_5_modified_x_tiles_inside_the_grid)
		{
			//Arrange
			const int EXPECTED_NB_MODIFIED_TILES = 5;
			enableAllDials();

			//Action
			repository->updateTileType(2, 3, Tile::X_TYPE);
			repository->updateTileType(1, 3, Tile::X_TYPE);
			repository->updateTileType(2, 4, Tile::X_TYPE);
			repository->updateTileType(5, 5, Tile::X_TYPE);
			repository->updateTileType(2, 0, Tile::X_TYPE);
			Grid* grid = repository->getGridFromGame();
			int actualNbModifiedTilesInGrid = countModifiedTiles(*grid);
			
			//Assert
			Assert::AreEqual(EXPECTED_NB_MODIFIED_TILES, actualNbModifiedTilesInGrid);
		}

		TEST_METHOD(saving_a_new_grid_should_have_the_same_grid_when_returning_the_grid)
		{
			//Arrange
			Grid* newGrid = new Grid;
			newGrid->enableDial(0, 0);
			newGrid->enableDial(0, 1);
			newGrid->enableDial(1, 0);
			newGrid->enableDial(1, 1);
			newGrid->setTile(Tile::X_TYPE, 0, 0);

			//Action
			repository->saveGame(*newGrid);
			enableAllDials();
			Grid* gridReturnedByDB = repository->getGridFromGame();

			//Assert
			Assert::IsTrue(areGridEqual(*newGrid, *gridReturnedByDB));
		}

		void enableAllDials()
		{
			repository->enableDial(0, 0);
			repository->enableDial(0, 1);
			repository->enableDial(1, 0);
			repository->enableDial(1, 1);
		}

		bool areAllTilesEmpty(const Grid& _grid)
		{
			emptyGrid->enableDial(0, 0);
			emptyGrid->enableDial(1, 0);
			emptyGrid->enableDial(0, 1);
			emptyGrid->enableDial(1, 1);
			for (unsigned int x = 0; x < 6; x++)
			{
				for (unsigned int y = 0; y < 6; y++)
				{
					if (*emptyGrid->getTile(x, y) != *_grid.getTile(x, y))
					{
						return true;
					}
				}
			}
			return false;
		}

		int countModifiedTiles(const Grid& _grid)
		{
			int nbModifiedXTiles = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (_grid.getTile(i, j)->getTileType() == Tile::X_TYPE) nbModifiedXTiles++;
					if (_grid.getTile(i, j)->getTileType() == Tile::O_TYPE) nbModifiedXTiles++;
				}
			}
			return nbModifiedXTiles;
		}

		bool areGridEqual(const Grid& _grid, const Grid& _otherGrid)
		{
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (_grid.getTile(i, j)->getTileType() != _otherGrid.getTile(i, j)->getTileType()) return false;
				}
			}
			return true;
		}
	};
}