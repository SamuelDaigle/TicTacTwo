#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTests
{
	TEST_CLASS(GameDatabaseHelperTests)
	{
	public:
		GameDatabaseHelper* databaseHelper;
		const string DATABASE_PATH = "game.bd";

		TEST_METHOD_INITIALIZE(GameDatabaseHelperTests_Initialize)
		{
			databaseHelper = new GameDatabaseHelper(DATABASE_PATH);
			databaseHelper->dropDatabase(); // in case other tests failed before.
			databaseHelper->createDatabase();
		}

		TEST_METHOD_CLEANUP(GameDatabaseHelperTests_CleanUp)
		{
			databaseHelper->dropDatabase();
			delete databaseHelper;
		}

		TEST_METHOD(creating_the_database_should_not_throw_exceptions)
		{
			//Arrange
			bool thrownException = false;
			databaseHelper->dropDatabase(); // to test when we create it.

			//Action
			try
			{
				databaseHelper->createDatabase();
			}
			catch (...)
			{
				thrownException = true;
			}

			//Assert
			Assert::IsFalse(thrownException);
		}

		TEST_METHOD(creating_the_database_that_is_already_created_should_throw_runtime_error_exception)
		{
			//Arrange
			bool thrownException = false;

			//Action
			try
			{
				databaseHelper->createDatabase();
			}
			catch (runtime_error e)
			{
				thrownException = true;
			}

			//Assert
			Assert::IsTrue(thrownException);
		}

		TEST_METHOD(seeding_the_database_should_not_throw_an_error)
		{
			//Arrange
			bool thrownException = false;

			//Action
			try
			{
				databaseHelper->seedGameDatabase(1);
			}
			catch (...)
			{
				thrownException = true;
			}

			//Assert
			Assert::IsFalse(thrownException);
		}

		TEST_METHOD(creating_a_second_game_should_not_throw_an_error)
		{
			//Arrange
			bool thrownException = false;
			databaseHelper->seedGameDatabase(1);

			//Action
			try
			{
				databaseHelper->seedGameDatabase(2);
			}
			catch (...)
			{
				thrownException = true;
			}

			//Assert
			Assert::IsFalse(thrownException);
		}

		TEST_METHOD(seeding_the_same_game_twice_should_throw_a_runtime_error)
		{
			//Arrange
			bool thrownException = false;
			databaseHelper->seedGameDatabase(1);

			//Action
			try
			{
				databaseHelper->seedGameDatabase(1);
			}
			catch (runtime_error e)
			{
				thrownException = true;
			}

			//Assert
			Assert::IsTrue(thrownException);
		}

		TEST_METHOD(getting_the_number_of_game_with_2_games_in_database_should_return_2)
		{
			//Arrange
			const int EXPECTED_NB_GAME = 2;
			bool thrownException = false;
			databaseHelper->seedGameDatabase(1);
			databaseHelper->seedGameDatabase(2);

			//Action
			int actualNbGame = databaseHelper->getNbGame();

			//Assert
			Assert::AreEqual(EXPECTED_NB_GAME, actualNbGame);
		}
	};
}