#pragma once
#include "stdafx.h"

class EasyComputer : public Computer
{
public:
	EasyComputer(const Grid & _grid, const Tile::TILE_TYPE &_playerTileType);
	~EasyComputer();
	const Point * getChoice() const;
private:

};

