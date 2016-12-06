#include "stdafx.h"

using namespace UnitTests;

FakeWindowAPI::FakeWindowAPI(const int _width, const int _height, const string& _windowTitle)
{
	numberOfCallToDrawLine = 0;
	numberOfCallToDrawButton = 0;
	numberOfCallToDrawImage = 0;
	getEventHasBeenCalled = false;
	hasEventHasBeenCalled = false;
	hasClearScreenBeenCalled = false;
	hasDisplayScreenBeenCalled = false;
	hasWaitHasBeenCalled = false;
	getMouseCoordinates_hasBeenCalled = false;
	quitHasBeenCalled = false;
}

FakeWindowAPI::~FakeWindowAPI()
{
}

void FakeWindowAPI::drawLine(int _xStartPosition, int _yStartPosition, int _xEndingPosition, int _yEndingPosition, int _color)
{
	numberOfCallToDrawLine++;
}


void FakeWindowAPI::drawButton(Button &_button)
{
	numberOfCallToDrawButton++;
}

void FakeWindowAPI::drawImage(const char* _imagePath, int _x, int _y, int _width, int _height)
{
	numberOfCallToDrawImage++;
}

 IWindowEvent& FakeWindowAPI::getEvent()
{
	getEventHasBeenCalled = true;

	IWindowEvent * event;
	event = listEvent.front();
	listEvent.pop();

	return *event;
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

 void FakeWindowAPI::clearScreen()
{
	hasClearScreenBeenCalled = true;
}

 void FakeWindowAPI::displayScreen()
{
	hasDisplayScreenBeenCalled = true;
}

 void FakeWindowAPI::wait(float _timeMillis)
{
	hasWaitHasBeenCalled = true;
}

 const Point& FakeWindowAPI::getMouseCoordinates()
 {
	 getMouseCoordinates_hasBeenCalled = true;
	 return Point(0, 0);
 }

 //////////////////////////////////////////////////////////////////////////

int FakeWindowAPI::drawLine_getnumberOfCall()
{
	return numberOfCallToDrawLine;
}

int FakeWindowAPI::drawButton_getnumberOfCall()
{
	return numberOfCallToDrawButton;
}

int FakeWindowAPI::drawImage_getnumberOfCall()
{
	return numberOfCallToDrawImage;
}

bool FakeWindowAPI::hasEvent_hasBeenCalled()
{
	return hasEventHasBeenCalled;
}

void FakeWindowAPI::hasEvent_shouldReturn(bool _valueToReturn)
{
	hasEventReturnValue = _valueToReturn;
}

bool FakeWindowAPI::clearScreen_hasBeenCalled()
{
	return hasClearScreenBeenCalled;
}

bool FakeWindowAPI::displayScreen_hasBeenCalled()
{
	return hasDisplayScreenBeenCalled;
}

bool FakeWindowAPI::wait_hasBeenCalled()
{
	return hasWaitHasBeenCalled;
}

bool FakeWindowAPI::getEvent_hasBeenCalled()
{
	return getEventHasBeenCalled;
}

string FakeWindowAPI::draw_getLastCall()
{
	return lastDrawCall;
}

bool FakeWindowAPI::quit_HasBeenCalled()
{
	return quitHasBeenCalled;
}

void FakeWindowAPI::addEvent(IWindowEvent & _winEvenement)
{
	listEvent.push(&_winEvenement);
}

void FakeWindowAPI::quitApp()
{
	quitHasBeenCalled = true;
}