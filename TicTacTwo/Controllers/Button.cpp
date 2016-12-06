#include "stdafx.h"


Button::Button()
{
	buttonXPosition = 0;
	buttonYPosition = 0;
	width = 1;
	height = 1;
	imagePath = nullptr;
	text = "";
}


Button::~Button()
{
}

bool Button::isClickInsideBorder(int _mouseXPosition, int _mouseYPosition)
{
	if (_mouseXPosition > buttonXPosition && _mouseXPosition < buttonXPosition + width)
	{
		if (_mouseYPosition > buttonYPosition && _mouseYPosition < buttonYPosition + height)
		{
			return true;
		}
	}
	return false;
}

//Set Methods

void Button::setXPosition(int _xPosition)
{
	if(_xPosition < 0) throw invalid_argument("X position must be positive");
	buttonXPosition = _xPosition;
}

void Button::setYPosition(int _yPosition)
{
	if (_yPosition < 0) throw invalid_argument("Y position must be positive");
	buttonYPosition = _yPosition;
}

void Button::setWidth(int _width)
{
	if (_width < 0) throw invalid_argument("Width must be positive");
	width = _width;
}

void Button::setHeight(int _height)
{
	if (_height < 0) throw invalid_argument("Height must be positive");
	height = _height;
}

void Button::setImagePath(char * _imagePath)
{
	if (_imagePath == nullptr) throw invalid_argument("Image must be valid");
	imagePath = _imagePath;
}

void Button::setText(const string & _text)
{
	text = _text;
}

//Get Methods
int Button::getXPosition() const
{
	return buttonXPosition;
}

int Button::getYPosition() const
{
	return buttonYPosition;
}

int Button::getWidth() const
{
	return width;
}

int Button::getHeight() const
{
	return height;
}

char * Button::getImagePath() const
{
	return imagePath;
}

const string & Button::getText() const
{
	return text;
}