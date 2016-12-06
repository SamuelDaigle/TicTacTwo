#pragma once
#include "stdafx.h"
#include <iostream>

class Window;
class IWindowAPI;

class WindowRender
{
public:
	WindowRender(IWindowAPI & windowAPI);
	~WindowRender();

	void run();
	void addLine(const Line& _line);

private:
	void input();
	void update() const;
	void render() const;

	bool isRunning;
	Window * window;
	IWindowAPI * windowAPI;
};

