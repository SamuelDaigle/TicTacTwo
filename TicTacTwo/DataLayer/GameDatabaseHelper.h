#pragma once
class GameDatabaseHelper
{
public:
	GameDatabaseHelper(const string& _databasePath);
	~GameDatabaseHelper();

	void createDatabase() const;
	void seedGameDatabase(int _gameID) const;
	void dropDatabase() const;
	int getNbGame() const;

private:
	void createGameTable() const;
	void createDialTable() const;
	void createTileTable() const;
	void insertNewGame(const string& _playerName) const;
	void insertNewDial(bool _enabled, int _xPosition, int _yPosition, int _gameID) const;
	void insertNewTile(int _xPosition, int _yPosition, int _gameID) const;
	void dropAll() const;

	void executeCommand(char* _command, bool _errorCheck = true) const;

	sqlite3 *database;
};

