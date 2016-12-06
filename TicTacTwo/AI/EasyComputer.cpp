#include "stdafx.h"

EasyComputer::EasyComputer(const Grid & _grid, const Tile::TILE_TYPE &_playerTileType) :
Computer(_grid, _playerTileType)
{
}

EasyComputer::~EasyComputer()
{
}

const Point * EasyComputer::getChoice() const
{
	return getRandomTile();
}

