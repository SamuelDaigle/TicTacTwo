#pragma once
#include "stdafx.h"

#include <queue>

using namespace std;

namespace UnitTests
{


	class FakeWindowAPI : public IWindowAPI
	{
	public:

		FakeWindowAPI(const int _width, const int _height, const string & _windowTitle);
		~FakeWindowAPI();

		void drawLine(int _xStartPosition, int _yStartPosition, int _xEndingPosition, int _yEndingPosition, int _color) override;
		void drawButton(Button& _button) override;
		void drawImage(const char* _imagePath, int _x, int _y, int _width, int _height) override;
		bool hasEvent() override;
		IWindowEvent & getEvent() override;
		void wait(float _timeMillis) override;
		void clearScreen() override;
		void displayScreen() override;
		const Point& getMouseCoordinates() override;
		void quitApp() override;

		// Méthodes pour le FAKE
		int drawLine_getnumberOfCall();
		int drawButton_getnumberOfCall();
		int drawImage_getnumberOfCall();
		bool hasEvent_hasBeenCalled();
		void hasEvent_shouldReturn(bool _valueToReturn);
		bool clearScreen_hasBeenCalled();
		bool displayScreen_hasBeenCalled();
		bool wait_hasBeenCalled();
		bool getEvent_hasBeenCalled();
		string draw_getLastCall();
		void addEvent(IWindowEvent & _winEvenement);
		bool quit_HasBeenCalled();

	private:
		// Attributs pour le FAKE
		int numberOfCallToDrawLine;
		int numberOfCallToDrawButton;
		int numberOfCallToDrawImage;
		bool hasEventHasBeenCalled;
		bool hasEventReturnValue;
		bool getEventHasBeenCalled;
		bool hasClearScreenBeenCalled;
		bool hasDisplayScreenBeenCalled;
		bool hasWaitHasBeenCalled;
		bool getMouseCoordinates_hasBeenCalled;
		string lastDrawCall;
		queue<IWindowEvent *> listEvent;
		bool quitHasBeenCalled;
	};
}
