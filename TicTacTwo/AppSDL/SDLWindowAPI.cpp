#include "stdafx.h"

SDLWindowAPI::SDLWindowAPI(const int _width, const int _height, const string & _windowName)
{
	if (_height < 0 || _width < 0) throw runtime_error("The dimension of the window must be positive");
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(_width, _height, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption(_windowName.c_str(), 0);
}

SDLWindowAPI::~SDLWindowAPI()
{
	if (image) SDL_FreeSurface(image);
	delete image;
	delete screen;
	SDL_Quit();
	if (mouseCoordinate) delete mouseCoordinate;
}

void SDLWindowAPI::drawLine(int _xStartPosition, int _yStartPosition, int _xEndingPosition, int _yEndingPosition, int _color)
{
	Draw_Line(screen, _xStartPosition, _yStartPosition, _xEndingPosition, _yEndingPosition, _color);
}

void SDLWindowAPI::drawButton(Button & button)
{
	drawImage(button.getImagePath() , button.getXPosition(), button.getYPosition(), button.getWidth(), button.getHeight());
}

void SDLWindowAPI::drawImage(const char* _imagePath, int _x, int _y, int _width, int _height)
{
	SDL_Rect imageRect = { _x, _y, _width, _height };

	if (image) SDL_FreeSurface(image);

	image = SDL_LoadBMP(_imagePath);

	if (!image) throw runtime_error("Can't load image");

	image->h = imageRect.h;
	image->w = imageRect.w;


	SDL_BlitSurface(image, NULL, screen, &imageRect);
}

bool SDLWindowAPI::hasEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			IWindowEvent * newEvent = new WindowEvent(QUIT);
			listEvent.push(newEvent);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			IWindowEvent * newEvent = new WindowEvent(CLICK);
			listEvent.push(newEvent);
		}
	}

	if (listEvent.empty())
	{
		return false;
	}
	return true;
}

void SDLWindowAPI::wait(float _timeMillis)
{
	SDL_Delay((Uint32)_timeMillis);
}

IWindowEvent & SDLWindowAPI::getEvent()
{
	if (!listEvent.empty())
	{
		IWindowEvent * event;
		event = listEvent.top();
		listEvent.pop();
		return *event;
	}
}

void SDLWindowAPI::clearScreen()
{
	SDL_FillRect(screen, 0, 0);
}

void SDLWindowAPI::displayScreen()
{
	SDL_Flip(screen);
}

const Point& SDLWindowAPI::getMouseCoordinates()
{
	int xValue = 0;
	int yValue = 0;
	SDL_GetMouseState(&xValue, &yValue);
	if (mouseCoordinate) delete mouseCoordinate;
	mouseCoordinate = new Point(xValue, yValue);
	return *mouseCoordinate;
}

void SDLWindowAPI::quitApp()
{
	IWindowEvent * newEvent = new WindowEvent(QUIT);
	listEvent.push(newEvent);
}