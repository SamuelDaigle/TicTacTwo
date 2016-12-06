#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(WindowRenderTests)
	{
	public:

		FakeWindowAPI * fakeWindowAPI;
		WindowRender * windowRender;

		WindowEvent * eventNone;
		WindowEvent * eventQuit;

		// to create basic elements of a grid.
		Line * line;
		Tile * tileBegin;
		Tile * tileBetween;
		Tile * tileEnd;


		TEST_METHOD_INITIALIZE(WindowRenderTests_Initialize)
		{
			fakeWindowAPI = new FakeWindowAPI(640, 480, "Super beau dessin");
			windowRender = new WindowRender(*fakeWindowAPI);

			eventNone = new WindowEvent();
			eventQuit = new WindowEvent(WIN_EVENEMENT::QUIT);

			initializeLine();
		}
		TEST_METHOD_CLEANUP(WindowRenderTests_CleanUp)
		{
			delete fakeWindowAPI;
			delete windowRender;
			delete line;
			delete tileBegin;
			delete tileBetween;
			delete tileEnd;
		}

		TEST_METHOD(run_should_look_for_event_on_windowApi)
		{
			//arrange
			fakeWindowAPI->addEvent(*eventQuit);

			//action 
			windowRender->run();

			//assert
			Assert::IsTrue(fakeWindowAPI->hasEvent_hasBeenCalled());
			Assert::IsTrue(fakeWindowAPI->getEvent_hasBeenCalled());
		}

		TEST_METHOD(run_should_clear_screen)
		{
			//arrange
			fakeWindowAPI->addEvent(*eventQuit);

			//action 
			windowRender->run();

			//assert
			Assert::IsTrue(fakeWindowAPI->clearScreen_hasBeenCalled());
		}

		TEST_METHOD(run_should_display_screen)
		{
			//arrange
			fakeWindowAPI->addEvent(*eventQuit);

			//action 
			windowRender->run();

			//assert
			Assert::IsTrue(fakeWindowAPI->displayScreen_hasBeenCalled());
		}

		TEST_METHOD(run_should_wait_for_window_regulation)
		{
			//arrange
			fakeWindowAPI->addEvent(*eventQuit);

			//action 
			windowRender->run();

			//assert
			Assert::IsTrue(fakeWindowAPI->wait_hasBeenCalled());
		}


		TEST_METHOD(added_line_should_be_rendered)
		{
			//arrange
			const int NUMBER_OF_LINE = 1;
			fakeWindowAPI->addEvent(*eventQuit);
			windowRender->addLine(*line);

			//action 
			windowRender->run();

			//assert
			Assert::AreEqual(NUMBER_OF_LINE, fakeWindowAPI->drawLine_getnumberOfCall());
		}

		void initializeLine()
		{
			line = new Line;
			tileBegin = new Tile;
			tileBetween = new Tile;
			tileEnd = new Tile;
			tileBegin->setPosition(Point(0, 0));
			tileBetween->setPosition(Point(1, 1));
			tileEnd->setPosition(Point(2, 2));
			line->addBack(tileBetween);
			line->addBack(tileBegin);
			line->addFront(tileEnd);
		}

	};
}