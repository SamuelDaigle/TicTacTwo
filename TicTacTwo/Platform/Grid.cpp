#include "stdafx.h"


Grid::Grid()
{
	for (unsigned int indexX = 0; indexX < NB_DIAL_X; ++indexX)
	{
		for (unsigned int indexY = 0; indexY < NB_DIAL_Y; ++indexY)
		{
			dials[indexX][indexY] = new Dial();
		}
	}
}


Grid::~Grid()
{
	lines.clear();
	for (unsigned int indexX = 0; indexX < NB_DIAL_X; ++indexX)
	{
		for (unsigned int indexY = 0; indexY < NB_DIAL_Y; ++indexY)
		{
			delete dials[indexX][indexY];
		}
	}
}

void Grid::enableDial(const unsigned int xPosition, const unsigned int yPosition)
{
	dials[xPosition][yPosition]->setEnabled();
	setTilesPosition(xPosition, yPosition);
}

Tile * Grid::getTile(const unsigned int xPosition, const unsigned int yPosition) const
{
	Tile * returnedTile;

	//Get the corresponding dial coordinates.
	int dialXCoordinate = (xPosition > 2) ? 1 : 0;
	int dialYCoordinate = (yPosition > 2) ? 1 : 0;

	//Get the tile position's in dial
	int tileXPosition = (dialXCoordinate == 1) ? xPosition - 3 : xPosition;
	int tileYPosition = (dialYCoordinate == 1) ? yPosition - 3 : yPosition;

	try
	{
		returnedTile = &dials[dialXCoordinate][dialYCoordinate]->getTile(tileXPosition, tileYPosition);
	}
	catch (...)
	{
		returnedTile = nullptr;
	}

	return returnedTile;
}

void Grid::setTile(Tile::TILE_TYPE _type, const unsigned int xPosition, const unsigned int yPosition) const
{
	//Get the corresponding dial coordinates.
	int dialXCoordinate = (xPosition > 2) ? 1 : 0;
	int dialYCoordinate = (yPosition > 2) ? 1 : 0;

	//Get the tile position's in dial
	int tileXPosition = (dialXCoordinate == 1) ? xPosition - 3 : xPosition;
	int tileYPosition = (dialYCoordinate == 1) ? yPosition - 3 : yPosition;

	dials[dialXCoordinate][dialYCoordinate]->setTile(_type, tileXPosition, tileYPosition);
}

void Grid::addLine(Line * _line)
{
	lines.push_back(_line);
}

vector<Line*> Grid::getLines() const
{
	return lines;
}

bool Grid::isFull()
{
	for (unsigned int indexX = 0; indexX < NB_DIAL_X; ++indexX)
	{
		for (unsigned int indexY = 0; indexY < NB_DIAL_Y; ++indexY)
		{
			Dial * dial = dials[indexX][indexY];
			if (!dial->isEnabled() || !dial->isFull())
			{
				return false;
			}
		}
	}
	return true;
}

void Grid::setTilesPosition(const unsigned int xDialPosition, const unsigned int yDialPosition)
{
	for (unsigned int indexX = 0; indexX < 3; ++indexX)
	{
		for (unsigned int indexY = 0; indexY < 3; ++indexY)
		{
			int tileXPosition = indexX + (3 * xDialPosition);
			int tileYPosition = indexY + (3 * yDialPosition);
			Point * tilePosition = new Point(tileXPosition, tileYPosition);
			dials[xDialPosition][yDialPosition]->getTile(indexX, indexY).setPosition(*tilePosition);
		}
	}
}

void Grid::enableDial(const Point * _position)
{
	validatePoint(_position);
	enableDial(_position->x, _position->y);
}

Tile * Grid::getTile(const Point * _position) const
{
	Tile * tileToReturn = nullptr;
	if (_position != nullptr)
	{
		tileToReturn = getTile(_position->x, _position->y);
	}
	return tileToReturn;
}

void Grid::setTile(Tile::TILE_TYPE _type, const Point * _position) const
{
	validatePoint(_position);
	setTile(_type, _position->x, _position->y);
}

void Grid::validatePoint(const Point * _position) const
{
	if (_position == nullptr)
	{
		throw std::invalid_argument("The point must not be null");
	}
}

bool Grid::isDialFull(const unsigned int xDialPosition, const unsigned int yDialPosition) const
{
	return (dials[xDialPosition][yDialPosition]->isFull());
}

void Grid::eraseLine(const unsigned int index)
{
	if (index >= lines.size())
		throw invalid_argument("Invalid index");

	delete lines[index];
	lines.erase(lines.begin() + index);
}
