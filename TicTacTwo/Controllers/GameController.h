#pragma once
#include "stdafx.h"

class GameController : public MainController
{
public:
	GameController(GameConfiguration * config);
	~GameController();
   
	void updateWindow() override;
	void createButtons() override;
	void manageChoice(Button & _button) override;

private:
	void createGrid();
	void createDial(int _xDialPosition, int _yDialPosition);
	void computerInput();

	void loadOldGame();
	void loadNewGame();

	void updateLinesToShow(int _tileX, int _tileY);
	void updateDials();
	void manageNextDial();
	void getWinner() const;
	
	int currentDialXPosition;
	int currentDialYPosition;
	bool isGameOver;

	Tile::TILE_TYPE playerType;
	Tile::TILE_TYPE computerType;

	GameDatabaseHelper* databaseHelper;
	GameRepository* repository;

	Grid * gameGrid;
	Computer * computer;
	LineManager * lineManager;
};

