#include "stdafx.h"
#include "GameDatabaseHelper.h"


GameDatabaseHelper::GameDatabaseHelper(const string& _databasePath)
{
	int returnCodeError = sqlite3_open(_databasePath.c_str(), &database);
	if (returnCodeError != SQLITE_OK) throw runtime_error("Could not open database: " + _databasePath);
}


GameDatabaseHelper::~GameDatabaseHelper()
{
	sqlite3_close(database);
}

void GameDatabaseHelper::createDatabase() const
{
	createGameTable();
	createDialTable();
	createTileTable();
}

void GameDatabaseHelper::seedGameDatabase(int _gameID) const
{
	if (_gameID <= getNbGame()) throw runtime_error("Game already exists");
	insertNewGame("Player");
	insertNewDial(false, 0, 0, _gameID);
	insertNewDial(false, 0, 1, _gameID);
	insertNewDial(false, 1, 0, _gameID);
	insertNewDial(false, 1, 1, _gameID);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			insertNewTile(i, j, _gameID);
		}
	}
}

void GameDatabaseHelper::dropDatabase() const
{
	dropAll();
}

void GameDatabaseHelper::createGameTable() const
{
	executeCommand("CREATE TABLE GAME ("  \
		"ID INTEGER PRIMARY KEY AUTOINCREMENT," \
		"PLAYER_NAME TEXT NULL" \
		");");
}

void GameDatabaseHelper::createDialTable() const
{
	executeCommand("CREATE TABLE DIAL ("  \
		"ID INTEGER PRIMARY KEY AUTOINCREMENT," \
		"ENABLED INT CHECK(ENABLED IN (0, 1)) NOT NULL," \
		"X_POSITION INT NOT NULL," \
		"Y_POSITION INT NOT NULL," \
		"GAME_ID INTEGER NOT NULL," \
		"FOREIGN KEY (GAME_ID) references GAME(ID)"
		");");
}

void GameDatabaseHelper::createTileTable() const
{
	executeCommand("CREATE TABLE TILE ("  \
		"ID INTEGER PRIMARY KEY AUTOINCREMENT," \
		"TYPE TEXT CHECK(TYPE IN ('E','O','X')) NOT NULL," \
		"X_POSITION INT NOT NULL," \
		"Y_POSITION INT NOT NULL," \
		"GAME_ID INTEGER NOT NULL," \
		"FOREIGN KEY (GAME_ID) references GAME(ID)" \
		");");
}

int GameDatabaseHelper::getNbGame() const
{
	sqlite3_stmt* sqlStatement;
	int returnedValueEnable = 1;

	// Create command
	char* sqlCommand = "SELECT COUNT(*) FROM GAME;";

	// execute statement
	int returnCodeError = sqlite3_prepare_v2(database, sqlCommand, -1, &sqlStatement, nullptr);
	if (returnCodeError != SQLITE_OK) throw runtime_error("Could not get the number of game");

	if (sqlite3_step(sqlStatement) == SQLITE_ROW)
	{
		returnedValueEnable = (int)sqlite3_column_int(sqlStatement, 0);
	}

	sqlite3_finalize(sqlStatement);

	return returnedValueEnable;
}

void GameDatabaseHelper::insertNewGame(const string& _playerName) const
{
	string dynamicCommand = "INSERT INTO GAME (PLAYER_NAME) VALUES ('" + _playerName + "');";
	executeCommand(const_cast<char *>(dynamicCommand.c_str()));
}

void GameDatabaseHelper::insertNewDial(bool _enabled, int _xPosition, int _yPosition, int _gameID) const
{
	int intEnabled = (_enabled ? 1 : 0);
	string dynamicCommand = "INSERT INTO DIAL (ENABLED, X_POSITION, Y_POSITION, GAME_ID) VALUES (" + to_string(intEnabled) + ", " + to_string(_xPosition) + ", " + to_string(_yPosition) + ", " +to_string(_gameID) + ");";
	executeCommand(const_cast<char *>(dynamicCommand.c_str()));
}

void GameDatabaseHelper::insertNewTile(int _xPosition, int _yPosition, int _gameID) const
{
	string dynamicCommand = "INSERT INTO TILE (TYPE, X_POSITION, Y_POSITION, GAME_ID) VALUES ('E', " + to_string(_xPosition) + ", " + to_string(_yPosition) + ", " + to_string(_gameID) + ");";
	executeCommand(const_cast<char *>(dynamicCommand.c_str()));
}

void GameDatabaseHelper::dropAll() const
{
	executeCommand("DROP TABLE TILE;", false);
	executeCommand("DROP TABLE DIAL;", false);
	executeCommand("DROP TABLE GAME;", false);
}

void GameDatabaseHelper::executeCommand(char* _command, bool _errorCheck /* = true */) const
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