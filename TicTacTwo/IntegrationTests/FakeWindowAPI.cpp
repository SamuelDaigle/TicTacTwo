#include "stdafx.h"
#include "FakeWindowAPI.h"

FakeWindowAPI::FakeWindowAPI()
{
	drawLineHasBeenCalled = false;
	drawButtonHasBeenCalled = false;
	hasEventHasBeenCalled = false;
	waitHasBeenCalled = false;
	clearScreenHasBeenCalled = false;
	displayScreenHasBeenCalled = false;
	getEventHasBeenCalled = false;
	getMouseCoordinatesHasBeenCalled = false;
}


FakeWindowAPI::~FakeWindowAPI()
{
}

void FakeWindowAPI::drawLine(int xStartPosition, int yStartPosition, int xEndingPosition, int yEndingPosition, int color)
{
	drawLineHasBeenCalled = true;
}

void FakeWindowAPI::drawButton(Button & button)
{
	drawButtonHasBeenCalled = true;
}

bool FakeWindowAPI::hasEvent()
{
	hasEventHasBeenCalled = true;

	if (listEvent.empty() != true)
	{
		return true;
	}
	return false;
}

IWindowEvent & FakeWindowAPI::getEvent()
{
	getEventHasBeenCalled = true;

	IWindowEvent * event;
	event = listEvent.front();
	listEvent.pop();

	return *event;
}

void FakeWindowAPI::wait(float _timeMillis)
{
	waitHasBeenCalled = true;
}

void FakeWindowAPI::clearScreen()
{
	clearScreenHasBeenCalled = true;
}

void FakeWindowAPI::displayScreen()
{
	displayScreenHasBeenCalled = true;
}

void FakeWindowAPI::getMouseCoordinates(int & x, int & y)
{
	getMouseCoordinatesHasBeenCalled = true;
}

bool FakeWindowAPI::drawLine_HasBeenCalled()
{
	return drawLineHasBeenCalled;
}

bool FakeWindowAPI::drawButton_HasBeenCalled()
{
	return drawButtonHasBeenCalled;
}

bool FakeWindowAPI::hasEvent_HasBeenCalled()
{
	return hasEventHasBeenCalled;
}

bool FakeWindowAPI::wait_HasBeenCalled()
{
	return waitHasBeenCalled;
}

bool FakeWindowAPI::clearScreen_HasBeenCalled()
{
	return clearScreenHasBeenCalled;
}

bool FakeWindowAPI::displayScreen_HasBeenCalled()
{
	return displayScreenHasBeenCalled;
}

bool FakeWindowAPI::getEvent_HasBeenCalled()
{
	return getEventHasBeenCalled;
}

bool FakeWindowAPI::getMouseCoordinates_HasBeenCalled()
{
	return getMouseCoordinatesHasBeenCalled;
}

