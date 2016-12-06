#include "stdafx.h"
#include "../Controllers/stdafx.h"

Window::Window(IWindowAPI & _windowAPI)
	:windowAPI(&_windowAPI),
	lineRenderer(new LineRenderer)
{
	setWindowController(*new MenuController(new GameConfiguration()));
}


Window::~Window()
{
	delete lineRenderer;
}


void Window::addButton(Button & _button)
{
	buttons.push_back(&_button);
}

void Window::updateButtonImage(const string & _text, char * _imagePath)
{
	bool essai;
	for each (Button * button in buttons)
	{
		if (button->getText() == _text)
		{
			button->setImagePath(_imagePath);
			break;
		}
	}
}

void Window::setWindowController(MainController & _controller)
{
	buttons.clear();
	currentController = &_controller;
	currentController->addWindowObservers(*this);
	currentController->createButtons();
	delete lineRenderer;
	lineRenderer = new LineRenderer();
}

void Window::addLine(const Line& _line)
{
	lineRenderer->addLine(_line);
}

void Window::render() const
{
	if (windowAPI == nullptr) throw runtime_error("Une fenetre ''WindowAPI'' est necessaire pour afficher");
	
	for each (Button * button in buttons)
	{
		windowAPI->drawButton(*button);
	}
	lineRenderer->draw(*windowAPI);
}

void Window::update() const
{
	currentController->updateWindow();
}

void Window::mouseInput(const Point& _mouseCoordinate) const
{
	for each (Button * button in buttons)
	{
		if (button->isClickInsideBorder(_mouseCoordinate.x, _mouseCoordinate.y))
		{
			currentController->manageChoice(*button);
			break;
		}
	}
}

void Window::clearScreen()
{
	windowAPI->clearScreen();
}

void Window::quitGame()
{
	windowAPI->quitApp();
}

