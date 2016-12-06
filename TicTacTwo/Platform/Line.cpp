#include "stdafx.h"


Line::Line()
{}


Line::~Line()
{
}

void Line::addFront(Tile * _tile)
{
	tiles.push_front(_tile);
	if (tiles.size() == 2)
	{
		determineOrientation();
	}
}

void Line::addBack(Tile * _tile)
{
	tiles.push_back(_tile);
	if (tiles.size() == 2)
	{
		determineOrientation();
	}
}

Line::LINE_ORIENTATION Line::getOrientation() const
{
	return orientation;
}

Tile & Line::getFrontTile() const
{
	return *tiles.front();
}

Tile & Line::getBackTile() const
{
	return *tiles.back();
}

int Line::getSize() const
{
	return tiles.size();
}

void Line::determineOrientation()
{
	Tile * tile1 = tiles.back();
	Tile * tile2 = tiles.front();
	if (tile1->getPosition().x == tile2->getPosition().x)
	{
		orientation = VERTICAL;
	}
	else if (tile1->getPosition().y == tile2->getPosition().y)
	{
		orientation = HORIZONTAL;
	}
	else if (tile1->getPosition().x < tile2->getPosition().x && tile1->getPosition().y > tile2->getPosition().y)
	{
		orientation = UP_DIAGONAL;
	}
	else
	{
		orientation = DOWN_DIAGONAL;
	}
}

Point & Line::getLineVariation() const
{
	Point * variation = new Point(0, 0);

	switch (getOrientation())
	{
	case Line::HORIZONTAL:
		variation = new Point(1, 0);
		break;
	case Line::VERTICAL:
		variation = new Point(0, 1);
		break;
	case Line::DOWN_DIAGONAL:
		variation = new Point(1, 1);
		break;
	case Line::UP_DIAGONAL:
		variation = new Point(1, -1);
	}
	return *variation;
}

const Point * Line::getPointBeforeLine() const
{
	Point lineVariation = getLineVariation();
	int xPosition = getBackTile().getPosition().x - lineVariation.x;
	int yPosition = getBackTile().getPosition().y - lineVariation.y;

	Point * point = new Point(xPosition, yPosition);

	return point;
}

const Point * Line::getPointAfterLine() const
{
	Point lineVariation = getLineVariation();
	int xPosition = getFrontTile().getPosition().x + lineVariation.x;
	int yPosition = getFrontTile().getPosition().y + lineVariation.y;

	Point * point = new Point(xPosition, yPosition);

	return point;
}