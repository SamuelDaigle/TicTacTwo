#pragma once
#include "stdafx.h"

#define X_DIAL_DIMENTION  3
#define Y_DIAL_DIMENTION  3

using namespace std;

class Dial
{
public:
	Dial();
	~Dial();
	void setTile(Tile::TILE_TYPE type, const unsigned int xPosition, const unsigned int yPosition);
	Tile & getTile(const unsigned int xPosition, const unsigned int yPosition) const;
	bool isFull() const;
	bool isEnabled() const;
	void setEnabled();
private:
	bool enabled;
	Tile * tiles[X_DIAL_DIMENTION][Y_DIAL_DIMENTION];
	void createEmptyTiles();
	void validateCall() const;
	bool isPositionValid(int xPosition, int yPosition) const;
};

