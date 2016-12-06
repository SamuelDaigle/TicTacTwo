#include "stdafx.h"
#include "../GameRender/Window.h"

OptionsController::OptionsController(GameConfiguration * config) : 
MainController(config)
{
	configuration = config;
}


OptionsController::~OptionsController()
{
}

void OptionsController::updateWindow()
{
	if (configuration->playerType == Tile::X_TYPE)
	{
		typeChoice->setYPosition(70);
		defaultImage->setImagePath("XType.bmp");
		customImage->setImagePath("christophe.bmp");
	}
	else
	{
		typeChoice->setYPosition(110);
		defaultImage->setImagePath("OType.bmp");
		customImage->setImagePath("computerChoice.bmp");
	}

	if (configuration->gameDifficulty == GameConfiguration::EASY)
	{
		difficultyChoice->setYPosition(70);
	}
	else
	{
		difficultyChoice->setYPosition(110);
	}

	if (configuration->playerImage == "XType.bmp" || configuration->playerImage == "OType.bmp")
	{
		imageChoice->setXPosition(90);
	}
	else
	{
		imageChoice->setXPosition(170);
	}
}

void OptionsController::createButtons()
{
	Button * difficultyTitle = &createButton(70, 30, 100, 30, "DifficultyTitle.bmp", "NA");
	Button * easyDifficulty = &createButton(70, 70, 100, 30, "Easy.bmp", "EASY");
	Button * normalDifficulty = &createButton(70, 110, 100, 30, "Normal.bmp", "NORMAL");

	Button * tileTypeTitle = &createButton(280, 30, 120, 30, "TileTypeTitle.bmp", "NA");
	Button * xPlayerType = &createButton(280, 70, 100, 30, "XPlayer.bmp", "X_TYPE");
	Button * oPlayerType = &createButton(280, 110, 100, 30, "OPlayer.bmp", "O_TYPE");

	Button * imageTitle = &createButton(70, 150, 120, 30, "ImageTitle.bmp", "NA");
	defaultImage = &createButton(70, 190, 70, 70, "XType.bmp", "DEFAULT");
	customImage = &createButton(150, 190, 70, 70, "christophe.bmp", "CUSTOM");

	Button * backToMenu = &createButton(0, 0, 100, 30, "Back.bmp", "MENU");

	typeChoice = &createButton(380, 70, 30, 30, "RedDot.bmp", "NA");
	difficultyChoice = &createButton(170, 70, 30, 30, "RedDot.bmp", "NA");
	imageChoice = &createButton(90, 270, 30, 30, "RedDot.bmp", "NA");

	windowObserver->addButton(*difficultyTitle);
	windowObserver->addButton(*tileTypeTitle);
	windowObserver->addButton(*imageTitle);
	windowObserver->addButton(*easyDifficulty);
	windowObserver->addButton(*normalDifficulty);
	windowObserver->addButton(*xPlayerType);
	windowObserver->addButton(*oPlayerType);
	windowObserver->addButton(*backToMenu);
	windowObserver->addButton(*typeChoice);
	windowObserver->addButton(*defaultImage);
	windowObserver->addButton(*customImage);
	windowObserver->addButton(*difficultyChoice);
	windowObserver->addButton(*imageChoice);
	
}

void OptionsController::manageChoice(Button & _button)
{
	string action = (string)_button.getText();
	
	if (action == "EASY")
	{
		configuration->gameDifficulty = GameConfiguration::EASY;
	}
	else if (action == "NORMAL")
	{
		configuration->gameDifficulty = GameConfiguration::NORMAL;
	}
	else if (action == "X_TYPE")
	{
		configuration->playerType = Tile::X_TYPE;
		configuration->computerType = Tile::O_TYPE;

		configuration->playerImage = (configuration->playerImage == "OType.bmp") ? "XType.bmp" : "christophe.bmp";
		configuration->computerImage = (configuration->playerImage == "XType.bmp") ? "OType.bmp" : "computerChoice.bmp";
	}
	else if (action == "O_TYPE")
	{
		configuration->playerType = Tile::O_TYPE;
		configuration->computerType = Tile::X_TYPE;

		configuration->playerImage = (configuration->playerImage == "XType.bmp") ? "OType.bmp" : "computerChoice.bmp";
		configuration->computerImage = (configuration->playerImage == "OType.bmp") ? "XType.bmp" : "christophe.bmp";
	}
	else if (action == "DEFAULT")
	{
		configuration->playerImage = (configuration->playerType == Tile::X_TYPE) ? "XType.bmp" : "OType.bmp";
		configuration->computerImage = (configuration->computerType == Tile::X_TYPE) ? "XType.bmp" : "OType.bmp";
	}
	else if (action == "CUSTOM")
	{
		configuration->playerImage = (configuration->playerType == Tile::X_TYPE) ? "christophe.bmp" : "computerChoice.bmp";
		configuration->computerImage = (configuration->computerType == Tile::X_TYPE) ? "christophe.bmp" : "computerChoice.bmp";
	}
	else if (action == "MENU")
	{
		windowObserver->setWindowController(*new MenuController(configuration));
	}
}
