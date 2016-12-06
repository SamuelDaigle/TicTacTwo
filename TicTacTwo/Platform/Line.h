#pragma once
#include "stdafx.h"

#include <list>

class Line
{
public:
	enum LINE_ORIENTATION
	{
		HORIZONTAL = 'H',
		VERTICAL = 'V',
		UP_DIAGONAL = 'U',
		DOWN_DIAGONAL = 'D'
	};
	Line();
	~Line();
	void addFront(Tile * _tile);
	void addBack(Tile * _tile);
	LINE_ORIENTATION getOrientation() const;
	Tile & getFrontTile() const;
	Tile & getBackTile() const;
	int getSize() const;


	const Point * getPointAfterLine() const;
	const Point * getPointBeforeLine() const;
	Point & getLineVariation() const;
private:
	void determineOrientation();
	LINE_ORIENTATION orientation;
	list<Tile*> tiles;
};

