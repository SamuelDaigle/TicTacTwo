#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AI/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(NormalComputerTests)
	{
	public:
		const Tile::TILE_TYPE COMPUTER_TILE_TYPE = Tile::X_TYPE;
		const Tile::TILE_TYPE OPPONENT_TYPE = Tile::O_TYPE;
		NormalComputer * normalComputer;
		Grid * testGrid;

		TEST_METHOD_INITIALIZE(NormalComputerTests_Initialize)
		{
			testGrid = new Grid();
			normalComputer = new NormalComputer(*testGrid, COMPUTER_TILE_TYPE);
		}

		TEST_METHOD_CLEANUP(NormalComputerTests_CleanUp)
		{
			delete testGrid;
			delete normalComputer;
		}

		TEST_METHOD(when_there_is_no_blocking_or_scoring_option_the_computer_choose_an_available_tile)
		{
			//Arrange
			const Point DIAL_POSITION(0, 0);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);

			//Action
			const Point * chosenTile = normalComputer->getChoice();

			bool chosenTileIsEmpty = testGrid->getTile(chosenTile->x, chosenTile->y)->getTileType() == Tile::EMPTY_TYPE;
			//Assert
			Assert::IsTrue(chosenTileIsEmpty);
		}
		
		TEST_METHOD(when_computer_can_make_point_getChoice_returns_a_tile_that_give_points)
		{
			//Arrange
			const Point TILE_THAT_GIVE_POINT(2, 2);
			const Point DIAL_POSITION(0, 0);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);
				//Setting tiles
			testGrid->setTile(COMPUTER_TILE_TYPE, 0, 0);
			testGrid->setTile(COMPUTER_TILE_TYPE, 1, 1);
				//Setting lines
			Line line = Line();
			line.addFront(testGrid->getTile(0, 0));
			line.addFront(testGrid->getTile(1, 1));
			testGrid->addLine(&line);

			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_THAT_GIVE_POINT == *chosenTile);
		}

		TEST_METHOD(when_opponent_can_make_point_getChoice_returns_a_tile_that_block_points)
		{
			//Arrange
			const Point TILE_THAT_BLOCK_POINT(2, 2);
			const Point DIAL_POSITION(0, 0);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);
				//Setting tiles
			testGrid->setTile(OPPONENT_TYPE, 0, 0);
			testGrid->setTile(OPPONENT_TYPE, 1, 1);
				//Setting lines
			Line line = Line();
			line.addFront(testGrid->getTile(0, 0));
			line.addFront(testGrid->getTile(1, 1));
			testGrid->addLine(&line);

			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_THAT_BLOCK_POINT == *chosenTile);
		}

		TEST_METHOD(when_tiles_dont_make_a_line_but_can_give_point_the_computer_choose_the_tile_to_make_the_point)
		{
			//Arrange
			const Point TILE_THAT_GIVE_POINT(1, 1);
			const Point DIAL_POSITION(0, 0);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);
			//Setting tiles
			testGrid->setTile(COMPUTER_TILE_TYPE, 0, 0); // X E E
			testGrid->setTile(COMPUTER_TILE_TYPE, 2, 2); // E E E
													     // E E X
			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_THAT_GIVE_POINT == *chosenTile);
		}

		TEST_METHOD(when_tiles_dont_make_a_line_but_can_block_a_point_the_computer_choose_the_tile_to_block_the_point)
		{
			//Arrange
			const Point TILE_THAT_GIVE_POINT(1, 1);
			const Point DIAL_POSITION(0, 0);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);
			//Setting tiles
			testGrid->setTile(OPPONENT_TYPE, 0, 0); // O E E
			testGrid->setTile(OPPONENT_TYPE, 2, 2); // E E E
													// E E O
			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_THAT_GIVE_POINT == *chosenTile);
		}

		TEST_METHOD(when_blocking_opponent_points_is_better_than_making_points_the_computer_choose_to_block_points)
		{
			//Arrange
			const Point TILE_THAT_BLOCK_POINT(2, 2);
			const Point TILE_THAT_GIVE_POINT(3, 2);
			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);
				//Setting tiles
			testGrid->setTile(OPPONENT_TYPE, 2, 0); //	E E O  X E E
			testGrid->setTile(OPPONENT_TYPE, 2, 1); //	E E O  X E E
			testGrid->setTile(OPPONENT_TYPE, 0, 2); //	O O E  E E E
			testGrid->setTile(OPPONENT_TYPE, 1, 2);
			testGrid->setTile(COMPUTER_TILE_TYPE, 3, 0);
			testGrid->setTile(COMPUTER_TILE_TYPE, 3, 1);
				//Setting lines
			Line opponentLine1 = Line();
			opponentLine1.addFront(testGrid->getTile(0, 2));
			opponentLine1.addFront(testGrid->getTile(1, 2));
			Line opponentLine2 = Line();
			opponentLine2.addFront(testGrid->getTile(2, 0));
			opponentLine2.addFront(testGrid->getTile(2, 1));
			Line computerLine = Line();
			computerLine.addFront(testGrid->getTile(3, 0));
			computerLine.addFront(testGrid->getTile(3, 1));
			testGrid->addLine(&opponentLine1);
			testGrid->addLine(&opponentLine2);
			testGrid->addLine(&computerLine);

			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_THAT_BLOCK_POINT == *chosenTile);
		}

		TEST_METHOD(when_making_points_is_better_than_block_point_then_computer_make_point)
		{
			//Arrange
			const Point TILE_THAT_GIVE_POINT(2, 2);
			const Point TILE_THAT_BLOCK_POINT(3, 2);
			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);
				//Setting tiles
			testGrid->setTile(COMPUTER_TILE_TYPE, 2, 0); //	E E X  O E E
			testGrid->setTile(COMPUTER_TILE_TYPE, 2, 1); //	E E X  O E E
			testGrid->setTile(COMPUTER_TILE_TYPE, 0, 2); //	X X E  E E E
			testGrid->setTile(COMPUTER_TILE_TYPE, 1, 2);
			testGrid->setTile(OPPONENT_TYPE, 3, 0);
			testGrid->setTile(OPPONENT_TYPE, 3, 1);
				//Setting lines
			//Setting lines
			Line computerLine1 = Line();
			computerLine1.addFront(testGrid->getTile(0, 2));
			computerLine1.addFront(testGrid->getTile(1, 2));
			Line computerLine2 = Line();
			computerLine2.addFront(testGrid->getTile(2, 0));
			computerLine2.addFront(testGrid->getTile(2, 1));
			Line opponentLine = Line();
			opponentLine.addFront(testGrid->getTile(3, 0));
			opponentLine.addFront(testGrid->getTile(3, 1));
			testGrid->addLine(&opponentLine);
			testGrid->addLine(&computerLine1);
			testGrid->addLine(&computerLine2);

			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_THAT_GIVE_POINT == *chosenTile);
		}

		TEST_METHOD(when_blocking_and_making_points_are_both_advantageous_computer_makes_one_the_two_action)
		{
			//Arrange
			const Point TILE_THAT_GIVE_POINT(2, 2);
			const Point TILE_THAT_BLOCK_POINT(3, 2);
			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);
				//Setting tiles
			testGrid->setTile(COMPUTER_TILE_TYPE, 2, 0); //	E E X  O E E
			testGrid->setTile(COMPUTER_TILE_TYPE, 2, 1); //	E E X  O E E
			testGrid->setTile(OPPONENT_TYPE, 3, 0);//   	E E E  E E E
			testGrid->setTile(OPPONENT_TYPE, 3, 1);
				//Setting lines
			Line opponentLine = Line();
			opponentLine.addFront(testGrid->getTile(2, 0));
			opponentLine.addFront(testGrid->getTile(2, 1));
			Line computerLine = Line();
			computerLine.addFront(testGrid->getTile(3, 0));
			computerLine.addFront(testGrid->getTile(3, 1));
			testGrid->addLine(&computerLine);
			testGrid->addLine(&opponentLine);

			//Action
			const Point * chosenTile = normalComputer->getChoice();

			bool tileIsOneOfTheChoice = (*chosenTile == TILE_THAT_GIVE_POINT || *chosenTile == TILE_THAT_BLOCK_POINT);
			//Assert	
			Assert::IsTrue(tileIsOneOfTheChoice);
		}

		TEST_METHOD(when_computer_have_many_blocking_options_he_choose_the_most_advantageous_one)
		{
			//Arrange
			const Point TILE_THAT_BLOCK_MORE_POINT(2, 2);
			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);
				//Setting tiles
			testGrid->setTile(OPPONENT_TYPE, 2, 0); //	E E O  E O E
			testGrid->setTile(OPPONENT_TYPE, 2, 1); //	E E O  E O E
			testGrid->setTile(OPPONENT_TYPE, 0, 2); //	O O E  E E E
			testGrid->setTile(OPPONENT_TYPE, 1, 2);
			testGrid->setTile(OPPONENT_TYPE, 4, 0);
			testGrid->setTile(OPPONENT_TYPE, 4, 1);
				//Setting lines
			//Setting lines
			Line opponentLine1 = Line();
			opponentLine1.addFront(testGrid->getTile(0, 2));
			opponentLine1.addFront(testGrid->getTile(1, 2));
			Line opponentLine2 = Line();
			opponentLine2.addFront(testGrid->getTile(2, 0));
			opponentLine2.addFront(testGrid->getTile(2, 1));
			Line opponentLine3 = Line();
			opponentLine3.addFront(testGrid->getTile(3, 0));
			opponentLine3.addFront(testGrid->getTile(3, 1));
			testGrid->addLine(&opponentLine1);
			testGrid->addLine(&opponentLine2);
			testGrid->addLine(&opponentLine3);

			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_THAT_BLOCK_MORE_POINT == *chosenTile);
		}

		TEST_METHOD(when_computer_have_many_point_options_he_choose_the_most_advantageous_one)
		{
			//Arrange
			const Point TILE_THAT_MAKE_MORE_POINT(2, 2);
			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);
				//Setting tiles
			testGrid->setTile(COMPUTER_TILE_TYPE, 2, 0); //	E E X  E X E
			testGrid->setTile(COMPUTER_TILE_TYPE, 2, 1); //	E E X  E X E
			testGrid->setTile(COMPUTER_TILE_TYPE, 0, 2); //	X X E  E E E
			testGrid->setTile(COMPUTER_TILE_TYPE, 1, 2);
			testGrid->setTile(COMPUTER_TILE_TYPE, 4, 0);
			testGrid->setTile(COMPUTER_TILE_TYPE, 4, 1);
				//Setting lines
			Line computerLine1 = Line();
			computerLine1.addFront(testGrid->getTile(0, 2));
			computerLine1.addFront(testGrid->getTile(1, 2));
			Line computerLine2 = Line();
			computerLine2.addFront(testGrid->getTile(2, 0));
			computerLine2.addFront(testGrid->getTile(2, 1));
			Line computerLine3 = Line();
			computerLine3.addFront(testGrid->getTile(4, 0));
			computerLine3.addFront(testGrid->getTile(4, 1));
			testGrid->addLine(&computerLine1);
			testGrid->addLine(&computerLine2);
			testGrid->addLine(&computerLine3);
			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_THAT_MAKE_MORE_POINT == *chosenTile);
		}

		TEST_METHOD(when_blocking_a_point_also_gives_a_point_computer_make_that_choice)
		{
			//Arrange
			const Point TILE_TO_CHOOSE(5, 2);
			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);
				//Setting tiles
			testGrid->setTile(COMPUTER_TILE_TYPE, 0, 1); //	O O E  E E O
			testGrid->setTile(COMPUTER_TILE_TYPE, 1, 1); //	X X E  E E O
			testGrid->setTile(OPPONENT_TYPE, 0, 0); //	    E E E  X X E
			testGrid->setTile(OPPONENT_TYPE, 1, 0);
			testGrid->setTile(COMPUTER_TILE_TYPE, 3, 2);
			testGrid->setTile(COMPUTER_TILE_TYPE, 4, 2);
			testGrid->setTile(OPPONENT_TYPE, 5, 0);
			testGrid->setTile(OPPONENT_TYPE, 5, 1);
				//Setting lines
			Line computerLine1 = Line();
			computerLine1.addFront(testGrid->getTile(0, 1));
			computerLine1.addFront(testGrid->getTile(1, 1));
			Line computerLine2 = Line();
			computerLine2.addFront(testGrid->getTile(3, 2));
			computerLine2.addFront(testGrid->getTile(4, 2));
			Line opponentLine1 = Line();
			opponentLine1.addFront(testGrid->getTile(0, 0));
			opponentLine1.addFront(testGrid->getTile(1, 0));
			Line opponentLine2 = Line();
			opponentLine2.addFront(testGrid->getTile(5, 0));
			opponentLine2.addFront(testGrid->getTile(5, 1));
			testGrid->addLine(&opponentLine1);
			testGrid->addLine(&opponentLine2);
			testGrid->addLine(&computerLine1);
			testGrid->addLine(&computerLine2);

			//Action
			const Point * chosenTile = normalComputer->getChoice();

			//Assert	
			Assert::IsTrue(TILE_TO_CHOOSE == *chosenTile);
		}

		TEST_METHOD(getChoice_when_no_dials_are_available_should_throw_exception)
		{
			//Arrange


			//Action
			bool exceptionThrown = false;

			try
			{
				normalComputer->getChoice();
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);

		}

		TEST_METHOD(getChoice_when_the_available_dials_are_full_should_throw_exception)
		{
			//Arrange
			const Point DIAL_POSITION(0, 0);
			testGrid->enableDial(DIAL_POSITION.x, DIAL_POSITION.y);
			testGrid->setTile(Tile::X_TYPE, 0, 0);
			testGrid->setTile(Tile::O_TYPE, 0, 1);
			testGrid->setTile(Tile::O_TYPE, 1, 0);
			testGrid->setTile(Tile::X_TYPE, 1, 1);
			testGrid->setTile(Tile::X_TYPE, 0, 2);
			testGrid->setTile(Tile::O_TYPE, 2, 0);
			testGrid->setTile(Tile::O_TYPE, 2, 1);
			testGrid->setTile(Tile::X_TYPE, 1, 2);
			testGrid->setTile(Tile::X_TYPE, 2, 2);

			//Action
			bool exceptionThrown = false;

			try
			{
				normalComputer->getChoice();
			}
			catch (runtime_error ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}
	};
}