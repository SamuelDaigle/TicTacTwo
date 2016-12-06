#include "stdafx.h"


GameRepository::GameRepository(const string& _databasePath)
{
	int returnCodeError = sqlite3_open(_databasePath.c_str(), &database);
	if (returnCodeError != SQLITE_OK) throw runtime_error("Could not open database: " + _databasePath);
	grid = new Grid();
	currentGameId = 0;
}

GameRepository::~GameRepository()
{
	for each (TileStructure* tileStruct in tiles)
	{
		delete tileStruct;
	}
	sqlite3_close(database);
	delete grid;
}

void GameRepository::setCurrentGame(int _gameID)
{
	currentGameId = _gameID;
}

Grid* GameRepository::getGridFromGame()
{
	if (currentGameId == 0) throw runtime_error("Current game id is not set.");
	sqlite3_stmt* sqlStatement;
	string sqlDynamicCommand = "SELECT * FROM TILE INNER JOIN GAME ON GAME.ID = TILE.GAME_ID WHERE GAME.ID = " + to_string(currentGameId) + ";";
	int returnCodeError;
	char* sqliteChar;

	// enable dials to put the tiles.
	if (isDialEnabled(0, 0)) grid->enableDial(0, 0);
	if (isDialEnabled(0, 1)) grid->enableDial(0, 1);
	if (isDialEnabled(1, 0)) grid->enableDial(1, 0);
	if (isDialEnabled(1, 1)) grid->enableDial(1, 1);

	// execute statement
	returnCodeError = sqlite3_prepare_v2(database, const_cast<char *>(sqlDynamicCommand.c_str()), -1, &sqlStatement, 0);
	if (returnCodeError != SQLITE_OK) throw runtime_error("Could not get the grid from game " + currentGameId);

	// for multiple results
	while (sqlite3_step(sqlStatement) == SQLITE_ROW)
	{
		TileStructure* tileStruct = new TileStructure;
		tileStruct->id = (int)sqlite3_column_int(sqlStatement, 0);
		sqliteChar = (char*)sqlite3_column_text(sqlStatement, 1);
		tileStruct->x_position = (int)sqlite3_column_int(sqlStatement, 2);
		tileStruct->y_position = (int)sqlite3_column_int(sqlStatement, 3);
		tileStruct->type = sqliteChar[0];
		tiles.push_back(tileStruct);

		if (tileStruct->type != 'e' && tileStruct->type != 'E')
		{
			setUpdatedTileToGrid(*tileStruct);
		}
	}

	sqlite3_finalize(sqlStatement);

	return grid;
}

bool GameRepository::isDialEnabled(int _xPosition, int _yPosition) const
{
	if (currentGameId == 0) throw runtime_error("Current game id is not set.");
	sqlite3_stmt* sqlStatement;
	bool isEnabledResult = false;

	// Create command
	string sqlDynamicCommand = "SELECT ENABLED FROM DIAL INNER JOIN GAME ON GAME.ID = DIAL.GAME_ID WHERE GAME.ID = " + to_string(currentGameId) +
		" AND X_POSITION = " + to_string(_xPosition) +
		" AND Y_POSITION = " + to_string(_yPosition) + ";";

	// execute statement
	int returnCodeError = sqlite3_prepare_v2(database, const_cast<char *>(sqlDynamicCommand.c_str()), -1, &sqlStatement, nullptr);
	if (returnCodeError != SQLITE_OK) throw runtime_error("Could not get the dial from game " + currentGameId);

	if (sqlite3_step(sqlStatement) == SQLITE_ROW)
	{
		int returnedValueEnable = (int)sqlite3_column_int(sqlStatement, 0);
		returnedValueEnable == 1 ? isEnabledResult = true : isEnabledResult = false;
	}

	sqlite3_finalize(sqlStatement);

	return isEnabledResult;
}

void GameRepository::enableDial(int _xPosition, int _yPosition) const
{
	if (currentGameId == 0) throw runtime_error("Current game id is not set.");
	string dynamicCommand = "UPDATE DIAL " \
		"SET ENABLED = 1 " \
		"WHERE X_POSITION = " + to_string(_xPosition) +
		" AND Y_POSITION = " + to_string(_yPosition) +
		" AND GAME_ID = " + to_string(currentGameId) + ";";
	executeCommand(const_cast<char *>(dynamicCommand.c_str()));
}

void GameRepository::saveGame(const Grid& _grid) const
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			updateTileType(i, j, _grid.getTile(i, j)->getTileType());
		}
	}
}

const Tile::TILE_TYPE GameRepository::getTileType(int _xPosition, int _yPosition) const
{
	if (currentGameId == 0) throw runtime_error("Current game id is not set.");
	sqlite3_stmt* sqlStatement;
	char* returnedCharTileType;
	char correctedCharTileType = 'E';

	// Create command
	string sqlDynamicCommand = "SELECT TYPE FROM TILE INNER JOIN GAME ON GAME.ID = TILE.GAME_ID WHERE GAME.ID = " + to_string(currentGameId) +
		" AND X_POSITION = " + to_string(_xPosition) +
		" AND Y_POSITION = " + to_string(_yPosition) + ";";

	// execute statement
	int returnCodeError = sqlite3_prepare_v2(database, const_cast<char *>(sqlDynamicCommand.c_str()), -1, &sqlStatement, nullptr);
	if (returnCodeError != SQLITE_OK) throw runtime_error("Could not get the dial from game " + currentGameId);

	if (sqlite3_step(sqlStatement) == SQLITE_ROW)
	{
		returnedCharTileType = (char*)sqlite3_column_text(sqlStatement, 0);
		correctedCharTileType = returnedCharTileType[0];
	}

	sqlite3_finalize(sqlStatement);

	return convertCharToTileType(correctedCharTileType);
}

void GameRepository::updateTileType(int _xPosition, int _yPosition, const Tile::TILE_TYPE& _tileType) const
{
	if (currentGameId == 0) throw runtime_error("Current game id is not set.");
	string dynamicCommand = "UPDATE TILE " \
		"SET TYPE = '";
	dynamicCommand += convertTileTypeToChar(_tileType);
	dynamicCommand += "' WHERE X_POSITION = " + to_string(_xPosition) +
		" AND Y_POSITION = " + to_string(_yPosition) +
		" AND GAME_ID = " + to_string(currentGameId) + ";";
	executeCommand(const_cast<char *>(dynamicCommand.c_str()));
}

void GameRepository::executeCommand(char* _command, bool _errorCheck /* = true */) const
{
	if (_errorCheck)
	{
		char* errorMessage = nullptr;
		int executionErrorCode = sqlite3_exec(database, _command, nullptr, 0, &errorMessage);
		if (executionErrorCode == SQLITE_ERROR) throw runtime_error("Command has error(s).");
		if (executionErrorCode == SQLITE_FAIL) throw runtime_error("Command has failed.");
		sqlite3_free(errorMessage);
	}
	else
	{
		sqlite3_exec(database, _command, nullptr, 0, nullptr);
	}
}

const Tile::TILE_TYPE GameRepository::convertCharToTileType(char _charTileType) const
{
	if (_charTileType == 'X' || _charTileType == 'x') return Tile::X_TYPE;
	if (_charTileType == 'O' || _charTileType == 'o') return Tile::O_TYPE;
	return Tile::EMPTY_TYPE;
}

char GameRepository::convertTileTypeToChar(const Tile::TILE_TYPE& _tileType) const
{
	if (_tileType == Tile::X_TYPE) return 'X';
	if (_tileType == Tile::O_TYPE) return 'O';
	return 'E';
}

void GameRepository::setUpdatedTileToGrid(const TileStructure& _tileStructure) const
{
	Tile::TILE_TYPE tileType = Tile::EMPTY_TYPE;
	if (_tileStructure.type == 'O' || _tileStructure.type == 'o')
	{
		tileType = Tile::O_TYPE;
	}
	else if (_tileStructure.type == 'X' || _tileStructure.type == 'x')
	{
		tileType = Tile::X_TYPE;
	}
	grid->setTile(tileType, _tileStructure.x_position, _tileStructure.y_position);
}