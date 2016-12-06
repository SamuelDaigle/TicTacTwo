#pragma once
#include "IWindowEvent.h"
#include "../Controllers/Button.h"
#include <iostream>
using namespace std;

class IWindowAPI
{
public:
	virtual void drawLine(int _xStartPosition, int _yStartPosition, int _xEndingPosition, int _yEndingPosition, int _color) = 0;
	virtual void drawButton(Button& _button) = 0;
	virtual void drawImage(const char* _imagePath, int _x, int _y, int _width, int _height) = 0;
	virtual bool hasEvent() = 0;
	virtual IWindowEvent & getEvent() = 0;
	virtual void wait(float _timeMillis) = 0;
	virtual void clearScreen()=0;
	virtual void displayScreen() = 0;
	virtual const Point& getMouseCoordinates() = 0;
	virtual void quitApp() = 0;
};
