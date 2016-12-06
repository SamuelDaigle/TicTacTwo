#pragma once
#include "stdafx.h"

class Window;
class WindowObserver;
class Button;

#include <iostream>
using namespace std;

class MainController
{
public:
	MainController(GameConfiguration * _config);
	~MainController();

	void addWindowObservers(WindowObserver & _observer);

	virtual void updateWindow();
	virtual void createButtons() = 0;
	virtual void manageChoice(Button & _button) = 0;

protected:
	Button & createButton(int _xPosition, int _yPosition, int _width, int _height, char * _imagePath, const string & _text) const;
	WindowObserver * windowObserver;
	GameConfiguration * configuration;
};

