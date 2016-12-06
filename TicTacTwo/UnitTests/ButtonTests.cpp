#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Controllers/stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ButtonTests)
	{
	public:
		Button * button;

		TEST_METHOD_INITIALIZE(ButtonTests_Initialize)
		{
			button = new Button();
		}

		TEST_METHOD_CLEANUP(ButtonTests_CleanUp)
		{
			delete button;
		}

		TEST_METHOD(set_and_get_x_position_of_button_should_work)
		{
			//Arrange
			const unsigned int X_POSITION = 345;

			//Action
			button->setXPosition(X_POSITION);

			unsigned int returnedValue = button->getXPosition();

			//Assert
			Assert::AreEqual(X_POSITION, returnedValue);
		}

		TEST_METHOD(setXPosition_with_an_invalid_value_shoudl_throw_an_exception)
		{
			//Arrange
			const unsigned int X_POSITION = -345;

			//Action
			bool exceptionThrown = false;
			try
			{
				button->setXPosition(X_POSITION);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}
			
			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(set_and_get_y_position_of_button_should_work)
		{
			//Arrange
			const unsigned int Y_POSITION = 345;

			//Action
			button->setYPosition(Y_POSITION);

			unsigned int returnedValue = button->getYPosition();

			//Assert
			Assert::AreEqual(Y_POSITION, returnedValue);
		}

		TEST_METHOD(setYPosition_with_an_invalid_value_shoudl_throw_an_exception)
		{
			//Arrange
			const int Y_POSITION = -345;

			//Action
			bool exceptionThrown = false;
			try
			{
				button->setYPosition(Y_POSITION);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(set_and_get_width_of_button_should_work)
		{
			//Arrange
			const unsigned int WIDTH = 40;

			//Action
			button->setWidth(WIDTH);

			unsigned int returnedValue = button->getWidth();

			//Assert
			Assert::AreEqual(WIDTH, returnedValue);
		}

		TEST_METHOD(setWidth_with_an_invalid_value_shoudl_throw_an_exception)
		{
			//Arrange
			const int WIDTH = -40;

			//Action
			bool exceptionThrown = false;
			try
			{
				button->setWidth(WIDTH);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(set_and_get_height_of_button_should_work)
		{
			//Arrange
			const unsigned int HEIGHT = 40;

			//Action
			button->setHeight(HEIGHT);
				
			unsigned int returnedValue = button->getHeight();

			//Assert
			Assert::AreEqual(HEIGHT, returnedValue);
		}

		TEST_METHOD(setHeight_height_an_invalid_value_shoudl_throw_an_exception)
		{
			//Arrange
			const int HEIGHT = -40;

			//Action
			bool exceptionThrown = false;
			try
			{
				button->setHeight(HEIGHT);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(set_and_get_path_of_image_of_button_should_work)
		{
			//Arrange
			char * IMAGE_PATH = "Hello world";

			//Action
			button->setImagePath(IMAGE_PATH);

			char * returnedValue = button->getImagePath();

			//Assert
			Assert::AreEqual(IMAGE_PATH, returnedValue);
		}

		TEST_METHOD(setImagePath_width_an_invalid_value_shoudl_throw_an_exception)
		{
			//Arrange
			char * INVALID_PATH = nullptr;

			//Action
			bool exceptionThrown = false;
			try
			{
				button->setImagePath(INVALID_PATH);
			}
			catch (invalid_argument ex)
			{
				exceptionThrown = true;
			}

			//Assert
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(set_and_get_text_of_button_should_work)
		{
			//Arrange
			string SOME_TEXT = "Hello world";

			//Action
			button->setText(SOME_TEXT);

			string returnedValue = button->getText();

			//Assert
			Assert::AreEqual(SOME_TEXT, returnedValue);
		}

		TEST_METHOD(isClickInsideBorder_should_return_true_if_the_clicked_position_is_in_the_button)
		{
			//Arrange
			button->setXPosition(40);
			button->setYPosition(40);
			button->setWidth(40);
			button->setHeight(40);
			Point clickedPosition(50, 50);

			//Action
			bool isInButton = button->isClickInsideBorder(clickedPosition.x, clickedPosition.y);

			//Assert
			Assert::IsTrue(isInButton);
		}

		TEST_METHOD(isClickInsideBorder_should_return_true_if_the_clicked_position_isnt_in_the_button)
		{
			//Arrange
			button->setXPosition(60);
			button->setYPosition(60);
			button->setWidth(60);
			button->setHeight(60);
			Point clickedPosition(50, 50);

			//Action
			bool isInButton = button->isClickInsideBorder(clickedPosition.x, clickedPosition.y);

			//Assert
			Assert::IsFalse(isInButton);
		}



	};
}