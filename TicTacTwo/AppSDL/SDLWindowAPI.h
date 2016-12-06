#pragma once
#include "../GameRender/IWindowAPI.h"
#include "../GameRender/IWindowEvent.h"
#include "../GameRender/WindowEvent.h"

#include "SDL.h"
#include "SDL_draw.h"

#include <iostream>
#include <stack>

using namespace std;

class SDLWindowAPI : public IWindowAPI
{
public:
	SDLWindowAPI(const int _width, const int _height, const string & _windowName);
	~SDLWindowAPI();

	void drawLine(int _xStartPosition, int _yStartPosition, int _xEndingPosition, int _yEndingPosition, int _color) override;
	void drawButton(Button& _button) override;
	void drawImage(const char* _imagePath, int _x, int _y, int _width, int _height) override;
	bool hasEvent() override;
	IWindowEvent& getEvent() override;
	void wait(float _timeMillis) override;
	void clearScreen() override;
	void displayScreen() override;
	const Point& getMouseCoordinates() override;
	void quitApp();

private:
	SDL_Surface * screen;
	stack<IWindowEvent*> listEvent;
	SDL_Surface * image;
	Point * mouseCoordinate;
};

