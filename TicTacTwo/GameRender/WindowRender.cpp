					#include "stdafx.h"
#include "IWindowAPI.h"

WindowRender::WindowRender(IWindowAPI & _windowAPI)
	:windowAPI(&_windowAPI),
	window(new Window(_windowAPI)),
	isRunning(true)
{
}


WindowRender::~WindowRender()
{
}

void WindowRender::run()
{
	while (isRunning)
	{
		input();
		update();
		render();

		windowAPI->wait(1000 / 30);
	}
}

void WindowRender::addLine(const Line& _line)
{
	window->addLine(_line);
}

void WindowRender::input()
{
	if (windowAPI->hasEvent())
	{
		WIN_EVENEMENT eventType = windowAPI->getEvent().getEventType();
		if (eventType == QUIT)
		{
			isRunning = false;
		}
		if (eventType == CLICK)
		{
			const Point& mouseCoordinate = windowAPI->getMouseCoordinates();
			cout << "X : " << mouseCoordinate.x << ", Y : " << mouseCoordinate.y << endl;
			window->mouseInput(mouseCoordinate);
		}
	}
}

void WindowRender::update() const
{
	window->update();
}

void WindowRender::render() const
{
	windowAPI->clearScreen();
	window->render();
	windowAPI->displayScreen();
}