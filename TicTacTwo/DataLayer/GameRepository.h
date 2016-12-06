#pragma once

#include "stdafx.h"

#include "sqlite3.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class GameRepository
{
public:
	GameRepository(const string& _databasePath);
	~GameRepository();
	void setCurrentGame(int _gameID);
	Grid* getGridFromGame();
	bool isDialEnabled(int _xPosition, int _yPosition) const;
	void enableDial(int _xPosition, int _yPosition) const;
	void saveGame(const Grid& _grid) const;

	const Tile::TILE_TYPE getTileType(int _xPosition, int _yPosition) const;
	void updateTileType(int _xPosition, int _yPosition, const Tile::TILE_TYPE& _tileType) const;


private:
	struct TileStructure
	{
		int id = 0;
		char type = 'E';
		int x_position = 0;
		int y_position = 0;
	};

	void setUpdatedTileToGrid(const TileStructure& _tileStructure) const;
	const Tile::TILE_TYPE convertCharToTileType(char _charTileType) const;
	char convertTileTypeToChar(const Tile::TILE_TYPE& _tileType) const;
	void executeCommand(char* _command, bool _errorCheck = true) const;


	sqlite3* database;
	vector<TileStructure*> tiles;
	Grid* grid;
	int currentGameId;
};

