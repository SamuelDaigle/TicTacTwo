#include "stdafx.h"
#include "../GameRender/Window.h"
#include <iostream>
#include <string>

GameController::GameController(GameConfiguration * config) :
MainController(config)
{
	isGameOver = false;
	computerType = configuration->computerType;
	playerType = configuration->playerType;

	currentDialXPosition = 0;
	currentDialYPosition = 0;

	databaseHelper = new GameDatabaseHelper("game.db");
	repository = new GameRepository("game.db");
	config->loadLastGame ? loadOldGame() : loadNewGame();

	if (configuration->gameDifficulty == GameConfiguration::EASY)
	{
		computer = new EasyComputer(*gameGrid, computerType);
	}
	else
	{
		computer = new NormalComputer(*gameGrid, computerType);
	}

	lineManager = new LineManager(*gameGrid);
}


GameController::~GameController()
{
	repository->saveGame(*gameGrid);
	windowObserver->clearScreen();
	vector<Line*> lines = gameGrid->getLines();
	delete computer;
	delete lineManager;
	delete repository;
	delete databaseHelper;
	
	for (Line * line : lines)
	{
		delete line;
	}
}

void GameController::updateWindow()
{
	updateDials();
}

void GameController::createButtons()
{
	Button * backToMenu = &createButton(540, 0, 100, 30, "Back.bmp", "MENU");
	windowObserver->addButton(*backToMenu);
	createDial(currentDialXPosition, currentDialYPosition);
}

void GameController::manageChoice(Button & _button)
{
	if (_button.getText() == "MENU")
	{
		windowObserver->setWindowController(*new MenuController(configuration));
		return;
	}

	int tileX = 0;
	int tileY = 0;

	tileX = stoi(_button.getText().substr(0, 1));
	tileY = stoi(_button.getText().substr(1, 1));

	if (gameGrid->getTile(tileX, tileY)->getTileType() == Tile::EMPTY_TYPE)
	{
		gameGrid->setTile(playerType , tileX, tileY);
		_button.setImagePath(configuration->playerImage);

		updateDials();
		updateLinesToShow(tileX, tileY);
		computerInput();
	}
}

void GameController::createDial(int _xDialPosition, int _yDialPosition)
{
	const int TILE_DIMENSION = 70;

	int tileXPosition = (_xDialPosition == 1) ? 3 : 0;
	int tileYPosition = (_yDialPosition == 1) ? 3 : 0;

	gameGrid->enableDial(_xDialPosition, _yDialPosition);

	for (int xPosition = tileXPosition; xPosition < tileXPosition + 3; xPosition++)
	{
		for (int yPosition = tileYPosition; yPosition < tileYPosition + 3; yPosition++)
		{
			if ((xPosition + yPosition) % 2 == 0)
			{
				windowObserver->addButton(createButton((xPosition * TILE_DIMENSION),
					(yPosition * TILE_DIMENSION),
					TILE_DIMENSION,
					TILE_DIMENSION,
					configuration->emptyTileImage,
					std::to_string(xPosition) + std::to_string(yPosition)));
			}
			else
			{
				windowObserver->addButton(createButton((xPosition * TILE_DIMENSION),
					(yPosition * TILE_DIMENSION),
					TILE_DIMENSION,
					TILE_DIMENSION,
					configuration->emptyTileImage,
					std::to_string(xPosition) + std::to_string(yPosition)));
			}
		}
	}
}

void GameController::updateDials()
{
	if (!gameGrid->isFull())
	{
		if (gameGrid->isDialFull(currentDialXPosition, currentDialYPosition))
		{
			manageNextDial();
			createButtons();
		}
	}
	else if (!isGameOver)
	{
		isGameOver = true;
		getWinner();

	}
}

void GameController::manageNextDial()
{
	if (currentDialXPosition == 0 & currentDialYPosition == 0)
	{
		currentDialXPosition++;
	}
	else if (currentDialXPosition == 1 && currentDialYPosition == 0)
	{
		currentDialXPosition--;
		currentDialYPosition++;
	}
	else if (currentDialXPosition == 0 && currentDialYPosition == 1)
	{
		currentDialXPosition++;
	}
}

void GameController::getWinner() const
{
	int computerScore = 0;
	int playerScore = 0;
	vector<Line *> lines = gameGrid->getLines();
	for (Line * line : lines)
	{
		if (line->getFrontTile().getTileType() == computerType)
		{
			switch (line->getSize())
			{
			case 3:
				computerScore++;
				break;

			case 4:
				computerScore += 2;
				break;

			case 5:
				computerScore += 3;
				break;

			case 6:
				computerScore += 5;
			}
		}
		else if (line->getFrontTile().getTileType() == playerType)
		{
			switch (line->getSize())
			{
			case 3:
				playerScore++;
				break;

			case 4:
				playerScore += 2;
				break;

			case 5:
				playerScore += 3;
				break;

			case 6:
				playerScore += 5;
			}
		}
	}
	cout << endl << "Player Score : " << playerScore << endl;
	cout << "Computer Score : " << computerScore << endl;

	if (computerScore > playerScore)
	{
		Button * backToMenu = &createButton(460, 200, 140, 70, "Defeat.bmp", "NA");
		windowObserver->addButton(*backToMenu);
	}
	else if (computerScore < playerScore)
	{
		Button * backToMenu = &createButton(460, 200, 140, 70, "Victory.bmp", "NA");
		windowObserver->addButton(*backToMenu);
	}
	else
	{
		Button * backToMenu = &createButton(460, 200, 140, 70, "Tie.bmp", "NA");
		windowObserver->addButton(*backToMenu);
	}
	
}

void GameController::loadNewGame()
{
	int gameID = 1;
	try
	{
		gameID += databaseHelper->getNbGame();
	}
	catch (runtime_error e)
	{
		databaseHelper->createDatabase();
		gameID += databaseHelper->getNbGame();
	}
	databaseHelper->seedGameDatabase(gameID);

	repository->setCurrentGame(gameID);
	gameGrid = repository->getGridFromGame();
}

void GameController::loadOldGame()
{
	int gameID = 0;
	try
	{
		gameID += databaseHelper->getNbGame();
	}
	catch (runtime_error e)
	{
		databaseHelper->createDatabase();
		gameID += databaseHelper->getNbGame();
	}

	repository->setCurrentGame(gameID);
	gameGrid = repository->getGridFromGame();
}

void GameController::updateLinesToShow(int _tileX, int _tileY)
{
	vector<Line*> createdLines = lineManager->updateLines(Point(_tileX, _tileY));

	for each (Line * line in createdLines)
	{
		windowObserver->addLine(*line);
	}
}

void GameController::computerInput()
{
	const Point * computerChoice = computer->getChoice();

	gameGrid->setTile(computerType, computerChoice->x, computerChoice->y);
	windowObserver->updateButtonImage(std::to_string(int(computerChoice->x)) + std::to_string(int(computerChoice->y)), configuration->computerImage);
	updateLinesToShow(int(computerChoice->x), int (computerChoice->y));
}