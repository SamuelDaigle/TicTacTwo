#pragma once
#include "stdafx.h"

using namespace std;

class Computer
{
public:
	Computer(const Grid & _grid, const Tile::TILE_TYPE &_computerTileType);
	~Computer();
	virtual const Point * getChoice() const = 0;
	Tile::TILE_TYPE getComputerTileType() const;
protected:
	const Grid * grid;
	Tile::TILE_TYPE computerTileType;
	vector<Point> getAllEmptyTiles() const;
	const Point * getRandomTile() const;
};

