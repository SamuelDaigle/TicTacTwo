#pragma once
#include "stdafx.h"

#include <iostream>
using namespace std;

class Button
{
public:
	Button();
	~Button();

	bool isClickInsideBorder(int _mouseXPosition, int _mouseYPosition);

	//Set methods
	void setXPosition(int _xPosition);
	void setYPosition(int _yPosition);
	void setWidth(int _width);
	void setHeight(int _height);
	void setImagePath(char * _imagePath);
	void setText(const string & _text);

	//Get methods
	int getXPosition() const;
	int getYPosition() const;
	int getWidth() const;
	int getHeight() const;
	char * getImagePath() const;
	const string& getText() const;

private:
	int buttonXPosition;
	int buttonYPosition;
	int width;
	int height;
	char * imagePath;
	string text;
};

