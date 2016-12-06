#pragma once
#include "stdafx.h"

#define NB_DIAL_X 2
#define NB_DIAL_Y 2

#include <vector>

using namespace std;

class Grid
{
public:
	Grid();
	~Grid();
	void enableDial(const unsigned int xPosition, const unsigned int yPosition);
	Tile * getTile(const unsigned int xPosition, const unsigned int yPosition) const;
	void setTile(Tile::TILE_TYPE _type, const unsigned int xPosition, const unsigned int yPosition) const;
	void enableDial(const Point * _position);
	Tile * getTile(const Point * _position) const;
	void setTile(Tile::TILE_TYPE _type, const Point * _position) const;
	void addLine(Line * _line);
	vector<Line*> getLines() const;
	bool isFull();
	bool isDialFull(const unsigned int xDialPosition, const unsigned int yDialPosition) const;
	void eraseLine(const unsigned int index);
private:
	vector<Line*> lines;
	Dial * dials[NB_DIAL_X][NB_DIAL_Y];
	void setTilesPosition(const unsigned int xDialPosition, const unsigned int yDialPosition);
	void validatePoint(const Point * _position) const;
};

