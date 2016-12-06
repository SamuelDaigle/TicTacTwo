#include "stdafx.h"
#include "../GameRender/Window.h"


MenuController::MenuController(GameConfiguration * config) : 
MainController(config)
{
}


MenuController::~MenuController()
{
}

void MenuController::createButtons()
{
	windowObserver->addButton(createButton(150, 50, 300, 100, "Jouer.bmp", "Jouer"));
	windowObserver->addButton(createButton(150, 200, 300, 100, "Load.bmp", "Load"));
	windowObserver->addButton(createButton(150, 350, 300, 100, "Quitter.bmp", "Quitter"));
	windowObserver->addButton(createButton(540, 380, 100, 100, "Gear.bmp", "Options"));
}

void MenuController::manageChoice(Button & _button)
{
	if (windowObserver == nullptr) throw invalid_argument("Window inexistent");

	if (_button.getText() == "Jouer")
	{
		cout << "Jouer" << endl;
		configuration->loadLastGame = false;
		windowObserver->setWindowController(*new GameController(configuration));
	}
	if (_button.getText() == "Load")
	{
		cout << "Load" << endl;
		configuration->loadLastGame = true;
		windowObserver->setWindowController(*new GameController(configuration));
	}
	if (_button.getText() == "Options")
	{
		cout << "Options" << endl;
		windowObserver->setWindowController(*new OptionsController(configuration));
	}
	if (_button.getText() == "Quitter")
	{
		windowObserver->quitGame();
	}
}
