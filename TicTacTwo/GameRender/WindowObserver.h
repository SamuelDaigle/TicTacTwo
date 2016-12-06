#pragma once
#include "stdafx.h"

class WindowObserver
{
public:
	virtual void addButton(Button & _button) = 0;
	virtual void updateButtonImage(const string & _buttonText, char * imagePath) = 0;
	virtual void addLine(const Line& _line) = 0;
	virtual void setWindowController(MainController & _mainController) = 0;
	virtual void clearScreen() = 0;
	virtual void quitGame() = 0;
};