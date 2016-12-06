#include "stdafx.h"

Dial::Dial()
{
	enabled = false;
	createEmptyTiles();
}


Dial::~Dial()
{
	for (unsigned int indexX = 0; indexX < X_DIAL_DIMENTION; ++indexX)
	{
		for (unsigned int indexY = 0; indexY < Y_DIAL_DIMENTION; ++indexY)
		{
			delete tiles[indexX][indexY];
		}
	}
}

void Dial::setTile(Tile::TILE_TYPE _type, const unsigned int xPosition, const unsigned int yPosition)
{
	validateCall();
	if (!isPositionValid(xPosition, yPosition))
	{
		throw invalid_argument("X or Y coordinates are not valid");
	}

	tiles[xPosition][yPosition]->changeType(_type);
}

Tile & Dial::getTile(const unsigned int xPosition, const unsigned int yPosition) const
{
	validateCall();
	if (!isPositionValid(xPosition, yPosition))
	{
		throw invalid_argument("X or Y coordinates are not valid");
	}

	return *tiles[xPosition][yPosition];
}

bool Dial::isFull() const
{
	validateCall();
	for (unsigned int indexX = 0; indexX < X_DIAL_DIMENTION; ++indexX)
	{
		for (unsigned int indexY = 0; indexY < Y_DIAL_DIMENTION; ++indexY)
		{
			if (tiles[indexX][indexY]->getTileType() == Tile::EMPTY_TYPE)
			{
				return false;
			}
		}
	}
	return true;
}

bool Dial::isEnabled() const
{
	return enabled;
}

void Dial::setEnabled()
{
	enabled = true;
}

void Dial::createEmptyTiles()
{
	for (unsigned int indexX = 0; indexX < X_DIAL_DIMENTION; ++indexX)
	{
		for (unsigned int indexY = 0; indexY < Y_DIAL_DIMENTION; ++indexY)
		{
			tiles[indexX][indexY] = new Tile();
		}
	}
}

void Dial::validateCall() const
{
	if (!enabled)
	{
		throw runtime_error("The Dial is not enabled");
	}
}

bool Dial::isPositionValid(int xPosition, int yPosition) const
{
	bool xIsValid = (xPosition >= 0 && xPosition < X_DIAL_DIMENTION);
	bool yIsValid = (yPosition >= 0 && yPosition < Y_DIAL_DIMENTION);

	return (xIsValid && yIsValid);
}