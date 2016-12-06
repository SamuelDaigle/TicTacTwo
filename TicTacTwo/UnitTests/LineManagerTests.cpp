#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Controllers/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(LineManagerTests)
	{
	public:
		Grid * testGrid;
		LineManager * manager;

		TEST_METHOD_INITIALIZE(LineManagerTests_Initialize)
		{
			testGrid = new Grid();
			manager = new LineManager(*testGrid);
		}

		TEST_METHOD_CLEANUP(LineManagerTests_CleanUp)
		{
			delete manager;
			delete testGrid;
		}

		TEST_METHOD(when_two_tiles_of_same_type_are_next_to_each_other_the_manager_creates_a_new_line)
		{
			//Arrange
			const unsigned int NUMBER_OF_LINES = 1;
			const Point * TILE_1 = new Point(0, 0);
			const Point * TILE_2 = new Point(1, 1);
			const Point * TILE_3 = new Point(2, 2);

			testGrid->enableDial(0, 0);

			testGrid->setTile(Tile::X_TYPE, TILE_1);

			//Action
			testGrid->setTile(Tile::X_TYPE, TILE_2);
			testGrid->setTile(Tile::O_TYPE, TILE_3);
			manager->updateLines(*TILE_2);

			vector<Line*> allLines = testGrid->getLines();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, allLines.size());

			delete TILE_1, TILE_2, TILE_3;
		}

		TEST_METHOD(when_a_tile_is_added_between_two_tiles_of_same_type_the_manager_creates_one_line)
		{
			//Arrange
			const unsigned int NUMBER_OF_LINES = 1;
			const Point * TILE_1 = new Point(0, 0);
			const Point * TILE_2 = new Point(1, 1);
			const Point * TILE_3 = new Point(2, 2);

			testGrid->enableDial(0, 0);

			testGrid->setTile(Tile::X_TYPE, TILE_1);
			testGrid->setTile(Tile::X_TYPE, TILE_3);

			//Action
			testGrid->setTile(Tile::X_TYPE, TILE_2);
			manager->updateLines(*TILE_2);

			vector<Line*> lines = testGrid->getLines();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, lines.size());

			delete TILE_1, TILE_2, TILE_3;
		}

		TEST_METHOD(when_a_new_tile_creates_multiple_lines_the_manager_creates_the_right_number_of_lines)
		{
			//Arrange
			const unsigned int NUMBER_OF_LINES = 6;
			const Point * TILE_1 = new Point(0, 0);
			const Point * TILE_2 = new Point(1, 1);
			const Point * TILE_3 = new Point(0, 1);
			const Point * TILE_4 = new Point(1, 0);

			testGrid->enableDial(0, 0);

			testGrid->setTile(Tile::X_TYPE, TILE_1);
			testGrid->setTile(Tile::X_TYPE, TILE_2);
			manager->updateLines(*TILE_2);
			testGrid->setTile(Tile::X_TYPE, TILE_3);
			manager->updateLines(*TILE_3);

			//Action
			testGrid->setTile(Tile::X_TYPE, TILE_4);
			manager->updateLines(*TILE_4);

			vector<Line*> lines = testGrid->getLines();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, lines.size());

			delete TILE_1, TILE_2, TILE_3, TILE_4;
		}

		TEST_METHOD(when_a_tile_is_added_next_to_a_line_of_same_type_the_tile_is_added_to_the_line)
		{
			//Arrange
			const unsigned int NUMBER_OF_LINES = 1;
			const unsigned int SIZE_OF_LINE = 3;
			const Point * TILE_1 = new Point(0, 0);
			const Point * TILE_2 = new Point(1, 1);
			const Point * TILE_3 = new Point(2, 2);

			testGrid->enableDial(0, 0);

			testGrid->setTile(Tile::X_TYPE, TILE_1);
			testGrid->setTile(Tile::X_TYPE, TILE_2);
			manager->updateLines(*TILE_2);

			//Action
			testGrid->setTile(Tile::X_TYPE, TILE_3);
			manager->updateLines(*TILE_3);

			vector<Line*> lines = testGrid->getLines();
			unsigned int sizeOfTheLine = lines[0]->getSize();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, lines.size());
			Assert::AreEqual(SIZE_OF_LINE, sizeOfTheLine);

			delete TILE_1, TILE_2, TILE_3;
		}

		TEST_METHOD(when_an_added_tile_continues_a_line_and_create_one_the_manager_add_tile_to_the_line_and_creates_a_line)
		{
			const unsigned int NUMBER_OF_LINES = 3;
			const unsigned int SIZE_OF_MODIFIED_LINE = 3;
			const Point * TILE_1 = new Point(0, 0);
			const Point * TILE_2 = new Point(1, 0);
			const Point * TILE_3 = new Point(2, 1);
			const Point * TILE_4 = new Point(2, 0);

			testGrid->enableDial(0, 0);

			testGrid->setTile(Tile::O_TYPE, TILE_1);
			testGrid->setTile(Tile::O_TYPE, TILE_2);
			manager->updateLines(*TILE_2);
			testGrid->setTile(Tile::O_TYPE, TILE_3);
			manager->updateLines(*TILE_3);

			//Action
			testGrid->setTile(Tile::O_TYPE, TILE_4);
			manager->updateLines(*TILE_4);

			vector<Line*> lines = testGrid->getLines();
			unsigned int sizeOfTheLine = lines[0]->getSize();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, lines.size());
			Assert::AreEqual(SIZE_OF_MODIFIED_LINE, sizeOfTheLine);

			delete TILE_1, TILE_2, TILE_3, TILE_4;
		}

		TEST_METHOD(when_a_tile_is_added_between_a_tile_and_a_line_of_same_type_the_manager_modifies_the_line)
		{
			//Arrange
			const unsigned int NUMBER_OF_LINES = 1;
			const unsigned int SIZE_OF_MODIFIED_LINE = 4;
			const Point * TILE_1 = new Point(0, 0);
			const Point * TILE_2 = new Point(1, 0);
			const Point * TILE_3 = new Point(3, 0);
			const Point * TILE_4 = new Point(2, 0);

			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);

			testGrid->setTile(Tile::O_TYPE, TILE_1);
			testGrid->setTile(Tile::O_TYPE, TILE_2);
			manager->updateLines(*TILE_2);
			testGrid->setTile(Tile::O_TYPE, TILE_3);

			//Action
			testGrid->setTile(Tile::O_TYPE, TILE_4);
			manager->updateLines(*TILE_4);

			vector<Line*> lines = testGrid->getLines();
			unsigned int sizeOfTheLine = lines[0]->getSize();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, lines.size());
			Assert::AreEqual(SIZE_OF_MODIFIED_LINE, sizeOfTheLine);

			delete TILE_1, TILE_2, TILE_3, TILE_4;
		}

		TEST_METHOD(when_an_added_tile_is_between_two_lines_of_same_orientation_the_manager_combine_the_lines)
		{
			//Arrange
			const unsigned int NUMBER_OF_LINES = 1;
			const unsigned int SIZE_OF_COMBINED_LINE = 5;
			const Point * TILE_1 = new Point(0, 0);
			const Point * TILE_2 = new Point(1, 0);
			const Point * TILE_3 = new Point(2, 0);
			const Point * TILE_4 = new Point(3, 0);
			const Point * TILE_5 = new Point(4, 0);

			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);

			testGrid->setTile(Tile::O_TYPE, TILE_1);
			testGrid->setTile(Tile::O_TYPE, TILE_2);
			manager->updateLines(*TILE_2);
			testGrid->setTile(Tile::O_TYPE, TILE_4);
			testGrid->setTile(Tile::O_TYPE, TILE_5);
			manager->updateLines(*TILE_5);

			//Action
			testGrid->setTile(Tile::O_TYPE, TILE_3);
			manager->updateLines(*TILE_3);

			vector<Line*> lines = testGrid->getLines();
			unsigned int sizeOfTheLine = lines[0]->getSize();

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, lines.size());
			Assert::AreEqual(SIZE_OF_COMBINED_LINE, sizeOfTheLine);

			delete TILE_1, TILE_2, TILE_3, TILE_4, TILE_5;

		}

		TEST_METHOD(when_an_added_tile_is_between_many_pairs_of_two_lines_of_same_orientation_the_manager_combine_the_lines)
		{
			//Arrange
			const unsigned int NUMBER_OF_LINES = 6;
			const unsigned int NUMBER_OF_COMBINED_LINES = 2;
			const unsigned int SIZE_OF_COMBINED_LINE = 5;
			const Point * TILE_1 = new Point(2, 0);
			const Point * TILE_2 = new Point(2, 1); // - - O   - - -
			const Point * TILE_3 = new Point(2, 3); // - - O   - - -
			const Point * TILE_4 = new Point(2, 4); // O O 0   O O -
													//
			const Point * TILE_5 = new Point(2, 2); // - - O   - - -
													// - - O   - - -
			const Point * TILE_6 = new Point(0, 2); // - - -   - - -
			const Point * TILE_7 = new Point(1, 2); 
			const Point * TILE_8 = new Point(3, 2);
			const Point * TILE_9 = new Point(4, 2);


			testGrid->enableDial(0, 0);
			testGrid->enableDial(1, 0);
			testGrid->enableDial(0, 1);

			testGrid->setTile(Tile::O_TYPE, TILE_1);
			manager->updateLines(*TILE_1);
			testGrid->setTile(Tile::O_TYPE, TILE_2);
			manager->updateLines(*TILE_2);
			testGrid->setTile(Tile::O_TYPE, TILE_3);
			manager->updateLines(*TILE_3);
			testGrid->setTile(Tile::O_TYPE, TILE_4);
			manager->updateLines(*TILE_4);
			testGrid->setTile(Tile::O_TYPE, TILE_6);
			manager->updateLines(*TILE_6);
			testGrid->setTile(Tile::O_TYPE, TILE_7);
			manager->updateLines(*TILE_7);
			testGrid->setTile(Tile::O_TYPE, TILE_8);
			manager->updateLines(*TILE_8);
			testGrid->setTile(Tile::O_TYPE, TILE_9);
			manager->updateLines(*TILE_9);

			//Action
			testGrid->setTile(Tile::O_TYPE, TILE_5);
			manager->updateLines(*TILE_5);

			vector<Line*> lines = testGrid->getLines();
			unsigned int combinedLines = getNumberOfLinesOfSameSize(SIZE_OF_COMBINED_LINE);

			//Assert
			Assert::AreEqual(NUMBER_OF_LINES, lines.size());
			Assert::AreEqual(NUMBER_OF_COMBINED_LINES, combinedLines);

			delete TILE_1, TILE_2, TILE_3, TILE_4, TILE_5, TILE_6, TILE_7, TILE_8, TILE_9;

		}

		int getNumberOfLinesOfSameSize(const int _lineSize)
		{
			vector<Line *> allLines = testGrid->getLines();
			int numberOfLines = 0;

			for (Line * line : allLines)
			{
				if (line->getSize() == _lineSize)
				{
					numberOfLines++;
				}
			}
			return numberOfLines;
		}

	};
}