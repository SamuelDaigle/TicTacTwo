#include "stdafx.h"
#include "Button.h"

MainController::MainController(GameConfiguration * config)
{
	configuration = config;
}


MainController::~MainController()
{
}

void MainController::updateWindow()
{

}

void MainController::addWindowObservers(WindowObserver & _observer)
{
	windowObserver = &_observer;
}

Button & MainController::createButton(int _xPosition, int _yPosition, int _width, int _height, char * _imagePath, const string & _text) const
{
	Button * newButton = new Button();

	newButton->setXPosition(_xPosition);
	newButton->setYPosition(_yPosition);
	newButton->setWidth(_width);
	newButton->setHeight(_height);
	newButton->setImagePath(_imagePath);
	newButton->setText(_text);

	return *newButton;
}
