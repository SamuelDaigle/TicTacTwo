#pragma once
#include "stdafx.h"
#include "../GameRender/IWindowAPI.h"
#include <queue>

class FakeWindowAPI : public IWindowAPI
{
public:
	FakeWindowAPI();
	~FakeWindowAPI();

	void drawLine(int xStartPosition, int yStartPosition, int xEndingPosition, int yEndingPosition, int color);
	void drawButton(Button & button);
	bool hasEvent();
	IWindowEvent & getEvent();
	void wait(float _timeMillis);
	void clearScreen();
	void displayScreen();
	void getMouseCoordinates(int & x, int & y);

	//Méthodes pour le FAKE
	bool drawLine_HasBeenCalled();
	bool drawButton_HasBeenCalled();
	bool hasEvent_HasBeenCalled();
	//bool hasEvent_shouldReturn(bool valueToReturn);
	bool wait_HasBeenCalled();
	bool clearScreen_HasBeenCalled();
	bool displayScreen_HasBeenCalled();
	bool getEvent_HasBeenCalled();
	bool getMouseCoordinates_HasBeenCalled();
	
private:
	// Attributs pour le FAKE
	bool drawLineHasBeenCalled;
	bool drawButtonHasBeenCalled;
	bool hasEventHasBeenCalled;
	//bool hasEventshouldReturn(bool valueToReturn);
	bool waitHasBeenCalled;
	bool clearScreenHasBeenCalled;
	bool displayScreenHasBeenCalled;
	bool getEventHasBeenCalled;
	bool getMouseCoordinatesHasBeenCalled;
	queue<IWindowEvent *> listEvent;
};

