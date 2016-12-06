#pragma once
#include "stdafx.h"
#include "IWindowAPI.h"
#include <vector>

using namespace std;

class Window : public WindowObserver
{
public:
	Window(IWindowAPI & _windowAPI);
	~Window();

	void addButton(Button & _button) override;
	void updateButtonImage(const string & _buttonText, char * _imagePath) override;
	void setWindowController(MainController & _mainController) override;
	void addLine(const Line& _line) override;
	void clearScreen() override;
	void quitGame() override;

	void render() const;
	void update() const;
	void mouseInput(const Point& _mouseCoordinate) const;
private:
	MainController * currentController;
	IWindowAPI * windowAPI;
	LineRenderer* lineRenderer;
	vector<Button*> buttons;
};

